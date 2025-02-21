#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <memory>
#include <string>

#include "Managers/ResourceManager.h"

namespace Engine
{
	class ITextFactory
	{
	public:
		virtual ~ITextFactory() = default;
		virtual std::shared_ptr<SDL_Surface> GetSurface(
			const std::string& text, TTF_Font* font, SDL_Color color) = 0;

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

		static std::shared_ptr<TTF_Font> LoadFont(const std::string& path, int fontSize)
		{
			TTF_Font* font = TTF_OpenFont(path.c_str(), fontSize);

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

	class DynamicTextFactory : public ITextFactory
	{
	public:
		std::shared_ptr<SDL_Surface> GetSurface(
			const std::string& text, TTF_Font* font, SDL_Color color) override
		{
			return LoadText(text, font, color);
		}
	};

	class CachedTextFactory : public ITextFactory
	{
	public:
		std::shared_ptr<SDL_Surface> GetSurface(
			const std::string& text, TTF_Font* font, SDL_Color color) override
		{
			const std::string colorID = std::to_string(color.r + color.g + color.b);
			const std::string textID = TTF_FontFaceStyleName(font) + text + colorID;
			TTF_Font* usedFont = font;

			auto loadText = [text, usedFont, color]() -> std::shared_ptr<SDL_Surface>
				{return LoadText(text, usedFont, color);};

			return ResourceManager<SDL_Surface>::GetInstance().
				GetByName(textID, loadText);
		}
	};
}