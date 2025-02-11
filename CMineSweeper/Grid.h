#pragma once
#include <vector>
#include "Globals.h"
#include "Cell.h"
#include "Random.h"
#include "Component.h"

class Grid : public Engine::Component
{
public:
	Grid(int x, int y) : Component(x, y, 0, 0)
	{
		using namespace Config;
		children.reserve(GRID_COLUMNS * GRID_ROWS);

		constexpr int spacing = CELL_SIZE + PADDING;
		SetRelSize(GRID_COLUMNS * spacing - PADDING,
					GRID_ROWS * spacing - PADDING);

		for (int col = 0; col < GRID_COLUMNS;col++)
		{
			for (int row = 0; row < GRID_ROWS;row++)
			{
				Cell* cell  = new Cell(0,0,
					CELL_SIZE, CELL_SIZE, row + 1, col + 1
				);
				cell->SetRelPosition(col * spacing,row * spacing);

				cell->SetAsChildOf(this);
			}
		}

		PlaceBombs();
	}

	void Render(SDL_Surface* surface) override
	{
		for (Component* child : children)
		{
			child->Render(surface);
		}
	}

	void HandleEvent(const SDL_Event& event) override
	{
		if (event.type == UserEvents::CELL_CLEARED)
		{
			HandleCellCleared(event.user);
		}
		if (event.type == UserEvents::NEW_GAME)
		{
			for (Component* child : children)
			{
				if (Cell* cell = dynamic_cast<Cell*>(child))
				{
					cell->Reset();				
				}
			}

			PlaceBombs();
		}

		for (Component* child : children)
		{
			child->HandleEvent(event);
		}
	}

protected:
	/*virtual void HandleChildPosition()
	{
		if (children.size() < 1) return;

		using namespace Config;
		for (int col = 0; col < GRID_COLUMNS;col++)
		{
			for (int row = 0; row < GRID_ROWS;row++)
			{
				constexpr int spacing = CELL_SIZE + PADDING;
				children[col * GRID_ROWS + row]->
			}
		}
	}*/

private:
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

			if (Cell* cell = dynamic_cast<Cell*>(children[randomIndex]))
			{
				if (cell->PlaceBomb())
				{
					--bombsToPlace;
				}
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