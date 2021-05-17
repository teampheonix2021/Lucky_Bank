#pragma once
#include "spaces/space.h"
class ClubOfLuck :
    public Space
{
public:
    explicit ClubOfLuck();
    vector<string> Name;
    vector<int> Price;
    ClubOfLuck Readcities(ClubOfLuck& C);

};

