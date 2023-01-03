#include <string>
#include <cstdarg>

#include "Debug.h"

#pragma region Format

std::string Format(const char* string, ...)
{
	va_list args;
	va_start(args, string);

	std::string result;

	while (*string != '\0')
	{
		if (*string == '%')
		{
			switch (*(string + 1))
			{
			case 'd':
			{
				const int nb = va_arg(args, int);
				result = result + std::to_string(nb);
				string++;
				break;
			}

			case 'f':
			{
				const double nb = va_arg(args, double);
				result = result + std::to_string(nb);
				string++;
				break;
			}

			case 'c':
			{
				const char c = va_arg(args, char);
				result.push_back(c);
				string++;
				break;
			}

			case 's':
			{
				const char* s = va_arg(args, char*);
				result = result + s;
				string++;
				break;
			}

			case '%':
				result.push_back('%');
				string++;
				break;

			default:
				break;
			}
		}
		else
		{
			result.push_back(*string);
		}
		string++;
	}
	va_end(args);

	return result;
}

std::string FormatV(const char* string, va_list args)
{
	std::string result;

	while (*string != '\0')
	{
		if (*string == '%')
		{
			switch (*(string + 1))
			{
			case 'd':
			{
				const int nb = va_arg(args, int);
				result = result + std::to_string(nb);
				string++;
				break;
			}

			case 'f':
			{
				const double nb = va_arg(args, double);
				result = result + std::to_string(nb);
				string++;
				break;
			}

			case 'c':
			{
				const char c = va_arg(args, char);
				result.push_back(c);
				string++;
				break;
			}

			case 's':
			{
				const char* s = va_arg(args, char*);
				result = result + s;
				string++;
				break;
			}

			case '%':
				result.push_back('%');
				string++;
				break;

			default:
				break;
			}
		}
		else
		{
			result.push_back(*string);
		}
		string++;
	}

	return result;
}

#pragma endregion

namespace Core::Debug
{
	void DebugLog(const char* string, const char* filename, int line, ...)
	{
		std::cout << filename;
		std::cout << '(' + std::to_string(line) + ')' + ':' + ' ';

		va_list args;
		va_start(args, string);

		while (*string != '\0')
		{
			if (*string == '%')
			{
				switch (*(string + 1))
				{
				case 'd':
				{
					const int nb = va_arg(args, int);
					std::cout << nb;
					string++;
					break;
				}

				case 'f':
				{
					const double nb = va_arg(args, double);
					std::cout << nb;
					string++;
					break;
				}

				case 'c':
				{
					const char c = va_arg(args, char);
					std::cout << c;
					string++;
					break;
				}

				case 's':
				{
					const char* s = va_arg(args, char*);
					std::cout << s;
					string++;
					break;
				}

				case '%':
					std::cout << '%';
					string++;
					break;

				default:
					break;
				}
			}
			else
			{
				std::cout << *string;
			}
			string++;
		}

		std::cout << '\n';
	}

	void Log::OpenFile(const char* filename)
	{
		file.open(filename, std::ofstream::in);

		if (!file)
		{
			Print("Debug file ( %s ) does not exist", filename);
			fileOpened = false;
		}
		else
		{
			fileOpened = true;
			file.clear();
			Print("Debug file ( %s ) opened", filename);
		}
	}

	void Log::CloseFile()
	{
		if (!file)
			return;
			
		Print("Closing debug file...");
		file.close();
	}

	void Log::Print(const char* string, ...)
	{
		va_list args;
		va_start(args, string);

		std::cout << FormatV(string, args) << '\n';

		va_end(args);
	}
}