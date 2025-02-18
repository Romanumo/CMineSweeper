#pragma once
#include "Engine/Button.h"
#include "Engine/Image.h"
#include "Engine/Text.h"
#include "EventListener.h"

class Grid;

class Cell : public Engine::Button, public EventListener
{
public:
	Cell(int x, int y, int w, int h, int row, int col, Grid* parent);

	void Render(SDL_Surface* surface) override;

	void HandleLeftClick() override;
	void HandleRightClick() override;

	void ReceiveNotification(const SDL_Event& event) override;
	bool PlaceBomb();
	void Reset();

	[[nodiscard]]
	bool HasBomb() const { return hasBomb; }

	[[nodiscard]]
	int GetRow() const { return row; }

	[[nodiscard]]
	int GetCol() const { return col; }

	void PlaceHint();

private:
	int row;
	int col;
	Grid* gridParent;

	void ClearCell();
	bool isCleared = false;
	bool hasBomb = false;
	bool hasFlag = false;

	void ReportEvent(uint32_t eventType);

	bool IsAdjacent(Cell* cell) const;
	void HandleClearedCell(const SDL_UserEvent& event);
	int adjacentBombs = 0;

	Engine::Image* flagImage;
	Engine::Image* bombImage;
	Engine::Text* text;
};