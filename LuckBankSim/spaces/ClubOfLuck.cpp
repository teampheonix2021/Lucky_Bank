#include "ClubOfLuck.h"

ClubOfLuck::ClubOfLuck()
{
}

ClubOfLuck ClubOfLuck::Readcities(ClubOfLuck& C)
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

		while (infile.getline(line, size))
		{
			//parse the line


			pch = strtok_s(line, ",", &context);
			while (pch != nullptr)
			{
				if (pch == Y_1)// push club of luck
				{
					Name.push_back(pch);//push the name
					pch = strtok_s(nullptr, ",", &context);
					Price.push_back(atoi(pch));//push the price
					break;
				}
				break;

				
				pch = strtok_s(nullptr, ",", &context);
			}
		}
		infile.close();
	}
	return C;
}
