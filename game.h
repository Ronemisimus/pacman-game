
#pragma once
#include <fstream>
#include "global.h"
#include "BoardGame.h"
#include "Creature.h"
#include "pacman.h"
#include "ghost.h"
#include "GhostMoveStrategy.h"
#include "fruit.h"
#include "collisionFlags.h"
#include "fruitLife.h"

using std::ofstream;
using std::string;

class Game
{//class to manage the game's status
private:
   
    fruit fruit1;
    bool isPaused;
    bool waitForMove; // after strike pause until player moves
    BoardGame* board;
    pacman* player;
	vector <ghost> enemies;
    vector <Creature*> creatures;
    vector<string> creatureSave;
    ofstream* saveFile;
   
public:
    Game(BoardGame* board);
    ~Game();
    void redrawBoard();
    void updateBoard(size_t frames);
    void updateGameFromLoad(size_t frames, bool silent);
    bool isDone();
    void changeBoard(BoardGame* next);
    void resetStats();
    void calculateSmartMoves();
    void updateGhostsSmatMoveList(Position playerPos);
    void fillCreatureVector();
    void setSaveFile(ofstream* saveFile);
    void save();
    void resetCreatureSave();
    void compressStrings();
    string compressFruit(string moves);
    string compress(string dirsOnly);
    bool loadStepsFile(ifstream& stepsFile);
    vector<Direction>* uncompress(ifstream& stepsFile);
    bool checkSpeed(Creature& c);
};