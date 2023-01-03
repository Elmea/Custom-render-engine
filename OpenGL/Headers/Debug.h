#pragma once
#include <cstdio>
#include <assert.h>
#include <fstream>
#include <iostream>
#include <cstdarg>

#ifdef NDEBUG
#define ASSERT(expression, assertionMessage) if(!(expression))std::abort()
#define ISDEBUGING false
#else
#define ASSERT(expression, assertionMessage) if(!(expression)){std::cout << "\"" <<assertionMessage << "\" assertion failed at line " << __LINE__ << " in function \'" << __func__ << "\' in " << __FILE__ << std::endl; __debugbreak();}
#define ISDEBUGING true
#endif

#define DEBUG_LOG(text,...) Core::Debug::DebugLog(text, __FILE__, __LINE__, __VA_ARGS__)

namespace Core::Debug
{
	void DebugLog(const char* string, const char* filename, int line, ...);
	
	class Log
	{
	public:
		void OpenFile(const char* filename);

		void Print(const char* string, ...);

		~Log() { CloseFile(); }

	private:
		bool fileOpened;
		void CloseFile();

		std::ofstream file;
	};

	static Core::Debug::Log log;
}

