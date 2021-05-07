#include "GUI.h"


GUI::GUI()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
    window.create(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Pheonix");
    window.setVerticalSyncEnabled(true);

//load the dice sides array 
   loadDiceSides();
}
// Function for getting control on any event such as keyboard or mouse 
void GUI::getControls(bool& exit)
{
    sf::Event event;

    //check the window events
    while (window.pollEvent(event))
        
    {
        //if ESC button is pressed the game window is closed!
       exit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

      
       // check if the closed button of window is closed
       if (event.type == event.Closed)
       {
           window.close();
       }
       //check if the left button of the mouse is pressed
       if (event.MouseButtonReleased&& event.mouseButton.button==sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect diceBtnBounds = diceRect.getGlobalBounds();
            sf::FloatRect playBtnBounds = playRect.getGlobalBounds();

            //if the mouse left button is pressed on the dice button, the side is changed
            if (diceBtnBounds.contains(mousePos))
            {
                if (!diceIsRolled)
                {
                    lastRoll = 0;
                    numberOfRolling = 0;

                }
            }

            //if mouse left button is pressed on the play button, The message box is appread
            if (playBtnBounds.contains(mousePos))
            {
                sf::ContextSettings settings;
                settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
                messagePrompt.create(sf::VideoMode(265, 166), "messageBox", sf::Style::Titlebar, settings);
                messagePrompt.setVerticalSyncEnabled(true);

            }


        }
    }//loop of window event

    //check the messagebox events
    while (messagePrompt.pollEvent(event))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = messagePrompt.mapPixelToCoords(sf::Mouse::getPosition(messagePrompt));
            sf::FloatRect okButtonBounds = okButton.getGlobalBounds();

            if (okButtonBounds.contains(mousePos))
            {
                messagePrompt.close();

            }

        }
    }//loop of messagebox events
}

void GUI::clear()
{
    window.clear(backgroundColor);
}

void GUI::display()
{
    window.display();
}
//This function can be changes to load arrays of images  according to the game components
void GUI::loadPlayImage(std::string path, float setPositionX, float setPositionY, float scaleX,float scaleY)
{
    //Create the texture
    sf::Texture texture;
    texture.loadFromFile(path);
    //Use the sprite to load the image and scale it,  another method in loadDiceSides() function
    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setPosition(sf::Vector2f(setPositionX, setPositionY)); // offset relative to the original position(0,0)
    sprite.scale(sf::Vector2f(scaleX, scaleY)); // factor relative to the current scale
    // Create play Edge
    playRect.setSize(sf::Vector2f(65.0f, 65.0f));
    playRect.setOutlineThickness(outlineThickness);
    playRect.setOutlineColor(outlineColor);
    playRect.setPosition(725, 750);

    window.draw(playRect);
    window.draw(sprite);

    
}
//This function can be changes to load arrays of text  according to the game components and adding more arguments for the positions
void GUI::loadText(string inText)
{
    
    // select the font
    sf::Font font;
    font.loadFromFile(ARIAL_FONT);
    text.setFont(font); // font is a sf::Font
    // set the string to display
    text.setString(inText);
    // set the character size
    text.setCharacterSize(15); // in pixels, not points!
    // set the color
    text.setFillColor(outlineColor);
    // set the text style
    text.setStyle(sf::Text::Bold);
    //set the text position
    text.setPosition(628.0f,470.0f);
    
   // Create Dice Edge, which can be used for applying events on the text
    textRect.setSize(sf::Vector2f(450.0f, 35.0f));
    textRect.setOutlineThickness(0); // can be outlineThickness to show border
    textRect.setOutlineColor(outlineColor);
    textRect.setPosition(530.0f, 650.0f);


    window.draw(textRect, sf::RenderStates());
    window.draw(text, sf::RenderStates());
   

}


//This function is invoked from the game object to allocate the menucomponents
void GUI::drawMenuItems()
{
    loadPlayImage("Images\\playImage.png", 732, 756, 0.5, 0.5);
    loadPlayImage("Images\\SAVE.jpg", 400, 200, 0.5, 0.5);
}

void GUI::drawText()
{

    loadText("Please click here to roll the dice");
}


//this function is invoked from messagebox object to popup the message box
void GUI::drawMessageBox()
{
    sf::Font arialFont;
    arialFont.loadFromFile(ARIAL_FONT);
    sf::Text messageTitle;
    messageTitle.setString("Welcome");
    messageTitle.setCharacterSize(25);
    messageTitle.setFont(arialFont);
    messageTitle.setPosition(15.0f, 15.0f);
    messageTitle.setFillColor(outlineColor);

    sf::Text messageText;
    messageText.setFont(arialFont);
    messageText.setString("Press on Ok button to Close!");
    messageText.setPosition(15.0f, 75.0f);
    messageText.setCharacterSize(15);
    messageText.setFillColor(outlineColor);

  
    sf::Texture okButtonTexture;
    okButtonTexture.loadFromFile("Images\\ok.png");
    okButton.setSize(sf::Vector2f(40.0f, 40.0f));
    okButton.setTexture(&okButtonTexture);
    okButton.setPosition(120.0f, 125.0f);
    okButton.setOutlineThickness(outlineThickness);
    okButton.setOutlineColor(outlineColor);
    okButtonTexture.setSmooth(true);

     messagePrompt.clear(backgroundColor);

        messagePrompt.draw(messageTitle);
        messagePrompt.draw(messageText);
        messagePrompt.draw(okButton);

    messagePrompt.display();
  }



