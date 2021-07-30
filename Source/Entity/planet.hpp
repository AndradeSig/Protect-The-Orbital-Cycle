#ifndef __PLANET
#define __PLANET

#include <iostream>
#include <cmath>
#include <SFML/Graphics.hpp>
#include "handler.hpp"

class Planet : public Handler
{
    public:

        sf::CircleShape planet_shape;
        sf::Texture     planet_texture;

        float angle;

        Planet();
        void start(sf::RenderWindow &window);
        void tick(float delta_time, sf::RenderWindow &window);
        void render(sf::RenderWindow &widnow);
};


Planet::Planet()
{
    this->type = PLANET;
}

void Planet::start(sf::RenderWindow &window)
{
    this->radius    = 32.0f;
    this->velocity  = 2.0f;
    this->force     = 100.0f;
    
    if(!planet_texture.loadFromFile("Resources/planet.png"))
    {
        system("clear");
        std::cout << "\n\n--> Não foi possível encontrar a Textura <-- " << "\n\n";
    }

    planet_shape.setPosition(sf::Vector2f(this->getPosX(), this->getPosY()));
    planet_shape.setRadius(this->getRadius());
    planet_shape.setTexture(&planet_texture);
}

void Planet::tick(float delta_time, sf::RenderWindow &window)
{
    //this->posX = planet_shape.getPosition().x;
    //this->posY = planet_shape.getPosition().y;
}

void Planet::render(sf::RenderWindow &window)
{
    planet_shape.setPosition(sf::Vector2f(this->posX, this->posY));
    window.draw(planet_shape);
}

#endif