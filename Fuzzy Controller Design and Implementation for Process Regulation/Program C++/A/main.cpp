#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <conio.h>

#include <vector>

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
	//vectorul me[] -> cuprinde rezultatele in urma apelarii functiilor pentru intrarea "eroare" (functiile de apartenenta)
	me.push_back(triunghi_stanga(e, -1.0, -0.5));	//NB
	me.push_back( triunghi(e, -1.0, -0.5, 0.0) );	//NS
	me.push_back( triunghi(e, -0.5, 0.0, 0.5) );	//ZE
	me.push_back( triunghi(e, 0.0, 0.5, 1.0) );		//PS												
	me.push_back(triunghi_dreapta(e, 0.5, 1.0));	//PB
}
void fuzzificare_derivataEroare(double de, std::vector<double> &mde)
{
	//vectorul mde[] -> cuprinde rezultatele in urma apelarii functiilor pentru intrarea "derr_eroare" (functiile de apartenenta)
	mde.push_back(triunghi_stanga(de, -1.0, 0.0));	//N
	mde.push_back( triunghi(de, -1.0, 0.0, 1.0) );	//Z
	mde.push_back(triunghi_dreapta(de, 0.0, 1.0));	//B
}

void inferenta_Mamdani(std::vector<double> me, std::vector<double> mde, std::vector <std::vector <double> > &mu)
{
	//se aplica inferenta Mamdani (se determina minimul dintre functiile de activare ale intrarilor "eroare" si "derr_eroare"
	//rezultatele in urma inferentei se retin in vectorul mu[]
	for (size_t i = 0; i < 3; ++i)	
		for (size_t j = 0; j < 5; ++j)
			mu[i][j] = std::min (me[j], mde[i]);				

	//randuri -> i -> derr_err -> NE ZE PO
	//coloane -> j -> eroare -> NB NS ZE PS PB
	std::cout << "Tabela de inferenta: " << std::endl;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << mu[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

}

double max_fctApartenenta(std::vector <std::vector <double> > mu, char reguli[3][5], char cuvant)
{
	//se calculeaza valoarea maxima a fiecarei functii de apartenenta 
	double max = 0.0;

	for (int i = 0; i < 3; ++i)	
		for (int j = 0; j < 5; ++j)		
			if (reguli[i][j] == cuvant)		
				max = std::max(max, mu[i][j]);

	return max;
}

double primulMaxim(double a, double b, double c, double max)
{
	double firstMax = (b-a)*(max) + a;

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
	/* -------------------------------------------------------------------------------- */
	//baza de reguli, unde:
	//n -> NB; m -> NS; z -> ZE; p -> PS; b -> PB;
	char reguli[3][5] = { 'n', 'm', 'z', 'z', 'p',
												'n', 'm', 'z', 'p', 'b',
												'm', 'z', 'z', 'p', 'b' };

	std::cout << "Tabela de reguli: " << std::endl;
	for (int i = 0; i < 3; ++i)
	{
		for (int j = 0; j < 5; ++j)
		{
			std::cout << reguli[i][j] << "\t";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
	/* -------------------------------------------------------------------------------- */

	while (true)
	{
		/* -------------------------------------------------------------------------------- */
		double e, de;
		std::cout << "Introduceti valoarea erorii: e = "; std::cin >> e;
		if (e < -1 || e > 1)
		{
			std::cout << "Universul de discurs pentru eroare este [-1; 1]. Valoarea introdusa nu apartine acestuia." << std::endl;
			std::cout << "Introduceti valoarea erorii: e = "; std::cin >> e;
		}

		std::cout << "Introduceti valoarea derivatei erorii: de = "; std::cin >> de;
		if (de < -1 || de > 1)
		{
			std::cout << "Universul de discurs pentru derivata erorii este [-1; 1]. Valoarea introdusa nu apartine acestuia." << std::endl;
			std::cout << "Introduceti valoarea derivatei erorii: de = "; std::cin >> de;
		}
		/* -------------------------------------------------------------------------------- */

		/* -------------------------------------------------------------------------------- */
		
		std::vector<double> me;
		me.reserve(5);
		std::vector<double> mde;
		mde.reserve(3);

		// * timp
		//apelare fct fuzzificare pentru a determina functiile de apartenenta
		fuzzificare_eroare(e, me);
		fuzzificare_derivataEroare(de, mde);

		std::cout << e << " apartine  " << me[0] << "  NB " << std::endl;
		std::cout << e << " apartine  " << me[1] << "  NS " << std::endl;
		std::cout << e << " apartine  " << me[2] << "  ZE " << std::endl;
		std::cout << e << " apartine  " << me[3] << "  PS " << std::endl;
		std::cout << e << " apartine  " << me[4] << "  PB " << std::endl;
		std::cout << std::endl;

		std::cout << de << " apartine  " << mde[0] << " N " << std::endl;
		std::cout << de << " apartine  " << mde[1] << " Z " << std::endl;
		std::cout << de << " apartine  " << mde[2] << " P " << std::endl;
		std::cout << std::endl;
		/* -------------------------------------------------------------------------------- */

		/* -------------------------------------------------------------------------------- */
		std::vector <std::vector <double> > mu;
		mu.resize(3);
		for (size_t i = 0; i < mu.size(); ++i)
			mu[i].resize(5);

		//tabela de inferenta
		inferenta_Mamdani(me, mde, mu);
		/* -------------------------------------------------------------------------------- */

		/* -------------------------------------------------------------------------------- */
		std::vector <double> max_apartenenta;
		max_apartenenta.reserve(5);
		max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'n'));
		max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'm'));
		max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'z'));
		max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'p'));
		max_apartenenta.push_back(max_fctApartenenta(mu, reguli, 'b'));
		/* -------------------------------------------------------------------------------- */

		/* -------------------------------------------------------------------------------- */
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
		std::cout << "Defuzzificare prin metoda MIJLOCUL MAXIMELOR (MOM): " << mom << "\n\n" << std::endl;
		/* -------------------------------------------------------------------------------- */
	}
}
