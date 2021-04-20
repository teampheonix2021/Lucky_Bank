#include "Edge.h"

using namespace std;

Edge::Edge(float position, bool EdgeDirection) : position(position), EdgeDirection(EdgeDirection) {}

void Edge::draw(GUI& gui)
{
    gui.drawEdge(position, EdgeDirection);
}


