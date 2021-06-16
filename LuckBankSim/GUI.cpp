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
   loadsounds();
   C.Readcities(C);
   L.ReadLuckCourt(L);
   Co.ReadLuckCourt(Co);
}

// Function for getting control on any event such as keyboard or mouse 
void GUI::getControls(bool& exit)
{
    sf::Event event;
    //check the window events
    while (window.pollEvent(event)) 
    {
        if (event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect Jerusalem = Board[1].getGlobalBounds();
            if (Jerusalem.contains(mousePos) && messagePrompt.isOpen() == false && playbuttonbool == true)
            {
                textbox = 8;
            }
        }

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect Luckrect = Luckrectangle.getGlobalBounds();
            sf::FloatRect Courtrect = Courtrectangle.getGlobalBounds();

            if (Luckrect.contains(mousePos))
            {
                luckcards = rand() % 15;
                drawluck(luckcards);
            }

            if (Courtrect.contains(mousePos))
            {
                courcards = rand() % 15;
                drawcourt(courcards);
            }
        }

        // text box near the mouse icon, Touch with cursor to display !
        if (event.TouchEnded)
        {
            sf::Vector2f mousePos2 = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect diceBtnBounds2 = diceRect.getGlobalBounds();
            sf::FloatRect saveBtnBounds2 = rectangle[0].getGlobalBounds();
            sf::FloatRect playBtnBounds2 = playRect.getGlobalBounds();
            sf::FloatRect player1 = Player[3].getGlobalBounds();
            sf::FloatRect player2 = Player[2].getGlobalBounds();
            sf::FloatRect player3 = Player[1].getGlobalBounds();
            sf::FloatRect player4 = Player[0].getGlobalBounds();

            if (diceBtnBounds2.contains(mousePos2))
            {
                textbox = 1;
                setmousepos(mousePos2);
            }
            else if (saveBtnBounds2.contains(mousePos2))
            {
                textbox = 2;
                setmousepos(mousePos2);
            }
            else if (playBtnBounds2.contains(mousePos2))
            {
                textbox = 3;
                setmousepos(mousePos2);
            }
            else if (player1.contains(mousePos2))
            {
                textbox = 4;
            }
            else if (player2.contains(mousePos2))
            {
                if (numofplayer == "3")
                {
                    textbox = 4;
                }
                else if (numofplayer == "4")
                {
                    textbox = 5;
                }
            }
            else if (player3.contains(mousePos2))
            {
                if (numofplayer == "2")
                {
                    textbox = 4;
                }
                else if (numofplayer == "3")
                {
                    textbox = 5;
                }
                else if (numofplayer == "4")
                {
                    textbox = 6;
                }
            }
            else if (player4.contains(mousePos2))
            {
                if (numofplayer == "2")
                {
                    textbox = 5;
                }
                else if (numofplayer == "3")
                {
                    textbox = 6;
                }
                else if (numofplayer == "4")
                {
                    textbox = 7;
                }
            }
            else
            {
                textbox = 0;
            }
        }

        //if ESC button is pressed the game window is closed!
       exit = sf::Keyboard::isKeyPressed(sf::Keyboard::Escape);

      
       // check if the closed button of window is closed
       if (event.type == event.Closed)
       {
           window.close();
       }
       //check if the left button of the mouse is pressed
       if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
            sf::FloatRect diceBtnBounds = diceRect.getGlobalBounds();
            sf::FloatRect playBtnBounds = playRect.getGlobalBounds();
            sf::FloatRect saveBtnBounds = rectangle[0].getGlobalBounds();

            //if the mouse left button is pressed on the dice button, the side is changed
            if (diceBtnBounds.contains(mousePos))
            {
                if (diceIsRolled == 0)
                {
                    lastRoll = 0;
                    numberOfRolling = 0;
                }  
                random();
            }

            //if mouse left button is pressed on the play button, The message box is appread
            if (playBtnBounds.contains(mousePos))
            {
                isopen2 = false;
                playsound.setBuffer(buffers[0]);
                playsound.play();
                playbutton(true);
                sf::ContextSettings settings;
                settings.antialiasingLevel = 8;  // Remove this line if the Board was too laggy
                messagePrompt.create(sf::VideoMode(265, 166), "Players", sf::Style::Titlebar, settings);
                //userinput.create(sf::VideoMode(265, 166), "Avatar", sf::Style::Titlebar, settings);
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
                sf::ContextSettings settings;
                settings.antialiasingLevel = 8;
                messagePrompt2.create(sf::VideoMode(265, 166), "Icons", sf::Style::Titlebar, settings);
                //messagePrompt2.setPosition(messagePrompt2.getPosition() + sf::Vector2i(50, 50));
                messagePrompt2.setVerticalSyncEnabled(true);
                messagePrompt.close();
            }

        }
    }//loop of messagebox events


    while (messagePrompt2.pollEvent(event))
    {
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2f mousePos = messagePrompt2.mapPixelToCoords(sf::Mouse::getPosition(messagePrompt2));
            sf::FloatRect okButtonBounds = okButton2.getGlobalBounds();

            if (okButtonBounds.contains(mousePos))
            {
                okButton2.setPosition(0,0);
                once2 = true;
                once = false;
                loop = 0;
                temp = 0;
                turns = 0;
                movep1 = 0;
                movep2 = 0;
                movep3 = 0;
                movep4 = 0;
                checkmessagebox2 = "";
                messagePrompt2.close();
                if (once2 == true)
                {
                    loadavatars();
                    pressed1 = false;
                    pressed2 = false;
                    pressed3 = false;
                    pressed4 = false;
                }
                isopen2 = true;
            }
        }
    }

    //while (userinput.pollEvent(event))
    //{
    //    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    //    {
    //        sf::Vector2f mousePos = userinput.mapPixelToCoords(sf::Mouse::getPosition(userinput));
    //        sf::FloatRect okButtonBounds = okButton.getGlobalBounds();

    //        if (okButtonBounds.contains(mousePos))
    //        {
    //            userinput.close();
    //        }

    //    }
    //}
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
    if (playbuttonbool == true && isopen2 == true)
    {
        loadText("Please click here to roll the dice", 628.0f, 470.0f);
    }
    //loadText("TEST", 240, 500);
}

