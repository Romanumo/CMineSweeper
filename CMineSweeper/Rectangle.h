#pragma once
#include <SDL.h>
#include "Globals.h"

namespace Engine
{
	class Rectangle
	{
	public:
		Rectangle(int x, int y, int w, int h,
			SDL_Color color = { 0,0,0, 255 }) :
			rect{ x, y, w, h }, color(color) {
		}

		virtual void Render(SDL_Surface* surface)
		{
			SDL_FillRect(surface, &rect, SDL_MapRGB(
				surface->format,
				color.r, color.g, color.b));
		}

		void SetColor(SDL_Color col) { color = col; }

		bool IsWithinBounds(int x, int y) const
		{
			if (x < rect.x) return false;
			if (y < rect.y) return false;
			if (x > rect.x + rect.w) return false;
			if (y > rect.y + rect.h) return false;

			return true;
		}

		SDL_Rect* GetRect() { return &rect; }

		virtual ~Rectangle() = default;

	private:
		SDL_Rect rect{ 0,0,0,0 };
		SDL_Color color{ 0,0,0,0 };
	};
}