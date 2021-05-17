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
    void setGroup(int a);
    City Readcities(City & C);
    vector<string> Name;
    vector<int> Price;
    vector<int> PassingFees;
};

