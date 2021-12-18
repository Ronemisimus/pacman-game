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
#include <vector>
#include <bits/stdc++.h>

using std::cout;
using std::cin;
using std::filesystem::path;
using std::ifstream;
using std::vector;
using std::sort;

bool IsLineEmpty(char* line);

class FileHandler
{
	
private:
	static FileHandler *fh;
	size_t filecount;
    size_t screensLoaded;
	directory_iterator di;
	
	BoardGame* loadScreen(size_t screenNum);
	FileHandler();
public:
	~FileHandler();
	FileHandler(const FileHandler&)=delete;
	static FileHandler* getInstance();
	void getFileList();
	BoardGame* loadNextScreen();
	void resetScreensLoaded();
	BoardGame* chooseScreen();
	int getFileCount() const;

private:
	vector<string> sortedFileList;
};
int compar(const void* p1, const void* p2);