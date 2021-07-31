#include <iostream>
#include <SFML/Graphics.hpp>

sf::Font    default_font;
sf::Text    points_text;
sf::Text    fps_text;

void LOAD_GUI()
{
    default_font.loadFromFile("Resources/DEFAULT_FONT.ttf");
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