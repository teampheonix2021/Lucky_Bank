#pragma once

#include "Drawable.h"

// Represents the dice of the game
class Menu : public Drawable
{

public:
    explicit Menu();
    void draw(GUI& gui) override;




};