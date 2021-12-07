#pragma once

#include <filesystem>
#include <string>
using std::filesystem::current_path;
using std::filesystem::directory_iterator;
using std::string;

class FileHandler
{
	
private:
	int filecount;
    int screensLoaded;
	directory_iterator di;
	

public:
	FileHandler();
	void getFileList();
	void loadScreen() ;
private:
	std::filesystem::path* sortedFileList;



};
int compar(const void* p1, const void* p2);