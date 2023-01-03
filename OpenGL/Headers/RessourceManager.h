#pragma once
#include <unordered_map>
#include <thread>
#include <atomic>

namespace Resource
{
	enum class Threading
	{
		Mono,
		Multi
	};

	class IResource
	{
	public:
		int id;

		virtual void Load(const char* fileName) = 0;

		virtual void Unload() = 0;
	};


	class ResourceManager
	{
	public:
		template<typename T>
		inline IResource* Create(const char* fileName);

		template<typename T>
		IResource* Create(const char* fileName, const char* tag);

		template<typename T>
		IResource* Get(const char* tag);

		template<typename T>
		void Delete(const char* tag);

		void Reset();

		void swapThreading();

		Threading getThreadingMode() { return threading; }

		~ResourceManager();

	private:
		std::unordered_map<std::string, IResource*> resources;

		Threading threading = Threading::Multi;
	};
}

#include "ResourceManager.inl"