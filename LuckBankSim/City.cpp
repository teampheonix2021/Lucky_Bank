#include "City.h"
#include<iostream>
#include<fstream>
#include <sstream>
using namespace std;

City::City()
{
}

void City::setGroup(int a)
{
		G.Group = a;
}

//spaceinfo
 City City::Readcities(City & C)
{
	fstream infile;
	infile.open("bankofluckfiles\\spaceinfo.txt");
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
		string Y_1 = "ClubOfLuck";
		string Y_2 = "GasStation";
		
		//while (infile.getline(line, size))
		//{
		//	//parse the line
		//	
		//	
		//		pch = strtok_s(line, ",", &context);
		//		while (pch != nullptr)
		//		{
		//			pch = strtok_s(NULL, ",", &context);
		//		}
		//		counter++;
		//	
		//}

		while (infile.getline(line, size))
		{
			//parse the line
			
			
				pch = strtok_s(line, ",", &context);
				while (pch != nullptr)
				{
					if (pch == Y_1)// skip the club of luck
					{
						pch = strtok_s(nullptr, ",", &context);
						pch = strtok_s(nullptr, ",", &context);
						break;
					}

					if (pch == Y_1)// skip the gas station
					{
						pch = strtok_s(nullptr, ",", &context);
						pch = strtok_s(nullptr, ",", &context);
						pch = strtok_s(nullptr, ",", &context);
						break;
					}

					Name.push_back(pch);//push the name
					pch = strtok_s(nullptr, ",", &context);
					//stringstream temp(pch);
					//temp >> c[i].price;
					Price.push_back(atoi(pch));//push the price
					pch = strtok_s(nullptr, ",", &context);
					PassingFees.push_back(atoi(pch));//push the
					pch = strtok_s(nullptr, ",", &context);
					P.GaragePrice.push_back(atoi(pch));//push the garage price
					pch = strtok_s(nullptr, ",", &context);
					P.GarageFees.push_back(atoi(pch));//push the garage fees
					pch = strtok_s(nullptr, ",", &context);
					R.RestAreaPrice.push_back(atoi(pch));//push the rest area price
					pch = strtok_s(nullptr, ",", &context);
					R.RestAreaFees.push_back(atoi(pch));//push the rest area fees
					pch = strtok_s(nullptr, ",", &context);
					M.MarketPrice.push_back(atoi(pch));//push the market price
					pch = strtok_s(nullptr, ",", &context);
					M.MarketFees.push_back(atoi(pch));//push the market fees
					pch = strtok_s(nullptr, ",", &context);
					G.Group = atoi(pch); // push the group
					pch = strtok_s(nullptr, ",", &context);
				}
			
			
		}
		infile.close();

	}
	return C;
}