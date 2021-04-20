#pragma once

#include "Drawable.h"

// Represents the dice of the game
class Text : public Drawable
{

public:
    explicit Text();
    void draw(GUI& gui) override;




};