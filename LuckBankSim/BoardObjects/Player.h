#pragma once

#include "Drawable.h"

// Represents the dice of the game
class Player : public Drawable
{

public:
    explicit Player();
    void draw(GUI& gui) override;

};