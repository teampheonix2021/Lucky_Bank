#pragma once


#include "Drawable.h"

// Represents the message box of the game
class UserInput : public Drawable
{

public:
    explicit UserInput();
    void draw(GUI& gui) override;




};
