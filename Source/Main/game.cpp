#include <iostream>
#include <SFML/Graphics.hpp>
#include "space.cpp"

#define GAME_TITLE     "Unknow Game Name"
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  820
#define FRAMERATE_GAME 60

sf::RectangleShape     space_background;
sf::Texture            space_texture;

void tick(float delta_time, sf::RenderWindow &window)
{
    whenUpdate(delta_time, window);
}

void render(sf::RenderWindow &window, float delta_time)
{
    window.clear(sf::Color::Black);

    space_background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    space_background.setPosition(sf::Vector2f(0,0));
    space_background.setTexture(&space_texture);

    window.draw(space_background);
    whenRender(window, delta_time);
    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(window.getPosition().x / 2, window.getPosition().y / 2));
    window.setFramerateLimit(FRAMERATE_GAME);

    sf::Clock game_clock;
    float delta_time        = 0.0f;
    float last_time         = 0.0f;

    /** WHEN START **/
    space_texture.loadFromFile("Resources/space.png");
    whenStart(window);

    while(window.isOpen())
    {
        sf::Event game_event;
        while(window.pollEvent(game_event))
        {
            switch(game_event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        /** DELTA TIME **/
        float current_time  = game_clock.restart().asSeconds();
        delta_time          = (current_time - last_time + 0.1) / 10;
        last_time           = current_time;

        tick(delta_time, window);
        render(window, delta_time);
    }

    return 0;
}
