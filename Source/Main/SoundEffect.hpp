#include <bits/stdc++.h>
#include <SFML/Audio.hpp>

class SoundEffect{
    bool _shouldPlay;
public:
    sf::SoundBuffer soundbuffer;
    sf::Sound       sound;

    void setBuffer(){
        sound.setBuffer(soundbuffer);
    }

    bool getShouldPlay(){
        if ( _shouldPlay){
            _shouldPlay = false;
            return true;    
        }
        if (!_shouldPlay){
            return false;
        }
    };

    void setShouldPlay(bool value){
        _shouldPlay = value;
    }

    void checkPlay(){
        if (getShouldPlay())
            sound.play();
    }
};