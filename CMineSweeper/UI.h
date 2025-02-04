#pragma once
#include <SDL.h>
#include "Grid.h"

class MineSweeperUI
{
public:
	void Render(SDL_Surface* surface)
	{
		minesweeperGrid.Render(surface);
	}

	void HandleEvent(const SDL_Event& event)
	{
		minesweeperGrid.HandleEvent(event);
	}

private:
	Grid minesweeperGrid{Config::PADDING, Config::PADDING};
};