#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"
#include "Component.h"
using namespace Engine;

Component::Component(int x, int y, int w, int h) :
	relTf{ x, y, w, h }, parent(nullptr)
{
	UpdateTransform();
}

Component::~Component()
{
	if (children.size() < 1) return;

	for(Component* child : children)
	{
		std::cout << this->GetName() << " deletes " 
			<< child->GetName() << std::endl;
		delete child;
	}
}

#pragma region Positioning

void Component::SetRelPosition(int x, int y)
{
	relTf.x = x;
	relTf.y = y;

	UpdateTransform();
}

void Component::SetRelSize(int w, int h)
{
	relTf.w = w;
	relTf.h = h;

	UpdateTransform();
}

void Component::UpdateTransform()
{
	UpdateAbsTf();
	HandleChildPosition();
}

void Component::UpdateAbsTf()
{
	absTf = relTf;

	if (parent != nullptr)
	{
		absTf.x += parent->GetAbsTf()->x;
		absTf.y += parent->GetAbsTf()->y;
	}
}

void Component::HandleChildPosition()
{
	if (children.size() < 1) return;

	for (Component* component : children)
	{
		component->UpdateTransform();
	}
}

#pragma endregion

#pragma region FamilyFunctions

void Component::PrintFamilyTree(int spacing)
{
	std::string offset(spacing, '-');
	std::cout << offset << GetName() << std::endl;

	if (children.size() < 1) return;

	for (Component* component : children)
	{
		component->PrintFamilyTree(spacing + 1);
	}
}

bool Component::SetAsChildOf(Component* parent)
{
	if (parent == this)
	{
		std::cout << "Component cannot be a child of himself" << std::endl;
		return false;
	}

	if (this->parent != nullptr)
	{
		std::cout << "Component already have a parent" << std::endl;
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

	this->parent = parent;
	parent->SetAsParentOf(this);
	return true;
}

bool Component::IsMyChild(Component* child) const
{
	if (children.size() < 1) return false;

	for (Component* component : children)
	{
		if (component == child) return true;

		if (component->IsMyChild(child)) return true;
	}

	return false;
}

bool Component::IsMyRelative(Component* child)
{
	if (child->GetParent() == nullptr) return false;

	return (child->GetParent() == this->GetParent());
}

void Component::SetAsParentOf(Component* child)
{
	children.push_back(child);
}

void Component::ReserveChildrenSize(int reserve) { children.reserve(reserve); }

#pragma endregion

#pragma region GettersSetters

std::string Component::GetName() { return typeid(*this).name(); }
Component* Component::GetParent() { return parent; }
const std::vector<Component*>& Component::GetChildren() { return children; }

const SDL_Rect* Component::GetAbsTf() const { return &absTf; }
SDL_Rect* Component::GetAbsTf() { return &absTf; }

#pragma endregion

bool Component::IsWithinBounds(int x, int y) const
{
	if (x < absTf.x) return false;
	if (y < absTf.y) return false;
	if (x > absTf.x + absTf.w) return false;
	if (y > absTf.y + absTf.h) return false;

	return true;
}