//this function is invoked from messagebox object to popup the message box
void GUI::drawMessageBox()
{
    sf::Font arialFont;
    arialFont.loadFromFile(ARIAL_FONT);
    sf::Text messageTitle;
    messageTitle.setString("Number Of Players");
    messageTitle.setCharacterSize(25);
    messageTitle.setFont(arialFont);
    messageTitle.setPosition(15.0f, 15.0f);
    messageTitle.setFillColor(outlineColor);

    sf::Text messageTitle2;
    messageTitle2.setString("You Chose : ");
    messageTitle2.setCharacterSize(15);
    messageTitle2.setFont(arialFont);
    messageTitle2.setPosition(15.0f, 80.0f);
    messageTitle2.setFillColor(outlineColor);

    sf::Text messageTitle3;
    messageTitle3.setString(numofplayer);
    messageTitle3.setCharacterSize(15);
    messageTitle3.setFont(arialFont);
    messageTitle3.setPosition(105.0f, 80.0f);
    messageTitle3.setFillColor(outlineColor);
    messageTitle3.setStyle(sf::Text::Bold);


   /* sf::Event event;
    playerText.setCharacterSize(25);
    playerText.setFont(arialFont);
    playerText.setPosition(15, 50);
    playerText.setFillColor(outlineColor);
    std::string playerInput;

    while (messagePrompt.pollEvent(event))
    {
        if (event.type == sf::Event::TextEntered)
        {
                playerInput += event.text.unicode;
                if (stoi(playerInput) >= 1 && stoi(playerInput) <= 4)
                {
                    numofplayer = stoi(playerInput);
                }
                else
                {
                    playerText.setString("Choose Between 1 and 4");
                }
                playerText.setString(playerInput);
        }
    }*/

   
    sf::Text Player2;
    sf::Text Player3;
    sf::Text Player4;

    Player2.setString("2");
    Player2.setCharacterSize(25);
    Player2.setFont(arialFont);
    Player2.setPosition(50.0f, 50.0f);
    Player2.setFillColor(outlineColor);

    Player3.setString("3");
    Player3.setCharacterSize(25);
    Player3.setFont(arialFont);
    Player3.setPosition(125.0f, 50.0f);
    Player3.setFillColor(outlineColor);

    Player4.setString("4");
    Player4.setCharacterSize(25);
    Player4.setFont(arialFont);
    Player4.setPosition(200.0f, 50.0f);
    Player4.setFillColor(outlineColor);

    sf::Event event;
    while (messagePrompt.pollEvent(event))
    {
        sf::Vector2f mousePos = messagePrompt.mapPixelToCoords(sf::Mouse::getPosition(messagePrompt));
        sf::FloatRect p2 = players_2.getGlobalBounds();
        sf::FloatRect p3 = players_3.getGlobalBounds();
        sf::FloatRect p4 = players_4.getGlobalBounds();
        if (event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            if (p2.contains(mousePos))
            {
                numofplayer = Player2.getString();
            }

            if (p3.contains(mousePos))
            {
                numofplayer = Player3.getString();
            }

            if (p4.contains(mousePos))
            {
                numofplayer = Player4.getString();
            }
        }
    }

    players_2.setSize(sf::Vector2f(20.0f, 26.0f));
    players_2.setPosition(48.0f, 53.0f);
    players_2.setOutlineThickness(0);
    players_2.setOutlineColor(outlineColor);

    players_3.setSize(sf::Vector2f(20.0f, 26.0f));
    players_3.setPosition(123.0f, 53.0f);
    players_3.setOutlineThickness(0);
    players_3.setOutlineColor(outlineColor);

    players_4.setSize(sf::Vector2f(20.0f, 26.0f));
    players_4.setPosition(198.0f, 53.0f);
    players_4.setOutlineThickness(0);
    players_4.setOutlineColor(outlineColor);

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
        messagePrompt.draw(messageTitle2);
        messagePrompt.draw(messageTitle3);
        messagePrompt.draw(okButton);
        messagePrompt.draw(players_2);
        messagePrompt.draw(players_3);
        messagePrompt.draw(players_4);
        messagePrompt.draw(Player2);
        messagePrompt.draw(Player3);
        messagePrompt.draw(Player4);

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
    if (playbuttonbool == true && isopen2 == true)
    {
        // decrease the second condition to see the suffeling among dice sides ex: numberOfRolling - lastRoll == 8
        if (numberOfRolling <= 10 && numberOfRolling - lastRoll == 2)
        {
            int dicenumber = rand() % 6;
            diceRect.setTexture(&diceTexture[dicenumber]);
            diceRect.setTexture(&diceTexture[roll]);
            lastRoll = numberOfRolling;
        }
        //draw the new side
        window.draw(diceRect, multiplicativeBlending);

        if (numberOfRolling <= 10) numberOfRolling++;
    }
}

    //function to draw rectangles
