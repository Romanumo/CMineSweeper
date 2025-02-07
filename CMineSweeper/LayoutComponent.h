#pragma once
#include <functional>
#include "Component.h"

namespace Engine
{
	/*Special Wrapper class for layout classes
	*/
	class LayoutComponent
	{
	public:
		LayoutComponent(Component& obj, int percentage) :
			object{ obj }, percentage(percentage) {
		}

		int GetPercentage() { return percentage; }

		Component* GetComponent() { return &object.get(); }

	private:
		//Reference wrapper ensure it never nullptr
		std::reference_wrapper<Component> object;
		int percentage = 0;
	};
}