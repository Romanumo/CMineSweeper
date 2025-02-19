#pragma once
#include <SDL_ttf.h>
#include <string>
#include "Globals.h"
#include "Component.h"

namespace Engine
{
	class Text : public Component
	{
	public:
		Text(int x, int y, int w, int h,
			const std::string& text, 
			SDL_Color color = { 0, 0,0,255 },
			int fontSize = 60) : 
			Component{x, y, w, h}, textColor(color)
		{
			font = TTF_OpenFont(Config::FONT.c_str(), fontSize);

			#ifdef SHOW_DEBUG_HELPERS
			Utils::CheckSDLErrors("TTF_OpenFont");
			#endif // SHOW_DEBUG_HELPERS

			SetText(text);
		}

		void SetText(const std::string& text)
		{
			SetText(text, textColor);
		}

		void SetText(const std::string& text, SDL_Color color)
		{
			if (textSurface)
			{
				SDL_FreeSurface(textSurface);
			}
			textColor = color;

			textSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

			UpdateTextPosition();
		}

		void Render(SDL_Surface* surface) override
		{
			SDL_BlitScaled(textSurface, nullptr, surface, &textPos);
		}

		~Text()
		{
			if (font) { TTF_CloseFont(font); }
			if (textSurface) { SDL_FreeSurface(textSurface); }
		}

		static SDL_Surface* SaveTextAsImage(
			const std::string& fontPath, int fontSize, 
			const std::string& text, SDL_Color color) 
		{
			TTF_Font* savedFont = TTF_OpenFont(fontPath.c_str(), fontSize);
			SDL_Surface* textSurface = TTF_RenderUTF8_Blended(savedFont, text.c_str(), color);
			TTF_CloseFont(savedFont);

			if(textSurface)return textSurface;
			
			std::cout << "Problem saving text" << std::endl;
			return nullptr;
		}

		virtual void HandleEvent(const SDL_Event& event) override {}

	protected:
		void HandleChildPosition() override
		{
			Component::HandleChildPosition();
			UpdateTextPosition();
		}

	private:
		SDL_Surface* textSurface = nullptr;
		TTF_Font* font = nullptr;

		SDL_Rect textPos{ 0,0,0,0 };
		SDL_Color textColor{ 0,0,0,255 };

		void UpdateTextPosition()
		{
			auto [x, y, w, h] = *GetAbsTf();

			//Horizontal Centering
			const int widthDifference = w - textSurface->w;
			const int leftOffset = widthDifference / 2;

			//Vertical Centering
			const int heightDifference = h - textSurface->h;
			const int topOffset = heightDifference / 2;

			textPos = { x + leftOffset, y + topOffset, w - widthDifference, h - heightDifference };
		}
	};
}
