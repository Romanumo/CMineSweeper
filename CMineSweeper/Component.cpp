#pragma once
#include <SDL.h>
#include <typeinfo>
#include <string>
#include "Globals.h"
#include "Component.h"
using namespace Engine;

void Component::SetPosition(int x, int y)
{
	rect.x = x;
	rect.y = y;

	HandleChildPosition();
}

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

void Component::HandleChildPosition()
{
	if (children.size() < 1) return;

	for (Component* component : children)
	{
		//TODO: Add a relative posiitoning
		component->SetPosition(rect.x, rect.y);
	}
}

bool Component::SetAsChildOf(Component* parent, std::string childName,
	std::string parentName)
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

#pragma endregion

bool Component::IsWithinBounds(int x, int y) const
{
	if (x < rect.x) return false;
	if (y < rect.y) return false;
	if (x > rect.x + rect.w) return false;
	if (y > rect.y + rect.h) return false;

	return true;
}