#ifndef __SUN
#define __SUN

#include <iostream>
#include <SFML/Graphics.hpp>
#include "handler.hpp"

class Sun : public Handler
{
    public:

        sf::CircleShape sun_shape;
        sf::Texture     sun_texture;

        Sun(std::string type);
        void start(sf::RenderWindow &window);
        void tick(float delta_time, sf::RenderWindow &window);
        void render(sf::RenderWindow &widnow);
};


Sun::Sun(std::string type)
{
    this->type  = type;
}

void Sun::start(sf::RenderWindow &window)
{
    if(!sun_texture.loadFromFile("Resources/sol.png"))
    {
        system("clear");
        std::cout << "\n\n--> Não foi possível encontrar a Textura <-- " << "\n\n";
    }

    this->radius = 100.0f; 
    this->posX   = (window.getSize().x/2 - getRadius()) - 64;
    this->posY   = (window.getSize().y/2 - getRadius()) - 64;

    sun_shape.setPosition(sf::Vector2f(this->getPosX(), this->getPosY()));
    sun_shape.setRadius(this->getRadius());
    sun_shape.setTexture(&sun_texture);
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