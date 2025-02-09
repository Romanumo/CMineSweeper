#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"

//TODO:
//Create an abstract method for HandleEvent
//Create Vector2D struct
//Implement a Relative Positioning for non layout object
namespace Engine
{
	class Component
	{
	public:
		Component(int x, int y, int w, int h) :
			rect{ x, y, w, h } , parent(nullptr)
		{
			children.reserve(Config::MAX_CHILDREN);
		}

		std::string GetName() { return typeid(*this).name(); }

		SDL_Rect* GetRect() { return &rect; }
		virtual void SetPosition(int x, int y);

		Component* GetParent() { return parent; }
		bool SetAsChildOf(Component* parent, std::string childName = "", 
			std::string parentName = "");

		void PrintFamilyTree(int spacing = 0);

		virtual void Render(SDL_Surface* surface) {}

		virtual ~Component() = default;

	protected:

		std::vector<Component*> children;
		Component* parent;

		virtual void HandleChildPosition();

		bool IsMyChild(Component* child) const;
		bool IsMyRelative(Component* child);
		bool IsWithinBounds(int x, int y) const;

	private:
		SDL_Rect rect{ 0,0,0,0 };

		void SetAsParentOf(Component* child);
	};
}