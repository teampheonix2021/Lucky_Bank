#pragma once

#include "Drawable.h"

// Represents the spaces Edge
class Edge : public Drawable
{
private:
    float position;  // The horizontal position of the Edge
    bool EdgeDirection; // "0" represents the vertical Edge and "1" reprents the horizontal Edge
    

public:
    explicit Edge(float position, bool EdgeDirection);
    void draw(GUI& gui) override;




};