void GUI::drawrect()
{
    //change the size in GUI.h first to increase the number of rectangles
    //Drawing Rectangles of the board

    //Rectangles of the left side of the board .... starts from the left down side
    Board[0].setSize(sf::Vector2f(100, 100));
    Board[0].setOutlineColor(outlineColor);
    Board[0].setOutlineThickness(outlineThickness);
    Board[0].setPosition(200, 750);

    Board[1].setSize(sf::Vector2f(100, 100));
    Board[1].setOutlineColor(outlineColor);
    Board[1].setOutlineThickness(outlineThickness);
    Board[1].setPosition(200, 650);

    Board[2].setSize(sf::Vector2f(100, 100));
    Board[2].setOutlineColor(outlineColor);
    Board[2].setOutlineThickness(outlineThickness);
    Board[2].setPosition(200, 550);

    Board[3].setSize(sf::Vector2f(100, 100));
    Board[3].setOutlineColor(outlineColor);
    Board[3].setOutlineThickness(outlineThickness);
    Board[3].setPosition(200, 450);

    Board[4].setSize(sf::Vector2f(100, 100));
    Board[4].setOutlineColor(outlineColor);
    Board[4].setOutlineThickness(outlineThickness);
    Board[4].setPosition(200, 350);

    Board[5].setSize(sf::Vector2f(100, 100));
    Board[5].setOutlineColor(outlineColor);
    Board[5].setOutlineThickness(outlineThickness);
    Board[5].setPosition(200, 250);

    Board[6].setSize(sf::Vector2f(100, 100));
    Board[6].setOutlineColor(outlineColor);
    Board[6].setOutlineThickness(outlineThickness);
    Board[6].setPosition(200, 150);

    Board[7].setSize(sf::Vector2f(100, 100));
    Board[7].setOutlineColor(outlineColor);
    Board[7].setOutlineThickness(outlineThickness);
    Board[7].setPosition(200, 50);


    window.draw(Board[0],multiplicativeBlending);
    window.draw(Board[1], multiplicativeBlending);
    window.draw(Board[2], multiplicativeBlending);
    window.draw(Board[3], multiplicativeBlending);
    window.draw(Board[4], multiplicativeBlending);
    window.draw(Board[5], multiplicativeBlending);
    window.draw(Board[6], multiplicativeBlending);
    window.draw(Board[7], multiplicativeBlending);


    //Rectangles of the Right side of the board .... starts from down
    Board[24].setSize(sf::Vector2f(100, 100));
    Board[24].setOutlineColor(outlineColor);
    Board[24].setOutlineThickness(outlineThickness);
    Board[24].setPosition(1200, 750);

    Board[23].setSize(sf::Vector2f(100, 100));
    Board[23].setOutlineColor(outlineColor);
    Board[23].setOutlineThickness(outlineThickness);
    Board[23].setPosition(1200, 650);

    Board[22].setSize(sf::Vector2f(100, 100));
    Board[22].setOutlineColor(outlineColor);
    Board[22].setOutlineThickness(outlineThickness);
    Board[22].setPosition(1200, 550);

    Board[21].setSize(sf::Vector2f(100, 100));
    Board[21].setOutlineColor(outlineColor);
    Board[21].setOutlineThickness(outlineThickness);
    Board[21].setPosition(1200, 450);

    Board[20].setSize(sf::Vector2f(100, 100));
    Board[20].setOutlineColor(outlineColor);
    Board[20].setOutlineThickness(outlineThickness);
    Board[20].setPosition(1200, 350);

    Board[19].setSize(sf::Vector2f(100, 100));
    Board[19].setOutlineColor(outlineColor);
    Board[19].setOutlineThickness(outlineThickness);
    Board[19].setPosition(1200, 250);

    Board[18].setSize(sf::Vector2f(100, 100));
    Board[18].setOutlineColor(outlineColor);
    Board[18].setOutlineThickness(outlineThickness);
    Board[18].setPosition(1200, 150);

    Board[17].setSize(sf::Vector2f(100, 100));
    Board[17].setOutlineColor(outlineColor);
    Board[17].setOutlineThickness(outlineThickness);
    Board[17].setPosition(1200, 50);

    window.draw(Board[17], multiplicativeBlending);
    window.draw(Board[18], multiplicativeBlending);
    window.draw(Board[19], multiplicativeBlending);
    window.draw(Board[20], multiplicativeBlending);
    window.draw(Board[21], multiplicativeBlending);
    window.draw(Board[22], multiplicativeBlending);
    window.draw(Board[23], multiplicativeBlending);
    window.draw(Board[24], multiplicativeBlending);


    //Rectangles for the upper side of the board .. starts from the left side
    Board[8].setSize(sf::Vector2f(100, 100));
    Board[8].setOutlineColor(outlineColor);
    Board[8].setOutlineThickness(outlineThickness);
    Board[8].setPosition(300, 50);

    Board[9].setSize(sf::Vector2f(100, 100));
    Board[9].setOutlineColor(outlineColor);
    Board[9].setOutlineThickness(outlineThickness);
    Board[9].setPosition(400, 50);

    Board[10].setSize(sf::Vector2f(100, 100));
    Board[10].setOutlineColor(outlineColor);
    Board[10].setOutlineThickness(outlineThickness);
    Board[10].setPosition(500, 50);

    Board[11].setSize(sf::Vector2f(100, 100));
    Board[11].setOutlineColor(outlineColor);
    Board[11].setOutlineThickness(outlineThickness);
    Board[11].setPosition(600, 50);

    Board[12].setSize(sf::Vector2f(100, 100));
    Board[12].setOutlineColor(outlineColor);
    Board[12].setOutlineThickness(outlineThickness);
    Board[12].setPosition(700, 50);

    Board[13].setSize(sf::Vector2f(100, 100));
    Board[13].setOutlineColor(outlineColor);
    Board[13].setOutlineThickness(outlineThickness);
    Board[13].setPosition(800, 50);

    Board[14].setSize(sf::Vector2f(100, 100));
    Board[14].setOutlineColor(outlineColor);
    Board[14].setOutlineThickness(outlineThickness);
    Board[14].setPosition(900, 50);

    Board[15].setSize(sf::Vector2f(100, 100));
    Board[15].setOutlineColor(outlineColor);
    Board[15].setOutlineThickness(outlineThickness);
    Board[15].setPosition(1000, 50);

    Board[16].setSize(sf::Vector2f(100, 100));
    Board[16].setOutlineColor(outlineColor);
    Board[16].setOutlineThickness(outlineThickness);
    Board[16].setPosition(1100, 50);

    window.draw(Board[8], multiplicativeBlending);
    window.draw(Board[9], multiplicativeBlending);
    window.draw(Board[10], multiplicativeBlending);
    window.draw(Board[11], multiplicativeBlending);
    window.draw(Board[12], multiplicativeBlending);
    window.draw(Board[13], multiplicativeBlending);
    window.draw(Board[14], multiplicativeBlending);
    window.draw(Board[15], multiplicativeBlending);
    window.draw(Board[16], multiplicativeBlending);


    //Rectangles for the down side of the board .... start from the right side
    Board[33].setSize(sf::Vector2f(100, 100));
    Board[33].setOutlineColor(outlineColor);
    Board[33].setOutlineThickness(outlineThickness);
    Board[33].setPosition(300, 750);

    Board[32].setSize(sf::Vector2f(100, 100));
    Board[32].setOutlineColor(outlineColor);
    Board[32].setOutlineThickness(outlineThickness);
    Board[32].setPosition(400, 750);

    Board[31].setSize(sf::Vector2f(100, 100));
    Board[31].setOutlineColor(outlineColor);
    Board[31].setOutlineThickness(outlineThickness);
    Board[31].setPosition(500, 750);

    Board[30].setSize(sf::Vector2f(100, 100));
    Board[30].setOutlineColor(outlineColor);
    Board[30].setOutlineThickness(outlineThickness);
    Board[30].setPosition(600, 750);

    Board[29].setSize(sf::Vector2f(100, 100));
    Board[29].setOutlineColor(outlineColor);
    Board[29].setOutlineThickness(outlineThickness);
    Board[29].setPosition(700, 750);

    Board[28].setSize(sf::Vector2f(100, 100));
    Board[28].setOutlineColor(outlineColor);
    Board[28].setOutlineThickness(outlineThickness);
    Board[28].setPosition(800, 750);

    Board[27].setSize(sf::Vector2f(100, 100));
    Board[27].setOutlineColor(outlineColor);
    Board[27].setOutlineThickness(outlineThickness);
    Board[27].setPosition(900, 750);

    Board[26].setSize(sf::Vector2f(100, 100));
    Board[26].setOutlineColor(outlineColor);
    Board[26].setOutlineThickness(outlineThickness);
    Board[26].setPosition(1000, 750);

    Board[25].setSize(sf::Vector2f(100, 100));
    Board[25].setOutlineColor(outlineColor);
    Board[25].setOutlineThickness(outlineThickness);
    Board[25].setPosition(1100, 750);

    window.draw(Board[25], multiplicativeBlending);
    window.draw(Board[26], multiplicativeBlending);
    window.draw(Board[27], multiplicativeBlending);
    window.draw(Board[28], multiplicativeBlending);
    window.draw(Board[29], multiplicativeBlending);
    window.draw(Board[30], multiplicativeBlending);
    window.draw(Board[31], multiplicativeBlending);
    window.draw(Board[32], multiplicativeBlending);
    window.draw(Board[33], multiplicativeBlending);

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

// text box Near the mouse Cursor
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

    if (textbox == 4)
    {
        playerdata("Player 1");
    }

    if (textbox == 5)
    {
        playerdata("Player 2");
    }

    if (textbox == 6)
    {
        playerdata("Player 3");
    }

    if (textbox == 7)
    {
        playerdata("Player 4");
    }

    if (textbox == 8)
    {
        if (isopen2 == true && playbuttonbool == true)
        {
            citydata(C.Name[0], C.Price[0], C.PassingFees[0], C.getparkprice(0), C.getparkfees(0), C.getrestprice(0), C.getrestfees(0), C.getmarketprice(0), C.getmarketfees(0),1);
        }
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

void GUI::player()
{
    if (isopen2 == true)
    {
        sf::Texture p1, p2, p3, p4;
        if (numofplayer == "2")
        {
            p1.loadFromFile("Images\\" + icons[1]);
            Player[0].setSize(sf::Vector2f(100, 100));
            Player[0].setOutlineColor(outlineColor);
            Player[0].setOutlineThickness(outlineThickness);
            Player[0].setPosition(50, 750);
            Player[0].setTexture(&p1);

            p2.loadFromFile("Images\\" + icons[0]);
            Player[1].setSize(sf::Vector2f(100, 100));
            Player[1].setOutlineColor(outlineColor);
            Player[1].setOutlineThickness(outlineThickness);
            Player[1].setPosition(50, 650);
            Player[1].setTexture(&p2);

            window.draw(Player[0], multiplicativeBlending);
            window.draw(Player[1], multiplicativeBlending);
        }

        else if (numofplayer == "3")
        {
            p1.loadFromFile("Images\\" + icons[2]);
            Player[0].setSize(sf::Vector2f(100, 100));
            Player[0].setOutlineColor(outlineColor);
            Player[0].setOutlineThickness(outlineThickness);
            Player[0].setPosition(50, 750);
            Player[0].setTexture(&p1);

            p2.loadFromFile("Images\\" + icons[1]);
            Player[1].setSize(sf::Vector2f(100, 100));
            Player[1].setOutlineColor(outlineColor);
            Player[1].setOutlineThickness(outlineThickness);
            Player[1].setPosition(50, 650);
            Player[1].setTexture(&p2);

            p3.loadFromFile("Images\\" + icons[0]);
            Player[2].setSize(sf::Vector2f(100, 100));
            Player[2].setOutlineColor(outlineColor);
            Player[2].setOutlineThickness(outlineThickness);
            Player[2].setPosition(50, 550);
            Player[2].setTexture(&p3);

            window.draw(Player[0], multiplicativeBlending);
            window.draw(Player[1], multiplicativeBlending);
            window.draw(Player[2], multiplicativeBlending);
        }

        else if (numofplayer == "4")
        {
            p1.loadFromFile("Images\\" + icons[3]);
            Player[0].setSize(sf::Vector2f(100, 100));
            Player[0].setOutlineColor(outlineColor);
            Player[0].setOutlineThickness(outlineThickness);
            Player[0].setPosition(50, 750);
            Player[0].setTexture(&p1);

            p2.loadFromFile("Images\\" + icons[2]);
            Player[1].setSize(sf::Vector2f(100, 100));
            Player[1].setOutlineColor(outlineColor);
            Player[1].setOutlineThickness(outlineThickness);
            Player[1].setPosition(50, 650);
            Player[1].setTexture(&p2);

            p3.loadFromFile("Images\\" + icons[1]);
            Player[2].setSize(sf::Vector2f(100, 100));
            Player[2].setOutlineColor(outlineColor);
            Player[2].setOutlineThickness(outlineThickness);
            Player[2].setPosition(50, 550);
            Player[2].setTexture(&p3);

            p4.loadFromFile("Images\\" + icons[0]);
            Player[3].setSize(sf::Vector2f(100, 100));
            Player[3].setOutlineColor(outlineColor);
            Player[3].setOutlineThickness(outlineThickness);
            Player[3].setPosition(50, 450);
            Player[3].setTexture(&p4);

            window.draw(Player[0], multiplicativeBlending);
            window.draw(Player[1], multiplicativeBlending);
            window.draw(Player[2], multiplicativeBlending);
            window.draw(Player[3], multiplicativeBlending);
        }
    }
}

// Rectangle to display the player and board info
void GUI::playerdata(string x)
{
    sf::Font font;
    font.loadFromFile(ARIAL_FONT);
    text.setFont(font);
    text.setString(x);
    text.setCharacterSize(15);
    text.setFillColor(outlineColor);
    text.setStyle(sf::Text::Bold);
    text.setPosition(1400, 100),

    //playerdata.setsize(sf::vector2f(150, 150));
    //playerdata.setoutlinethickness(0); // can be outlinethickness to show border
    //playerdata.setoutlinecolor(outlinecolor);
    //playerdata.setposition(1400, 100);

    //window.draw(Playerdata, multiplicativeBlending);
    window.draw(text, sf::RenderStates());
}

void GUI::playbutton(bool x)
{
    playbuttonbool = x;
}

void GUI::ava(bool x)
{
    drawavatarbool = x;
}

void GUI::citydata(string name, int price, int passingfees, int Garageprice, int Garagefees, int restprice, int restfees, int marketprice, int marketfees, int index)
{
    sf::Font font;
    //sf::String price;
    //sf::String passingfees;
    //sf::String Garageprice;
    //sf::String Garagefees;
    //sf::String restprice;
    //sf::String restfees;
    //sf::String marketprice;
    //sf::String marketfees;
}

//drawing cities on board with Auto Functions
void GUI::DrawCity()
{
    if (isopen2 == true && playbuttonbool == true)
    {
        for (int i = 0, name = 0; name < C.Name.size(); i++, name++)
        {
            sf::Text price;
            sf::Font font;
            sf::Text Ci;
            sf::Color citycolor;

            if (C.getgroup(name) == 1)
            {
                citycolor = sf::Color::Blue;
            }
            else  if (C.getgroup(name) == 2)
            {
                citycolor = sf::Color::Green;
            }
            else  if (C.getgroup(name) == 3)
            {
                citycolor = sf::Color::Red;
            }
            else  if (C.getgroup(name) == 4)
            {
                citycolor = sf::Color::Color(255, 64, 70);
            }
            else  if (C.getgroup(name) == 5)
            {
                citycolor = sf::Color::Color(255, 154, 157);
            }
            else  if (C.getgroup(name) == 6)
            {
                citycolor = sf::Color::Color(178, 77, 80);
            }
            else  if (C.getgroup(name) == 7)
            {
                citycolor = sf::Color::Color(255, 213, 0);
            }
            else  if (C.getgroup(name) == 8)
            {
                citycolor = sf::Color::Color(159, 140, 44);
            }
            else  if (C.getgroup(name) == 9)
            {
                citycolor = sf::Color::Color(1, 180, 255);
            }
            if (i == 0 || i == 3 || i == 7 || i == 10 || i == 12 || i == 14 || i == 17 || i == 20 || i == 24 || i == 29 || i == 31)
            {
                i = i + 1;
                font.loadFromFile(ARIAL_FONT);
                Ci.setFont(font);
                Ci.setString(C.Name[name]);
                Ci.setCharacterSize(15);
                Ci.setFillColor(citycolor);
                Ci.setStyle(sf::Text::Bold);
                Ci.setPosition(Board[i].getPosition());

                price.setFont(font);
                price.setString(to_string(C.Price[name]));
                price.setCharacterSize(15);
                price.setFillColor(outlineColor);
                price.setStyle(sf::Text::Bold);
                price.setPosition(Board[i].getPosition());

                if (i >= 7 && i <= 17)
                {
                    Ci.setRotation(180);
                    price.setRotation(180);
                    Ci.move(90, 90);
                    price.move(55, 55);
                }
                else if (i >= 18 && i <= 24)
                {
                    Ci.setRotation(270);
                    price.setRotation(270);
                    Ci.move(0, 80);
                    price.move(50, 65);
                }
                else if (i >= 24 && i <= 34)
                {
                    Ci.setRotation(0);
                    price.setRotation(0);
                    Ci.move(25, 0);
                    price.move(38, 35);
                }
                else
                {
                    Ci.setRotation(90);
                    price.setRotation(90);
                    Ci.move(100, 20);
                    price.move(50, 35);
                }

                window.draw(price, sf::RenderStates()),
                    window.draw(Ci, sf::RenderStates());

            }
            else
            {
                font.loadFromFile(ARIAL_FONT);
                Ci.setFont(font);
                Ci.setString(C.Name[name]);
                Ci.setCharacterSize(15);
                Ci.setFillColor(citycolor);
                Ci.setStyle(sf::Text::Bold);
                Ci.setPosition(Board[i].getPosition());

                price.setFont(font);
                price.setString(to_string(C.Price[name]));
                price.setCharacterSize(15);
                price.setFillColor(outlineColor);
                price.setStyle(sf::Text::Bold);
                price.setPosition(Board[i].getPosition());

                if (i >= 7 && i <= 17)
                {
                    Ci.setRotation(180);
                    price.setRotation(180);
                    Ci.move(90, 90);
                    price.move(55, 55);
                }
                else if (i >= 18 && i <= 24)
                {
                    Ci.setRotation(270);
                    price.setRotation(270);
                    Ci.move(0, 80);
                    price.move(50, 65);
                }
                else if (i >= 24 && i <= 34)
                {
                    Ci.setRotation(0);
                    price.setRotation(0);
                    Ci.move(25, 0);
                    price.move(38, 35);
                }
                else
                {
                    Ci.setRotation(90);
                    price.setRotation(90);
                    Ci.move(100, 20);
                    price.move(50, 35);
                }


                window.draw(price, sf::RenderStates()),
                window.draw(Ci, sf::RenderStates());
            }
        }
    }
}

//void GUI::input()
//{
//    sf::Font arialFont;
//    sf::Texture texture;
//    sf::Sprite sprite;
//    arialFont.loadFromFile(ARIAL_FONT);
//    texture.loadFromFile("Images\\Icon1.jpeg");
//    sprite.setTexture(texture);
//    sprite.setPosition(100, 50); // offset relative to the original position(0,0)
//    sprite.scale(sf::Vector2f(0.3, 0.3)); // factor relative to the current scale
//    userinput.draw(sprite);
//
//
//    sf::Text messageTitle;
//    messageTitle.setString("Choose Avatars :");
//    messageTitle.setCharacterSize(25);
//    messageTitle.setFont(arialFont);
//    messageTitle.setPosition(15.0f, 15.0f);
//    messageTitle.setFillColor(outlineColor);
//
//
//    sf::Texture okButtonTexture;
//    okButtonTexture.loadFromFile("Images\\ok.png");
//    okButton.setSize(sf::Vector2f(40.0f, 40.0f));
//    okButton.setTexture(&okButtonTexture);
//    okButton.setPosition(120.0f, 125.0f);
//    okButton.setOutlineThickness(outlineThickness);
//    okButton.setOutlineColor(outlineColor);
//    okButtonTexture.setSmooth(true);
//
//
//    userinput.clear(backgroundColor);
//
//    userinput.draw(messageTitle);
//    userinput.draw(sprite);
//    userinput.draw(okButton);
//
//    userinput.display();



    /*sf::Event event;
    playertext.setcharactersize(25);
    playertext.setfont(arialfont);
    playertext.setposition(15, 50);
    playertext.setfillcolor(outlinecolor);
    std::string playerinput;

    sf::texture okbuttontexture;
    okbuttontexture.loadfromfile("images\\ok.png");
    okbutton.setsize(sf::vector2f(40.0f, 40.0f));
    okbutton.settexture(&okbuttontexture);
    okbutton.setposition(120.0f, 125.0f);
    okbutton.setoutlinethickness(outlinethickness);
    okbutton.setoutlinecolor(outlinecolor);
    okbuttontexture.setsmooth(true);

    while (userinput.pollevent(event))
    {
        if (event.type == sf::event::textentered)
        {
            playerinput += event.text.unicode;
            if (stoi(playerinput) >= 1 && stoi(playerinput) <= 4)
            {
                numofplayer = stoi(playerinput);
            }
            else
            {
                playertext.setstring("choose between 1 and 4");
            }
            playertext.setstring(playerinput);
        }
    }
    userinput.clear(backgroundcolor);
    userinput.draw(okbutton);
    userinput.draw(playertext);
    userinput.display();*/
//}

void GUI::drawluck(int index)
{
    drawluckcourt("BankOfLuckFiles\\Luck-Court Card\\" + L.Location[index], 950, 200, 0.5, 0.5);
    cout << index;
}

void GUI::drawcourt(int index)
{
    drawluckcourt("BankOfLuckFiles\\Luck-Court Card\\" + Co.Location[index], 400, 550, 0.5, 0.5);
}

void GUI::drawluckcourt(std::string path, float setPositionX, float setPositionY, float scaleX, float scaleY)
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


    window.draw(sprite);
    //add delay here
}

// drawing the avatars of number of players
void GUI::drawavatar()
{
    if (isopen2 == true && playbuttonbool == true)
    {
        int num = stoi(numofplayer);

        for (int j = 0; j < num; j++)
        {
            window.draw(Avatar[j]);
        }
        ava(true);
    }
}


// Loading the Avatars
void GUI::loadavatars()
{
    position = sf::Vector2f(200, 750);

    for (int i = 0; i < stoi(numofplayer); i++)
    {
        avata[i].loadFromFile("Images\\" + icons[i]);
        Avatar[i].setTexture(&avata[i]);
        Avatar[i].setPosition(position);
        Avatar[i].setSize(sf::Vector2f(32, 32));
        if (position.x > 200)
        {
            position = sf::Vector2f(200, 750);
            position = position + sf::Vector2f(0, 35);
        }
        else
        {
            position = position + sf::Vector2f(35, 0);
        }
    }
    //// Avatar 1
    //avata[0].loadFromFile("Images\\" + icons[0]);
    //Avatar[0].setTexture(&avata[0]);
    //Avatar[0].setPosition(position);
    //Avatar[0].setSize(sf::Vector2f(32, 32));
    //// Avatar 2
    //avata[1].loadFromFile("Images\\" + icons[1]);
    //Avatar[1].setTexture(&avata[1]);
    //Avatar[1].setPosition(position + sf::Vector2f(35, 0));
    //Avatar[1].setSize(sf::Vector2f(32, 32));

    //// Avatar 3
    //avata[2].loadFromFile("Images\\" + icons[2]);
    //Avatar[2].setTexture(&avata[2]);
    //Avatar[2].setPosition(position + sf::Vector2f(0, 35));
    //Avatar[2].setSize(sf::Vector2f(32, 32));

    //// Avatar 4
    //avata[3].loadFromFile("Images\\" + icons[3]);
    //Avatar[3].setTexture(&avata[3]);
    //Avatar[3].setPosition(position + sf::Vector2f(0, 35) + sf::Vector2f(35, 0));
    //Avatar[3].setSize(sf::Vector2f(32, 32));
}

void GUI::moveavatar(int roll)
{
    if (isopen2 == true && playbuttonbool == true && drawavatarbool == true)
    {
        int num = stoi(numofplayer);
       /* move += roll;
            for (int j = 0; j <= move; j++)
            {
                if (move >= 34)
                {
                    move = (move - 34);
                    Avatar[0].setPosition(Board[move].getPosition());

                }
                else
                {
                    Avatar[0].setPosition(Board[move].getPosition());
                }

            }*/
        if (turns == num)
        {
            turns = 0;
        }
        if (turns == 0)
        {
            movep1 += roll;
            if (movep1 >= 34)
            {
                movep1 = (movep1 - 34);
                Avatar[turns].setPosition(Board[movep1].getPosition());
                turns++;

            }
            else
            {
                Avatar[turns].setPosition(Board[movep1].getPosition());
                turns++;
            }
        }
        else if (turns == 1)
        {
            movep2 += roll;
            if (movep2 >= 34)
            {
                movep2 = (movep2 - 34);
                Avatar[turns].setPosition(Board[movep2].getPosition() + sf::Vector2f(35.0,0.0));
                turns++;

            }
            else
            {
                Avatar[turns].setPosition(Board[movep2].getPosition() + sf::Vector2f(35.0, 0.0));
                turns++;
            }
        }
        else if (turns == 2)
        {
            movep3 += roll;
            if (movep3 >= 34)
            {
                movep3 = (movep3 - 34);
                Avatar[turns].setPosition(Board[movep3].getPosition() + sf::Vector2f(0.0, 35.0));
                turns++;

            }
            else
            {
                Avatar[turns].setPosition(Board[movep3].getPosition() + sf::Vector2f(0.0, 35.0));
                turns++;
            }
        }
        else if (turns == 3)
        {
            movep4 += roll;
            if (movep4 >= 34)
            {
                movep3 = (movep4 - 34);
                Avatar[turns].setPosition(Board[movep4].getPosition() + sf::Vector2f(35.0, 35.0));
                turns++;

            }
            else
            {
                Avatar[turns].setPosition(Board[movep4].getPosition() + sf::Vector2f(35.0, 35.0));
                turns++;
            }
        }
    }
}

void GUI::random()
{
    srand(time(NULL));
    roll = rand() % 6;
    diceRect.setTexture(&diceTexture[roll]);
    moveavatar(roll + 1);
    diceIsRolled = 0;
}


void GUI::loadsounds()
{
    buffers[0].loadFromFile("Sounds\\Player button.wav");
}

void GUI::drawMessageBox2()
{
    if (messagePrompt.isOpen() == false && playbuttonbool == true)
    {
        sf::Font arialFont;
        arialFont.loadFromFile(ARIAL_FONT);
        sf::Text messageTitle;
        messageTitle.setString("Choose Icon");
        messageTitle.setCharacterSize(15);
        messageTitle.setFont(arialFont);
        messageTitle.setPosition(15.0f, 15.0f);
        messageTitle.setFillColor(outlineColor);

        sf::Text messageTitle2;
        messageTitle2.setString("Player Number : ");
        messageTitle2.setCharacterSize(15);
        messageTitle2.setFont(arialFont);
        messageTitle2.setPosition(15.0f, 30.0f);
        messageTitle2.setFillColor(outlineColor);


        sf::Texture Icon1;
        sf::Texture Icon2;
        sf::Texture Icon3;
        sf::Texture Icon4;

        Icon1.loadFromFile("Images\\Icon1.jpeg");
        Ic1.setSize(sf::Vector2f(40.0f, 40.0f));
        Ic1.setPosition(15.0f, 53.0f);
        Ic1.setOutlineThickness(0);
        Ic1.setOutlineColor(outlineColor);
        Ic1.setTexture(&Icon1);
        Icon1.setSmooth(true);

        Icon2.loadFromFile("Images\\Icon2.jpeg");
        Ic2.setSize(sf::Vector2f(40.0f, 40.0f));
        Ic2.setPosition(70.0f, 53.0f);
        Ic2.setOutlineThickness(0);
        Ic2.setOutlineColor(outlineColor);
        Ic2.setTexture(&Icon2);
        Icon2.setSmooth(true);

        Icon3.loadFromFile("Images\\Icon3.jpeg");
        Ic3.setSize(sf::Vector2f(40.0f, 40.0f));
        Ic3.setPosition(125.0f, 53.0f);
        Ic3.setOutlineThickness(0);
        Ic3.setOutlineColor(outlineColor);
        Ic3.setTexture(&Icon3);
        Icon3.setSmooth(true);

        Icon4.loadFromFile("Images\\Icon4.jpeg");
        Ic4.setSize(sf::Vector2f(40.0f, 40.0f));
        Ic4.setPosition(180.0f, 53.0f);
        Ic4.setOutlineThickness(0);
        Ic4.setOutlineColor(outlineColor);
        Ic4.setTexture(&Icon4);
        Icon4.setSmooth(true);

        sf::Text messageTitle3;
        if (loop < stoi(numofplayer))
        {
            messageTitle3.setString(to_string(loop + 1));
        }
        else
        {
            messageTitle3.setString(to_string(loop));
        }
        messageTitle3.setCharacterSize(15);
        messageTitle3.setFont(arialFont);
        messageTitle3.setPosition(205.0f, 30.0f);
        messageTitle3.setFillColor(outlineColor);
        messageTitle3.setStyle(sf::Text::Bold);


        sf::Event event;
        while (messagePrompt2.pollEvent(event))
        {
            sf::Vector2f mousePos = messagePrompt2.mapPixelToCoords(sf::Mouse::getPosition(messagePrompt2));
            sf::FloatRect icon1 = Ic1.getGlobalBounds();
            sf::FloatRect icon2 = Ic2.getGlobalBounds();
            sf::FloatRect icon3 = Ic3.getGlobalBounds();
            sf::FloatRect icon4 = Ic4.getGlobalBounds();

            if (event.MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left && loop < stoi(numofplayer))
            {
                if (icon1.contains(mousePos) && pressed1 == false)
                {
                    icons[loop] = "Icon1.jpeg";
                    loop++;
                    checkmessagebox2 = "Done !";
                    pressed1 = true;
                }

                else if (icon2.contains(mousePos) && pressed2 == false)
                {
                    icons[loop] = "Icon2.jpeg";
                    loop++;
                    checkmessagebox2 = "Done !";
                    pressed2 = true;
                }

                else if (icon3.contains(mousePos) && pressed3 == false)
                {
                    icons[loop] = "Icon3.jpeg";
                    loop++;
                    checkmessagebox2 = "Done !";
                    pressed3 = true;
                }
                
                else if (icon4.contains(mousePos) && pressed4 == false)
                {
                    icons[loop] = "Icon4.jpeg";
                    loop++;
                    checkmessagebox2 = "Done !";
                    pressed4 = true;
                }

                else
                {
                    checkmessagebox2 = "Click Again !";
                }
            }
        }
        sf::Text messageTitle4;

        messageTitle4.setString(checkmessagebox2);
        messageTitle4.setCharacterSize(15);
        messageTitle4.setFont(arialFont);
        messageTitle4.setPosition(15.0f, 110.0f);
        messageTitle4.setFillColor(outlineColor);
        messageTitle4.setStyle(sf::Text::Bold);


        sf::Text messageTitle5;

        messageTitle5.setString(to_string(temp));
        messageTitle5.setCharacterSize(15);
        messageTitle5.setFont(arialFont);
        messageTitle5.setPosition(120.0f, 125.0f);
        messageTitle5.setFillColor(outlineColor);
        messageTitle5.setStyle(sf::Text::Bold);


        if (loop == stoi(numofplayer))
        {
            if (once == false)
            {
                countdown.restart();
                once = true;
            }
            sf::Time elapsed = countdown.getElapsedTime();
            temp = timer.asSeconds() - elapsed.asSeconds();
        }


        messagePrompt2.clear(backgroundColor);

        messagePrompt2.draw(messageTitle);
        messagePrompt2.draw(messageTitle2);
        messagePrompt2.draw(messageTitle3);
        messagePrompt2.draw(messageTitle4);
        if (temp >= 1)
        {
            messagePrompt2.draw(messageTitle5);
        }
        else if (temp < 1 && once == true)
        {
            sf::Texture okButtonTexture;
            okButtonTexture.loadFromFile("Images\\ok.png");
            okButton2.setSize(sf::Vector2f(40.0f, 40.0f));
            okButton2.setTexture(&okButtonTexture);
            okButton2.setPosition(120.0f, 125.0f);
            okButton2.setOutlineThickness(outlineThickness);
            okButton2.setOutlineColor(outlineColor);
            okButtonTexture.setSmooth(true);
            messagePrompt2.draw(okButton2);
        }
        messagePrompt2.draw(Ic1);
        messagePrompt2.draw(Ic2);
        messagePrompt2.draw(Ic3);
        messagePrompt2.draw(Ic4);

        messagePrompt2.display();       
    }
}


//void GUI::delay(int number_of_seconds)
//{
//    // Converting time into milli_seconds
//    int milli_seconds = 1000 * number_of_seconds;
//
//    // Storing start time
//    clock_t start_time = clock();
//
//    // looping till required time is not achieved
//    while (clock() < start_time + milli_seconds)
//        ;
//}