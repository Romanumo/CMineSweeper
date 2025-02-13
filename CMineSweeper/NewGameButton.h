#pragma once
#include "Engine/Button.h"
#include "Engine/Globals.h"
#include "Engine/Text.h"

class NewGameButton : public Engine::Button
{
public:
	NewGameButton(int x, int y, int w, int h) :
		Button{ x, y, w, h },
		text{ new Engine::Text{x, y, w, h, "New Game", {}, 40 } }
	{
		text->SetAsChildOf(this);
	};

	void Render(SDL_Surface* surface) override
	{
		Button::Render(surface);
		text->Render(surface);
	}

	void HandleLeftClick() override
	{
		SDL_Event newGame{ UserEvents::NEW_GAME };
		SDL_PushEvent(&newGame);
	}

private:
	Engine::Text* text;
};