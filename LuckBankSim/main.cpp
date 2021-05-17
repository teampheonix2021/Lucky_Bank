#include "Game.h"


int main()
{
  // Create an object of ApplicationManager
  Game Game;
   while (!Game.exited())
    {
        // Read new user (or whatever else)
        Game.readGUIInput();
        // Simulate the Board for one more frame
        Game.simulate();
        // Update the Board graphical interface
        Game.updateGUIOutput();
    }
    return 0;
}