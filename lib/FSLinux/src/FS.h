#ifndef FS_h
#define FS_h

#include <fstream>
#include <memory>

typedef std::fstream File;

class FS
{
public:
File open(const char* path, const char* mode);
};

extern FS linuxFS;

#endif