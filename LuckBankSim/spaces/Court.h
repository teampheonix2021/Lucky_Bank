#pragma once
#include "spaces/space.h"
class Court:
    public Space
{
public:
    explicit Court();
    vector<string> CardType;
    vector<int> No;
    vector <string> Location;
    Court ReadLuckCourt(Court& C);

};