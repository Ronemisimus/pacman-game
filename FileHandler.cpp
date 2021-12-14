#include "FileHandler.h"


using std::cout;
using std::filesystem::path;
using std::ifstream;

BoardGame* FileHandler::loadScreen() 
{
    
    if (screensLoaded < filecount)
    {
       
        ifstream ReadScreen(sortedFileList[screensLoaded].generic_string(), std::ios_base::in);
       
        
        if (ReadScreen.is_open())
        {
            int BoardRows;
            int row = 0, col = 0;
            while (ReadScreen.good())
            {
                
                char line[1024];
                ReadScreen.getline(line, 1024);
               
                int len = strlen(line);
                row++;
                if (IsLineEmpty(line)==false)
                {
                    BoardRows = row;
                }
                col = col > len ? col : len;
                
            }
            BoardGame* res = new BoardGame(BoardRows, col);
            ReadScreen.seekg(0);

            screensLoaded++;
            res->initBoard(ReadScreen);
            return res;
       }
    

    }
    return nullptr;
}

void FileHandler::resetScreensLoaded()
{
    this->screensLoaded = 0;
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
  
}

bool IsLineEmpty(char* line)
{
    while (line[0] != '\n' && line[0] != '\r' && line[0]!='\0')
    {
        if (line[0] != ' ' && line[0] != CHAR_LEGEND)
        {
            return false;
        }
        line++;

    }
    return true;
}