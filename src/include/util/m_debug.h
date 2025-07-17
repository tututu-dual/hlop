#ifndef __M_DEBUG_H__
#define __M_DEBUG_H__

#include <iostream>
#include <sstream>

#include "msg.h"

#ifdef M_DEBUG
#define INFO(fmt, ...)                                                           \
	do {                                                                         \
		std::cout << "[INFO] " << hlop::format(fmt, ##__VA_ARGS__) << std::endl; \
	} while (0)

#define ERROR(fmt, ...)                                                           \
	do {                                                                          \
		std::cerr << "[ERROR] " << hlop::format(fmt, ##__VA_ARGS__) << std::endl; \
	} while (0)

#define INFO_VEC(msg, vec)                    \
	do {                                      \
		INFO("{}(n = {}):", msg, vec.size()); \
		INFO(hlop::vtos(vec));                \
	} while (0)
#else // M_DEBUG
#define INFO(fmt, ...) \
	do {               \
	} while (0)

#define ERROR(fmt, ...) \
	do {                \
	} while (0)

#define INFO_VEC(msg, vec) \
	do {                   \
	} while (0)
#endif // M_DEBUG

#ifdef M_DEBUG_VERBOSE
#define DEBUG(fmt, ...)                                                           \
	do {                                                                          \
		std::cout << "[DEBUG] " << hlop::format(fmt, ##__VA_ARGS__) << std::endl; \
	} while (0)
#define DEBUG_VEC(msg, vec)                    \
	do {                                       \
		DEBUG("{}(n = {}):", msg, vec.size()); \
		DEBUG(hlop::vtos(vec));                \
	} while (0)
#else // M_DEBUG_VERBOSE
#define DEBUG(fmt, ...) \
	do {                \
	} while (0)
#define DEBUG_VEC(msg, vec) \
	do {                    \
	} while (0)
#endif // M_DEBUG_VERBOSE

#endif // __M_DEBUG_H__