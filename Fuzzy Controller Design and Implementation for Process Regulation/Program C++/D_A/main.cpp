#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

#include <chrono>

std::vector<double> extragereValoriEroare_fisier()
{
	std::ifstream fin("date3.txt");

	std::vector<double> date; date.reserve(10003);
	double e = 0;

	while (!fin.eof())
	{
		fin >> e;

		if (e > 1.0)
			e = 1.00;

		date.push_back(e);
	}
	fin.close();

	return date;
}

std::vector<double> calculareDerErr(std::vector<double> eroare)
{
	std::vector<double> derErr;
	derErr.reserve(eroare.size());
	derErr.push_back(0.0); //pentru e[0] - e[-1]

	double t_e = 0.1;
	for (int i = 1; i < eroare.size(); ++i)
	{
		double esantion = (eroare[i] - eroare[i - 1]) / t_e;

		derErr.push_back(esantion);
	}

	return derErr;
}

double triunghi(double e, double a, double b, double c)
{
	if (e < a)
		return 0;

	if (e >= b && e <= c)
		return (c - e) / (c - b);

	if (e >= a && e <= b)
		return (e - a) / (b - a);

	if (e > c)
		return 0;
}

double triunghi_stanga(double e, double a, double b)
{
	if (e < a)
		return 0;
	if (e > b)
		return 0;

	if (e >= a && e <= b)
		return (b - e) / (b - a);
}

double triunghi_dreapta(double e, double a, double b)
{
	if (e < a)
		return 0;
	if (e > b)
		return 0;

	if (e >= a && e <= b)
		return (e - a) / (b - a);
}

void fuzzificare_eroare(double e, std::vector<double> &me)
{
	me.push_back(triunghi_stanga(e, -1.0, -0.5));	//NB
	me.push_back(triunghi(e, -1.0, -0.5, 0.0));	//NS
	me.push_back(triunghi(e, -0.5, 0.0, 0.5));	//ZE
	me.push_back(triunghi(e, 0.0, 0.5, 1.0));		//PS												
	me.push_back(triunghi_dreapta(e, 0.5, 1.0));	//PB
}
void fuzzificare_derivataEroare(double de, std::vector<double> &mde)
{
	mde.push_back(triunghi_stanga(de, -1.0, 0.0));	//N
	mde.push_back(triunghi(de, -1.0, 0.0, 1.0));	//Z
	mde.push_back(triunghi_dreapta(de, 0.0, 1.0));	//B
}

void inferenta_Mamdani(std::vector<double> me, std::vector<double> mde, std::vector <std::vector <double> > &mu)
{
	for (size_t i = 0; i < 3; ++i)
		for (size_t j = 0; j < 5; ++j)
			mu[i][j] = std::min(me[j], mde[i]);
}

double max_fctApartenenta(std::vector <std::vector <double> > mu, char reguli[3][5], char cuvant)
{
	double max = 0.0;

	for (int i = 0; i < 3; ++i)
		for (int j = 0; j < 5; ++j)
			if (reguli[i][j] == cuvant)
				max = std::max(max, mu[i][j]);

	return max;
}

double primulMaxim(double a, double b, double c, double max)
{
	double firstMax = (b - a)*(max)+a;

	if (a == b)
		firstMax = a;

	return firstMax;
}

double ultimulMaxim(double a, double b, double c, double max)
{
	double lastMax = c - (c - b)*(max);

	if (b == c)
		lastMax = c;

	return lastMax;
}

void main()
{
	//baza de reguli, unde:
	//n -> NB; m -> NS; z -> ZE; p -> PS; b -> PB;
	char reguli[3][5] = { 'n', 'm', 'z', 'z', 'p',
												'n', 'm', 'z', 'p', 'b',
												'm', 'z', 'z', 'p', 'b' };

	std::vector<double> eroare = extragereValoriEroare_fisier();
	std::vector<double> derivataErorii = calculareDerErr(eroare);

	auto start = std::chrono::high_resolution_clock::now();

	for (size_t e = 0; e < eroare.size(); ++e)
	{
			std::vector<double> me;
			me.reserve(5);
			std::vector<double> mde;
			mde.reserve(3);

			fuzzificare_eroare(eroare[e], me);
			fuzzificare_derivataEroare(derivataErorii[e], mde);

			std::vector <std::vector <double> > mu;
			mu.resize(3);
			for (size_t i = 0; i < mu.size(); ++i)
				mu[i].resize(5);

			inferenta_Mamdani(me, mde, mu);

			std::vector <double> max_apartenenta;
			max_apartenenta.reserve(5);
			max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'n'));
			max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'm'));
			max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'z'));
			max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'p'));
			max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'b'));
	
			double max = 0.0;
			for (size_t i = 0; i < 5; ++i)
			{
				max = std::max(max, max_apartenenta[i]);
			}

			double som = 0.0;
			if (max == max_apartenenta[0])
			{
				som = primulMaxim(-1.0, -1.0, -0.5, max);
				max_apartenenta[0] = 10; //label
			}
			else if (max == max_apartenenta[1])
			{
				som = primulMaxim(-1.0, -0.5, 0.0, max);
				max_apartenenta[1] = 10;
			}
			else if (max == max_apartenenta[2])
			{
				som = primulMaxim(-0.5, 0.0, 0.5, max);
				max_apartenenta[2] = 10;
			}
			else if (max == max_apartenenta[3])
			{
				som = primulMaxim(0.0, 0.5, 1.0, max);
				max_apartenenta[3] = 10;
			}
			else if (max == max_apartenenta[4])
			{
				som = primulMaxim(0.5, 1.0, 1.0, max);
				max_apartenenta[4] = 10;
			}

			double lom = 0.0;
			if (max == max_apartenenta[0])
				lom = ultimulMaxim(-1.0, -1.0, -0.5, max);
			else if (max == max_apartenenta[1])
				lom = ultimulMaxim(-1.0, -0.5, 0.0, max);
			else if (max == max_apartenenta[2])
				lom = ultimulMaxim(-0.5, 0.0, 0.5, max);
			else if (max == max_apartenenta[3])
				lom = ultimulMaxim(0.0, 0.5, 1.0, max);
			else if (max == max_apartenenta[4])
				lom = ultimulMaxim(0.5, 1.0, 1.0, max);
			else
			{
				for (size_t i = 0; i < max_apartenenta.size(); ++i)
				{
					if (max_apartenenta[i] == 10)
					{
						if (i == 0) lom = ultimulMaxim(-1.0, -1.0, -0.5, max);
						if (i == 1) lom = ultimulMaxim(-1.0, -0.5, 0.0, max);
						if (i == 2) lom = ultimulMaxim(-0.5, 0.0, 0.5, max);
						if (i == 3) lom = ultimulMaxim(0.0, 0.5, 1.0, max);
						if (i == 4) lom = ultimulMaxim(0.5, 1.0, 1.0, max);
					}
				}
			}

			double mom = (som + lom) / 2;

			std::vector<double> allDeffuz;
			allDeffuz.reserve(eroare.size());
			allDeffuz.push_back(mom);
		}
	
	auto duration = std::chrono::duration<double> (std::chrono::high_resolution_clock::now() - start);
	std::cout << "Timpul pentru programul 1 este de:" << duration.count() << "s. \n";

	system("pause");
}
