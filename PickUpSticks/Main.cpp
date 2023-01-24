#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <cmath>


int RandomNumberGenerator(int min, int max)
{
    int range = max - min;
    int randNum = min + rand() % range;
    return randNum;
}

int main()
{


    // ------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
    // Setup
    // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
# pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks!", sf::Style::None);
    srand(time(NULL));


   

    // Player Texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Player_Stand.png");

    // Grass Texture
    sf::Texture grassTexture;
    grassTexture.loadFromFile("Assets/Grass.png");

    // Stick Texture
    sf::Texture stickTexture;
    stickTexture.loadFromFile("Assets/Stick.png");

    if (!playerTexture.loadFromFile("Assets/Player_Stand.png"))
    {
        // Error message
        std::cout << "Texture load failed for Assets/Player_Stand.png" << std::endl;
    }
    else
    {
        std::cout << "Texture loaded successfully" << std::endl;
    }
    if (!grassTexture.loadFromFile("Assets/Grass.png"))
    {
        std::cout << "Texture load failed for Assets/Grass.png" << std::endl;
    }
    else
    {
        std::cout << "Texture loaded successfully" << std::endl;
    }

    // Player Sprite
    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    // Grass Sprite
    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);

    // Stick Sprite
    sf::Sprite stickSprite;
    stickSprite.setTexture(stickTexture);

    // Vector for grass Sprites
    std::vector<sf::Sprite> grassVector;

    int numGrassSpritesToAdd = 10;

    // Grass position and colours
    for (int i = 0; i < numGrassSpritesToAdd; ++i)
    {
        int max = 250;
        int min = 100;
        int range = max - min;
        int num = min + rand() % range;

        float randScale = 1 + rand() % 1;
        
        grassSprite.setOrigin((grassTexture.getSize().x) / 2, (grassTexture.getSize().y) / 2);
        grassSprite.setScale(randScale, randScale);
        grassSprite.setColor(sf::Color(num, num, num));
        grassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
        grassVector.push_back(grassSprite);
    }

    // Vector for stick Sprites
    std::vector<sf::Sprite> stickSprites;

    // Stick Position and Rotation
    stickSprite.setRotation(rand() % 360);
    stickSprite.setOrigin(stickTexture.getSize().x / 2, stickTexture.getSize().y / 2);
    stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
    stickSprites.push_back(stickSprite);

    // Player position
    playerSprite.setPosition(sf::Vector2f(500.0f, 500.0f));
 
    // Rotation
    playerSprite.setRotation(0);

    // Scale
    playerSprite.setScale(1.2f, 1.2f);

    // Origin
    playerSprite.setOrigin((playerTexture.getSize().x) / 2, (playerTexture.getSize().y) / 2);

    // Load fonts
    sf::Font gameFont;
    gameFont.loadFromFile("Assets/GameFont.ttf");

 

    // Create Text Objects
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");
    gameTitle.setFillColor(sf::Color::Cyan);
    gameTitle.setOutlineThickness(2.0f);
    gameTitle.setCharacterSize(60);
  //  gameTitle.setStyle(sf::Style::);


    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition((float)window.getSize().x / 2.0f - textWidth / 2.0f, 10.0f);
    

    sf::Text scoreLabel;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString("Score: ");
    scoreLabel.setFillColor(sf::Color::Cyan);
    scoreLabel.setOutlineThickness(2.0f);
    scoreLabel.setPosition(0, 10);
    
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");

    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();
    
    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/Music.OGG");
    gameMusic.setVolume(50);
    gameMusic.setLoop(true);
    gameMusic.play();
    
    
    float xDir = (10 - rand() % 21)/10.0f;
    float yDir = (10 - rand() % 21)/10.0f;
    sf::Vector2f direction(xDir, yDir);
    bool dashPressedPrev = false;
    bool dashPressed = false;

#pragma endregion 
    // End Setup


   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Event Polling
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Event Polling


    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                {
                    window.close();
                }
            }

            if (event.type == sf::Event::Closed)
                window.close();
        }

#pragma endregion
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Update
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Update
        
        direction.x = 0;
        direction.y = 0;
        
        if (sf::Joystick::isConnected(0))
        {

            float axisX = sf::Joystick::getAxisPosition(1, sf::Joystick::X);
            float axisY = sf::Joystick::getAxisPosition(1, sf::Joystick::Y); 

            float deadzone = 40;

            if (abs(axisX) > deadzone)
            {
                direction.x = axisX / 100.0f;
            }
            if (abs(axisY) > deadzone)
            {
                direction.y = axisY / 100.0f;
            }

            direction.x = sf::Joystick::getAxisPosition(1, sf::Joystick::X) / 100.0f;
        }   direction.y = sf::Joystick::getAxisPosition(1, sf::Joystick::Y) / 100.0f;

      //  if(sf::Joystick::isButtonPressed(sf::Joystick::))

        
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
        {
            direction.x = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)|| sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
        {
            direction.x = 1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) || sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
        {
            direction.y = -1;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
        {
            direction.y = 1;
        }


       
        playerSprite.setPosition(playerSprite.getPosition() + direction * 0.1f);
        
       
        sf::Vector2f dashDirection(direction.x + 0.1, 0);

        dashPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1,10);

        if (dashPressed && !dashPressedPrev)
        {
            playerSprite.setPosition(playerSprite.getPosition() + direction * 300.0f);
        }

        dashPressedPrev = dashPressed;

        if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
        {
            sf::Vector2i localPosition = sf::Mouse::getPosition(window);
            sf::Vector2f mousePositionFloat = (sf::Vector2f)localPosition;

            stickSprite.setPosition(mousePositionFloat);
            stickSprites.push_back(stickSprite);
        }

       



#pragma endregion
    
   // -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
   // Drawing
   // --------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Drawing


        window.clear(sf::Color(67, 232, 111));
       

        // Draw Grass
        for (int i = 0; i < grassVector.size(); ++i)
        {
            window.draw(grassVector[i]);
        }

        // Draw Player
        for (int i = 0; i < stickSprites.size(); ++i)
        {
            window.draw(stickSprites[i]);
        }
       
        window.draw(playerSprite);
        window.draw(gameTitle);
        window.draw(scoreLabel);

        window.display();
    }

    return 0;


#pragma endregion
    

       
}