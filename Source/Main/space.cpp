#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../Entity/handler.hpp"
#include "../Entity/sun.hpp"
#include "../Entity/planet.hpp"
#include "../Entity/asteroid.hpp"
#include "Animator.hpp"
#include "SoundEffect.hpp"

/** GUI **/
#include "UserInterface.cpp"

/** External API **/
#include "../API/random.hpp"                 // https://github.com/effolkronium/random
using Random = effolkronium::random_static; /** External API to use Random **/


/** VARIABLES || OBJECTS **/
std::vector<Handler *> handler;
Sun *sun;
Planet *planet;

int POINTS  = 0;

#define PI 3.14159265359f
#define G 500000.0f

SoundEffect asteroidSound;
Animator asteroid_animations;

void whenStart(sf::RenderWindow &window)
{

    LOAD_GUI(); /** TO LOAD GUI **/

    sun = new Sun();
    planet = new Planet();

    /** PUSH HANDLER OBJECT **/
    handler.push_back(sun);
    handler.push_back(planet);

    /** OBJECTS WHEN START **/
    planet->posX = (window.getSize().x / 2 - planet->getRadius()) - 16;
    planet->posY = (window.getSize().y / 2 - planet->getRadius()) - 16;

    for (Handler *current_handler : handler)
    {
        current_handler->start(window);
    }

    for (uint8_t px = 0; px <= 4; px++)
    {
        sf::Texture frame;
        frame.loadFromFile("Resources/destroying/asteroid" + std::to_string(px) + ".png");
        asteroid_animations.frames.push_back(frame);
    }

    //distance_X  = sun->getPosX() - planet->getPosX();
    //distance_Y  = sun->getPosY() - planet->getPosY();
    //distance    = std::sqrt( std::pow(distance_X, 2) + std::pow(distance_Y, 2));
    //ang_orbita  = std::atan(distance_X / distance_Y) * 180/PI;
}

float distance;
float ang_orbita;


void whenUpdate(float delta_time, sf::RenderWindow &window)
{
    sun->mass = 10.0f;
    planet->mass = 10.0f;
    distance = 200;

    //velocidade orbital
    planet->velocity = std::sqrt((G * sun->mass * planet->mass) / distance);

    planet->posX = sun->getPosX() + (std::cos(ang_orbita * PI / 180) * distance);
    planet->posY = sun->getPosY() + (std::sin(ang_orbita * PI / 180) * distance);

    // 30° por segundo
    ang_orbita += 30 * delta_time;

    /** SPAWN ASTEROIDS **/
    double random_number = Random::get(0, 100); /** Get random numbers between 0 and 100 **/
    if (random_number < 0.01)
    {
        Asteroid *asteroid = new Asteroid();
        handler.push_back(asteroid);
    }

    /** COLLISION BETWEEN ASTEROIDS, PLANET AND SUN **/
    for (uint16_t x = 0; x < handler.size(); x++)
    {
        if (handler[x]->isCollidingWith({*sun, *planet}))
        {
            asteroid_animations.addAnimHere({handler[x]->getPosX() - handler[x]->getRadius(), 
                                             handler[x]->getPosY() - handler[x]->getRadius()});
            asteroidSound.setShouldPlay(true);
            handler.erase(handler.begin() + x);   
        }
    }


    /** DETECT MOUSE COLLISION **/
    sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

    for(uint16_t x = 0; x < handler.size(); x++)
    {
        if(mousePosition.x > handler[x]->getPosX() - handler[x]->getRadius() && mousePosition.x < handler[x]->getPosX() + handler[x]->getRadius()
        || mousePosition.y > handler[x]->getPosY() + handler[x]->getRadius() && mousePosition.y < handler[x]->getPosY() - handler[x]->getRadius()/2)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
            {
                if(handler[x]->type != Handler::PLANET && handler[x]->type != Handler::SUN)
                {
                    asteroid_animations.addAnimHere({handler[x]->getPosX() - handler[x]->getRadius(), 
                                                handler[x]->getPosY() - handler[x]->getRadius()});
                    asteroidSound.setShouldPlay(true);
                    handler.erase(handler.begin() + x);
                    POINTS++;   /** + points **/   
                }
            }
        }
    }

    for (Handler *current_handler : handler)
    {
        current_handler->tick(delta_time, window);
    }
}

void whenRender(sf::RenderWindow &window, float delta_time)
{
    for (Handler *current_handler : handler)
    {
        current_handler->render(window);
    }
    asteroid_animations.renderAnims(&window, delta_time);

    SHOW_GUI_POINTS("POINTS:" + std::to_string(POINTS), window);
}
