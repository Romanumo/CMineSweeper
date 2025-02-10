#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"

//Relative positioning work in this way
//SDL_Rect that every child has, now would be overwritten
//TO be relative rather than absolute. 
//This changes their relative point from which they cound a distance
//So a child with 12:13 and parent with 15:10
//Now becomes a child with 27:23

//TODO:
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

		//This rect is the relative positioning from parent
		SDL_Rect relativeRect = rect;

		void SetAsParentOf(Component* child);
	};
}