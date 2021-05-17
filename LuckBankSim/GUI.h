#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <chrono>
#include <random>
#include "Defs.h"
#include "spaces/City.h"
#include "spaces/Court.h"
#include "spaces/Luck.h"


// Represents the game GUI
// This class is the ONLY one that interacts with the user
// This class is also the ONLY one aware of the graphics library being used
// That is, if the graphics library was to be changes, this class is the only thing to be changed
class GUI
{
private:
    //edits
    City C;
    Luck L;
    Court Co;
    int luckcards = 0;
    int courcards = 0;
    int textbox = 0;
    int roll;
    string numofplayer;
    bool playbuttonbool = false;
    bool drawavatarbool = false;
    int i = 0;
    sf::Text Player2;
    sf::Text Player3;
    sf::Text Player4;


    sf::Vector2f mouseposition; //mousepositon for textbox function .. etc

    sf::RenderWindow window;  // Represents the game window
    sf::RenderWindow messagePrompt;//Represents the messageBox window
    sf::RenderWindow userinput; //Represents the user input
    
    //Blending mode, mix between the image and the rectangle-credits to ENG KAREEEEEEEEEEEEEEEEEEEEEEEM*******
    sf::BlendMode multiplicativeBlending = sf::BlendMultiply; //mixing
    sf::BlendMode alphaBlending = sf::BlendAlpha;
    sf::BlendMode additiveBlending = sf::BlendAdd;
    sf::BlendMode noBlending = sf::BlendNone;

    const sf::Color  // Colors used for drawing (can change the whole theme of the game)
        backgroundColor = sf::Color::White,
        outlineColor = sf::Color::Black,
        ballFillColor = sf::Color::White,
        Red = sf::Color::Red,
        flipperFillColor = sf::Color::White,
        windowcolor = sf::Color::Color(255, 245, 199);
    const float outlineThickness = -1.0f;  // Negative sign means inwards
    // array of rectangles to draw any number of rectangles you want .. just change the size to the number of rectangles you want

    sf::RectangleShape textRect, playRect, diceRect, saverect, okButton,rectangle[4],Board[34],Luckrectangle,Courtrectangle ,Player[4], players_2, players_3, players_4, Avatar[4]; // Rectangle edges of the board components
    sf::Texture diceTexture[6];// dicesides
    sf::Text   text;// load Text
    int  numberOfRolling = 0, lastRoll = 0; // For rolling dice
    bool diceIsRolled = 0;// variable for checking if the dice is rolled
 
public:
    GUI();  // Constructor
    void getControls(bool & exit);  // Detects exit button pressed
    void clear();  // Clears the frame (first step in rendering a new frame)
    void display();  // Displays the frame (last step in rendering a new frame)
    
   
    void loadPlayImage(string path, float offsetPositionX, float offsetPositionY, float scaleX, float scaleY);//Loading image as a texture and drawing the texture using sprite
    void loadText(string inText, float offsetPositionX, float offsetPositionY);//For drawing text
    void drawMessageBox();// Drawing message box object
    void drawMenuItems();// Drawng Tool bar menu
    void drawText(); //draw the text on the board
    void drawEdge(float position, bool EdgeDir);// Draws boarders of the spaces, The positions can be read from a file
    void loadDiceSides();//load dice side in textures
    void drawRollDice();// rolling the dice
    //void input();

    void drawrect(); //draw rectangle as you want
    void player(); // draw player's avatar
    void loadtextbox(string textbox, sf::Vector2f); //display the text box
    void drawtextbox();
    void playerdata(string textbox); // display info rectangle
    void settextbox(int x);
    void setmousepos(sf::Vector2f);
    void playbutton(bool); //checks if the play button is pressed or not
    void ava(bool);
    void citydata(string, int, int, int, int, int, int, int, int, int);
    void DrawCity();
    void drawcourt(int);
    void drawluck(int);
    void drawluckcourt(string path, float offsetPositionX, float offsetPositionY, float scaleX, float scaleY);
    void drawavatar();
    void moveavatar();
};

//https://www.rapidtables.com/web/color/RGB_Color.html to generate the color we want by using sf::Color::Color(red value ,green value , blue value);