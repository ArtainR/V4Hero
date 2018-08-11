#include "Drum.h"
#include <iostream>

using namespace std;

Drum::Drum()
{
    t_flash.loadFromFile("resources/graphics/rhythm/drums/flash.png");
    s_flash.setTexture(t_flash);
}

void Drum::Load(string drum, int perfection, sf::RenderWindow& window)
{
    if(drum == "pata")
    {
        t_drum.loadFromFile("resources/graphics/rhythm/drums/pata.png");

        ///Describe the pattern of the drums being placed on the screen
        pattern_X.push_back(135); ///Drum 2
        pattern_Y.push_back(295);
        pattern_Angle.push_back(-20);
        pattern_Xspeed.push_back(-8);
        pattern_Yspeed.push_back(-200);
        pattern_rotateSpeed.push_back(40);

        pattern_X.push_back(100); ///Drum 4
        pattern_Y.push_back(410);
        pattern_Angle.push_back(-20);
        pattern_Xspeed.push_back(-8);
        pattern_Yspeed.push_back(140);
        pattern_rotateSpeed.push_back(-40);


        pattern_X.push_back(80); ///Drum 3
        pattern_Y.push_back(340);
        pattern_Angle.push_back(3);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-20);
        pattern_rotateSpeed.push_back(60);

        pattern_X.push_back(95); ///Drum 1
        pattern_Y.push_back(220);
        pattern_Angle.push_back(-7);
        pattern_Xspeed.push_back(20);
        pattern_Yspeed.push_back(-20);
        pattern_rotateSpeed.push_back(-60);


        pattern_X.push_back(100); ///Drum 4
        pattern_Y.push_back(410);
        pattern_Angle.push_back(-15);
        pattern_Xspeed.push_back(-8);
        pattern_Yspeed.push_back(140);
        pattern_rotateSpeed.push_back(-40);

        pattern_X.push_back(135); ///Drum 2
        pattern_Y.push_back(295);
        pattern_Angle.push_back(-23);
        pattern_Xspeed.push_back(-8);
        pattern_Yspeed.push_back(-200);
        pattern_rotateSpeed.push_back(40);


        pattern_X.push_back(80); ///Drum 3
        pattern_Y.push_back(340);
        pattern_Angle.push_back(3);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-20);
        pattern_rotateSpeed.push_back(60);

        pattern_X.push_back(95); ///Drum 1
        pattern_Y.push_back(220);
        pattern_Angle.push_back(-7);
        pattern_Xspeed.push_back(20);
        pattern_Yspeed.push_back(-20);
        pattern_rotateSpeed.push_back(-60);
    }

    if(drum == "pon")
    {
        t_drum.loadFromFile("resources/graphics/rhythm/drums/pon.png");

        ///Describe the pattern of the drums being placed on the screen
        pattern_X.push_back(1140); ///Drum 2
        pattern_Y.push_back(290);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-10);
        pattern_rotateSpeed.push_back(-60);

        pattern_X.push_back(1165); ///Drum 4
        pattern_Y.push_back(410);
        pattern_Angle.push_back(20);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-40);
        pattern_rotateSpeed.push_back(30);


        pattern_X.push_back(1110); ///Drum 3
        pattern_Y.push_back(340);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(20);
        pattern_Yspeed.push_back(20);
        pattern_rotateSpeed.push_back(-30);

        pattern_X.push_back(1135); ///Drum 1
        pattern_Y.push_back(220);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(10);
        pattern_Yspeed.push_back(100);
        pattern_rotateSpeed.push_back(50);


        pattern_X.push_back(1165); ///Drum 4
        pattern_Y.push_back(410);
        pattern_Angle.push_back(20);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-40);
        pattern_rotateSpeed.push_back(30);

        pattern_X.push_back(1140); ///Drum 2
        pattern_Y.push_back(290);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(-10);
        pattern_rotateSpeed.push_back(-60);


        pattern_X.push_back(1110); ///Drum 3
        pattern_Y.push_back(340);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(20);
        pattern_Yspeed.push_back(20);
        pattern_rotateSpeed.push_back(-30);

        pattern_X.push_back(1135); ///Drum 1
        pattern_Y.push_back(220);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(10);
        pattern_Yspeed.push_back(100);
        pattern_rotateSpeed.push_back(50);
    }

    if(drum == "don")
    {
        t_drum.loadFromFile("resources/graphics/rhythm/drums/don.png");

        ///Describe the pattern of the drums being placed on the screen
        pattern_X.push_back(690); ///Drum 3
        pattern_Y.push_back(650);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(-30);
        pattern_Yspeed.push_back(-30);
        pattern_rotateSpeed.push_back(40);

        pattern_X.push_back(515); ///Drum 1
        pattern_Y.push_back(660);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(-50);
        pattern_Yspeed.push_back(-50);
        pattern_rotateSpeed.push_back(60);


        pattern_X.push_back(605); ///Drum 2
        pattern_Y.push_back(665);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(-50);
        pattern_Yspeed.push_back(-50);
        pattern_rotateSpeed.push_back(-60);

        pattern_X.push_back(780); ///Drum 4
        pattern_Y.push_back(670);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(90);
        pattern_Yspeed.push_back(-30);
        pattern_rotateSpeed.push_back(-60);


        pattern_X.push_back(515); ///Drum 1
        pattern_Y.push_back(660);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(-50);
        pattern_Yspeed.push_back(-50);
        pattern_rotateSpeed.push_back(60);

        pattern_X.push_back(690); ///Drum 3
        pattern_Y.push_back(650);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(-30);
        pattern_Yspeed.push_back(-30);
        pattern_rotateSpeed.push_back(40);


        pattern_X.push_back(605); ///Drum 2
        pattern_Y.push_back(665);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(-50);
        pattern_Yspeed.push_back(-50);
        pattern_rotateSpeed.push_back(-60);

        pattern_X.push_back(780); ///Drum 4
        pattern_Y.push_back(670);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(90);
        pattern_Yspeed.push_back(-30);
        pattern_rotateSpeed.push_back(-60);

        isDon = true;
    }

    if(drum == "chaka")
    {
        t_drum.loadFromFile("resources/graphics/rhythm/drums/chaka.png");

        ///Describe the pattern of the drums being placed on the screen
        pattern_X.push_back(635); ///Drum 3
        pattern_Y.push_back(105);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(10);
        pattern_Yspeed.push_back(20);
        pattern_rotateSpeed.push_back(40);

        pattern_X.push_back(460); ///Drum 1
        pattern_Y.push_back(70);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(-70);
        pattern_Yspeed.push_back(30);
        pattern_rotateSpeed.push_back(-60);


        pattern_X.push_back(550); ///Drum 2
        pattern_Y.push_back(75);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(40);
        pattern_rotateSpeed.push_back(20);

        pattern_X.push_back(715); ///Drum 4
        pattern_Y.push_back(85);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(40);
        pattern_Yspeed.push_back(-60);
        pattern_rotateSpeed.push_back(60);


        pattern_X.push_back(460); ///Drum 1
        pattern_Y.push_back(70);
        pattern_Angle.push_back(10);
        pattern_Xspeed.push_back(-70);
        pattern_Yspeed.push_back(30);
        pattern_rotateSpeed.push_back(-60);

        pattern_X.push_back(635); ///Drum 3
        pattern_Y.push_back(105);
        pattern_Angle.push_back(0);
        pattern_Xspeed.push_back(10);
        pattern_Yspeed.push_back(20);
        pattern_rotateSpeed.push_back(40);


        pattern_X.push_back(550); ///Drum 2
        pattern_Y.push_back(75);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(-40);
        pattern_Yspeed.push_back(40);
        pattern_rotateSpeed.push_back(20);

        pattern_X.push_back(715); ///Drum 4
        pattern_Y.push_back(85);
        pattern_Angle.push_back(-10);
        pattern_Xspeed.push_back(40);
        pattern_Yspeed.push_back(-60);
        pattern_rotateSpeed.push_back(60);
    }

    if(perfection == 0) ///BEST beat
    {
        if(!isDon)
        {
            x_scale = 1.2;
            y_scale = 1.2;
        }

        isBest = true;
    }

    t_drum.setSmooth(true);

    drumClock.restart();
}

