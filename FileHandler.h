#pragma once

#include <filesystem>
#include <string>
using std::filesystem::current_path;
using std::filesystem::directory_iterator;
using std::string;
#include <iostream>
#include <fstream>
#include "BoardGame.h"
#include <string.h>


bool IsLineEmpty(char* line);

class FileHandler
{
	
private:
	int filecount;
    int screensLoaded;
	directory_iterator di;
	

public:
	FileHandler();
	void getFileList();
	BoardGame* loadScreen() ;
	void resetScreensLoaded();
private:
	std::filesystem::path* sortedFileList;



};
int compar(const void* p1, const void* p2);