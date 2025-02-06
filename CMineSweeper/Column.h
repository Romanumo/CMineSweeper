#pragma once
#include <vector>
#include <memory>
#include "Rectangle.h"

class Column
{
public:

private:
	std::vector<std::unique_ptr<Engine::Rectangle>> children;
};