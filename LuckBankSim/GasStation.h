#pragma once
#include "spaces/space.h"

using namespace std;
class GasStation :
    public Space
{
public:
    explicit GasStation();
      vector<string> Name;
    vector<int> Price;
    vector<int> PassingFees;
    GasStation Readcities(GasStation& C);

};

