#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h> 
int main()
{


    // ---------------------------------------------------------------------------------------------------------------------------------
    // Setup
    // ---------------------------------------------------------------------------------------------------------------------------------
# pragma region Setup


    sf::RenderWindow window(sf::VideoMode::getDesktopMode(), "Pick Up Sticks!", sf::Style::None);

    // Player Texture
    sf::Texture playerTexture;
    playerTexture.loadFromFile("Assets/Player_Stand.png");

    // Grass Texture
    sf::Texture grassTexture;
    grassTexture.loadFromFile("Assets/Grass.png");

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

    sf::Sprite playerSprite;
    playerSprite.setTexture(playerTexture);

    sf::Sprite grassSprite;
    grassSprite.setTexture(grassTexture);

    std::vector<sf::Sprite> grassVector;
    for (int i = 0; i < 5; ++i)
    {
        grassVector.push_back(grassSprite);
    }

    // Position Setup
    playerSprite.setPosition(sf::Vector2f(0.0f, 100.0f));

    int randNum;
    // Seed random number
    srand(time(NULL));

    // Generate random number
    
    randNum = rand() % (window.getSize().x - grassTexture.getSize().x) + (window.getSize().y - grassTexture.getSize().y);

    // Grass positions
    for (int i = 0; i < grassVector.size(); ++i)
    {
        grassVector[i].setPosition(sf::Vector2f(randNum, randNum));
    }

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


        window.clear(sf::Color(74, 193, 54));
      

        // Draw Grass
        for (int i = 0; i < grassVector.size(); ++i)
        {
            window.draw(grassVector[i]);
        }

        // Draw Player
        window.draw(playerSprite);
        window.display();
    }

    return 0;


#pragma endregion
    

       
}