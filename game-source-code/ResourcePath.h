#pragma once

#include <string>
#if defined(__APPLE__)
#include <CoreFoundation/CoreFoundation.h>
#endif

/**
 * @brief Get platform specific resource path
 * 
 * Obtains the path to the resource folder using OS specific libraries when required
 * 
 * @return std::string 
 */
std::string resourcePath();