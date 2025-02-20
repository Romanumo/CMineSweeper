#pragma once
#include <SDL_ttf.h>
#include <string>
#include "Globals.h"
#include "Component.h"

//Text works on an assumtion of one font
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
			fontID = Config::FONT + std::to_string(fontSize);
			auto loadFont = [fontSize]() -> std::shared_ptr<TTF_Font>
				{return LoadFont(Config::FONT, fontSize);};

			font = ResourceManager<TTF_Font>::GetInstance().
				GetByName(fontID, loadFont);

			SetText(text);
		}

		void SetText(const std::string& text) { SetText(text, textColor); }

		void SetText(const std::string& text, SDL_Color color)
		{
			if (textSurface)
			{
				SDL_FreeSurface(textSurface);
			}
			textColor = color;

			//UniqueNameFormat font_text_color
			textSurface = TTF_RenderUTF8_Blended(font.get(), text.c_str(), color);

			UpdateTextPosition();
		}

		void Render(SDL_Surface* surface) override
		{
			SDL_BlitScaled(textSurface, nullptr, surface, &textPos);
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

		~Text()
		{
			if (textSurface) { SDL_FreeSurface(textSurface); }
		}

	protected:
		void HandleChildPosition() override
		{
			Component::HandleChildPosition();
			UpdateTextPosition();
		}

	private:
		SDL_Surface* textSurface = nullptr;
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
	};
}
