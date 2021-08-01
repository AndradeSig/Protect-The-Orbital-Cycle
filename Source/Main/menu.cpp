#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>
#include "../Entity/handler.hpp"


class MainMenu
{
    public:

        sf::Font                          main_menu_font;
        sf::Text                          main_menu_title_text;

        std::array<sf::RectangleShape, 2> buttons;
        std::array<sf::Text, 2>           buttons_text;
        sf::RectangleShape                wallpaper_menu_background;
        sf::Texture                       wallpaper_menu_texture;
        sf::Color                         default_color;

        MainMenu(sf::RenderWindow &window)
        {
            default_color   = sf::Color::Black;

            wallpaper_menu_texture.loadFromFile("Resources/menu-wallpaper.jpg");
            wallpaper_menu_background.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
            wallpaper_menu_background.setTexture(&wallpaper_menu_texture);

            main_menu_font.loadFromFile("Resources/DEFAULT_FONT.ttf");

            
            /**     MAIN MENU TITLE     **/
            main_menu_title_text.setPosition(sf::Vector2f(window.getSize().x/6, window.getSize().y/6));
            main_menu_title_text.setFont(main_menu_font);
            main_menu_title_text.setCharacterSize(64);


            /**     BUTTONS MENU    **/
            buttons[0].setPosition(sf::Vector2f(window.getSize().x/2 - 124, window.getSize().y/3));
            buttons[0].setSize(sf::Vector2f(240, 80));
            buttons[0].setFillColor(default_color);
            buttons[0].setOutlineThickness(2.f);
            buttons[0].setOutlineColor(sf::Color::White);

            buttons[1].setPosition(sf::Vector2f(window.getSize().x/2 - 124, window.getSize().y/2));
            buttons[1].setSize(sf::Vector2f(240, 80));
            buttons[1].setFillColor(default_color);
            buttons[1].setOutlineThickness(2.f);
            buttons[1].setOutlineColor(sf::Color::White);


            /**     BUTTONS TEXT    **/
            buttons_text[0].setPosition(sf::Vector2f(window.getSize().x/2 - 82, window.getSize().y/3 + 16));
            buttons_text[0].setFont(main_menu_font);
            buttons_text[0].setCharacterSize(32);
            buttons_text[0].setString("New Game");

            buttons_text[1].setPosition(sf::Vector2f(window.getSize().x/2 - 88, window.getSize().y/2 + 16));
            buttons_text[1].setFont(main_menu_font);
            buttons_text[1].setCharacterSize(32);
            buttons_text[1].setString("Quit Game");
        }

        void whenMenuRender(sf::RenderWindow &window)
        {
            window.draw(wallpaper_menu_background);
            window.draw(main_menu_title_text);
            for(auto button : buttons)
            {
                window.draw(button);
            }
            for(auto button_text : buttons_text)
            {
                window.draw(button_text);
            }
        }
};


MainMenu *main_menu;

void whenMainMenuStart(sf::RenderWindow &window)
{
    main_menu = new MainMenu(window);
}

void whenMainMenuRender(sf::RenderWindow &window)
{
    main_menu->whenMenuRender(window);
}
