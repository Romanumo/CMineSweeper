#pragma once
#include <string>

#include "Engine/Globals.h"

#include "Engine/Rectangle.h"
#include "Engine/Image.h"
#include "Engine/Text.h"
#include "Engine/Row.h"

class FlagCounter : public Engine::Rectangle
{
public:
    FlagCounter(int x, int y, int w, int h) :
        Rectangle{ x, y, w, h, Config::COUNTER_COLOR },
        image{ new Engine::Image{0, 0,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FOOTER_HEIGHT - Config::PADDING,
            Config::FLAG_IMAGE} },
        text{ new Engine::Text{0, 0,
            w - Config::FOOTER_HEIGHT - 24, h,
            std::to_string(Config::BOMB_COUNT),
            {255, 255, 255, 255}, 30} },
        layout{new Engine::Row{ Config::PADDING, Config::PADDING, 0, 0,
            std::vector<Engine::Component*>{
            image, text
            }}}
    {
        layout->SetAsChildOf(this);
    }

    void Render(SDL_Surface* surface) override
    {
        Rectangle::Render(surface);
        layout->Render(surface);
    }

    void HandleEvent(const SDL_Event& event) 
    {
        /*if (event.type == SDL_MOUSEMOTION)
        {
            SetRelPosition(event.motion.x, event.motion.y);
        }*/

        if (event.type == UserEvents::FLAG_PLACED) 
        {
            --flagsAvailable;
        }
        else if (event.type == UserEvents::FLAG_CLEARED) 
        {
            ++flagsAvailable;
        }
        else if (event.type == UserEvents::GAME_WON)
        {
            flagsAvailable = 0;
        }
        else if (event.type == UserEvents::NEW_GAME) 
        {
            flagsAvailable = Config::BOMB_COUNT;
        }
        else { return; }

        text->SetText(std::to_string(flagsAvailable));
    }

private:
    Engine::Image* image;
    Engine::Text* text;
    Engine::Row* layout;

    int flagsAvailable = Config::BOMB_COUNT;
};