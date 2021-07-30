#include <bits/stdc++.h>
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
std::vector<Handler *> handler;
Sun *sun;
Planet *planet;

#define PI 3.14159265359f
#define G 500000.0f

class Animator
{
private:
    struct Animation
    {
        float posX;
        float posY;
        float creation_time;
        uint current_frame;
    };

public:

    std::vector<Animation> animations;
    std::vector<sf::Texture> frames;
    float time_interframes = 0.2f;
    float time;

    void addFrame(std::pair<float, float> new_position)
    {
        animations.push_back((Animation){new_position.first, new_position.second, time});
    }

    void changeFrame(float delta_time)
    {
        for (int x = 0; x < animations.size(); x++)
        {
            if (time - animations[x].creation_time >= time_interframes)
            {
                animations[x].current_frame++;
                if (animations[x].current_frame > frames.size())
                    animations.erase(animations.begin() + x);
            }
        }
    }

    void renderAnims(sf::RenderWindow *window, float delta_time)
    {
        time += delta_time;
        for (auto anim : animations)
        {
            sf::Sprite sprite;
            sprite.setScale(sf::Vector2f(2.0f, 2.0f));
            sprite.move(sf::Vector2f(anim.posX, anim.posY));
            sprite.setTexture(frames[anim.current_frame]);
            window->draw(sprite);
        }
        changeFrame(delta_time);
    }

};

Animator asteroid_animations;

void whenStart(sf::RenderWindow &window)
{
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

    //80° por segundo
    ang_orbita += 80 * delta_time;

    /** SPAWN ASTEROIDS **/
    std::srand(1000000000 * delta_time);

    uint16_t random_number = std::rand() % 100;

    if (random_number < 3)
    {
        Asteroid *asteroid = new Asteroid();
        handler.push_back(asteroid);
    }

    /** COLLISION BETWEEN ASTEROIDS, PLANET AND SUN **/
    for (uint16_t x = 0; x < handler.size(); x++)
    {
        if (handler[x]->isCollidingWith({*sun, *planet}))
        {
            asteroid_animations.addFrame({handler[x]->getPosX(), handler[x]->getPosY()});
            handler.erase(handler.begin() + x);
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
}
