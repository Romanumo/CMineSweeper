#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"

//Problems:
//What about a situation when the parent dies?
//Does the child die with him?
//What about layout, it can have an reference created to an object
//Does it have to delete all the object when that layout dies?
//You need to free space after all

namespace Engine
{
	class Component
	{
	public:
		Component(int x, int y, int w, int h);

		SDL_Rect* GetAbsTf();
		const SDL_Rect* GetAbsTf() const;

		void SetRelSize(int w, int h);
		void SetRelPosition(int x, int y);

		std::string GetName();
		Component* GetParent();
		const std::vector<Component*>& GetChildren();

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