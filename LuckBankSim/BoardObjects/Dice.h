#pragma once

#include "Drawable.h"

// Represents the dice of the game
class Dice : public Drawable
{

public:
    explicit Dice();
    void draw(GUI& gui) override;




};