#ifndef __HANDLER
#define __HANDLER

#include <iostream>
#include <SFML/Graphics.hpp>


class Handler
{
    public:
        enum Types {NONE, HANDLER, SUN, PLANET, ASTEROID};

        Handler::Types type = HANDLER;
        sf::Texture texture;

        double posX;
        double posY;
        double last_posX;
        double last_posY;
        double dS;
        double dSx;
        double dSy;
        double dir_x;
        double dir_y;
        float radius;
        float velocity;
        float force;
        float mass;
        float life = 100;

        virtual void  start(sf::RenderWindow &window);
        virtual void  tick(float delta_time, sf::RenderWindow &window);
        virtual void  render(sf::RenderWindow &widnow);
        virtual int   getPosX();
        virtual int   getPosY();
        virtual float getRadius();
        virtual Types  isCollidingWith(std::vector<Handler> objects);
};

void Handler::start(sf::RenderWindow &window)
{

}

void Handler::tick(float delta_time, sf::RenderWindow &window)
{

}

void Handler::render(sf::RenderWindow &window)
{

}

int Handler::getPosX()
{
    return (int)posX + radius;// - (radius / 2);
}

int Handler::getPosY()
{
    return (int)posY + radius;// - (radius / 2);
}

float Handler::getRadius()
{
    return radius;
}

Handler::Types Handler::isCollidingWith(std::vector<Handler> objects){

    for (auto object : objects){

        double distance = std::sqrt(std::pow(getPosX() - object.getPosX(), 2) +
                                    std::pow(getPosY() - object.getPosY(), 2));

        if (distance < (object.getRadius() + getRadius()) && distance != 0){
            return object.type;
        }

    }
    return NONE;
}

#endif
