#pragma once
#include <vector>
#include "Globals.h"
#include "Cell.h"

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
		for (auto& child : children)
		{
			child.HandleEvent(event);
		}
	}

private:
	std::vector<Cell> children;
};