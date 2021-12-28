#include "FileHandler.h"

FileHandler* FileHandler::fh = nullptr;

FileHandler::FileHandler():filecount(0)
{
    getFileList();
}

FileHandler::~FileHandler()
{
    
}

BoardGame* FileHandler::loadNextScreen() 
{
    BoardGame* res = loadScreen(screensLoaded);
    if(screensLoaded<filecount) screensLoaded++;
    
    return res;
}

int lineLen(char line[1024])
{//calculate the logical size of the board's first line
    //while making sure there is enough space for the legend
    int linelen = strlen(line);
    char* legend = strchr(line, CHAR_LEGEND);

    if(line[linelen-1]=='\r')
    {
        linelen--;
    }

    if(legend)
    {
        int legendlen = strlen(legend);

        if(legend[legendlen-1]=='\r')
        {
            legendlen--;
        }

        if(legendlen<20)
        {
            linelen+=(20-legendlen);
        }
    }

    return linelen;
}

BoardGame* FileHandler::loadScreen(size_t screenNum)
{
    BoardGame* res = nullptr;
    //only if the requested file exists:
    if (screenNum < filecount)
    {
        string filename(sortedScreenFileList[screenNum]);//get the file's name
        ifstream ReadScreen(filename, std::ios_base::in);
       
        
        if (ReadScreen.is_open())
        {
            int BoardRows;
            int row = 0, col = 0;

            char line[1024];
            ReadScreen.getline(line, 1024);
            row++;
            col = lineLen(line);//save board's width

            while (ReadScreen.good())
            {
                ReadScreen.getline(line, 1024);
                row++;
            }

            BoardRows = row;//save board's height

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



void FileHandler::getFileList()
{//function to create a list of the screen files from the folder

    std::filesystem::path dir = current_path();
    di = directory_iterator(dir);
    int count = 0;
    for (auto& f : directory_iterator(dir))
    {
        if (f.path().extension().compare(".screen") == 0)
        {
            count++;
            sortedScreenFileList.push_back(f.path().filename().generic_string());
        }
        if (f.path().extension().compare(".steps") == 0)
        {
            sortedStepsFileList.push_back(f.path().filename().generic_string());
        }
        if (f.path().extension().compare(".result") == 0)
        {
            sortedResultFileList.push_back(f.path().filename().generic_string());
        }
    }
    filecount = count;
  //sort the files in lexicographical order
    sort(sortedScreenFileList.begin(), sortedScreenFileList.end());
    sort(sortedStepsFileList.begin(), sortedStepsFileList.end());
    sort(sortedResultFileList.begin(), sortedResultFileList.end());
}



BoardGame* FileHandler::chooseScreen(size_t& file_num)
{//when the user chooses to load a specific screen
    cout << "enter screen name: ";
    char filename[1024];
    cin.getline(filename, 1024);

    BoardGame* res=nullptr;

    bool found = false;

    for (size_t i = 0; i < filecount && !found; i++)
    {
        if(strcmp(sortedScreenFileList[i].c_str(), filename)==0)
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

FileHandler* FileHandler::getInstance()
{//returns the only instance of the file handler
    if(!fh)
    {
        fh = new FileHandler();
    }
    return fh;
}

ofstream* FileHandler::getSaveFile(size_t file_num) const
{

    string fname = sortedScreenFileList[file_num];
    int lastDot=fname.rfind('.');
    fname=fname.substr(0, lastDot)+".steps";
    return new ofstream(fname);
}

size_t FileHandler::getScreensLoaded() const
{
    return screensLoaded;
}

