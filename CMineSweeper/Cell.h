#pragma once
#include "Button.h"

class Cell : public Engine::Button
{
public:
	Cell(int x, int y, int w, int h, int row, int col);

	void HandleEvent(const SDL_Event& event) override;
	void Render(SDL_Surface* surface) override;

	void HandleLeftClick() override;

	[[nodiscard]]
	int GetRow() const { return row; }

	[[nodiscard]]
	int GetCol() const { return col; }

private:
	int row;
	int col;

	void ClearCell();
	bool isCleared = false;

	void ReportEvent(uint32_t eventType);
};

