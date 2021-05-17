#include "City.h"
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;

City::City() {}

void City::setGroup(int a)
{
	G.Group = a;
}

//SpaceInfo
void City::Readcities()
{
	fstream infile;
	infile.open("BankOfLuckFiles\\spaceinfo.txt");
	if (!infile)
	{
		cout << "open file failure" << endl;
	}
	else
	{
		char* pch;
		char* context = nullptr;
		const int size = 300;
		char line[size];
		City* C = new City[counter];

		while (infile.getline(line, size))
		{
			//parse the line
			for (int i = 0; i <= counter && i < 23; ++i)
			{
				pch = strtok_s(line, ",", &context);
				while (pch != nullptr)
				{
					C[i].Name = pch;//push the name
					pch = strtok_s(nullptr, ",", &context);
					//stringstream temp(pch);
					//temp >> C[i].Price;
					C[i].Price = atoi(pch);
					pch = strtok_s(nullptr, ",", &context);
					C[i].PassingFees = atoi(pch);
					pch = strtok_s(nullptr, ",", &context);
					C[i].P.setGaragePrice(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].P.setGarageFees(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].R.setRestAreaPrice(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].R.setRestAreaFees(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].M.setMarketPrice(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].M.setMarketFees(atoi(pch));
					pch = strtok_s(nullptr, ",", &context);
					C[i].G.Group = atoi(pch);
					pch = strtok_s(nullptr, ",", &context);
				}
				counter++;
			}
		}
		infile.close();
	}
}



