#include "FileHandler.h"

BoardGame* FileHandler::loadNextScreen() 
{
    BoardGame* res = loadScreen(screensLoaded);
    if(screensLoaded<filecount) screensLoaded++;
    
    return res;
}

BoardGame* FileHandler::loadScreen(size_t screenNum)
{
    BoardGame* res = nullptr;

    if (screenNum < filecount)
    {
        string filename(sortedFileList[screenNum]);
        ifstream ReadScreen(filename, std::ios_base::in);
       
        
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
            res = new BoardGame(BoardRows, col);
            ReadScreen.seekg(0);
            res->initBoard(ReadScreen);
       }
    }

    return res;
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
    string* path1 = (string*)p1;
    string* path2 = (string*)p2;
    return strcmp(path1->c_str(),path2->c_str());
}

void FileHandler::getFileList()
{

    std::filesystem::path dir = current_path();
    di = directory_iterator(dir);
    int count = 0;
    for (auto& f : directory_iterator(dir))
    {
        if (f.path().extension().compare(".screen") == 0)
        {
            count++;
            sortedFileList.push_back(f.path().filename().generic_string());
        }
    }
    filecount = count;
  
    sort(sortedFileList.begin(), sortedFileList.end());

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

BoardGame* FileHandler::chooseScreen()
{
    cout << "enter screen name: ";
    char filename[1024];
    cin.getline(filename, 1024);

    BoardGame* res=nullptr;

    bool found = false;
    size_t file_num = 0;

    for (size_t i = 0; i < filecount && !found; i++)
    {
        if(strcmp(sortedFileList[i].c_str(), filename)==0)
        {
            found =true;
            file_num = i;
        }
    }

    if(found)
    {
        cout << "file found - click any key to play\n";
        res = loadScreen(file_num);
    }
    else
    {
        cout << "file not found - click any key to return to the menu\n";
    }

    #ifdef LINUX
        system("read -N 1");
    #else
        system("pause");
    #endif

    #ifdef LINUX
        system("clear");
    #else
        system("cls");
    #endif

    return res;
    
}

int FileHandler::getFileCount() const
{
    return filecount;
}
