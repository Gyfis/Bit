#include "ScreenManager.h"

// definice statickych promennycha

HANDLE ScreenManager::timerHandle = NULL;

HANDLE ScreenManager::bufferHandle = NULL;
CHAR_INFO ScreenManager::bufferChInfo[windowWidthC * windowHeightC];
COORD ScreenManager::bufferSize;
COORD ScreenManager::bufferOffset;
SMALL_RECT ScreenManager::bufferWriteRect;


ScreenManager::ScreenManager(void)
{
}


ScreenManager::~ScreenManager(void)
{
}


// public methods

void ScreenManager::Initialize()
{	
	// setup font
	// setup buff. size
	// create buffer
	// hide cursor
	// run timer

	ScreenManager::SetupScreen();
	ScreenManager::CreateAndActivateBuffer();
	ScreenManager::HideCursor();
	ScreenManager::InitializeTimer();



}

CHAR_INFO ScreenManager::GetCharAtPosition(size_t pos)
{
	return ScreenManager::bufferChInfo[pos];
}

vector<vector<CHAR_INFO>> ScreenManager::GetCharsAtRect(SMALL_RECT pos)
{
	vector<vector<CHAR_INFO>> fullVector;
	vector<CHAR_INFO> rowVector;

	for (size_t j = 0; j < pos.Bottom; j++)
	{
		for (size_t i = 0; i < pos.Right; i++)
		{
			rowVector.push_back(ScreenManager::bufferChInfo[(pos.Top + j) * windowWidthC + (pos.Left + i)]);
		}
		fullVector.push_back(rowVector);
		rowVector.clear();
	}

	return fullVector;
}

void ScreenManager::ReplaceCharAtPosition(CHAR_INFO chInfo, size_t pos)
{
	ScreenManager::bufferChInfo[pos] = chInfo;
}

void ScreenManager::ReplaceCharsAtPositionInRow(CHAR_INFO chInfo, size_t pos, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		ScreenManager::bufferChInfo[pos + i] = chInfo; // i know that 'i' won't be over the size of the vector, and [] operator is faster then .at method
	}
}

void ScreenManager::ReplaceCharsAtPositionInColumn(CHAR_INFO chInfo, size_t pos, size_t len)
{
	for (size_t i = 0; i < len; i++)
	{
		ScreenManager::bufferChInfo[pos + (i * windowWidthC)] = chInfo;	
	}
}

void ScreenManager::ReplaceCharsAtRect(CHAR_INFO chInfo, SMALL_RECT pos)
{
	for (size_t j = 0; j < pos.Bottom; j++)
	{
		for (size_t i = 0; i < pos.Right; i++)
		{
			ScreenManager::bufferChInfo[(pos.Top + j) * windowWidthC + (pos.Left + i)] = chInfo;
		}
	}
}

void ScreenManager::ReplaceCharsAtPositionInRow(vector<CHAR_INFO> vec, size_t pos)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		ScreenManager::bufferChInfo[pos + i] = vec[i]; // i know that 'i' won't be over the size of the vector, and [] operator is faster then .at method
	}
}

void ScreenManager::ReplaceCharsAtPositionInColumn(vector<CHAR_INFO> vec, size_t pos)
{
	for (size_t i = 0; i < vec.size(); i++)
	{
		ScreenManager::bufferChInfo[pos + (i * windowWidthC)] = vec[i]; // i know that 'i' won't be over the size of the vector, and [] operator is faster then .at method
	}
}

void ScreenManager::ReplaceCharsAtRect(vector<vector<CHAR_INFO> > vec, SMALL_RECT pos)
{
	for (size_t j = 0; j < pos.Bottom; j++)
	{
		for (size_t i = 0; i < pos.Right; i++)
		{
			ScreenManager::bufferChInfo[(pos.Top + j) * windowWidthC + (pos.Left + i)] = vec[j][i];
		}
	}
}

void ScreenManager::ReplaceCharsAtRect(vector<vector<CHAR_INFO>> vec1, vector<vector<CHAR_INFO>> vec2, SMALL_RECT sr1, SMALL_RECT sr2, bool horizontal)
{
	if (horizontal)
	{
		for (size_t j = 0; j < sr1.Bottom; j++) 
		{
			for (size_t i = 0; i < sr1.Right + sr2.Right; i++)
			{
				ScreenManager::bufferChInfo[(sr1.Top + j) * windowWidthC + sr1.Left + i] = (i < sr1.Right ? vec1[j][i] : vec2[j][i - sr1.Right]);
			}
		}
	}
	else
	{
		for (size_t j = 0; j < sr1.Bottom + sr2.Bottom; j++)
		{
			for (size_t i = 0; i < sr1.Right; i++)
			{
				ScreenManager::bufferChInfo[(sr1.Top + j) * windowWidthC + sr1.Left + i] = (j < sr1.Bottom ? vec1[j][i] : vec2[j - sr1.Bottom][i]);
			}
		}
	}
}

