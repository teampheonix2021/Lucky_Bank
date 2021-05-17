#pragma once


#include "Drawable.h"

// Represents the dice of the game
class DrawCity : public Drawable
{

public:
    explicit DrawCity();
    void draw(GUI& gui) override;




};