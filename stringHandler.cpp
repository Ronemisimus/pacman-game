#include "stringHandler.h"

vector<Direction>* stringHandler::uncompress(ifstream& stepsFile)
{
    vector<Direction>* res = new vector<Direction>();

    Direction dir;
    size_t amount;
    char curr=0;
    bool endOfSteps = false;
    while (!endOfSteps && stepsFile.good())
    {                                       
        curr = stepsFile.get();
        switch (curr)
        {
        case 'S':
            dir = Direction::STAY;
            break;
        case 'L':
            dir = Direction::LEFT;
            break;
        case 'R':
            dir = Direction::RIGHT;
            break;
        case 'D':
            dir = Direction::DOWN;
            break;
        case 'U':
            dir = Direction::UP;
            break;
        default:
            endOfSteps=true;
            break;
        }
        if(!endOfSteps)
        {
            stepsFile >> amount;

            for (size_t i = 0; i < amount; i++)
            {
                res->push_back(dir);
            }
            if(amount<=0)
            {
                endOfSteps=true;
            }
        }
    }

    if(curr=='\r')
    {
        stepsFile.get();
    }
    
    return res;
}

string stringHandler::compressFruit(string moves)
{
    string res = "";
    string dirs="";
    string check = "UDSLR";
    for(char& current:moves)
    {
        if(check.find(current)!=std::string::npos)
        {
            dirs+=current;
        }
        else
        {
            dirs=compress(dirs);
            res+=dirs;
            res+=current;
            dirs="";
        }
    }
    if(dirs.size()!=0)
    {
        dirs=compress(dirs);
        res+=dirs;
    }
    return res;
}

string stringHandler::compress(string dirsOnly)
{
    string res="";
    int duplicates=0;
    char prev=' ';
    for(auto& current:dirsOnly)
    {
        if(prev==current)
        {
            duplicates++;
        }
        else
        {
            if(prev!=' ')
            {
                res+=prev;
                res+=std::to_string(duplicates);
            }
            duplicates=1;
        }
        prev = current;
    }
    if(duplicates!=0)
    {
        res+=prev;
        res+=std::to_string(duplicates);
    }

    return res;
}

