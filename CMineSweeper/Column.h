#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Component.h"
#include "LayoutComponent.h"
#include "Globals.h"

namespace Engine
{
	class Column : Component
	{
	public:
		Column(int x, int y, int w, int h) :
			Component(x, y, w, h)
		{
			children.reserve(Config::MAX_LAYOUT_COUNT);
		}

		void AddComponent(Component& object, int percentage)
		{
			if (overallPercentage + percentage > 100)
			{
				std::cout << "Column exceeds combined components size" << std::endl;
				return;
			}

			children.push_back(LayoutComponent(object, percentage));
			overallPercentage += percentage;
		}

		void Render(SDL_Surface* surface) override
		{
			for (LayoutComponent component : children)
			{
				component.GetComponent()->Render(surface);
			}
		}

	private:
		std::vector<LayoutComponent> children;
		int overallPercentage = 0;
	};
}