// a smiliar function can be used for drawing individual lines
void GUI::drawEdge(float position, bool EdgeDir)
{
    if (EdgeDir == 0) //condition for drawing the vertical Edges
    {
        sf::Vertex line[] =
        {
                sf::Vertex(sf::Vector2f(300,50), outlineColor),
                sf::Vertex(sf::Vector2f(300, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(400,50), outlineColor),
                sf::Vertex(sf::Vector2f(400, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(500,50), outlineColor),
                sf::Vertex(sf::Vector2f(500, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(600,50), outlineColor),
                sf::Vertex(sf::Vector2f(600, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(700,50), outlineColor),
                sf::Vertex(sf::Vector2f(700, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(800,50), outlineColor),
                sf::Vertex(sf::Vector2f(800, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(900,50), outlineColor),
                sf::Vertex(sf::Vector2f(900, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(1000,50), outlineColor),
                sf::Vertex(sf::Vector2f(1000, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(1100,50), outlineColor),
                sf::Vertex(sf::Vector2f(1100, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(1200,50), outlineColor),
                sf::Vertex(sf::Vector2f(1200, BOARD_HEIGHT - 750), outlineColor),
                sf::Vertex(sf::Vector2f(300,550), outlineColor),
                sf::Vertex(sf::Vector2f(300, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(400,750), outlineColor),
                sf::Vertex(sf::Vector2f(400, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(500,750), outlineColor),
                sf::Vertex(sf::Vector2f(500, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(600,750), outlineColor),
                sf::Vertex(sf::Vector2f(600, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(700,750), outlineColor),
                sf::Vertex(sf::Vector2f(700, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(800,750), outlineColor),
                sf::Vertex(sf::Vector2f(800, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(900,750), outlineColor),
                sf::Vertex(sf::Vector2f(900, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(1000,750), outlineColor),
                sf::Vertex(sf::Vector2f(1000, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(1100,750), outlineColor),
                sf::Vertex(sf::Vector2f(1100, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(1200,100), outlineColor),
                sf::Vertex(sf::Vector2f(1200, BOARD_HEIGHT - 50), outlineColor),
                sf::Vertex(sf::Vector2f(position,50), outlineColor),
                sf::Vertex(sf::Vector2f(position, BOARD_HEIGHT - 50), outlineColor),

        };
        window.draw(line, 50, sf::Lines);
    }

    else if (EdgeDir == 1) // Condition for drawing the horizontal Edge
    {
        sf::Vertex line[] =
        {
          sf::Vertex(sf::Vector2f(200, 750), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 750), outlineColor),
          sf::Vertex(sf::Vector2f(200, 850), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 850), outlineColor),
          sf::Vertex(sf::Vector2f(200, 50), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 50), outlineColor),
          sf::Vertex(sf::Vector2f(200, 150), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 150), outlineColor),
          sf::Vertex(sf::Vector2f(200, 650), outlineColor),
          sf::Vertex(sf::Vector2f(300, 650), outlineColor),
          sf::Vertex(sf::Vector2f(200, 550), outlineColor),
          sf::Vertex(sf::Vector2f(300, 550), outlineColor),
          sf::Vertex(sf::Vector2f(200, 450), outlineColor),
          sf::Vertex(sf::Vector2f(300, 450), outlineColor),
          sf::Vertex(sf::Vector2f(200, 350), outlineColor),
          sf::Vertex(sf::Vector2f(300, 350), outlineColor),
          sf::Vertex(sf::Vector2f(200, 250), outlineColor),
          sf::Vertex(sf::Vector2f(300, 250), outlineColor),
          sf::Vertex(sf::Vector2f(1200, 650), outlineColor),
          sf::Vertex(sf::Vector2f(1300, 650), outlineColor),
          sf::Vertex(sf::Vector2f(1200, 550), outlineColor),
          sf::Vertex(sf::Vector2f(1300, 550), outlineColor),
          sf::Vertex(sf::Vector2f(1200, 450), outlineColor),
          sf::Vertex(sf::Vector2f(1300, 450), outlineColor),
          sf::Vertex(sf::Vector2f(1200, 350), outlineColor),
          sf::Vertex(sf::Vector2f(1300, 350), outlineColor),
          sf::Vertex(sf::Vector2f(1200, 250), outlineColor),
          sf::Vertex(sf::Vector2f(1300, 250), outlineColor),
        };
        window.draw(line, 30, sf::Lines);
    }
}



// Create pool of dice sides
void GUI::loadDiceSides()
{
    diceRect.setSize(sf::Vector2f(DICEX, DICEY));
    diceRect.setPosition(720.0f, 410.0f);
    //You should add more lines and images for more dice sides
    diceTexture[0].loadFromFile("Images/dice/1.png");
    diceTexture[1].loadFromFile("Images/dice/2.png");
    diceTexture[2].loadFromFile("Images/dice/3.png");
    diceTexture[3].loadFromFile("Images/dice/4.png");
    diceTexture[4].loadFromFile("Images/dice/5.png");
    diceTexture[5].loadFromFile("Images/dice/6.png");
    for (int i = 0; i < 6; i++)
        diceTexture[i].setSmooth(true);    
}
// //this function is invoked from dice object to roll the dice
void GUI::drawRollDice()
{
    // decrease the second condition to see the suffeling among dice sides ex: numberOfRolling - lastRoll == 8
    if (numberOfRolling <= 100 && numberOfRolling - lastRoll == 20)
    {
       int  dicePicNumber = rand() % 6;
        diceRect.setTexture(&diceTexture[dicePicNumber]);
        lastRoll = numberOfRolling;
       
    }
   //draw the new side
   window.draw(diceRect);

   if (numberOfRolling <= 100) numberOfRolling++;
}