#pragma once
#define SHOW_DEBUG_HELPERS

#include<iostream>
#include<SDL.h>
#include<string>

namespace UserEvents 
{
	inline Uint32 CELL_CLEARED = SDL_RegisterEvents(1);
}

namespace Config
{
	//Game Settings
	inline const std::string GAME_NAME = "MineSweeper";
	inline constexpr int GRID_COLUMNS = 8;
	inline constexpr int GRID_ROWS = 4;

	//Size and Positioning
	inline constexpr int PADDING = 5;
	inline constexpr int CELL_SIZE = 50;

	inline constexpr int GRID_HEIGHT =
		GRID_ROWS * CELL_SIZE + PADDING * (GRID_ROWS - 1);

	inline constexpr int GRID_WIDTH =
		GRID_COLUMNS * CELL_SIZE + PADDING * (GRID_COLUMNS - 1);

	inline constexpr int WINDOW_HEIGHT = GRID_HEIGHT + PADDING * 2;
	inline constexpr int WINDOW_WIDTH = GRID_WIDTH + PADDING * 2;

	//Colors
	inline constexpr SDL_Color BACKGROUND_COLOR{ 170, 170, 170, 255 };
	inline constexpr SDL_Color BUTTON_COLOR{ 200, 200, 200, 255 };
	inline constexpr SDL_Color BUTTON_HOVER_COLOR{ 220, 220, 220, 255 };
	inline constexpr SDL_Color BUTTON_CLEARED_COLOR{ 240, 240, 240, 255 };

	//Asset Paths
	inline const std::string FONT = "Assets/Rubik-SemiBold.ttf";
}

namespace Utils
{
#ifdef SHOW_DEBUG_HELPERS
	inline void CheckSDLErrors(const std::string& msg)
	{
		const char* error = SDL_GetError();
		if (*error != '\0')
		{
			std::cerr << msg << "Error: " << error << '\n';
			SDL_ClearError();
		}
	}
#endif // SHOW_DEBUG_HELPERS
}