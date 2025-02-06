#pragma once
#include "Button.h"
#include "GLobals.h"
#include "Text.h"

class NewGameButton : public Engine::Button
{
public:
	NewGameButton(int x, int y, int w, int h) :
		Button{ x, y, w, h },
		text{ x, y, w, h, "New Game", {}, 40 } {};

	void Render(SDL_Surface* surface) override
	{
		Button::Render(surface);
		text.Render(surface);
	}

	void HandleLeftClick() override
	{
		SDL_Event newGame{ UserEvents::NEW_GAME };
		SDL_PushEvent(&newGame);
	}

private:
	Engine::Text text;
};