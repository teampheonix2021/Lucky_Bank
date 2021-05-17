#pragma once
#include "space.h"
#include <string>
#include "Defs.h"
#include"Parking.h"
#include"RestArea.h"
#include"Market.h"
#include <vector>
using namespace std;

class City :
    public Space
{
protected:
   //string Name;
   //int Price;
   //int PassingFees;
   Group G;
   Parking P;
   RestArea R;
   Market M;
public:
    City();
    void setGroup(int a);
    City Readcities(City & C);
    vector<string> Name;
    vector<int> Price;
    vector<int> PassingFees;
};

