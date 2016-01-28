#pragma once


#include <map>
#include <string>
#include <deque>

#include "AlertManager.h"
#include "ScreenManager.h"
#include "Reader.h"
#include "LettersManager.h"

#include "Constants.h"


using namespace std;


class Writer
{
public:

	static void Initialize();

	static void Write(string s, size_t speed);
	static void RemoveTimer();
	static void ClearOutput();

private:

	Writer(void);
	~Writer(void);
	
	static void PrintLines();
	static size_t currentLine;
	static size_t currentChar;
	static HANDLE printHandle;
	static deque<string> lines;
	static size_t outputSpeed;	
	static bool waitingForKey;

	static bool isWriting;

	static bool showWaitingSwitch;

	static AlertManager alertManager;

	static bool writing;

	static void CALLBACK Update(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

};

