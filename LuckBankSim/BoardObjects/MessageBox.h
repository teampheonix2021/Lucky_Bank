#pragma once

#include "Drawable.h"

// Represents the message box of the game
class MessageBox : public Drawable
{

public:
    explicit MessageBox();
    void draw(GUI& gui) override;




};
