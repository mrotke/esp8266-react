#ifndef FS_h
#define FS_h

#include <fstream>
#include <memory>

typedef std::fstream File;

class FS
{
public:
File open(const char* path, const char* mode);
private:
std::string changePath2Flat(const char* path);
};

extern FS linuxFS;

#endif