#pragma once
#include <Windows.h>
#include <iostream>
#include "Constants.h"


using namespace std;

class ScreenManager
{
public:
	
	
	ScreenManager(void);
	~ScreenManager(void);	

	static void Initialize();

	static void ReplaceCharAtPosition(CHAR_INFO chInfo, size_t pos);
	static void ReplaceCharsAtPositionInRow(CHAR_INFO chInfo, size_t pos, size_t len);
	static void ReplaceCharsAtPositionInColumn(CHAR_INFO chInfo, size_t pos, size_t len);
	static void ReplaceCharsAtRect(CHAR_INFO chInfo, SMALL_RECT pos);
	static void ReplaceCharsAtPositionInRow(vector<CHAR_INFO> vec, size_t pos);
	static void ReplaceCharsAtPositionInColumn(vector<CHAR_INFO> vec, size_t pos);
	static void ReplaceCharsAtRect(vector<vector<CHAR_INFO> > vec, SMALL_RECT pos);
	static void ReplaceCharsAtRect(vector<vector<CHAR_INFO>> vec1, vector<vector<CHAR_INFO>> vec2, SMALL_RECT sr1, SMALL_RECT sr2, bool horizontal);

	static void ClearScreen();

	static CHAR_INFO GetCharAtPosition(size_t pos);
	static vector<vector<CHAR_INFO>> GetCharsAtRect(SMALL_RECT pos);	

private:
	static HANDLE timerHandle;

	static HANDLE bufferHandle;
	static CHAR_INFO bufferChInfo[windowWidthC * windowHeightC];

	static COORD bufferSize;
    static COORD bufferOffset;
	static SMALL_RECT bufferWriteRect;

	static void CreateAndActivateBuffer();
	static void HideCursor();
	static void InitializeTimer();
	static void SetupScreen();
	static void SetFontSize(int size);
	static void SetWindow(int width, int height);

	static void ReplaceScreenWithChar(CHAR_INFO chInfo);

	static void CALLBACK Update(PVOID lpParameter, BOOLEAN TimerOrWaitFired);
};

