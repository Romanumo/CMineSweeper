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

//Problems:
//What about a situation when the parent dies?
//Does the child die with him?
//What about layout, it can have an reference created to an object
//Does it have to delete all the object when that layout dies?
//You need to free space after all

//Component inheritance have confusing names.
//AS I still get lost in what to oevrride and what to leave. 
//Especially dealing with inheritance

//Create on how should locations work, like
//Padding situations, does column have padding only outside
//Or its inckuded inside as well?
//Might need to have padding be what it is, so look up on internet
//Since padding is inner margin, then the goal is to have
//Layout cover FULL Window and have inner padding
namespace Engine
{
	class Component
	{
	public:
		Component(int x, int y, int w, int h);

		std::string GetName();
		Component* GetParent();
		const std::vector<Component*> GetChildren();

		SDL_Rect* GetAbsTf();
		const SDL_Rect* GetAbsTf() const;

		void SetRelSize(int w, int h);
		void SetRelPosition(int x, int y);

		bool SetAsChildOf(Component* parent);
		void PrintFamilyTree(int spacing = 0);

		virtual void Render(SDL_Surface* surface) = 0;
		virtual void HandleEvent(const SDL_Event& event) = 0;

		virtual ~Component() = default;

	protected:
		virtual void HandleChildPosition();

		void ReserveChildrenSize(int reserve);
		bool IsMyChild(Component* child) const;
		bool IsMyRelative(Component* child);
		bool IsWithinBounds(int x, int y) const;

	private:
		SDL_Rect absTf{ 0,0,0,0 };
		SDL_Rect relTf = absTf;

		Component* parent;
		std::vector<Component*> children;

		void UpdateAbsTf();
		void UpdateTransform();
		void SetAsParentOf(Component* child);
	};
}