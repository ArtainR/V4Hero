#ifndef DRUM_H
#define DRUM_H

#include <SFML/Graphics.hpp>

class Drum
{
    public:
    sf::Texture t_drum;
    sf::Texture t_flash;

    sf::Sprite s_drum;
    sf::Sprite s_flash;

    sf::Clock drumClock;
    float alpha = 255;

    float x=0,y=0;
    float x_scale=1,y_scale=1;

    float x_flashscale=0.01,y_flashscale=0.01;
    float flashalpha = 125;

    float rotation = 0;
    float fps=60;
    bool isBest = false;
    bool isDon = false;

    std::vector<float> pattern_X;
    std::vector<float> pattern_Y;
    std::vector<float> pattern_Angle;
    std::vector<float> pattern_Xspeed;
    std::vector<float> pattern_Yspeed;
    std::vector<float> pattern_rotateSpeed;

    int pattern = 0;

    Drum();
    void Load(std::string drum, int perfection, sf::RenderWindow& window);
    void Draw(sf::RenderWindow& window);
};

#endif // DRUM_H