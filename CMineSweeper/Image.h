#pragma once
#include <SDL_image.h>
#include <string>
#include "Component.h"

#include "Globals.h"

namespace Engine
{
	class Image : public Component
	{
	public:
		Image(int x, int y, int w, int h,
			const std::string& file) :
			Component{ x, y, w, h }
		{
			imageSurface = IMG_Load(file.c_str());

			#ifdef SHOW_DEBUG_HELPERS
			Utils::CheckSDLErrors("IMG_Load");
			#endif // SHOW_DEBUG_HELPERS
		}

		void Render(SDL_Surface* destSurface) override
		{
			SDL_BlitScaled(imageSurface, nullptr, destSurface, GetRect());
		}

		~Image()
		{
			if (imageSurface)
			{
				SDL_FreeSurface(imageSurface);
			}
		}

		//Image(const Image&) = delete;

	private:
		SDL_Surface* imageSurface = nullptr;
	};
}