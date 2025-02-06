#pragma once
#include <SDL.h>
#include "Grid.h"
#include "NewGameButton.h"
#include "FlagCounter.h"

class MineSweeperUI
{
public:
	void Render(SDL_Surface* surface)
	{
		minesweeperGrid.Render(surface);
		newGameButton.Render(surface);
		counter.Render(surface);
	}

	void HandleEvent(const SDL_Event& event)
	{
		minesweeperGrid.HandleEvent(event);
		newGameButton.HandleEvent(event);
		counter.HandleEvent(event);
	}

private:
	Grid minesweeperGrid{Config::PADDING, Config::PADDING};

	NewGameButton newGameButton{ Config::PADDING,
	Config::GRID_HEIGHT + Config::PADDING * 2,
	Config::GRID_WIDTH - Config::COUNTER_WIDTH,
	Config::FOOTER_HEIGHT - Config::PADDING };

	FlagCounter counter{
	Config::WINDOW_WIDTH - Config::PADDING
	- Config::COUNTER_WIDTH,
	Config::GRID_HEIGHT + Config::PADDING * 2,
	Config::COUNTER_WIDTH,
	Config::FOOTER_HEIGHT - Config::PADDING
	};
};