void ScreenManager::ReplaceScreenWithChar(CHAR_INFO chInfo)
{
	for (size_t i = 0; i < windowHeightC; i++)
	{
		for (size_t j = 0; j < windowWidthC; j++)
		{
			ScreenManager::bufferChInfo[i * windowWidthC + j] = chInfo;
		}
	}
}

void ScreenManager::ClearScreen()
{
	CHAR_INFO chInfo;
	chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
	chInfo.Char.AsciiChar = pieceOfEvilC;
	ScreenManager::ReplaceScreenWithChar(chInfo);
}


// private methods

void ScreenManager::CreateAndActivateBuffer()
{	
    ScreenManager::bufferHandle = CreateConsoleScreenBuffer( 
       GENERIC_READ |           
       GENERIC_WRITE, 
       FILE_SHARE_READ | 
       FILE_SHARE_WRITE,        
       NULL,                    
       CONSOLE_TEXTMODE_BUFFER, 
       NULL);             
	
	ScreenManager::bufferSize.Y = windowHeightC;
	ScreenManager::bufferSize.X = windowWidthC;
	
	ScreenManager::bufferOffset.Y = 0;
	ScreenManager::bufferOffset.X = 0;

	ScreenManager::bufferWriteRect.Top = 0;
	ScreenManager::bufferWriteRect.Left = 0;
	ScreenManager::bufferWriteRect.Bottom = windowHeightC - 1;
	ScreenManager::bufferWriteRect.Right = windowWidthC - 1;

	SetConsoleActiveScreenBuffer(ScreenManager::bufferHandle);

}

void ScreenManager::HideCursor()
{
	CONSOLE_CURSOR_INFO cinfo;
	cinfo.dwSize = 100;				// aby sel videt, kdyby se neschoval
	cinfo.bVisible = false;

	SetConsoleCursorInfo(ScreenManager::bufferHandle, &cinfo);
}

void ScreenManager::InitializeTimer()
{
	CreateTimerQueueTimer(&ScreenManager::timerHandle, NULL, Update, NULL, 0, redrawFrequenceC, NULL);
}

void ScreenManager::SetupScreen()
{
	ScreenManager::SetFontSize(fontSizeC);
	ScreenManager::SetWindow(windowWidthC, windowHeightC);
}

void ScreenManager::SetFontSize(int size)
{
	PCONSOLE_FONT_INFOEX lpConsoleCurrentFontEx = new CONSOLE_FONT_INFOEX() ; 
	lpConsoleCurrentFontEx-> cbSize = sizeof (CONSOLE_FONT_INFOEX);

	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetCurrentConsoleFontEx(handle, 0, lpConsoleCurrentFontEx);
	lpConsoleCurrentFontEx->dwFontSize.X = size; 
	lpConsoleCurrentFontEx->dwFontSize.Y = size; 
	SetCurrentConsoleFontEx(handle, 0, lpConsoleCurrentFontEx); 
}

void ScreenManager::SetWindow(int width, int height)
{	    
	COORD size; 
    size.X = width; 
    size.Y = height; 

    SMALL_RECT rect; 
    rect.Top = 0; 
    rect.Left = 0; 
    rect.Bottom = height - 1; 
    rect.Right = width - 1; 

    HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
    SetConsoleScreenBufferSize(handle, size);            // Set Buffer Size 
    SetConsoleWindowInfo(handle, TRUE, &rect);            // Set Window Size 
}

void CALLBACK ScreenManager::Update(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{

	WriteConsoleOutput( 
		ScreenManager::bufferHandle, // screen buffer to write to 
        ScreenManager::bufferChInfo,        // buffer to copy from 
        ScreenManager::bufferSize,     // col-row size of chiBuffer 
        ScreenManager::bufferOffset,    // top left src cell in chiBuffer 
		&ScreenManager::bufferWriteRect);  // dest. screen buffer rectangle 

}

 