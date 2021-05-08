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
        sf::Vector2f mousePos2 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        sf::FloatRect diceBtnBounds2 = diceRect.getGlobalBounds();
        sf::FloatRect saveBtnBounds2 = rectangle[0].getGlobalBounds();
        sf::FloatRect playBtnBounds2 = playRect.getGlobalBounds();
        if (diceBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 1;
        }
        else if (saveBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 2;
        }
        else if (playBtnBounds2.contains(mousePos2) && event.TouchEnded)
        {
            textbox = 3;
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
    playRect.setPosition(43, 94);
    
    rectangle[0].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[0].setOutlineThickness(outlineThickness);
    rectangle[0].setOutlineColor(outlineColor);
    rectangle[0].setPosition(43, 194);

    window.draw(playRect,multiplicativeBlending);
    window.draw(rectangle[0], multiplicativeBlending);
    rectangle[0].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[0].setOutlineThickness(outlineThickness);
    rectangle[0].setOutlineColor(outlineColor);
    rectangle[0].setPosition(54, 50);

    window.draw(rectangle[0],multiplicativeBlending);

    rectangle[1].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[1].setOutlineThickness(outlineThickness);
    rectangle[1].setOutlineColor(outlineColor);
    rectangle[1].setPosition(54, 150);

    window.draw(rectangle[1], multiplicativeBlending);

    rectangle[2].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[2].setOutlineThickness(outlineThickness);
    rectangle[2].setOutlineColor(outlineColor);
    rectangle[2].setPosition(54, 250);

    window.draw(rectangle[2], multiplicativeBlending);

    rectangle[3].setSize(sf::Vector2f(65.0f, 65.0f));
    rectangle[3].setOutlineThickness(outlineThickness);
    rectangle[3].setOutlineColor(outlineColor);
    rectangle[3].setPosition(54, 350);

    window.draw(rectangle[3], multiplicativeBlending);
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

               //LUCK AND COURT RECT
               sf::Vertex(sf::Vector2f(950,200), outlineColor),
               sf::Vertex(sf::Vector2f(950, BOARD_HEIGHT - 550), outlineColor),
               sf::Vertex(sf::Vector2f(1100,200), outlineColor),
               sf::Vertex(sf::Vector2f(1100, BOARD_HEIGHT - 550), outlineColor),
               sf::Vertex(sf::Vector2f(400,550), outlineColor),
               sf::Vertex(sf::Vector2f(400, BOARD_HEIGHT - 200), outlineColor),
               sf::Vertex(sf::Vector2f(550,550), outlineColor),
               sf::Vertex(sf::Vector2f(550, BOARD_HEIGHT - 200), outlineColor),
        };
        window.draw(line, 70, sf::Lines);
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

          //LUCK AND COURT RECT
          sf::Vertex(sf::Vector2f(950, 200), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 400, 200), outlineColor),
          sf::Vertex(sf::Vector2f(950, 350), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 400, 350), outlineColor),
          sf::Vertex(sf::Vector2f(400, 550), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 950, 550), outlineColor),
          sf::Vertex(sf::Vector2f(400, 700), outlineColor),
          sf::Vertex(sf::Vector2f(BOARD_WIDTH - 950, 700), outlineColor),


        };
        window.draw(line, 50, sf::Lines);
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
    if (numberOfRolling <= 100 && numberOfRolling - lastRoll == 8)
    {
       int  dicePicNumber = rand() % 6;
        diceRect.setTexture(&diceTexture[dicePicNumber]);
        lastRoll = numberOfRolling;
       
    }
   //draw the new side
   window.draw(diceRect);

   if (numberOfRolling <= 100) numberOfRolling++;
}

    //function to draw rectangles
void GUI::drawrect()
{
    //change the size in GUI.h first to increase the number of rectangles
   /* rectangle[0].setSize(sf::Vector2f(200, 200));
    rectangle[0].setFillColor(outlineColor);
    rectangle[0].setOutlineThickness(outlineThickness);
    rectangle[0].setPosition(300, 400);

    rectangle[1].setSize(sf::Vector2f(200, 200));
    rectangle[1].setFillColor(sf::Color::Black);
    rectangle[1].setOutlineThickness(outlineThickness);
    rectangle[1].setPosition(600, 400);
    window.draw(rectangle[0]);
    window.draw(rectangle[1]);*/
}


void GUI::loadtextbox(string textbox)
{
    sf::Font font;
    font.loadFromFile(ARIAL_FONT);
    text.setFont(font); 
    text.setString(textbox);
    text.setCharacterSize(15);
    text.setFillColor(outlineColor);
    text.setStyle(sf::Text::Bold);
    text.setPosition(50, 800);
    window.draw(text, sf::RenderStates());
}

void GUI::drawtextbox()
{
    if (textbox == 1)
    {
        loadtextbox("Dice" );
    }

    if (textbox == 2)
    {
        loadtextbox("Save Button");
    }

    if (textbox == 3)
    {
        loadtextbox("Play Button");
    }
}

void GUI::settextbox(int x)
{
    textbox = x;
}