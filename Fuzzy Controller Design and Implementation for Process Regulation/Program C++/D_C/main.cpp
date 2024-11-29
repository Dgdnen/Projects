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

void valori_eroare(std::vector <double> &me)
{
	me.push_back(-1);
	me.push_back(-0.8);
	me.push_back(-0.6);
	me.push_back(-0.4);
	me.push_back(-0.2);
	me.push_back(0);
	me.push_back(0.2);
	me.push_back(0.4);
	me.push_back(0.6);
	me.push_back(0.8);
	me.push_back(1);
}

void valori_derErr(std::vector <double> &mde)
{
	mde.push_back(-1);
	mde.push_back(-0.5);
	mde.push_back(0);
	mde.push_back(0.5);
	mde.push_back(1);
}

void valoriActive_comanda(double e, double de, std::vector<double> me, std::vector<double> mde, double reguli[5][11], std::vector<double> &mu)
{
	for (size_t i = 0; i < mde.size(); ++i)
	{
		for (size_t j = 0; j < me.size(); ++j)
		{
			if ((e > me[j] && e < me[j + 1]) && (de > mde[i] && de < mde[i + 1]))
			{
				mu.push_back(reguli[i][j]);
				mu.push_back(reguli[i][j + 1]);
				mu.push_back(reguli[i + 1][j]);
				mu.push_back(reguli[i + 1][j + 1]);
			}

			if (e == me[j] && (de > mde[i] && de < mde[i + 1]))
			{
				mu.push_back(reguli[i][j]);
				mu.push_back(reguli[i + 1][j]);
			}

			if ((e > me[j] && e < me[j + 1]) && de == mde[i])
			{
				mu.push_back(reguli[i][j]);
				mu.push_back(reguli[i][j + 1]);
			}

			if (e == me[j] && de == mde[i])
			{
				mu.push_back(reguli[i][j]);
			}
		}
	}
}

void main()
{
	//baza de reguli
	double reguli[5][11] = { -1, -0.9, -0.5, -0.5, 0, 0, 0, -0.01, -0.01, 0.5, 0.5,
													-0.88, -0.88, -0.5, -0.5, 0, 0, 0, 0.25, 0.25, 0.63, 0.63,
													-1, -0.9, -0.5, -0.5, 0, 0, 0, 0.5, 0.5, 0.9, 1,
													-0.63, -0.63, -0.25, -0.25, 0, 0, 0, 0.5, 0.5, 0.88, 0.88,
													-0.5, -0.5, -0.01, -0.01, 0, 0, 0, 0.5, 0.5, 0.9, 1 }; 

	std::vector<double> eroare = extragereValoriEroare_fisier();
	std::vector<double> derivataErorii = calculareDerErr(eroare);

	auto start = std::chrono::high_resolution_clock::now();

	for (size_t e = 0; e < eroare.size(); ++e)
	{
		std::vector<double> me;
		me.reserve(11);
		valori_eroare(me);

		std::vector<double> mde;
		mde.reserve(5);
		valori_derErr(mde);

		std::vector<double> mu;
		mu.reserve(4);
		valoriActive_comanda(eroare[e], derivataErorii[e], me, mde, reguli, mu);

		std::vector<double> ponderi_w;
		ponderi_w.reserve(4);
		for (size_t i = 0; i < mde.size(); ++i)
		{
			for (size_t j = 0; j < me.size(); ++j)
			{
				if ((eroare[e] > me[j] && eroare[e] < me[j + 1]) && (derivataErorii[e] > mde[i] && derivataErorii[e] < mde[i + 1]))
				{
					double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i + 1])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w1 = (abs(eroare[e] - me[j])*abs(derivataErorii[e] - mde[i + 1])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w2 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w3 = (abs(eroare[e] - me[j])*abs(derivataErorii[e] - mde[i])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));

					ponderi_w.push_back(w0);
					ponderi_w.push_back(w1);
					ponderi_w.push_back(w2);
					ponderi_w.push_back(w3);

					break;
				}

				if (eroare[e] == me[j] && (derivataErorii[e] > mde[i] && derivataErorii[e] < mde[i + 1]))
				{
					if (eroare[e] == 1)
					{
						double w0 = (abs(eroare[e] - me[j - 1])*abs(derivataErorii[e] - mde[i + 1])) / (0.2 * abs(mde[i] - mde[i + 1]));
						double w1 = (abs(eroare[e] - me[j - 1])*abs(derivataErorii[e] - mde[i])) / (0.2 * abs(mde[i] - mde[i + 1]));

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						break;
					}
					else
					{
						double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i + 1])) / (0.2 * abs(mde[i] - mde[i + 1]));
						double w1 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i])) / (0.2 * abs(mde[i] - mde[i + 1]));

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						break;
					}					
				}

				if ((eroare[e] > me[j] && eroare[e] < me[j + 1]) && derivataErorii[e] == mde[i])
				{			
					if (derivataErorii[e] == 1)
					{
						double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i - 1])) / (abs(me[j] - me[j + 1]) * 0.5);
						double w1 = (abs(eroare[e] - me[j])*abs(derivataErorii[e] - mde[i - 1])) / (abs(me[j] - me[j + 1]) * 0.5);

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						break;
					}

					else
					{
						double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i + 1])) / (abs(me[j] - me[j + 1]) * 0.5);
						double w1 = (abs(eroare[e] - me[j])*abs(derivataErorii[e] - mde[i + 1])) / (abs(me[j] - me[j + 1]) * 0.5);

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						break;
					}				
				}

				if (eroare[e] == me[j] && derivataErorii[e] == mde[i])
				{
					if (eroare[e] == 1 && derivataErorii[e] == 1)
					{
						double w0 = (abs(eroare[e] - me[j - 1])*abs(derivataErorii[e] - mde[i - 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						break;

					}
					if (eroare[e] == 1 && derivataErorii[e] == mde[i])
					{
						double w0 = (abs(eroare[e] - me[j - 1])*abs(derivataErorii[e] - mde[i + 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						break;

					}
					if (derivataErorii[e] == 1 && eroare[e] == me[j])
					{
						double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i - 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						break;
					}
					else
					{
						double w0 = (abs(eroare[e] - me[j + 1])*abs(derivataErorii[e] - mde[i + 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						break;
					}
				}
			}
		}

		double u = 0;
		for (size_t i = 0; i < ponderi_w.size(); ++i)
		{
			u += ponderi_w[i] * mu[i];
		}

		std::vector<double> allDeffuz;
		allDeffuz.reserve(eroare.size());
		allDeffuz.push_back(u);
	}

	auto duration = std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start);
	std::cout << "Timpul pentru programul 2 este de:" << duration.count() << "s. \n";

	system("pause");
}
