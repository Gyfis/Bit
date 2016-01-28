#include "FileLoader.h"


FileLoader::FileLoader(void) { }

FileLoader::~FileLoader(void) { }


void FileLoader::Open(string file)
{
	FileLoader::fileHandler = ifstream(file);
}

string FileLoader::GetLine()
{
	string s;
	getline(FileLoader::fileHandler, s);
	return s;
}

int FileLoader::GetInt()
{
	int i;
	FileLoader::fileHandler >> i;
	FileLoader::GetLine();
	return i;
}

size_t FileLoader::GetSizeT()
{
	size_t st;
	FileLoader::fileHandler >> st;
	FileLoader::GetLine();
	return st;
}

size_t FileLoader::GetSizeT(size_t id)
{
	if (id == 0)
	{
		string s = FileLoader::GetLine();
		stringstream lineStream(s);

		size_t value;

		while (lineStream >> value)
		{
			FileLoader::loadedSizeTs.push_back(value);
		}
	}
	else if (id == -1)
	{
		FileLoader::loadedSizeTs.clear();
	}
	else return FileLoader::loadedSizeTs[id - 1];
	return 0;
}

void FileLoader::Close()
{
	FileLoader::fileHandler.close();
}
