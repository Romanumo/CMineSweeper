#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Layout.h"

namespace Engine
{
	class Column : public Layout
	{
	public:
		Column(int padding, int margin, int x, int y, std::vector<Component*> components) :
			Layout(padding, margin, x, y, components) 
		{
			HandleChildPosition();
		}

		Column(int padding, int margin, std::vector<Component*> components) :
			Column(padding, margin, 0, 0, components) {
		}

		Column(std::vector<Component*> components) :
			Column(Config::PADDING, 0, 0,0, components) {}

	protected:
		void HandleChildPosition() override
		{
			if (children.size() < 1) return;

			const SDL_Rect* rect = GetRect();
			int yLength = GetMargin();

			for (Component* component : children)
			{
				component->SetRelPosition(GetMargin(), yLength);
				yLength += component->GetRect()->h + GetPadding();
			}
		}

		void StretchContainer(const SDL_Rect* objRect,
			const SDL_Rect* myRect) override
		{
			int updatedW = 0;
			int updatedH = 0;

			updatedH = objRect->h + myRect->h + GetPadding();
			if (objRect->w > myRect->w)
			{
				updatedW = objRect->w;
			}

			SetRelSize(updatedW, updatedH);
		}
	};
}