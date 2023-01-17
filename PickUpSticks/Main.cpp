#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 


int RandomNumberGenerator(int min, int max)
{
    int range = max - min;
    int randNum = min + rand() % range;
    return randNum;
}

int main()
{


    // ---------------------------------------------------------------------------------------------------------------------------------
    // Setup
    // ---------------------------------------------------------------------------------------------------------------------------------
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

    int numGrassSpritesToAdd = 5;

    // Grass position and colours
    for (int i = 0; i < numGrassSpritesToAdd; ++i)
    {
        int max = 250;
        int min = 100;
        int range = max - min;
        int num = min + rand() % range;

        float randScale = 1 + rand() % 1;
        
        grassSprite.setScale(randScale, randScale);
        grassSprite.setColor(sf::Color(num, num, num));
        grassSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
        grassVector.push_back(grassSprite);
    }

    // Vector for stick Sprites
    std::vector<sf::Sprite> stickSprites;

    // Stick position
    stickSprite.setRotation(rand() % 360);
    stickSprite.setPosition(sf::Vector2f(rand() % (window.getSize().x - grassTexture.getSize().x), rand() % (window.getSize().y - grassTexture.getSize().y)));
    stickSprites.push_back(stickSprite);

    // Player position
    playerSprite.setPosition(sf::Vector2f(200.0f, 500.0f));
 
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
    float textWidth = gameTitle.getLocalBounds().width;
    gameTitle.setPosition((float)window.getSize().x/2.0f - textWidth/2.0f, 10.0f);

    sf::Text scoreLabel;
    scoreLabel.setFont(gameFont);
    scoreLabel.setString("Score: ");
    scoreLabel.setPosition(0, 10);

    
        

    

#pragma endregion


   // -------------------------------------------------------------------------------------------------------------------------------------
   // Event Polling
   // --------------------------------------------------------------------------------------------------------------------------------------
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
    
   // -------------------------------------------------------------------------------------------------------------------------------------------
   // Drawing
   // ---------------------------------------------------------------------------------------------------------------------------------------------
#pragma region Drawing


        window.clear(sf::Color(67, 232, 111));
       

        // Draw Grass
        for (int i = 0; i < grassVector.size(); ++i)
        {
            window.draw(grassVector[i]);
        }

        // Draw Player
        window.draw(playerSprite);
        window.draw(stickSprite);
        window.draw(gameTitle);
        window.draw(scoreLabel);
        window.display();
    }

    return 0;


#pragma endregion
    

       
}