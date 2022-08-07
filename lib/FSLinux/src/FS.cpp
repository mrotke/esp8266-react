#include "FS.h"
#include <string.h>
#include <algorithm>

using namespace std;

FS linuxFS = FS();

File FS::open(const char* path, const char* mode)
{
    string flatPath = changePath2Flat(path);
    fstream file_Handler;
    

    file_Handler.open(flatPath, ios::out | ios::app);
    file_Handler.close();

    if (strcmp(mode,"r") == 0)
        file_Handler.open(flatPath, ios::in);
    if (strcmp(mode,"w") == 0)
        file_Handler.open(flatPath, ios::out);

    return file_Handler;
}

string FS::changePath2Flat(const char* path)
{
    string str(path);
    std::replace(str.begin(),str.end(),'/','_');
    return str;
}