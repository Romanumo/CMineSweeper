#pragma once
#include <vector>

#include "Engine/Globals.h"
#include "Engine/Random.h"
#include "Engine/Component.h"
#include "FlagCounter.h"
#include "EventManager.h"
#include "Cell.h"

//Cells observer of grid. Grid notifies cells of certain userEvents happening
//Cells can subscribe to certain events
//Make a separate event receiver and notifier abstract classes/interfaces?

class Grid : public Engine::Component, public EventManager
{
public:
	Grid(int x, int y, FlagCounter* flagCounter);

	void Render(SDL_Surface* surface) override;
	void HandleEvent(const SDL_Event& event) override;

	bool ReceiveFlagPlacement();
	void ReceiveFlagRemoval();
	void SetFlagCounter(FlagCounter* counter);

private:
	int cellsToClear = 0;
	int flagsAvailable = Config::BOMB_COUNT;
	FlagCounter* flagCounter;

	void RefreshGrid();

	void PlaceBombs(Cell& openedCell);
	void SetBombHints(const Cell& bombCell);
	void HandleCellCleared(const Cell& openedCell);

	Cell* GetChildToCell(int index);
	std::vector<Cell*> GetNeigborCells(const Cell& cell);
	bool IsCellInsideArea(std::vector<Cell*> area, Cell* cell);
};