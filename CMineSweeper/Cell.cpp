#include "Cell.h"
#include <iostream>
#include "Globals.h"

//But every CELL has A BOMB IMAGE
Cell::Cell(int x, int y, int w, int h, int row, int col) :
	Button{ x, y, w, h }, row(row), col(col),
	bombImage{x, y, w, h, Config::BOMB_IMAGE},
	flagImage{ x, y, w, h, Config::FLAG_IMAGE },
	text{x, y, w, h,
	std::to_string(adjacentBombs),
	Config::TEXT_COLORS[adjacentBombs]} 
{
	bombImage.SetAsChildOf(this);
	flagImage.SetAsChildOf(this);
	text.SetAsChildOf(this);
};

void Cell::HandleEvent(const SDL_Event& event) 
{
	if (event.type == UserEvents::CELL_CLEARED)
	{
		HandleClearedCell(event.user);
	}
	else if (event.type == UserEvents::BOMB_PLACED)
	{
		HandlePlacedBomb(event.user);
	}
	else if(event.type == UserEvents::GAME_LOST || 
		event.type == UserEvents::GAME_WON)
	{
		if (HasBomb())
		{
			SetColor((event.type == UserEvents::GAME_LOST) ? 
					Config::BUTTON_FAILURE_COLOR : Config::BUTTON_SUCCESS_COLOR);
			isCleared = true;
		}

		SetEnabled(false);
	}

	Button::HandleEvent(event);
}

void Cell::Render(SDL_Surface* surface)
{
	Button::Render(surface);
	if (isCleared && hasBomb)
	{
		bombImage.Render(surface);
	}
	else if (hasFlag)
	{
		flagImage.Render(surface);
	}
	else if (isCleared && adjacentBombs > 0)
	{
		text.Render(surface);
	}
#ifdef SHOW_DEBUG_HELPERS
	else if (hasBomb)
	{
		bombImage.Render(surface);
	}
	else if (adjacentBombs > 0)
	{
		text.Render(surface);
	}
#endif // SHOW_DEBUG_HELPERS
}

void Cell::ClearCell()
{
	if (isCleared) return;
	if (hasFlag) return;

	isCleared = true;
	SetEnabled(false);
	SetColor(Config::BUTTON_CLEARED_COLOR);
	ReportEvent(UserEvents::CELL_CLEARED);
}

void Cell::HandleLeftClick()
{
	ClearCell();
}

void Cell::HandleRightClick()
{
	hasFlag = !hasFlag;

	ReportEvent((hasFlag) ? UserEvents::FLAG_PLACED : UserEvents::FLAG_CLEARED);
}

void Cell::ReportEvent(uint32_t eventType)
{
	SDL_Event event{eventType};
	event.user.data1 = this;
	SDL_PushEvent(&event);
}

bool Cell::PlaceBomb()
{
	if (hasBomb) return false;

	hasBomb = true;
	ReportEvent(UserEvents::BOMB_PLACED);
	return true;
}

bool Cell::IsAdjacent(Cell* other) const
{
	return !(other == this) &&
		std::abs(GetRow() - other->GetRow()) <= 1 &&
		std::abs(GetCol() - other->GetCol()) <= 1;
}

void Cell::HandlePlacedBomb(const SDL_UserEvent& event)
{
	Cell* bombCell = static_cast<Cell*>(event.data1);

	if (IsAdjacent(bombCell))
	{
		++adjacentBombs;
		text.SetText(std::to_string(adjacentBombs),
				Config::TEXT_COLORS[adjacentBombs]);
	}
}

void Cell::HandleClearedCell(const SDL_UserEvent& event)
{
	Cell* clearedCell = static_cast<Cell*>(event.data1);

	if (clearedCell->HasBomb()) return;
	
	if (IsAdjacent(clearedCell) && clearedCell->adjacentBombs == 0)
	{
		ClearCell();
	}
}

void Cell::Reset()
{
	isCleared = false;
	hasBomb = false;
	hasFlag = false;
	adjacentBombs = 0;
	SetEnabled(true);
	SetColor(Config::BUTTON_COLOR);
}