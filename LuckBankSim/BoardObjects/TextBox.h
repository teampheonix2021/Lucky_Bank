#pragma once


#include "Drawable.h"

//text box to the user
class textbox : public Drawable
{

public:
    explicit textbox();
    void draw(GUI& gui) override;
};