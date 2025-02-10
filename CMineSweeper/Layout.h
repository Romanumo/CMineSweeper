#pragma once
#include <vector>
#include <iostream>
#include <memory>
#include "Component.h"

namespace Engine
{
	class Layout : public Component
	{
	public:
		Layout(int padding, int x, int y, std::vector<Component*> components) :
			Component(x, y, 0, 0), padding(padding)
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

			StretchContainer(objRect, myRect);
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

	protected:
		int GetPadding() { return padding; }

		virtual void StretchContainer(const SDL_Rect* objRect,
			const SDL_Rect* myRect) {}

	private:
		int padding = 0;
	};
}