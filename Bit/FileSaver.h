#pragma once
#include <fstream>
#include <string>

using namespace std;

class FileSaver
{
public:
	FileSaver();
	~FileSaver();

	void Open(string file);
	void WriteLine(string line);
	void WriteLine(size_t line);
	void Close();

private:

	ofstream fileHandler;

};

