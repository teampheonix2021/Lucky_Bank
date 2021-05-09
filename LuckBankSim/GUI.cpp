#include "GUI.h"


GUI::GUI()
{
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
    window.create(sf::VideoMode(BOARD_WIDTH, BOARD_HEIGHT), "Pheonix");

    //set icon to window
    auto image = sf::Image{};
    image.loadFromFile("Images/Phoenix.jpg");
    window.setIcon(image.getSize().x, image.getSize().y, image.getPixelsPtr());


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
        sf::Vector2f mousePos2 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::FloatRect diceBtnBounds2 = diceRect.getGlobalBounds();
        sf::FloatRect saveBtnBounds2 = rectangle[0].getGlobalBounds();
        sf::FloatRect playBtnBounds2 = playRect.getGlobalBounds();
        if (diceBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 1;
            setmousepos(mousePos2);
        }
        else if (saveBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 2;
            setmousepos(mousePos2);
        }
        else if (playBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 3;
            setmousepos(mousePos2);
        }
        else
        {
            textbox = 0;
        }

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
            sf::FloatRect saveBtnBounds = rectangle[0].getGlobalBounds();

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
    playRect.setPosition(54, 50);

    window.draw(playRect,multiplicativeBlending);

    rectangle[0].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[0].setOutlineThickness(outlineThickness);
    rectangle[0].setOutlineColor(outlineColor);
    rectangle[0].setPosition(54, 150);

    window.draw(rectangle[0], multiplicativeBlending);

    rectangle[1].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[1].setOutlineThickness(outlineThickness);
    rectangle[1].setOutlineColor(outlineColor);
    rectangle[1].setPosition(54, 250);

    window.draw(rectangle[1], multiplicativeBlending);

    rectangle[2].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[2].setOutlineThickness(outlineThickness);
    rectangle[2].setOutlineColor(outlineColor);
    rectangle[2].setPosition(54, 350);

    window.draw(rectangle[2], multiplicativeBlending);
    window.draw(sprite);
}

//This function can be changes to load arrays of text  according to the game components and adding more arguments for the positions
void GUI::loadText(std::string inText, float offsetPositionX, float offsetPositionY)
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
    text.setPosition(offsetPositionX,offsetPositionY);
    
   // Create Dice Edge, which can be used for applying events on the text
    textRect.setSize(sf::Vector2f(450.0f, 35.0f));
    textRect.setOutlineThickness(0); // can be outlineThickness to show border
    textRect.setOutlineColor(outlineColor);
    textRect.setPosition(628.0f, 470.0f);


    window.draw(textRect,multiplicativeBlending);
    window.draw(text, sf::RenderStates());
  
}


//This function is invoked from the game object to allocate the menucomponents
void GUI::drawMenuItems()
{
    loadPlayImage("Images\\Start.jpg", 60, 56, 0.5, 0.5);
    loadPlayImage("Images\\SAVE.jpg", 60, 156, 0.5, 0.5);
    loadPlayImage("Images\\Load.png", 60, 256, 0.5, 0.5);
    loadPlayImage("Images\\End.jpg", 60, 356, 0.5, 0.5);
    
}

