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

#ifdef SHOW_DEBUG_HELPERS
	MineSweeperUI()
	{
		layout.PrintFamilyTree();
	}
#endif // SHOW_DEBUG_HELPERS


	void Render(SDL_Surface* surface)
	{
		minesweeperGrid.Render(surface);
		layout.Render(surface);
	}

	void HandleEvent(const SDL_Event& event)
	{
		minesweeperGrid.HandleEvent(event);
		layout.HandleEvent(event);
	}

private:
	Grid minesweeperGrid{Config::PADDING, Config::PADDING};

	NewGameButton newGameButton{0, 0,
	Config::GRID_WIDTH - Config::COUNTER_WIDTH,
	Config::FOOTER_HEIGHT - Config::PADDING };

	FlagCounter counter{ 0,0,
	Config::COUNTER_WIDTH - Config::PADDING,
	Config::FOOTER_HEIGHT - Config::PADDING
	};

	Engine::Row layout{ Config::PADDING, Config::PADDING,
		Config::GRID_HEIGHT + Config::PADDING,
		std::vector<Engine::Component*>{
		&counter, &newGameButton
		} 
	};
};