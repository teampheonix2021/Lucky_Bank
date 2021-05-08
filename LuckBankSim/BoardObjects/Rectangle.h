#pragma once


#include "Drawable.h"

// draw rectangles
class rectangle : public Drawable
{

public:
    explicit rectangle();
    void draw(GUI& gui) override;
};