void GUI::drawText()
{

    loadText("Please click here to roll the dice", 628.0f, 470.0f);
    loadText("TEST", 240, 500);
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
                /*sf::Vertex(sf::Vector2f(300,50), outlineColor),
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
                sf::Vertex(sf::Vector2f(1200, BOARD_HEIGHT - 50), outlineColor),*/
                sf::Vertex(sf::Vector2f(position,50), outlineColor),
                sf::Vertex(sf::Vector2f(position, BOARD_HEIGHT - 50), outlineColor),

               //LUCK AND COURT RECT
              /* sf::Vertex(sf::Vector2f(950,200), outlineColor),
               sf::Vertex(sf::Vector2f(950, BOARD_HEIGHT - 550), outlineColor),
               sf::Vertex(sf::Vector2f(1100,200), outlineColor),
               sf::Vertex(sf::Vector2f(1100, BOARD_HEIGHT - 550), outlineColor),
               sf::Vertex(sf::Vector2f(400,550), outlineColor),
               sf::Vertex(sf::Vector2f(400, BOARD_HEIGHT - 200), outlineColor),
               sf::Vertex(sf::Vector2f(550,550), outlineColor),
               sf::Vertex(sf::Vector2f(550, BOARD_HEIGHT - 200), outlineColor),*/
        };
        window.draw(line, 70, sf::Lines);
    }

    //else if (EdgeDir == 1) // Condition for drawing the horizontal Edge
    //{
    //    sf::Vertex line[] =
    //    {
    //      /*sf::Vertex(sf::Vector2f(200, 750), outlineColor),
    //      sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 750), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 850), outlineColor),
    //      sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 850), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 50), outlineColor),
    //      sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 50), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 150), outlineColor),
    //      sf::Vertex(sf::Vector2f(BOARD_WIDTH - 200, 150), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 650), outlineColor),
    //      sf::Vertex(sf::Vector2f(300, 650), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 550), outlineColor),
    //      sf::Vertex(sf::Vector2f(300, 550), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 450), outlineColor),
    //      sf::Vertex(sf::Vector2f(300, 450), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 350), outlineColor),
    //      sf::Vertex(sf::Vector2f(300, 350), outlineColor),
    //      sf::Vertex(sf::Vector2f(200, 250), outlineColor),
    //      sf::Vertex(sf::Vector2f(300, 250), outlineColor),
    //      sf::Vertex(sf::Vector2f(1200, 650), outlineColor),
    //      sf::Vertex(sf::Vector2f(1300, 650), outlineColor),
    //      sf::Vertex(sf::Vector2f(1200, 550), outlineColor),
    //      sf::Vertex(sf::Vector2f(1300, 550), outlineColor),
    //      sf::Vertex(sf::Vector2f(1200, 450), outlineColor),
    //      sf::Vertex(sf::Vector2f(1300, 450), outlineColor),
    //      sf::Vertex(sf::Vector2f(1200, 350), outlineColor),
    //      sf::Vertex(sf::Vector2f(1300, 350), outlineColor),
    //      sf::Vertex(sf::Vector2f(1200, 250), outlineColor),
    //      sf::Vertex(sf::Vector2f(1300, 250), outlineColor),*/

    //      ////LUCK AND COURT RECT
    //      //sf::Vertex(sf::Vector2f(950, 200), outlineColor),
    //      //sf::Vertex(sf::Vector2f(BOARD_WIDTH - 400, 200), outlineColor),
    //      //sf::Vertex(sf::Vector2f(950, 350), outlineColor),
    //      //sf::Vertex(sf::Vector2f(BOARD_WIDTH - 400, 350), outlineColor),
    //      //sf::Vertex(sf::Vector2f(400, 550), outlineColor),
    //      //sf::Vertex(sf::Vector2f(BOARD_WIDTH - 950, 550), outlineColor),
    //      //sf::Vertex(sf::Vector2f(400, 700), outlineColor),
    //      //sf::Vertex(sf::Vector2f(BOARD_WIDTH - 950, 700), outlineColor),


    //    };
    //    window.draw(line, 50, sf::Lines);
    //}
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
    if (numberOfRolling <= 100 && numberOfRolling - lastRoll == 8)
    {
       int  dicePicNumber = rand() % 6;
        diceRect.setTexture(&diceTexture[dicePicNumber]);
        lastRoll = numberOfRolling;
       
    }
   //draw the new side
   window.draw(diceRect, multiplicativeBlending);

   if (numberOfRolling <= 100) numberOfRolling++;
}

    //function to draw rectangles
