#pragma once

#include <iostream>

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )  // NOLINT(bugprone-macro-parentheses)
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif
