#pragma once
#include <SDL_ttf.h>
#include <string>

#include "Managers/Globals.h"
#include "Component.h"

//Text could use a strategy for a change of assigning text

namespace Engine
{
	class Text : public Component
	{
	public:
		Text(int x, int y, int w, int h,
			const std::string& text, 
			SDL_Color color = { 0, 0,0,255 },
			int fontSize = 60, bool isCached = false) : 
			Component{x, y, w, h}, textColor(color)
		{
			fontID = Config::FONT + std::to_string(fontSize);
			auto loadFont = [fontSize]() -> std::shared_ptr<TTF_Font>
				{return LoadFont(Config::FONT, fontSize);};

			font = ResourceManager<TTF_Font>::GetInstance().
				GetByName(fontID, loadFont);

			SetText(text, color, isCached);
		}

		void SetText(const std::string& text) { SetText(text, textColor); }

		void SetText(const std::string& text, SDL_Color color, bool isCached = false)
		{
			textColor = color;

			//UniqueNameFormat font_text
			//Assumed the 2 different colors would not be cached
			if (isCached)
			{
				const std::string colorID = std::to_string(color.r + color.g + color.b);
				const std::string textID = fontID + text + colorID;
				TTF_Font* usedFont = font.get();

				auto loadText = [text, usedFont, color]() -> std::shared_ptr<SDL_Surface>
					{return LoadText(text, usedFont, color);};

				textSurface = ResourceManager<SDL_Surface>::GetInstance().
					GetByName(textID, loadText);
			}
			else
			{
				textSurface = LoadText(text, font.get(), textColor);
			}

			UpdateTextPosition();
		}

		void Render(SDL_Surface* surface) override
		{
			SDL_BlitScaled(textSurface.get(), nullptr, surface, &textPos);
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
		std::shared_ptr<SDL_Surface> textSurface = nullptr;
		std::shared_ptr<TTF_Font> font = nullptr;
		std::string fontID;

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

		static std::shared_ptr<TTF_Font> LoadFont(const std::string& path, int fontSize)
		{
			TTF_Font* font = TTF_OpenFont(Config::FONT.c_str(), fontSize);

			if (!font)
			{
				#ifdef SHOW_DEBUG_HELPERS
				Utils::CheckSDLErrors("TTF_OpenFont");
				#endif // SHOW_DEBUG_HELPERS

				return nullptr;
			}

			return std::shared_ptr<TTF_Font>(font, TTF_CloseFont);
		}

		static std::shared_ptr<SDL_Surface> LoadText(const std::string& text, TTF_Font* font, SDL_Color color)
		{
			SDL_Surface* rawSurface = TTF_RenderUTF8_Blended(font, text.c_str(), color);
			if (!rawSurface)
			{
				#ifdef SHOW_DEBUG_HELPERS
				Utils::CheckSDLErrors("TEXT_Load");
				#endif // SHOW_DEBUG_HELPERS

				return nullptr;
			}

			return std::shared_ptr<SDL_Surface>(rawSurface, SDL_FreeSurface);
		}
	};
}
