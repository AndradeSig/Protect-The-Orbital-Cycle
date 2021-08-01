#ifndef __SUN
#define __SUN

#include <iostream>
#include <SFML/Graphics.hpp>
#include "handler.hpp"

class Sun : public Handler
{
    public:

        sf::CircleShape sun_shape;

        Sun();
        void start(sf::RenderWindow &window);
        void tick(float delta_time, sf::RenderWindow &window);
        void render(sf::RenderWindow &widnow);
};


Sun::Sun()
{
    this->type = SUN;
}

void Sun::start(sf::RenderWindow &window)
{
    if(!texture.loadFromFile("Resources/sol.png"))
    {
        system("clear");
        std::cout << "\n\n--> Não foi possível encontrar a Textura <-- " << "\n\n";
    }

    this->radius = 100.0f; 
    this->posX   = window.getSize().x/3;
    this->posY   = window.getSize().y/3 - 64;

    sun_shape.setPosition(sf::Vector2f(this->getPosX(), this->getPosY()));
    sun_shape.setRadius(this->getRadius());
    sun_shape.setTexture(&texture);
}

void Sun::tick(float delta_time, sf::RenderWindow &window)
{
    this->posX = sun_shape.getPosition().x;
    this->posY = sun_shape.getPosition().y;
}

void Sun::render(sf::RenderWindow &window)
{
    window.draw(sun_shape);
}

#endif
