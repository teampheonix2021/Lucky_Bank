#pragma once
#include <fstream>
#include "space.h"
#include <string>
#include "Defs.h"
#include"Parking.h"
#include"RestArea.h"
#include"Market.h"

using namespace std;

class City : public Space
{
private:
    int counter = 0;
   string Name;
   int Price;
   int PassingFees;
   Group G;
   Parking P;
   RestArea R;
   Market M;
public:
    explicit City();
    void setGroup(int a);
    void Readcities();
};

