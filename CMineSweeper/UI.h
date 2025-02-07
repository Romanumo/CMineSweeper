#pragma once
#include <SDL.h>
#include "Grid.h"
#include "Component.h"
#include "NewGameButton.h"
#include "FlagCounter.h"
#include "Row.h"

class MineSweeperUI
{
public:
	void Render(SDL_Surface* surface)
	{
		minesweeperGrid.Render(surface);
		layout.Render(surface);
	}

	void HandleEvent(const SDL_Event& event)
	{
		minesweeperGrid.HandleEvent(event);
		newGameButton.HandleEvent(event);
		counter.HandleEvent(event);
	}

private:
	Grid minesweeperGrid{Config::PADDING, Config::PADDING};

	NewGameButton newGameButton{0,
	Config::GRID_HEIGHT + Config::PADDING * 2,
	Config::GRID_WIDTH - Config::COUNTER_WIDTH,
	Config::FOOTER_HEIGHT - Config::PADDING };

	FlagCounter counter{ 0,
	Config::GRID_HEIGHT + Config::PADDING * 2,
	Config::COUNTER_WIDTH - Config::PADDING,
	Config::FOOTER_HEIGHT - Config::PADDING
	};

	Engine::Row layout{ Config::PADDING, Config::PADDING,
		Config::GRID_HEIGHT + Config::PADDING,
		std::vector<Engine::Component*>{
		&newGameButton, &counter
		} 
	};
};