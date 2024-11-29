#include <iostream>
#include <algorithm>
#include <stdio.h>
#include <conio.h>

#include <vector>

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

				std::cout << "Casute active: " << std::endl;
				std::cout << mu[0] << "\t" << mu[1] << std::endl;
				std::cout << mu[2] << "\t" << mu[3] << std::endl;
			}

			if (e == me[j] && (de > mde[i] && de < mde[i + 1]))
			{
				mu.push_back(reguli[i][j]);
				mu.push_back(reguli[i + 1][j]);

				std::cout << "Casute active: " << std::endl;
				std::cout << mu[0] << "\n" << mu[1] << std::endl;
			}

			if ((e > me[j] && e < me[j + 1]) && de == mde[i])
			{
				mu.push_back(reguli[i][j]);
				mu.push_back(reguli[i][j + 1]);

				std::cout << "Casute active: " << std::endl;
				std::cout << mu[0] << "\t" << mu[1] << std::endl;
			}

			if (e == me[j] && de == mde[i])
			{
				mu.push_back(reguli[i][j]);

				std::cout << "Casute active: " << std::endl;
				std::cout << mu[0] << std::endl;
			}
		}
	}
}

void main()
{
	/* -------------------------------------------------------------------------------- */
	//baza de reguli
	double reguli[5][11] = { -1, -0.9, -0.5, -0.5, 0, 0, 0, -0.01, -0.01, 0.5, 0.5,
													-0.88, -0.88, -0.5, -0.5, 0, 0, 0, 0.25, 0.25, 0.63, 0.63,
													-1, -0.9, -0.5, -0.5, 0, 0, 0, 0.5, 0.5, 0.9, 1,
													-0.63, -0.63, -0.25, -0.25, 0, 0, 0, 0.5, 0.5, 0.88, 0.88,
													-0.5, -0.5, -0.01, -0.01, 0, 0, 0, 0.5, 0.5, 0.9, 1 }; //y

	std::cout << "Tabela de reguli: " << std::endl;
	for (int i = 0; i < 5; ++i)
	{
		for (int j = 0; j < 11; ++j)
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
		me.reserve(11);
		valori_eroare(me);
		
		std::vector<double> mde;
		mde.reserve(5);
		valori_derErr(mde);
		/* -------------------------------------------------------------------------------- */

		// * timp

		/* -------------------------------------------------------------------------------- */
		std::vector<double> mu;
		mu.reserve(4);
		valoriActive_comanda(e, de, me, mde, reguli, mu);
		/* -------------------------------------------------------------------------------- */

		/* -------------------------------------------------------------------------------- */
		std::vector<double> ponderi_w;
		ponderi_w.reserve(4);
		for (size_t i = 0; i < mde.size(); ++i)
		{
			for (size_t j = 0; j < me.size(); ++j)
			{
				if ((e > me[j] && e < me[j + 1]) && (de > mde[i] && de < mde[i + 1]))
				{
					double w0 = (abs(e - me[j + 1])*abs(de - mde[i + 1])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w1 = (abs(e - me[j])*abs(de - mde[i + 1])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w2 = (abs(e - me[j + 1])*abs(de - mde[i])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));
					double w3 = (abs(e - me[j])*abs(de - mde[i])) / (abs(me[j] - me[j + 1])*abs(mde[i] - mde[i + 1]));

					ponderi_w.push_back(w0);
					ponderi_w.push_back(w1);
					ponderi_w.push_back(w2);
					ponderi_w.push_back(w3);

					std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
					std::cout << ponderi_w[0] << "\t" << ponderi_w[1] << std::endl;
					std::cout << ponderi_w[2] << "\t" << ponderi_w[3] << std::endl;

					break;
				}

				if (e == me[j] && (de > mde[i] && de < mde[i + 1]))
				{
					if (e == 1)
					{
						double w0 = (abs(e - me[j - 1])*abs(de - mde[i + 1])) / (0.2 * abs(mde[i] - mde[i + 1]));
						double w1 = (abs(e - me[j - 1])*abs(de - mde[i])) / (0.2 * abs(mde[i] - mde[i + 1]));

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << "\n" << ponderi_w[1] << std::endl;

						break;
					}
					else
					{
						double w0 = (abs(e - me[j + 1])*abs(de - mde[i + 1])) / (0.2 * abs(mde[i] - mde[i + 1]));
						double w1 = (abs(e - me[j + 1])*abs(de - mde[i])) / (0.2 * abs(mde[i] - mde[i + 1]));

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << "\n" << ponderi_w[1] << std::endl;

						break;
					}
				}

				if ((e > me[j] && e < me[j + 1]) && de == mde[i])
				{
					if (de == 1)
					{
						double w0 = (abs(e - me[j + 1])*abs(de - mde[i - 1])) / (abs(me[j] - me[j + 1]) * 0.5);
						double w1 = (abs(e - me[j])*abs(de - mde[i - 1])) / (abs(me[j] - me[j + 1]) * 0.5);

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << "\t" << ponderi_w[1] << std::endl;

						break;
					}

					else
					{
						double w0 = (abs(e - me[j + 1])*abs(de - mde[i + 1])) / (abs(me[j] - me[j + 1]) * 0.5);
						double w1 = (abs(e - me[j])*abs(de - mde[i + 1])) / (abs(me[j] - me[j + 1]) * 0.5);

						ponderi_w.push_back(w0);
						ponderi_w.push_back(w1);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << "\t" << ponderi_w[1] << std::endl;

						break;
					}
				}

				if (e == me[j] && de == mde[i])
				{
					if (e == 1 && de == 1)
					{
						double w0 = (abs(e - me[j - 1])*abs(de - mde[i - 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << std::endl;

						break;

					}
					if (e == 1 && de == mde[i])
					{
						double w0 = (abs(e - me[j - 1])*abs(de - mde[i + 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << std::endl;
						break;

					}
					if (de == 1 && e == me[j])
					{
						double w0 = (abs(e - me[j + 1])*abs(de - mde[i - 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << std::endl;

						break;
					}
					else
					{
						double w0 = (abs(e - me[j + 1])*abs(de - mde[i + 1])) / (0.2 * 0.5);
						ponderi_w.push_back(w0);

						std::cout << "Ponderile corespunzatoare casutelor active: " << std::endl;
						std::cout << ponderi_w[0] << std::endl;

						break;
					}
				}
			}
		}
		/* -------------------------------------------------------------------------------- */

		double verificare_ponderi = 0.0;
		double u = 0.0;
		for (size_t i = 0; i < ponderi_w.size(); ++i)
		{
			verificare_ponderi += ponderi_w[i];
			u += double(ponderi_w[i]) * double(mu[i]);
		}
		if (verificare_ponderi != 1.0)
			std::cout << "Programul nu calculeaza corect ponderile! Suma lor trebuie sa fie 1." << std::endl;

		std::cout << "u = " << u << "\n\n" << std::endl;
		/* -------------------------------------------------------------------------------- */
	}
}
