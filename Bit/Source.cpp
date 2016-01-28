
#include <iostream>

#include "Constants.h"
#include "ScreenManager.h"
#include "LayoutManager.h"
#include "LettersManager.h"
#include "PhaseManager.h"
#include "Writer.h"
#include "Reader.h"
#include "Bit.h"

//#include <crtdbg.h>

using namespace std;

int main()
{

	/*
	#ifdef _DEBUG
		_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	#endif
	*/
	
	ScreenManager::Initialize();
	LayoutManager::Initialize();
	LettersManager::Initialize();
	
	Bit::Initialize();
	PhaseManager::Initialize();

	Writer::Initialize();
	Reader::Initialize();

	Reader::Run();
}