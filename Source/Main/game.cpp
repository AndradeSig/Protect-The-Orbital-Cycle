#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "space.cpp"
#include "menu.cpp"

#define GAME_TITLE     "PROTECT THE ORBITAL CICLE"
#define SCREEN_WIDTH   1280
#define SCREEN_HEIGHT  820
#define FRAMERATE_GAME 60

enum GAME_STATES
{
    MAIN_MENU   = 0,
    GAMEPLAY    = 1,
    GAME_OVER   = 2
};

GAME_STATES game_state = MAIN_MENU;

sf::RectangleShape      space_background;
sf::Texture             space_texture;

std::array<sf::Text, 3> game_over_screen_text;


void tick(float delta_time, sf::RenderWindow &window)
{
    if(game_state == MAIN_MENU)
    {
        sf::Vector2i localMousePosition = sf::Mouse::getPosition(window);
        sf::RectangleShape  button01    = main_menu->buttons[0];
        sf::RectangleShape  button02    = main_menu->buttons[1];
        if(localMousePosition.x > button01.getPosition().x - button01.getSize().x && localMousePosition.x < button01.getPosition().x + button01.getSize().x
        && localMousePosition.y < button01.getPosition().y + button01.getSize().y && localMousePosition.y > button01.getPosition().y - button01.getSize().y)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                game_state  = GAMEPLAY;
        }
        else if(localMousePosition.x > button02.getPosition().x - button02.getSize().x && localMousePosition.x < button02.getPosition().x + button02.getSize().x
        && localMousePosition.y < button02.getPosition().y + button02.getSize().y && localMousePosition.y > button02.getPosition().y - button02.getSize().y)
        {
            if(sf::Mouse::isButtonPressed(sf::Mouse::Left))
                window.close();
        }
    }

    if(game_state == GAMEPLAY)
    {
        whenUpdate(delta_time, window);
        if(gameOver)
            game_state  = GAME_OVER;
    }

    if(game_state == GAME_OVER)
    {
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
            #ifdef __linux__
                system("./orbitalcycle_linux &");
            #endif
            
            #ifdef __FreeBSD__
				system("./orbitalcycle_linux &");
			#endif

            #ifdef _WIN32
                system("START /B orbitalcycle_win.exe");
            #endif
            
            #ifdef _WIN64
				system("START /B orbitalcycle_win.exe");
			#endif

            exit(0);
            game_state  = GAMEPLAY;
        }
    }
}

void render(sf::RenderWindow &window, float delta_time, float fps)
{
    window.clear(sf::Color::Black);

    space_background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
    space_background.setPosition(sf::Vector2f(0,0));
    space_background.setTexture(&space_texture);

    /**     RENDER MAIN MENU    **/
    if(game_state == MAIN_MENU)
    {
        main_menu->main_menu_title_text.setString(GAME_TITLE);
        whenMainMenuRender(window);
    }

    /**     RENDER GAMEPLAY     **/
    if(game_state == GAMEPLAY)
    {
        window.draw(space_background);
        whenRender(window, delta_time);

        /** SHOW FPS **/
        SHOW_GUI_FPS("FPS: " + std::to_string(fps), window);
    }

    if(game_state == GAME_OVER)
    {
        window.draw(space_background);
        game_over_screen_text[0].setPosition(window.getSize().x/3, window.getSize().y/3);
        game_over_screen_text[0].setCharacterSize(48);
        game_over_screen_text[0].setString("-- Game Over --");
        game_over_screen_text[1].setPosition(window.getSize().x/3 + 96, window.getSize().y/3 + 80);
        game_over_screen_text[1].setCharacterSize(24);
        game_over_screen_text[1].setString("Total Points: " + std::to_string(POINTS));
        game_over_screen_text[2].setPosition(window.getSize().x/3 - 32, window.getSize().y/2);
        game_over_screen_text[2].setCharacterSize(32);
        game_over_screen_text[2].setString("> Press Enter to Restart <");
        for(auto text : game_over_screen_text)
        {
            text.setFont(default_font);
            text.setFillColor(sf::Color::White);
            window.draw(text);
        }
    }

    window.display();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), GAME_TITLE, sf::Style::Close | sf::Style::Titlebar);
    window.setPosition(sf::Vector2i(window.getPosition().x / 2, window.getPosition().y / 2));
    window.setFramerateLimit(FRAMERATE_GAME);

    sf::Music music;
    music.openFromFile("Resources/AMagicalJourneyThroughSpace_LeonellCassio.ogg");
    music.setVolume(50.f);
    music.setLoop(true);
    music.play();

    asteroidSound.soundbuffer.loadFromFile("Resources/mixkit-sea-mine-explosion-1184.ogg");
    asteroidSound.setBuffer();

    sf::Clock game_clock;
    float delta_time        = 0.0f;
    float last_time         = 0.0f;

    /** WHEN START **/
    whenMainMenuStart(window);
    space_texture.loadFromFile("Resources/space.png");
    default_font.loadFromFile("Resources/DEFAULT_FONT.ttf");
    whenStart(window);

    while(window.isOpen())
    {
        sf::Event game_event;
        while(window.pollEvent(game_event))
        {
            switch(game_event.type){
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }
        
        /** DELTA TIME **/
        float current_time      = game_clock.restart().asSeconds();
        delta_time              = (current_time - last_time + 0.1) / 10;
        float frames_per_sec    = (1.0f / current_time) + 1.0f;
        last_time               = current_time;

        tick(delta_time, window);
        render(window, delta_time, frames_per_sec);

        asteroidSound.checkPlay();
    }

    return 0;
}
