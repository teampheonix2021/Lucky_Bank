#include "Court.h"

Court::Court()
{
}

Court Court::ReadLuckCourt(Court& C)
{
	fstream infile;
	infile.open("bankofluckfiles\\Luck-Court Card\\LuckCourtCardInfo.txt");
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
		string Y_1 = "Court";
		string Y_2 = "Luck";

		while (infile.getline(line, size))
		{
			//parse the line


			pch = strtok_s(line, ",", &context);
			while (pch != nullptr)
			{
				if (pch == Y_2)// push the Court
				{
					C.CardType.push_back(pch);// push the Court Card Type
					pch = strtok_s(nullptr, ",", &context);
					C.No.push_back(atoi(pch));// push the Court Card number
					pch = strtok_s(nullptr, ",", &context);
					C.Location.push_back(pch);// push the Court card location 

					break;
				}

				pch = strtok_s(nullptr, ",", &context);
			}
		}
		infile.close();
	}
	return C;
}