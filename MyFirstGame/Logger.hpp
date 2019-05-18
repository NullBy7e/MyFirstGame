#pragma once
#include <iostream>
#include <time.h>

namespace logger {
	class Info {
		Info() = default;

		friend std::ostream& operator<<(Info& log, char* const& text) 
		{
			struct tm newtime{};
			__time32_t aclock;

			char buffer[32];
			_time32(&aclock);
			_localtime32_s(&newtime, &aclock);
			asctime_s(buffer, 32, &newtime);

			return std::cout << "[" << buffer << "] " << text;
		}

	};
	static inline Info info{};
};
