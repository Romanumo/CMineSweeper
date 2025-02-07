#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"

//TODO:
//Separate Component into h and cpp
//Create an abstract method for HandleEvent
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

		SDL_Rect* GetRect() { return &rect; }
		virtual void SetPosition(int x, int y) 
		{
			rect.x = x; 
			rect.y = y; 

			HandleChildPosition();
		}

		bool SetAsChildOf(Component* parent, std::string childName = "",
								std::string parentName = "")
		{
			if (parent == this)
			{
				std::cout << "Component cannot be a child of himself" << std::endl;
				return false;
			}

			if (IsMyChild(parent))
			{
				std::cout << "Component ancestor is his child" << std::endl;
				return false;
			}

			if (IsMyRelative(parent))
			{
				std::cout << "Component cannot be a child of his relative" << std::endl;
				return false;
			}

			if (childName.size() > 0 && parentName.size() > 0)
			{
				std::cout << childName << " Is a child of "
					<< parentName << std::endl;
			}

			this->parent = parent;
			parent->SetAsParentOf(this);
			return true;
		}

		Component* GetParent() { return parent; }
		std::string GetName(){return typeid(*this).name();}

		void PrintTree(int spacing = 0)
		{
			std::string offset(spacing, '-');
			std::cout << offset << GetName() << std::endl;

			if (children.size() < 1) return;

			for (Component* component : children)
			{
				component->PrintTree(spacing+1);
			}
		}

		virtual void Render(SDL_Surface* surface) {}

		virtual ~Component() = default;

	protected:

		std::vector<Component*> children;
		Component* parent;

		virtual void HandleChildPosition()
		{
			if (children.size() < 1) return;

			for (Component* component : children)
			{
				//TODO: Add a relative posiitoning
				component->SetPosition(rect.x, rect.y);
			}
		}

		bool IsMyChild(Component* child) const
		{
			if (children.size() < 1) return false;

			for (Component* component : children)
			{
				if (component == child) return true;

				if (component->IsMyChild(child)) return true;
			}

			return false;
		}

		bool IsMyRelative(Component* child)
		{
			if (child->GetParent() == nullptr) return false;

			return (child->GetParent() == this->GetParent());
		}

		bool IsWithinBounds(int x, int y) const
		{
			if (x < rect.x) return false;
			if (y < rect.y) return false;
			if (x > rect.x + rect.w) return false;
			if (y > rect.y + rect.h) return false;

			return true;
		}

	private:
		SDL_Rect rect{ 0,0,0,0 };

		void SetAsParentOf(Component* child)
		{
			children.push_back(child);
		}
	};
}