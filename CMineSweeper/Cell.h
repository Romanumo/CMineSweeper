#pragma once
#include "Button.h"
#include "Image.h"
#include "Text.h"

class Cell : public Engine::Button
{
public:
	Cell(int x, int y, int w, int h, int row, int col);

	void HandleEvent(const SDL_Event& event) override;
	void Render(SDL_Surface* surface) override;

	void HandleLeftClick() override;
	void HandleRightClick() override;

	bool PlaceBomb();
	void Reset();

	[[nodiscard]]
	bool HasBomb() const { return hasBomb; }

	[[nodiscard]]
	int GetRow() const { return row; }

	[[nodiscard]]
	int GetCol() const { return col; }

private:
	int row;
	int col;

	void ClearCell();
	bool isCleared = false;
	bool hasBomb = false;
	bool hasFlag = false;

	void ReportEvent(uint32_t eventType);
	bool IsAdjacent(Cell* cell) const;

	void HandlePlacedBomb(const SDL_UserEvent& event);
	void HandleClearedCell(const SDL_UserEvent& event);
	int adjacentBombs = 0;

	Engine::Image flagImage;
	Engine::Image bombImage;
	Engine::Text text;
};