#ifndef __M_DEBUG_H__
#define __M_DEBUG_H__

#ifdef M_DEBUG
#include <iostream>
#include <sstream>

#include "msg.h"

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
#else
#define INFO(fmt, ...) \
	do {               \
	} while (0)

#define ERROR(fmt, ...) \
	do {                \
	} while (0)

#define INFO_VEC(msg, vec) \
	do {                   \
	} while (0)
#endif

#endif // __M_DEBUG_H__