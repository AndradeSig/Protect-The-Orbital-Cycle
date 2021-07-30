#ifndef __ASTEROID
#define __ASTEROID

#include <iostream>
#include <cmath>
#include <time.h>
#include <SFML/Graphics.hpp>
#include "handler.hpp"

#define PI 3.14159265359f

class Asteroid : public Handler
{
    public:

        sf::CircleShape asteroid_shape;
        sf::Texture     asteroid_texture;
        sf::Texture     asteroid_texture_destroying[4];
    
        float angle     = 0.0f;

        uint8_t frames_anim   = 0;
        uint8_t current_anim  = 0;
        uint8_t max_anim      = 3;
        uint8_t anim_speed    = 20;

        Asteroid();
        void tick(float delta_time, sf::RenderWindow &window);
        void render(sf::RenderWindow &widnow);
};

Asteroid::Asteroid()
{

    this->type = ASTEROID;


    for(uint8_t px = 0; px <= 4; px++){
        asteroid_texture_destroying[px].loadFromFile("Resources/destroying/asteroid" + std::to_string(px) + ".png");
    }

    /** RANDOMIZE **/
    std::srand(time(NULL));

    angle           = (std::rand() % 360) * PI / 180; /** CHOOSE A RANDOM ANGLE **/
    
    /** SELECT A RANDOM LOCAL TO SPAWN **/
    uint16_t random_number_to_spawn = std::rand() % 3;
    if(random_number_to_spawn == 0)
        dir_y   = -18;
    else if(random_number_to_spawn == 1)
        dir_y   = 820;
    else if(random_number_to_spawn == 2)
        dir_x   = -18;
    else if(random_number_to_spawn == 3)
        dir_y   = 1280;

    //system("clear");
    //std::cout << random_number_to_spawn << "\n";

    this->radius    = 22.0f;
    this->velocity  = 14.0f;

    if(!asteroid_texture.loadFromFile("Resources/asteroide.png"))
    {
        system("clear");
        std::cout << "\n\n--> Não foi possível encontrar a Textura <-- " << "\n\n";
    }

    asteroid_shape.setPosition(sf::Vector2f( this->dir_x, this->dir_y ));
    asteroid_shape.setRadius(this->getRadius());
}

void Asteroid::tick(float delta_time, sf::RenderWindow &window)
{
    this->posX = asteroid_shape.getPosition().x;
    this->posY = asteroid_shape.getPosition().y;

    float window_x      = window.getSize().x;
    float window_y      = window.getSize().y;

    float new_angle_x   = std::cos(angle);
    float new_angle_y   = std::sin(angle);

    asteroid_shape.move(sf::Vector2f(new_angle_x * this->velocity * delta_time, new_angle_y * this->velocity * delta_time));

    /** System to destroy asteroids when they pass the screen **/
    if(this->posY >= window_y)
        asteroid_shape.setPosition(sf::Vector2f(this->posX, this->posY - window_y));

    else if(this->posY < -40)
        asteroid_shape.setPosition(sf::Vector2f(this->posX, this->posY + window_y));

    else if(this->posX >= window_x)
        asteroid_shape.setPosition(sf::Vector2f(this->posX - window_x, this->posY));

    else if(this->posX < -40)
        asteroid_shape.setPosition(sf::Vector2f(this->posX + window_x, this->posY));
    
    if(!this->isDestroyed){
        frames_anim++;
        if(frames_anim >= anim_speed){
            frames_anim = 0;
            current_anim++;
            if(current_anim >= max_anim){
                current_anim = 0;
            }
        }
    }else{
        frames_anim  = 0;
        current_anim = 0;
    }

}

void Asteroid::render(sf::RenderWindow &window)
{
    if(!this->isDestroyed){
        asteroid_shape.setTexture(&asteroid_texture_destroying[current_anim]);
    }else{
        asteroid_shape.setTexture(&asteroid_texture);
    }

    window.draw(asteroid_shape);
}

#endif