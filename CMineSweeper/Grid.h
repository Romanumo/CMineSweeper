#pragma once
#include <vector>

#include "Engine/Globals.h"
#include "Engine/Random.h"
#include "Engine/Component.h"
#include "Cell.h"

//Manage subscription system for triggering of certain events
//So that not every cell look for events
//But the grid sends them to needed cells

class Grid : public Engine::Component
{
public:
	Grid(int x, int y);

	void Render(SDL_Surface* surface) override;
	void HandleEvent(const SDL_Event& event) override;

private:
	int cellsToClear = 0;

	void RefreshGrid();

	void PlaceBombs(Cell& openedCell);
	void SetBombHints(const Cell& bombCell);
	void HandleCellCleared(const Cell& openedCell);

	Cell* GetChildToCell(int index);
	std::vector<Cell*> GetNeigborCells(const Cell& cell);
	bool IsCellInsideArea(std::vector<Cell*> area, Cell* cell);
};