#ifndef __M_DEBUG_H__
#define __M_DEBUG_H__

#include <iostream>
#include <sstream>

#include "aux.h"
#include "msg.h"

#define LEVEL_OUT(level, fmt, ...)                    \
	do {                                              \
		std::cout << "[" << level << "] "             \
		          << hlop::format(fmt, ##__VA_ARGS__) \
		          << std::endl;                       \
	} while (0)

#define LEVEL_OUT_VEC(level, fmt, vec, ...)           \
	do {                                              \
		std::cout << "[" << level << "] "             \
		          << hlop::format(fmt, ##__VA_ARGS__) \
		          << "{n = " << vec.size() << "}: "   \
		          << hlop::vtos(vec)                  \
		          << std::endl;                       \
	} while (0)

#define LEVEL_OUT_MAP(level, fmt, map, ...)           \
	do {                                              \
		std::cout << "[" << level << "] "             \
		          << hlop::format(fmt, ##__VA_ARGS__) \
		          << "{n = " << map.size() << "}: "   \
		          << hlop::mtos(map)                  \
		          << std::endl;                       \
	} while (0)

#ifdef M_DEBUG
#define INFO(fmt, ...) \
	LEVEL_OUT("INFO", fmt, ##__VA_ARGS__)
#define INFO_VEC(fmt, vec, ...) \
	LEVEL_OUT_VEC("INFO", fmt, vec, ##__VA_ARGS__)
#define INFO_MAP(fmt, map, ...) \
	LEVEL_OUT_MAP("INFO", fmt, map, ##__VA_ARGS__)
#else // M_DEBUG
#define INFO(fmt, ...)
#define INFO_VEC(fmt, vec, ...)
#define INFO_MAP(fmt, map, ...)
#endif // M_DEBUG

#ifdef M_DEBUG_VERBOSE
#define DEBUG(fmt, ...) \
	LEVEL_OUT("DEBUG", fmt, ##__VA_ARGS__)
#define DEBUG_VEC(fmt, vec, ...) \
	LEVEL_OUT_VEC("DEBUG", fmt, vec, ##__VA_ARGS__)
#define DEBUG_MAP(fmt, map, ...) \
	LEVEL_OUT_MAP("DEBUG", fmt, map, ##__VA_ARGS__)
#else // M_DEBUG_VERBOSE
#define DEBUG(fmt, ...)
#define DEBUG_VEC(fmt, vec, ...)
#define DEBUG_MAP(fmt, map, ...)
#endif // M_DEBUG_VERBOSE
#endif // __M_DEBUG_H__