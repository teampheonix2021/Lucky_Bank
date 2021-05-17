#pragma once


#include "Drawable.h"

// Represents the dice of the game
class Avatar : public Drawable
{

public:
    explicit Avatar();
    void draw(GUI& gui) override;




};