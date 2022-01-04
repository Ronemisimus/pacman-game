#pragma once
#include <fstream>

using std::ifstream;

class GameResult
{
private:
    int deathTimes[3];
    int endTime;
    bool win;
public:
    GameResult(ifstream* file, bool& goodFile);

    int* const getDeathTimes() const;
    int getEndTimes() const;
    bool isWin() const;
};