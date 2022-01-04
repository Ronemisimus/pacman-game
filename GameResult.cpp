#include "GameResult.h"

GameResult::GameResult(ifstream* file, bool& goodFile)
{
    if(!file)
    {
        goodFile=false;
    }
    else
    {
        ifstream& f = *file;
        char eventType;
        int time;
        int deaths=0;
        goodFile = true;

        for(auto& t:deathTimes)
        {
            t=-1;
        }

        while (f.good() && goodFile)
        {
            eventType = f.get();

            switch (eventType)
            {
            case 'd':
                if(deaths<3 && f >> time)
                {
                    this->deathTimes[deaths++] = time;
                }
                else
                {
                    goodFile=false;
                }
                break;
            case 'l':
                if(deaths<=3 && f >> time)
                {
                    this->endTime = time;
                    this->win=false;
                }
                else
                {
                    goodFile=false;
                }
                break;
            case 'w':
                if(deaths<3 && f >> time)
                {
                    this->endTime = time;
                    this->win=true;
                }
                else
                {
                    goodFile=false;
                }
                break;
            default:
                goodFile=false;
                break;
            }
            
            if(f.get()=='\r')
            {
                f.get();
            }
        }        
    }
}

int* const GameResult::getDeathTimes() const
{
    return (int* const)deathTimes;
}

int GameResult::getEndTimes() const
{
    return endTime;
}

bool GameResult::isWin() const
{
    return win;
}

