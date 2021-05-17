#pragma once


#include "Drawable.h"

//text box to the user
class PlayerData : public Drawable
{

public:
    explicit PlayerData();
    void draw(GUI& gui) override;

};