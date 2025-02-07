#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Component.h"
#include "LayoutComponent.h"

namespace Engine
{
	class Row : Component
	{
	public:
		Row(int x, int y, int w, int h, int padding) :
			Component(x, y, w, h), 
			percentilePadding((static_cast<float>(padding)/h)*100.0f)
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
		int percentilePadding = 0;
		int overallPercentage = 0;
	};
}