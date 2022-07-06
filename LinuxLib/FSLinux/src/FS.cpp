#include "FS.h"
#include <string.h>

using namespace std;

FS linuxFS = FS();

File FS::open(const char* path, const char* mode)
{
    fstream file_Handler;
    if (strcmp(mode,"r") == 0)
        file_Handler.open(path, ios::in);
    if (strcmp(mode,"w") == 0)
        file_Handler.open(path, ios::out);

    return file_Handler;
}