void Drum::Draw(sf::RenderWindow& window)
{
    float ratio_X = window.getSize().x / float(1280);
    float ratio_Y = window.getSize().y / float(720);

    if(isDon)
    {
        if(isBest)
        {
            x_scale += 1 / fps;
            y_scale += 1 / fps;
            rotation += pattern_rotateSpeed[pattern] / fps;
            x += pattern_Xspeed[pattern] / fps;
            y += pattern_Yspeed[pattern] / fps;

            alpha -= float(510) / fps;

            if(alpha <= 0)
            alpha = 0;
        }
        else
        {
            if(drumClock.getElapsedTime().asSeconds() > 0.5)
            {
                alpha -= float(510) / fps;

                if(alpha <= 0)
                alpha = 0;
            }
        }
    }
    else
    {
        if(drumClock.getElapsedTime().asSeconds() > 0.5)
        {
            if(isBest)
            {
                x_scale += 1 / fps;
                y_scale += 1 / fps;
                rotation += pattern_rotateSpeed[pattern] / fps;
                x += pattern_Xspeed[pattern] / fps;
                y += pattern_Yspeed[pattern] / fps;
            }

            alpha -= float(510) / fps;

            if(alpha <= 0)
            alpha = 0;
        }
        else
        {
            if(isBest)
            {
                if(drumClock.getElapsedTime().asMilliseconds() <= 25)
                {
                    if((x_scale >= 1.2) && (y_scale >= 1.2))
                    {
                        x_scale += 1 / fps;
                        y_scale += 1 / fps;
                    }
                }
                else
                {
                    if((x_scale > 1) && (y_scale > 1))
                    {
                        x_scale -= 3 / fps;
                        y_scale -= 3 / fps;
                    }
                    else
                    {
                        x_scale = 1;
                        y_scale = 1;
                    }
                }
            }
        }
    }

    s_drum.setTexture(t_drum);
    s_drum.setScale(x_scale*ratio_X,y_scale*ratio_Y);
    s_drum.setColor(sf::Color(255,255,255,alpha));
    s_drum.setRotation(rotation+pattern_Angle[pattern]);

    s_drum.setOrigin(s_drum.getLocalBounds().width/2,s_drum.getLocalBounds().height/2);

    s_drum.setPosition(x+pattern_X[pattern]*ratio_X,y+pattern_Y[pattern]*ratio_Y);

    if(drumClock.getElapsedTime().asMilliseconds() < 200)
    {
        x_flashscale += float(15) / fps;
        y_flashscale += float(15) / fps;
        flashalpha -= float(800) / fps;
    }
    else
    {
        flashalpha = 0;
    }

    if(flashalpha <= 0)
    flashalpha = 0;

    s_flash.setTexture(t_flash);
    s_flash.setColor(sf::Color(255,255,255,flashalpha));
    s_flash.setScale(x_flashscale*ratio_X,y_flashscale*ratio_Y);
    s_flash.setOrigin(s_flash.getLocalBounds().width/2,s_flash.getLocalBounds().height/2);
    s_flash.setPosition(x+pattern_X[pattern]*ratio_X,y+pattern_Y[pattern]*ratio_Y);

    window.draw(s_drum);
    window.draw(s_flash);
}