#include "Game.h"
#include <iostream>
#include <fstream>
#include "City.h"
using namespace std;

//int main()
//{
//	int counter = 0;
//	fstream infile;
//	infile.open("BankOfLuckFiles\\spaceinfo.txt");
//	if (!infile)
//	{
//		cout << "open file failure" << endl;
//	}
//	else
//	{
//		char* pch;
//		char* context = nullptr;
//		const int size = 300;
//		char line[size];
//
//
//		while (infile.getline(line, size))
//		{
//			//parse the line
//
//
//			pch = strtok_s(line, ",", &context);
//			while (pch != nullptr)
//			{
//				cout << pch << "||";
//				pch = strtok_s(NULL, ",", &context);
//			}
//			counter++;
//			cout << counter << endl;
//		}
//		cout << counter << endl;
//	}
//}

int main()
{
    City C1;
    C1.Readcities(C1);

    // Create an object of ApplicationManager
    Game Game;
    while (!Game.exited())
    {
        // Read new user (or whatever else)
        Game.readGUIInput();
        // Simulate the Board for one more frame
        Game.simulate();
        // Update the Board graphical interface
        Game.updateGUIOutput();
    }
    return 0;
}