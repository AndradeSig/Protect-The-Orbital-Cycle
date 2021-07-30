#include <iostream>
#include <vector>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "../Entity/handler.hpp"
#include "../Entity/sun.hpp"
#include "../Entity/planet.hpp"
#include "../Entity/asteroid.hpp"

/** VARIABLES || OBJECTS **/
std::vector<Handler*> handler;
Sun         *sun;
Planet      *planet;

#define PI 3.14159265359f
#define G  500000.0f


void whenStart(sf::RenderWindow &window)
{
    sun             = new Sun();
    planet          = new Planet();

    /** PUSH HANDLER OBJECT **/
    handler.push_back(sun);
    handler.push_back(planet);

    /** OBJECTS WHEN START **/
    planet->posX   = (window.getSize().x/2 - planet->getRadius()) - 16;
    planet->posY   = (window.getSize().y/2 - planet->getRadius()) - 16;

    for(Handler *current_handler : handler){
        current_handler->start(window);
    }

    //distance_X  = sun->getPosX() - planet->getPosX();
    //distance_Y  = sun->getPosY() - planet->getPosY();
    //distance    = std::sqrt( std::pow(distance_X, 2) + std::pow(distance_Y, 2));
    //ang_orbita  = std::atan(distance_X / distance_Y) * 180/PI;
}

float  distance;
float  ang_orbita;


/** EVERYTHING THAT HAPPENS IN COLLISIONS WILL BE IN THIS METHOD **/
void cause_collision(uint16_t x)
{
    handler[x]->isDestroyed     = true;
    handler.erase(handler.begin() + x);
}


void whenUpdate(float delta_time, sf::RenderWindow &window)
{
    sun->mass     = 10.0f;
    planet->mass  = 10.0f;
    distance = 200;

    //velocidade orbital
    planet->velocity = std::sqrt((G * sun->mass * planet->mass) / distance);

    planet->posX = sun->getPosX() + (std::cos(ang_orbita * PI/180) * distance);
    planet->posY = sun->getPosY() + (std::sin(ang_orbita * PI/180) * distance);

    ang_orbita += 4 * delta_time;

    /** SPAWN ASTEROIDS **/
    std::srand(1000000000 * delta_time);

    uint16_t random_number  = std::rand() % 100;

    if(random_number < 3){
        Asteroid *asteroid  = new Asteroid();
        handler.push_back(asteroid);
    }


    /** COLLISION BETWEEN ASTEROIDS, PLANET AND SUN **/
    for (uint16_t x = 0; x < handler.size(); x++){
        if (handler[x]->isCollidingWith({*sun, *planet})){
            cause_collision(x);       
        }
    }


    for(Handler *current_handler : handler){
        current_handler->tick(delta_time, window);
    }
}

void whenRender(sf::RenderWindow &window)
{
    for(Handler *current_handler : handler){
        current_handler->render(window);
    }
}
