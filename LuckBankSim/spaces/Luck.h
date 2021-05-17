#pragma once
#include "space.h"
class Luck :
    public Space
{
public:
    explicit Luck();
    vector<string> CardType;
    vector<int> No;
    vector <string> Location;
    Luck ReadLuckCourt(Luck& C);

};