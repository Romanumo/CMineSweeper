#include "Cell.h"
#include <iostream>
#include "Globals.h"

Cell::Cell(int x, int y, int w, int h, int row, int col) :
	Button{ x, y, w, h }, row(row), col(col) {};

void Cell::HandleEvent(const SDL_Event& event)
{
	if (event.type == UserEvents::CELL_CLEARED)
	{
		std::cout << "A cell is cleared" << std::endl;
	}

	Button::HandleEvent(event);
}

void Cell::Render(SDL_Surface* surface)
{
	Button::Render(surface);
}

void Cell::ClearCell()
{
	if (isCleared) return;

	isCleared = true;
	SetEnabled(false);
	SetColor(Config::BUTTON_CLEARED_COLOR);
	ReportEvent(UserEvents::CELL_CLEARED);
}

void Cell::HandleLeftClick()
{
	ClearCell();
}

void Cell::ReportEvent(uint32_t eventType)
{
	SDL_Event event{eventType};
	event.user.data1 = this;
	SDL_PushEvent(&event);
}