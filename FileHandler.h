#pragma once

#include <algorithm>
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



using std::cout;
using std::cin;
using std::filesystem::path;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::sort;



class FileHandler
{//class to load screen files
	
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
	BoardGame* chooseScreen(size_t& file_num);
	int getFileCount() const;
	ofstream* getSaveFile(size_t file_num) const;
	ifstream* getStepsFile(size_t file_num) const;
	ifstream* getResultFile(size_t file_num) const;
	size_t getScreensLoaded() const;

private:
	vector<string> sortedScreenFileList;
	vector<string> sortedStepsFileList;
	vector<string> sortedResultFileList;
};
