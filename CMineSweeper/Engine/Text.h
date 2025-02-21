#pragma once
#include <SDL_ttf.h>
#include <string>

#include "Managers/Globals.h"
#include "TextFactory.h"
#include "Component.h"

//Text could use a strategy for a change of assigning text

namespace Engine
{
	class Text : public Component
	{
	public:
		Text(int x, int y, int w, int h,
			const std::string& text, 
			ITextFactory* textFactory = new DynamicTextFactory(),
			SDL_Color color = { 0, 0,0,255 },
			int fontSize = 60) : 
			Component{x, y, w, h}, textColor(color), 
			textFactory(textFactory)
		{
			const std::string& fontID = Config::FONT + std::to_string(fontSize);
			auto loadFont = [fontSize]() -> std::shared_ptr<TTF_Font>
				{return ITextFactory::LoadFont(Config::FONT, fontSize);};

			font = ResourceManager<TTF_Font>::GetInstance().
				GetByName(fontID, loadFont);

			SetText(text, color);
		}

		void SetText(const std::string& text) { SetText(text, textColor); }

		void SetText(const std::string& text, SDL_Color color)
		{
			textColor = color;

			textSurface = textFactory->GetSurface(text, font.get(), color);

			UpdateTextPosition();
		}

		void Render(SDL_Surface* surface) override
		{
			SDL_BlitScaled(textSurface.get(), nullptr, surface, &textPos);
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

		SDL_Rect textPos{ 0,0,0,0 };
		SDL_Color textColor{ 0,0,0,255 };

		ITextFactory* textFactory;

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
