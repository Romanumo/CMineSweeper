#pragma once
#define SHOW_DEBUG_HELPERS

#include<iostream>
#include<SDL.h>
#include<string>

namespace UserEvents {}

namespace Config
{
	//Game Settings
	inline const std::string GAME_NAME = "MineSweeper";

	//Size and Positioning
	inline constexpr int WINDOW_HEIGHT = 200;
	inline constexpr int WINDOW_WIDTH = 400;

	//Colors
	inline constexpr SDL_Color BACKGROUND_COLOR{ 170, 170, 170, 255 };
	inline constexpr SDL_Color BUTTON_COLOR{ 200, 200, 200, 255 };
	inline constexpr SDL_Color BUTTON_HOVER_COLOR{ 220, 220, 220, 255 };

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