#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Component.h"

namespace Engine
{
	class Row : public Component
	{
	public:
		Row(int padding, int x, int y, std::vector<Component*> components) :
			Component(x,y,0,0), padding(padding)
		{
			for (Component* component : components)
			{
				AddComponent(*component);
			}
		}

		void AddComponent(Component& child)
		{
			if (!child.SetAsChildOf(this)) return;

			const SDL_Rect* myRect = GetRect();
			const SDL_Rect* objRect = child.GetRect();
			child.SetPosition(myRect->w + myRect->x, myRect->y + padding);

			StretchContainer(objRect, myRect);
		}

		void StretchContainer(const SDL_Rect* objRect, const SDL_Rect* myRect)
		{
			int updatedW = 0;
			int updatedH = 0;

			updatedW = objRect->w + myRect->w + padding;
			if (objRect->h > myRect->h)
			{
				updatedH = objRect->h;
			}

			SetSize(updatedW, updatedH);
		}

		void Render(SDL_Surface* surface) override
		{
			for (Component* component : children)
			{
				component->Render(surface);
			}
		}

		void HandleEvent(const SDL_Event& event) override
		{
			for (Component* component : children)
			{
				component->HandleEvent(event);
			}
		}

		Row() = default;

	protected:
		void HandleChildPosition() override
		{
			if (children.size() < 1) return;
			SDL_Rect* rect = GetRect();
			int xLength = 0;

			for (Component* component : children)
			{
				component->SetPosition(rect->x + xLength, rect->y);
				xLength += component->GetRect()->w + padding;
			}
		}

	private:
		int padding = 0;
	};
}