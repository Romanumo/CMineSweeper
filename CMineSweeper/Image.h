#pragma once
#include <SDL_image.h>
#include <string>

#include "Globals.h"

namespace Engine
{
	class Image
	{
	public:
		Image(int x, int y, int w, int h,
			const std::string& file, int padding = 12) :
			destRect{ x + padding / 2, y + padding / 2, w - padding, h - padding }
		{
			imageSurface = IMG_Load(file.c_str());

			#ifdef SHOW_DEBUG_HELPERS
			Utils::CheckSDLErrors("IMG_Load");
			#endif // SHOW_DEBUG_HELPERS
		}

		void Render(SDL_Surface* destSurface)
		{
			SDL_BlitScaled(imageSurface, nullptr, destSurface, &destRect);
		}

		~Image()
		{
			if (imageSurface)
			{
				SDL_FreeSurface(imageSurface);
			}
		}

		Image(const	Image&) {}

	private:
		SDL_Surface* imageSurface = nullptr;
		SDL_Rect destRect{ 0,0,0,0 };
	};
}