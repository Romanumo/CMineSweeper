#pragma once
#include <SDL_image.h>
#include <string>
#include "Component.h"
#include "ImageAtlas.h"

#include "Globals.h"

//Since IMageAtlas you acn change pointer into a shared pointer

namespace Engine
{
	class Image : public Component
	{
	public:
		Image(int x, int y, int w, int h,
			const std::string& file) :
			Component{ x, y, w, h }
		{
			LoadImage(file);
		}

		virtual void HandleEvent(const SDL_Event& event) override {}

		void Render(SDL_Surface* destSurface) override
		{
			SDL_BlitScaled(imageSurface, nullptr, destSurface, GetAbsTf());
		}

		void ChangeImage(const std::string& filePath)
		{
			FreeImage();
			LoadImage(filePath);
		}

		~Image() { FreeImage(); }

	private:
		SDL_Surface* imageSurface = nullptr;

		void FreeImage()
		{
			if (imageSurface)
			{
				SDL_FreeSurface(imageSurface);
			}
		}

		void LoadImage(const std::string& filePath)
		{
			imageSurface = ImageAtlas::GetInstance().GetImage(filePath);
		}
	};
}