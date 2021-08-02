#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "../Entity/handler.hpp"

sf::Font    default_font;
sf::Text    points_text;
sf::Text    fps_text;

struct LifeIcon{
    sf::Sprite  sprite;
    sf::Texture texture;
};
LifeIcon life_icon;

void LOAD_GUI()
{
    default_font.loadFromFile("Resources/DEFAULT_FONT.ttf");
    
    life_icon.texture.loadFromFile("Resources/life.png");
    life_icon.sprite.setTexture(life_icon.texture);
}

void SHOW_GUI_POINTS(std::string str_points ,sf::RenderWindow &window)
{
    points_text.setPosition(sf::Vector2f(window.getSize().x / 32, window.getSize().y / 24));
    points_text.setFont(default_font); 
    points_text.setCharacterSize(48);
    points_text.setFillColor(sf::Color::White);
    points_text.setString(str_points);
    window.draw(points_text);
}

void SHOW_GUI_FPS(std::string str_fps ,sf::RenderWindow &window)
{
    fps_text.setPosition(sf::Vector2f(window.getSize().x / 32, window.getSize().y / 9));
    fps_text.setFont(default_font); 
    fps_text.setCharacterSize(16);
    fps_text.setFillColor(sf::Color::White);
    fps_text.setString(str_fps);
    window.draw(fps_text);
}

struct vec2i { int x, y; };
vec2i lifebar_size = { 200, 20 };
void SHOW_LIFEBAR(Handler* obj, std::pair<int, int> position, sf::RenderWindow &window){

    life_icon.sprite.setPosition(position.first - 40, position.second - 5);
    life_icon.sprite.setScale(1.8f, 1.8f);
    window.draw(life_icon.sprite);

    sf::CircleShape icon(15.0f);
    icon.setTexture(&obj->texture);
    icon.setPosition(sf::Vector2f(position.first - 80, position.second - 5));
    window.draw(icon);

    sf::RectangleShape outline(sf::Vector2f(lifebar_size.x, lifebar_size.y));
    outline.setPosition(*new sf::Vector2f(position.first, position.second));
    outline.setFillColor(sf::Color::Transparent);
    outline.setOutlineColor(sf::Color::White);
    outline.setOutlineThickness(2.0f);
    window.draw(outline);
    
    if (obj->life <= 0) return;
    sf::RectangleShape lifebar(sf::Vector2f(lifebar_size.x * (obj->life / 100), lifebar_size.y));
    lifebar.setPosition(*new sf::Vector2f(position.first, position.second));
    lifebar.setFillColor(sf::Color::Red);
    window.draw(lifebar);
}