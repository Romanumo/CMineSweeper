#pragma once
#include<SDL.h>
#include<SDL_image.h>
#include<string>
#include<unordered_map>

#include"Globals.h"

template<typename Resource>
class ResourceManager
{
public:
	static ResourceManager& GetInstance()
	{ 
		static ResourceManager atlas;
		return atlas; 
	}

	ResourceManager(const ResourceManager&) = delete;
	ResourceManager& operator=(const ResourceManager&) = delete;

	template <typename Load>
	std::shared_ptr<Resource> GetByPath(const std::string& path, Load loadFunction)
	{
		auto image = resourcePool.find(path);
		if (image != resourcePool.end()) return image->second;

		auto resource = loadFunction(path);
		if (resource) resourcePool[path] = resource;

		return resource;
	}

	std::shared_ptr<Resource> GetByName(const std::string& assetName)
	{
		auto image = resourcePool.find(assetName);
		if (image != resourcePool.end()) return image->second;

		return nullptr;
	}

	void AddAnAsset(const std::string& assetName, std::shared_ptr<Resource> asset)
	{
		resourcePool[assetName] = asset;
	}

	void FreeAll()
	{
		//Since we have sharedPointer, it will automatically clear the space
		resourcePool.clear();
	}

private:
	ResourceManager() {}
	~ResourceManager() { FreeAll(); }

	std::unordered_map<std::string, std::shared_ptr<Resource>> resourcePool;
};