#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"

//TODO:
//Implement a Relative Positioning for non layout object
//Create column
//Refactor and check code
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
		const SDL_Rect* GetRect() const { return &rect; }

		SDL_Rect* GetRect() { return &rect; }
		Component* GetParent() { return parent; }

		virtual void SetPosition(int x, int y);
		virtual void SetSize(int w, int h);

		bool SetAsChildOf(Component* parent, std::string childName = "", 
			std::string parentName = "");

		void PrintFamilyTree(int spacing = 0);

		virtual void Render(SDL_Surface* surface) = 0;
		virtual void HandleEvent(const SDL_Event& event) = 0;

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