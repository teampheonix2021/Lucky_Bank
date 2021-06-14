#pragma once

#include <chrono>
using namespace std::chrono;
#include "GUI.h"
#include "Defs.h"
#include "BoardObjects/Player.h"
#include "BoardObjects/Text.h"
#include "BoardObjects/Menu.h"
#include "BoardObjects/Dice.h"
#include "BoardObjects/Edge.h"
#include "BoardObjects/MessageBox.h"
#include "BoardObjects/MessageBox2.h"
#include "BoardObjects/Rectangle.h"
#include "BoardObjects/TextBox.h"
#include "BoardObjects/PlayerData.h"
#include "BoardObjects/DrawCity.h"
#include "BoardObjects/UserInput.h"
#include "BoardObjects/Avatar.h"

// Represents a game, keeps track of everything relevant to the game and delegates the tasks to their proper objects
class Game
{
private:
    high_resolution_clock::time_point lastFrame;  // Time point of the last rendered frame
    GUI gui;  // An object representing the game gui
    Edge leftEdge, rightEdge, upEdge, bottomEdge; // The edges of the game spaces
    MessageBox  messageBox;//The message box component
    Dice dice;
    Menu menu;
    Text text;
    rectangle rect; //draw a rectangle
    textbox textbo;
    Player player;
    PlayerData data;
    DrawCity City;
    Avatar avatar;
    MessageBox2 messageBox2;

    bool exit;  // Flags about the user's exit keygame controls
    

public:
    Game();
    void readGUIInput(); //this method is called by the main to check any event as long as the game window object is found
    void simulate(); ; //this method is called by the main to get the time between frames as long as the game window object is found
    void updateGUIOutput(); //this method is called by the main to draw the game components as long as the game window object is found
    bool exited();// this method is used to return the exit properity 
};
