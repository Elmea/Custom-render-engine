#pragma once

#include <type_traits>
#include <string>
#include <unordered_map>

#include "threadManager.h"

namespace Resource
{
	template<typename T>
	inline IResource* ResourceManager::Create(const char* fileName)
	{
		std::string tag = fileName;
		if (!std::is_base_of<IResource, T>())
			return nullptr;

		if (resources[tag] != nullptr)
			delete resources[tag];

		T* resource = new T();
		resources[tag] = (IResource*)resource;
		resources[tag]->id = resources.size();

		if (threading == Threading::Multi)
			Core::threadManager.AddThread(Core::ThreadType::LOAD, new std::thread(&IResource::Load, resource, fileName));
		else
			resources[tag]->Load(fileName);

		return resources[tag];
	}

	template<typename T>
	inline IResource* ResourceManager::Create(const char* fileName, const char* _tag)
	{
		std::string tag = _tag;
		if (!std::is_base_of<IResource, T>())
			return nullptr;

		if (resources[tag] != nullptr)
			delete resources[tag];

		T* resource = new T();
		resources[tag] = (IResource*)resource;
		resources[tag]->id = resources.size();

		if (threading == Threading::Multi)
			Core::threadManager.AddThread(Core::ThreadType::LOAD, new std::thread(&IResource::Load, resource, fileName));
		else
			resources[tag]->Load(fileName);

		return resources[tag];

	}

	template<typename T>
	inline IResource* ResourceManager::Get(const char* _tag)
	{
		std::string tag = _tag;
		if (!resources[tag])
			return nullptr;

		return resources[tag];
	}

	template<typename T>
	inline void ResourceManager::Delete(const char* _tag)
	{
		std::string tag = _tag;
		if (!resources[tag])
			return;

		delete resources[tag];
		resources.erase(tag);
	}

	inline void ResourceManager::Reset()
	{
		for (auto resource : resources)
		{
			delete resource.second;
		}
		resources.clear();
	}

	inline ResourceManager::~ResourceManager()
	{
		for (auto resource : resources)
		{
			resource.second->Unload();
			delete resource.second;
		}
		resources.clear();
	}

	inline void ResourceManager::swapThreading()
	{
		switch (threading)
		{
		case Resource::Threading::Mono:
			threading = Threading::Multi;
			break;
		case Resource::Threading::Multi:
			threading = Threading::Mono;
			break;
		default:
			break;
		}
	}
}