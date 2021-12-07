#include "FileHandler.h"
#include <iostream>
#include <fstream>
using std::cout;
using std::filesystem::path;
using std::ifstream;
void FileHandler::loadScreen() 
{

    if (screensLoaded < filecount)
    {
        ifstream ReadScreen(sortedFileList[screensLoaded], std::ios_base::in);
        while (ReadScreen.good())
        {
            char line[1024];
            ReadScreen.getline(line,1024);
            cout << line<<"\n";
        }
        
        //load screen

        screensLoaded++;
    }
}
FileHandler::FileHandler():filecount(0)
{
    getFileList();
}
int compar(const void* p1, const void* p2)
{
    path* path1 = (path*)p1;
    path* path2 = (path*)p2;
    return path1->compare(*path2);
}

void FileHandler::getFileList()
{

    std::filesystem::path dir = current_path();
   di = directory_iterator(dir);
    int count = 0;
    for (auto& f : directory_iterator(dir))
    {
        if (f.path().extension().compare(".screen") == 0 && f.path().filename().compare("pacman_") > 0)
        {
            count++;
        }
    }
    filecount = count;
   
    sortedFileList = new path[filecount];
    for (int i = 0; i < filecount; )
    {
        if (di->path().extension().compare(".screen") == 0 && di->path().filename().compare("pacman_") > 0)
        {
            sortedFileList[i] = di->path();
            i++;
            
        }
        di++;
    }
    qsort(sortedFileList, filecount, sizeof(path),compar);
    for (int j = 0; j < filecount; j++)
    {
        cout << sortedFileList[j] << "\n";
    }
}