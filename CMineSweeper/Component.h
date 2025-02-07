#pragma once
#include <SDL.h>
#include "Globals.h"

namespace Engine
{
	class Component
	{
	public:
		Component(int x, int y, int w, int h) :
			container{ x, y, w, h } {
		}

		bool IsWithinBounds(int x, int y) const
		{
			if (x < container.x) return false;
			if (y < container.y) return false;
			if (x > container.x + container.w) return false;
			if (y > container.y + container.h) return false;

			return true;
		}

		SDL_Rect* GetRect() { return &container; }

		virtual void Render(SDL_Surface* surface) {}

		virtual ~Component() = default;

	protected:
		SDL_Rect container{ 0,0,0,0 };
	};
}