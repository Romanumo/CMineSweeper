#pragma once
#include <vector>
#include "Globals.h"
#include "Cell.h"
#include "Random.h"

class Grid
{
public:
	Grid(int x, int y)
	{
		using namespace Config;
		children.reserve(GRID_COLUMNS * GRID_ROWS);
		for (int col = 0; col < GRID_COLUMNS;col++)
		{
			for (int row = 0; row < GRID_ROWS;row++)
			{
				constexpr int spacing = CELL_SIZE + PADDING;
				children.emplace_back(
					x + spacing * col,
					y + spacing * row,
					CELL_SIZE, CELL_SIZE, row + 1, col + 1
				);
			}
		}

		PlaceBombs();
	}

	void Render(SDL_Surface* surface)
	{
		for (auto& child : children)
		{
			child.Render(surface);
		}
	}

	void HandleEvent(const SDL_Event& event)
	{
		if (event.type == UserEvents::CELL_CLEARED)
		{
			HandleCellCleared(event.user);
		}
		if (event.type == UserEvents::NEW_GAME)
		{
			for (auto& child : children)
			{
				child.Reset();
			}

			PlaceBombs();
		}

		for (auto& child : children)
		{
			child.HandleEvent(event);
		}
	}

private:
	std::vector<Cell> children;
	int cellsToClear = 0;

	void PlaceBombs()
	{
		int bombsToPlace = Config::BOMB_COUNT;
		cellsToClear =
			Config::GRID_COLUMNS * Config::GRID_ROWS - Config::BOMB_COUNT;

		while (bombsToPlace > 0)
		{
			const size_t randomIndex =
				Engine::Random::Int(0, children.size() - 1);
			if (children[randomIndex].PlaceBomb())
			{
				--bombsToPlace;
			}
		}
	}

	void HandleCellCleared(const SDL_UserEvent& event)
	{
		auto* cell = static_cast<Cell*>(event.data1);
		if (cell->HasBomb())
		{
			SDL_Event gameLost{UserEvents::GAME_LOST};
			SDL_PushEvent(&gameLost);
		}
		else
		{
			--cellsToClear;
			if (cellsToClear == 0)
			{
				SDL_Event gameWon{ UserEvents::GAME_WON };
				SDL_PushEvent(&gameWon);
			}
		}
	}
};