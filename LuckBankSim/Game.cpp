
#include "Game.h"

Game::Game(): leftEdge(200, 0), rightEdge(BOARD_WIDTH - 200, 0), upEdge(200, 1), bottomEdge(BOARD_HEIGHT - 200, 1) // This line should be removed to create dynamic edges
{
    lastFrame = high_resolution_clock::now();
    exit = false;
}

void Game::readGUIInput()
{
    //check if the keyboard ESC button is pressed to exit the game
    gui.getControls(exit);
}

void Game::simulate()
{
    // Measuring time elapsed in-between frames.
    high_resolution_clock::time_point thisFrame = high_resolution_clock::now();
    duration<float> timeSpan = duration_cast<duration<float>>(thisFrame - lastFrame);
    lastFrame = thisFrame;
    float deltaTime = timeSpan.count();  // Delta time in seconds

}

void Game::updateGUIOutput()
{
    
   gui.clear();


    // Drawing the Edges of the spaces, line by line
    leftEdge.draw(gui);
    rightEdge.draw(gui);
    upEdge.draw(gui);
    bottomEdge.draw(gui);
    menu.draw(gui);

   //Drawing rectangles
    rect.draw(gui);
    
   //Drawing the message box

    messageBox.draw(gui);
   
    //drawing the text box to the user
    textbo.draw(gui);

  /// Rolling the dice
    dice.draw(gui);
    text.draw(gui);

    gui.display();
    
}

bool Game::exited()
{
    return exit;
}
