#include "FileSaver.h"

FileSaver::FileSaver() { }

FileSaver::~FileSaver() { }

void FileSaver::Open(string file)
{
	FileSaver::fileHandler.open(file, ios::trunc);
}

void FileSaver::WriteLine(string line)
{
	FileSaver::fileHandler << line;
	FileSaver::fileHandler << "\n";
}

void FileSaver::WriteLine(size_t line)
{
	FileSaver::fileHandler << line;
	FileSaver::fileHandler << "\n";
}

void FileSaver::Close()
{
	FileSaver::fileHandler.close();
}