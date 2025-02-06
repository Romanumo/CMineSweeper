#pragma once
#include <string>

#include "Globals.h"

#include "Rectangle.h"
#include "Image.h"
#include "Text.h"

class FlagCounter : public Engine::Rectangle
{
public:
    FlagCounter(int x, int y, int w, int h) :
        Rectangle{ x, y, w, h, Config::COUNTER_COLOR },
        image{x + Config::PADDING, y + Config::PADDING,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FLAG_IMAGE, 24 },
        text {x + Config::FOOTER_HEIGHT, y,
            w - Config::FOOTER_HEIGHT - 24, h,
            std::to_string(Config::BOMB_COUNT),
            {255, 255, 255, 255}, 30} {}

    void Render(SDL_Surface* surface) override
    {
        Rectangle::Render(surface);
        image.Render(surface);
        text.Render(surface);
    }

    void HandleEvent(const SDL_Event& E) 
    {
        if (E.type == UserEvents::FLAG_PLACED) 
        {
            --flagsAvailable;
        }
        else if (E.type == UserEvents::FLAG_CLEARED) 
        {
            ++flagsAvailable;
        }
        else if (E.type == UserEvents::GAME_WON)
        {
            flagsAvailable = 0;
        }
        else if (E.type == UserEvents::NEW_GAME) 
        {
            flagsAvailable = Config::BOMB_COUNT;
        }
        else { return; }

        text.SetText(std::to_string(flagsAvailable));
    }

private:
    Engine::Image image;
    Engine::Text text;
    int flagsAvailable = Config::BOMB_COUNT;
};