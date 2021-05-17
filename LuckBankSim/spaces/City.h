#pragma once
#include <fstream>
#include "space.h"
#include <string>
#include "../Defs.h"
#include"Parking.h"
#include"RestArea.h"
#include"Market.h"
#include <vector>
using namespace std;

class City : public Space
{
protected:
    Group G;
   Parking P;
   RestArea R;
   Market M;
public:
    explicit City();
    City Readcities(City & C);
    int getparkprice(int);
    int getparkfees(int);
    int getrestprice(int);
    int getrestfees(int);
    int getmarketprice(int);
    int getmarketfees(int);
    int getgroup(int);
    vector<string> Name;
    vector<int> Price;
    vector<int> PassingFees;
};

