#pragma once
#include <SDL_image.h>
#include <string>
#include "Component.h"
#include "ResourceManager.h"

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
			SetImage(file);
		}

		virtual void HandleEvent(const SDL_Event& event) override {}

		void Render(SDL_Surface* destSurface) override
		{
			SDL_BlitScaled(imageSurface.get(), nullptr, destSurface, GetAbsTf());
		}

		void SetImage(const std::string& filePath)
		{
			imageSurface = ResourceManager<SDL_Surface>::GetInstance().GetByPath(filePath, LoadImage);
		}

	private:
		std::shared_ptr<SDL_Surface> imageSurface = nullptr;

		static std::shared_ptr<SDL_Surface> LoadImage(const std::string& filePath)
		{
			SDL_Surface* rawSurface = IMG_Load(filePath.c_str());
			if (!rawSurface)
			{
				#ifdef SHOW_DEBUG_HELPERS
				Utils::CheckSDLErrors("IMG_Load");
				#endif // SHOW_DEBUG_HELPERS

				return nullptr;
			}
			return std::shared_ptr<SDL_Surface>(rawSurface, SDL_FreeSurface);
		}
	};
}