#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
#include <cmath>

enum class GameState
{
    RUNNING,        //RUNNING = 0
    GAME_OVER,       // GAME_OVER = 1
    NUM_GAME_STATES
};

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

    sf::Texture playerTextureStand;
    playerTextureStand.loadFromFile("Assets/Player_Stand.png");

    sf::Texture playerTextureWalk1;
    playerTextureWalk1.loadFromFile("Assets/Player_Walk_1.png");

    sf::Texture playerTextureWalk2;
    playerTextureWalk2.loadFromFile("Assets/Player_Walk_2.png");

    // Load player animation
    std::vector<sf::Texture> playerWalk;
    int numFrames = 2;
    std::string baseFilePath = "Assets/Player_Walk_";
    std::string fileType = ".png";

    // For loop to populate vector
    for (int i = 0; i < numFrames; ++i)
    {
        playerWalk.push_back(sf::Texture());
        playerWalk[i].loadFromFile(baseFilePath + std::to_string((int)(i + 1)) +fileType);
    }


    /*playerWalk.push_back(sf::Texture());
    playerWalk[0].loadFromFile("Assets/Player_Walk_1.png");
    playerWalk.push_back(sf::Texture());
    playerWalk[1].loadFromFile("Assets/Player_Walk_2.png");*/

    std::vector<sf::Texture> playerStand;
    playerStand.push_back(sf::Texture());
    playerStand[0].loadFromFile("Assets/Player_Stand.png");

    std::vector<sf::Texture>* currentClip = &playerStand;
   

    // Player Texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Player_Stand.png");

    // Grass Texture
    sf::Texture grassTexture;
    grassTexture.loadFromFile("Assets/Grass.png");

    // Stick Texture
    sf::Texture stickTexture;
    stickTexture.loadFromFile("Assets/Stick.png");

  
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
    // Game Title
    sf::Text gameTitle;
    gameTitle.setFont(gameFont);
    gameTitle.setString("Pick Up Sticks");
    gameTitle.setFillColor(sf::Color::Cyan);
    gameTitle.setOutlineThickness(2.0f);
    gameTitle.setCharacterSize(60);

    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition((float)window.getSize().x / 2.0f - textWidth / 2.0f, 10.0f);


    // Timer
    sf::Text timerText;
    timerText.setFont(gameFont);
    timerText.setString("Time Left: ");
    timerText.setFillColor(sf::Color::Cyan);
    timerText.setOutlineThickness(2.0f);
    timerText.setCharacterSize(20);
    timerText.setPosition((float)window.getSize().x - 500.0f, 10.0f);


   
    // Score label
    sf::Text scoreLabel;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString("Score: ");
    scoreLabel.setFillColor(sf::Color::Cyan);
    scoreLabel.setOutlineThickness(2.0f);
    scoreLabel.setPosition(0, 10);
    
    // Game over
    sf::Text gameOverText;
    gameOverText.setFont(gameFont);
    gameOverText.setString("Game Over");
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setOutlineThickness(2.0f);
    gameOverText.setCharacterSize(60);
    

    gameOverText.setPosition((float)window.getSize().x / 2 - 250.0f , window.getSize().y / 2);

    // Sound
    sf::SoundBuffer startSFXBuffer;
    startSFXBuffer.loadFromFile("Assets/Start.wav");
    sf::Sound startSFX;
    startSFX.setBuffer(startSFXBuffer);
    startSFX.play();
    
    // Music
    sf::Music gameMusic;
    gameMusic.openFromFile("Assets/Music.OGG");
    gameMusic.setVolume(50);
    gameMusic.setLoop(true);
    gameMusic.play();
    
    // Set a random direction vector
    float xDir = (10 - rand() % 21)/10.0f;
    float yDir = (10 - rand() % 21)/10.0f;
    sf::Vector2f direction(xDir, yDir);
    bool dashPressedPrev = false;
    bool dashPressed = false;

    // Clocks and Timers
    sf::Clock deltaTimeClock;
    sf::Clock totalTimeClock;
    sf::Clock gameTimer;
    float gameDuration = 30;         // How long the game will last
    sf::Clock stickSpawnTimer;
    float stickTimer = 1;           // Time between stick spawns

    // Player animation variables
    float framesPerSecond = 12.0f;
    sf::Time timePerFrame = sf::seconds(1.0f / framesPerSecond);
    sf::Clock animationClock;
   // sf::Time timePerFrame = sf::seconds(0.1f);
    int currentFrame = 0;
   
    // Set game running to true
   // bool gameRunning = true;

    GameState currentState = GameState::RUNNING;           // assign the value 0 


    int score = 0;
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

        // Get time
        sf::Time deltaTime = deltaTimeClock.restart();
        

        // Game Timer
        float gameTimeFloat = gameTimer.getElapsedTime().asSeconds();
        float remainingTimeFloat = gameDuration - gameTimeFloat;
        if (remainingTimeFloat <= 0)
        {
            currentState = GameState::GAME_OVER;
            remainingTimeFloat = 0;
            
        }
        std::string timerString = "Time Remaining: ";
        timerString += std::to_string((int)ceil(remainingTimeFloat));

        // Display time passed this game
        timerText.setString(timerString);
       
        

       



        
        // Set direction vector to 0
        direction.x = 0;
        direction.y = 0;
        
        // Gamepad input
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

     // Game Loop
        if (currentState == GameState::RUNNING)
        {
            
 
            // Keyboard input
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            {
                direction.x = -1;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) || sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
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

            if (direction.x != 0 || direction.y != 0)
            {
                currentClip = &playerWalk;
            }
            else
            {
                currentClip = &playerStand;
            }


            // Update player position based on movement direction
            float speed = 700;
            // velocity = direction * speed
            sf::Vector2f velocity = direction * speed;
            // distance traveled = velocity * time
            sf::Vector2f distance = velocity * deltaTime.asSeconds();
            playerSprite.setPosition(playerSprite.getPosition() + distance);

            // Check for dash input
            dashPressed = sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Joystick::isButtonPressed(1, 10);

            // Check if player dashed last frame
            if (dashPressed && !dashPressedPrev)
            {
                // Dash
                playerSprite.setPosition(playerSprite.getPosition() + direction * 300.0f);
            }

            
            dashPressedPrev = dashPressed;

            // Check for mouse inout
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                // Get mouse position
                sf::Vector2i localPosition = sf::Mouse::getPosition(window);
                sf::Vector2f mousePositionFloat = (sf::Vector2f)localPosition;

                // Spawn a stick on mouse position
                stickSprite.setPosition(mousePositionFloat);
                stickSprites.push_back(stickSprite);
            }

            // Spawn Sticks
            float stickSpawnFloat = stickSpawnTimer.getElapsedTime().asSeconds();
            if (stickSpawnFloat >= stickTimer)
            {
                stickSprite.setRotation(rand() % 360);
                stickSprite.setOrigin(stickTexture.getSize().x / 2, stickTexture.getSize().y / 2);
                stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
                stickSprites.push_back(stickSprite);
                stickSpawnTimer.restart();
            }


            sf::FloatRect playerBounds = playerSprite.getGlobalBounds();

            // Loop through all stick sprites and check if they collide with player
            for (auto it = stickSprites.begin(); it != stickSprites.end(); )
            {
             
                //  "it" is an iterator, which can be used like a pointer to a sprite
                sf::FloatRect stickBounds = it->getGlobalBounds();
                    // If the stick and player overlap...
                  if (playerBounds.intersects(stickBounds))
                  {
                         it = stickSprites.erase(it);
                         ++score;
                         
                  }
                  else
                  {
                      ++it;
                  }
            }
          
            
          // Process Animation

            sf::Time timePassedThisFrame = animationClock.getElapsedTime();
            if (timePassedThisFrame >= timePerFrame)
            {
                animationClock.restart();

                // Go to the next frame of the animation
                ++currentFrame;
                if (currentFrame >= currentClip->size())
                {
                    currentFrame = 0;
                }
                playerSprite.setTexture((*currentClip)[currentFrame]);

            }

            

        } // END OF IF(GAMERUNNING)
        
        if (currentState == GameState::GAME_OVER)
        {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter) && (currentState == GameState::GAME_OVER))
            {
                currentState = GameState::RUNNING;
                stickSprites.clear();
                score = 0;
                gameTimer.restart();
            }

        }

        // Score
        std::string scoreString = "Score: ";
        scoreString += std::to_string(score);
        scoreLabel.setString(scoreString);

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
        window.draw(timerText);
        if (currentState == GameState::GAME_OVER)
        {
            window.draw(gameOverText);
        }
        window.display();
    }

    return 0;


#pragma endregion
    

       
}