void GUI::drawrect()
{
    //change the size in GUI.h first to increase the number of rectangles
    //Drawing Rectangles of the board

    //Rectangles of the left side of the board .... starts from the left down side
    rectangleleft[0].setSize(sf::Vector2f(100, 100));
    rectangleleft[0].setOutlineColor(outlineColor);
    rectangleleft[0].setOutlineThickness(outlineThickness);
    rectangleleft[0].setPosition(200, 750);

    rectangleleft[1].setSize(sf::Vector2f(100, 100));
    rectangleleft[1].setOutlineColor(outlineColor);
    rectangleleft[1].setOutlineThickness(outlineThickness);
    rectangleleft[1].setPosition(200, 650);

    rectangleleft[2].setSize(sf::Vector2f(100, 100));
    rectangleleft[2].setOutlineColor(outlineColor);
    rectangleleft[2].setOutlineThickness(outlineThickness);
    rectangleleft[2].setPosition(200, 550);

    rectangleleft[3].setSize(sf::Vector2f(100, 100));
    rectangleleft[3].setOutlineColor(outlineColor);
    rectangleleft[3].setOutlineThickness(outlineThickness);
    rectangleleft[3].setPosition(200, 450);

    rectangleleft[4].setSize(sf::Vector2f(100, 100));
    rectangleleft[4].setOutlineColor(outlineColor);
    rectangleleft[4].setOutlineThickness(outlineThickness);
    rectangleleft[4].setPosition(200, 350);

    rectangleleft[5].setSize(sf::Vector2f(100, 100));
    rectangleleft[5].setOutlineColor(outlineColor);
    rectangleleft[5].setOutlineThickness(outlineThickness);
    rectangleleft[5].setPosition(200, 250);

    rectangleleft[6].setSize(sf::Vector2f(100, 100));
    rectangleleft[6].setOutlineColor(outlineColor);
    rectangleleft[6].setOutlineThickness(outlineThickness);
    rectangleleft[6].setPosition(200, 150);

    rectangleleft[7].setSize(sf::Vector2f(100, 100));
    rectangleleft[7].setOutlineColor(outlineColor);
    rectangleleft[7].setOutlineThickness(outlineThickness);
    rectangleleft[7].setPosition(200, 50);
    window.draw(rectangleleft[0],multiplicativeBlending);
    window.draw(rectangleleft[1], multiplicativeBlending);
    window.draw(rectangleleft[2], multiplicativeBlending);
    window.draw(rectangleleft[3], multiplicativeBlending);
    window.draw(rectangleleft[4], multiplicativeBlending);
    window.draw(rectangleleft[5], multiplicativeBlending);
    window.draw(rectangleleft[6], multiplicativeBlending);
    window.draw(rectangleleft[7], multiplicativeBlending);


    //Rectangles of the Right side of the board .... starts from down
    rectangleright[7].setSize(sf::Vector2f(100, 100));
    rectangleright[7].setOutlineColor(outlineColor);
    rectangleright[7].setOutlineThickness(outlineThickness);
    rectangleright[7].setPosition(1200, 750);

    rectangleright[6].setSize(sf::Vector2f(100, 100));
    rectangleright[6].setOutlineColor(outlineColor);
    rectangleright[6].setOutlineThickness(outlineThickness);
    rectangleright[6].setPosition(1200, 650);

    rectangleright[5].setSize(sf::Vector2f(100, 100));
    rectangleright[5].setOutlineColor(outlineColor);
    rectangleright[5].setOutlineThickness(outlineThickness);
    rectangleright[5].setPosition(1200, 550);

    rectangleright[4].setSize(sf::Vector2f(100, 100));
    rectangleright[4].setOutlineColor(outlineColor);
    rectangleright[4].setOutlineThickness(outlineThickness);
    rectangleright[4].setPosition(1200, 450);

    rectangleright[3].setSize(sf::Vector2f(100, 100));
    rectangleright[3].setOutlineColor(outlineColor);
    rectangleright[3].setOutlineThickness(outlineThickness);
    rectangleright[3].setPosition(1200, 350);

    rectangleright[2].setSize(sf::Vector2f(100, 100));
    rectangleright[2].setOutlineColor(outlineColor);
    rectangleright[2].setOutlineThickness(outlineThickness);
    rectangleright[2].setPosition(1200, 250);

    rectangleright[1].setSize(sf::Vector2f(100, 100));
    rectangleright[1].setOutlineColor(outlineColor);
    rectangleright[1].setOutlineThickness(outlineThickness);
    rectangleright[1].setPosition(1200, 150);

    rectangleright[0].setSize(sf::Vector2f(100, 100));
    rectangleright[0].setOutlineColor(outlineColor);
    rectangleright[0].setOutlineThickness(outlineThickness);
    rectangleright[0].setPosition(1200, 50);

    window.draw(rectangleright[0], multiplicativeBlending);
    window.draw(rectangleright[1], multiplicativeBlending);
    window.draw(rectangleright[2], multiplicativeBlending);
    window.draw(rectangleright[3], multiplicativeBlending);
    window.draw(rectangleright[4], multiplicativeBlending);
    window.draw(rectangleright[5], multiplicativeBlending);
    window.draw(rectangleright[6], multiplicativeBlending);
    window.draw(rectangleright[7], multiplicativeBlending);


    //Rectangles for the upper side of the board .. starts from the left side
    rectangleup[0].setSize(sf::Vector2f(100, 100));
    rectangleup[0].setOutlineColor(outlineColor);
    rectangleup[0].setOutlineThickness(outlineThickness);
    rectangleup[0].setPosition(300, 50);

    rectangleup[1].setSize(sf::Vector2f(100, 100));
    rectangleup[1].setOutlineColor(outlineColor);
    rectangleup[1].setOutlineThickness(outlineThickness);
    rectangleup[1].setPosition(400, 50);

    rectangleup[2].setSize(sf::Vector2f(100, 100));
    rectangleup[2].setOutlineColor(outlineColor);
    rectangleup[2].setOutlineThickness(outlineThickness);
    rectangleup[2].setPosition(500, 50);

    rectangleup[3].setSize(sf::Vector2f(100, 100));
    rectangleup[3].setOutlineColor(outlineColor);
    rectangleup[3].setOutlineThickness(outlineThickness);
    rectangleup[3].setPosition(600, 50);

    rectangleup[4].setSize(sf::Vector2f(100, 100));
    rectangleup[4].setOutlineColor(outlineColor);
    rectangleup[4].setOutlineThickness(outlineThickness);
    rectangleup[4].setPosition(700, 50);

    rectangleup[5].setSize(sf::Vector2f(100, 100));
    rectangleup[5].setOutlineColor(outlineColor);
    rectangleup[5].setOutlineThickness(outlineThickness);
    rectangleup[5].setPosition(800, 50);

    rectangleup[6].setSize(sf::Vector2f(100, 100));
    rectangleup[6].setOutlineColor(outlineColor);
    rectangleup[6].setOutlineThickness(outlineThickness);
    rectangleup[6].setPosition(900, 50);

    rectangleup[7].setSize(sf::Vector2f(100, 100));
    rectangleup[7].setOutlineColor(outlineColor);
    rectangleup[7].setOutlineThickness(outlineThickness);
    rectangleup[7].setPosition(1000, 50);

    rectangleup[8].setSize(sf::Vector2f(100, 100));
    rectangleup[8].setOutlineColor(outlineColor);
    rectangleup[8].setOutlineThickness(outlineThickness);
    rectangleup[8].setPosition(1100, 50);

    window.draw(rectangleup[0], multiplicativeBlending);
    window.draw(rectangleup[1], multiplicativeBlending);
    window.draw(rectangleup[2], multiplicativeBlending);
    window.draw(rectangleup[3], multiplicativeBlending);
    window.draw(rectangleup[4], multiplicativeBlending);
    window.draw(rectangleup[5], multiplicativeBlending);
    window.draw(rectangleup[6], multiplicativeBlending);
    window.draw(rectangleup[7], multiplicativeBlending);
    window.draw(rectangleup[8], multiplicativeBlending);


    //Rectangles for the down side of the board .... start from the right side
    rectangledown[8].setSize(sf::Vector2f(100, 100));
    rectangledown[8].setOutlineColor(outlineColor);
    rectangledown[8].setOutlineThickness(outlineThickness);
    rectangledown[8].setPosition(300, 750);

    rectangledown[7].setSize(sf::Vector2f(100, 100));
    rectangledown[7].setOutlineColor(outlineColor);
    rectangledown[7].setOutlineThickness(outlineThickness);
    rectangledown[7].setPosition(400, 750);

    rectangledown[6].setSize(sf::Vector2f(100, 100));
    rectangledown[6].setOutlineColor(outlineColor);
    rectangledown[6].setOutlineThickness(outlineThickness);
    rectangledown[6].setPosition(500, 750);

    rectangledown[5].setSize(sf::Vector2f(100, 100));
    rectangledown[5].setOutlineColor(outlineColor);
    rectangledown[5].setOutlineThickness(outlineThickness);
    rectangledown[5].setPosition(600, 750);

    rectangledown[4].setSize(sf::Vector2f(100, 100));
    rectangledown[4].setOutlineColor(outlineColor);
    rectangledown[4].setOutlineThickness(outlineThickness);
    rectangledown[4].setPosition(700, 750);

    rectangledown[3].setSize(sf::Vector2f(100, 100));
    rectangledown[3].setOutlineColor(outlineColor);
    rectangledown[3].setOutlineThickness(outlineThickness);
    rectangledown[3].setPosition(800, 750);

    rectangledown[2].setSize(sf::Vector2f(100, 100));
    rectangledown[2].setOutlineColor(outlineColor);
    rectangledown[2].setOutlineThickness(outlineThickness);
    rectangledown[2].setPosition(900, 750);

    rectangledown[1].setSize(sf::Vector2f(100, 100));
    rectangledown[1].setOutlineColor(outlineColor);
    rectangledown[1].setOutlineThickness(outlineThickness);
    rectangledown[1].setPosition(1000, 750);

    rectangledown[0].setSize(sf::Vector2f(100, 100));
    rectangledown[0].setOutlineColor(outlineColor);
    rectangledown[0].setOutlineThickness(outlineThickness);
    rectangledown[0].setPosition(1100, 750);

    window.draw(rectangledown[0], multiplicativeBlending);
    window.draw(rectangledown[1], multiplicativeBlending);
    window.draw(rectangledown[2], multiplicativeBlending);
    window.draw(rectangledown[3], multiplicativeBlending);
    window.draw(rectangledown[4], multiplicativeBlending);
    window.draw(rectangledown[5], multiplicativeBlending);
    window.draw(rectangledown[6], multiplicativeBlending);
    window.draw(rectangledown[7], multiplicativeBlending);
    window.draw(rectangledown[8], multiplicativeBlending);

    //Court Rectangle 
    Courtrectangle.setSize(sf::Vector2f(150, 150));
    Courtrectangle.setOutlineColor(outlineColor);
    Courtrectangle.setOutlineThickness(outlineThickness);
    Courtrectangle.setPosition(400, 550);

    window.draw(Courtrectangle, multiplicativeBlending);

    //Luck Rectangle
    Luckrectangle.setSize(sf::Vector2f(150, 150));
    Luckrectangle.setOutlineColor(outlineColor);
    Luckrectangle.setOutlineThickness(outlineThickness);
    Luckrectangle.setPosition(950, 200);

    window.draw(Luckrectangle, multiplicativeBlending);
}


void GUI::loadtextbox(string textbox, sf::Vector2f mousepos)
{
    sf::Font font;
    font.loadFromFile(ARIAL_FONT);
    text.setFont(font); 
    text.setString(textbox);
    text.setCharacterSize(15);
    text.setFillColor(Red);
    text.setStyle(sf::Text::Bold);
    text.setPosition(mousepos),
    text.move(15, 15), //Moves the position of mousepos
    window.draw(text, sf::RenderStates());
}

void GUI::drawtextbox()
{
    if (textbox == 1)
    {
        loadtextbox("Dice",mouseposition);
    }

    if (textbox == 2)
    {
        loadtextbox("Save Button", mouseposition);
    }

    if (textbox == 3)
    {
        loadtextbox("Play Button", mouseposition);
    }
}

void GUI::settextbox(int x)
{
    textbox = x;
}

void GUI::setmousepos(sf::Vector2f x)
{
    mouseposition = x;
}