#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<unordered_map>

#include"Globals.h"

class ImageAtlas
{
public:
	static ImageAtlas& GetInstance()
	{ 
		static ImageAtlas atlas;
		return atlas; 
	}

	ImageAtlas(const ImageAtlas&) = delete;
	ImageAtlas& operator=(const ImageAtlas&) = delete;

	SDL_Surface* GetImage(const std::string& path)
	{
		auto image = imagePool.find(path);
		if (image != imagePool.end()) return image->second;

		SDL_Surface* surface = IMG_Load(path.c_str());
		if (!surface)
		{
#ifdef SHOW_DEBUG_HELPERS
			Utils::CheckSDLErrors("IMG_Load");
#endif // SHOW_DEBUG_HELPERS

			return nullptr;
		}

		imagePool[path] = surface;
		return surface;
	}

	void FreeAll()
	{
		for (auto& pair : imagePool)
		{
			SDL_FreeSurface(pair.second);
		}
		imagePool.clear();
	}

private:
	ImageAtlas() {}
	~ImageAtlas() { FreeAll(); }

	std::unordered_map<std::string, SDL_Surface*> imagePool;
};