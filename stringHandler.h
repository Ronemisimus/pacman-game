#include "global.h"
#include <fstream>
#include <string>

using std::ifstream;
using std::string;

class stringHandler
{
private:
    /* data */
public:
    static vector<Direction>* uncompress(ifstream& stepsFile);
    static string compressFruit(string moves);
    static string compress(string dirsOnly);
};

