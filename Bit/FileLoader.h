#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class FileLoader
{
public:
	
	FileLoader(void);
	~FileLoader(void);

	void Open(string file);
	
	string GetLine();
	int GetInt();
	size_t GetSizeT();
	size_t FileLoader::GetSizeT(size_t id);

	void Close();


private:
	
	vector<size_t> loadedSizeTs;
	ifstream fileHandler;
};

