#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Layout.h"

namespace Engine
{
	class Row : public Layout
	{
	public:
		Row(int padding, int x, int y, std::vector<Component*> components) :
			Layout(padding, x,y,components)
		{
			HandleChildPosition();
		}

		Row(std::vector<Component*> components) :
			Row(Config::PADDING, Config::PADDING, Config::PADDING, components) {
		}

	protected:
		void HandleChildPosition() override
		{
			if (children.size() < 1) return;

			const SDL_Rect* rect = GetRect();
			int xLength = 0;

			for (Component* component : children)
			{
				component->SetRelPosition(xLength, GetPadding());
				xLength += component->GetRect()->w + GetPadding();
			}
		}

		void StretchContainer(const SDL_Rect* objRect, 
							const SDL_Rect* myRect) override
		{
			int updatedW = 0;
			int updatedH = 0;

			updatedW = objRect->w + myRect->w + GetPadding();
			if (objRect->h > myRect->h)
			{
				updatedH = objRect->h;
			}

			SetRelSize(updatedW, updatedH);
		}
	};
}