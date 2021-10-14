#include "ResourcePath.h"

std::string resourcePath()
{
#if defined(__APPLE__)
    auto mainBundle = CFBundleGetMainBundle();
    auto resourcesURL = CFBundleCopyResourcesDirectoryURL(mainBundle);
    char path[1024];
    if (!CFURLGetFileSystemRepresentation(resourcesURL, TRUE, (UInt8 *)path, 1024))
    {
        throw std::runtime_error("Cannot get Resource Path");
    }
    CFRelease(resourcesURL);
    return strncat(path, "/", 1024);
#else
    return "Resources/";
#endif
}