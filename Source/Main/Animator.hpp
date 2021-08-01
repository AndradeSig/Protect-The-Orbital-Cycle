#include <bits/stdc++.h>
#include <SFML/Graphics.hpp>

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

    void addAnimHere(std::pair<float, float> new_position)
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
