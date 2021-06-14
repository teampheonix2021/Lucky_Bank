#pragma once


#include "Drawable.h"

// Represents the message box of the game
class MessageBox2 : public Drawable
{

public:
    explicit MessageBox2();
    void draw(GUI& gui) override;




};
