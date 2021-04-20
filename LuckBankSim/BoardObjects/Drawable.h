#pragma once

#include "../GUI.h"

// An interface class that should be implemented by any class that has a visual representation
class Drawable
{
public:
    virtual void draw(GUI & gui) = 0;  // Uses the GUI object to draw itself
};
