#pragma once


#include "BoardObjects/Drawable.h"

// Represents the dice of the game
class rectangle : public Drawable
{

public:
    explicit rectangle();
    void draw(GUI& gui) override;
};