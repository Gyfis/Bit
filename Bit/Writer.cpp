#include "Writer.h"


size_t Writer::currentLine;
size_t Writer::currentChar;
HANDLE Writer::printHandle;
deque<string> Writer::lines;
size_t Writer::outputSpeed;
bool Writer::waitingForKey;

bool Writer::isWriting;

//HANDLE Writer::waitHandle;
//size_t Writer::waitingSpeed;
bool Writer::showWaitingSwitch;
bool Writer::writing;
//size_t Writer::readerHandleNumber;

AlertManager Writer::alertManager;
//ScreenManager Writer::sr;

Writer::Writer(void)
{
}

Writer::~Writer(void)
{
}


void Writer::Initialize()
{

	
	Writer::waitingForKey = false;
	//Writer::waitingSpeed = 350;
	Writer::showWaitingSwitch = false;
	Writer::isWriting = false;
}


// public methods

void Writer::Write(string s, size_t speed)
{
	Writer::outputSpeed = speed;

	Writer::lines.clear();

	string helpString = "";
	string keepString = "";

	for (size_t i = 0; i < s.length(); i++)
	{
		if (s[i] != ' ') helpString += s[i];
		else if (keepString.length() + helpString.length() > outputUsableCharsC) 
		{
			Writer::lines.push_back(keepString);
			keepString = helpString;
			helpString = "";
		}
		else 
		{
			if (keepString != "") keepString += " ";
			keepString += helpString;
			helpString = "";
		}
	}


	if (keepString.length() + helpString.length() > outputUsableCharsC) 
	{
		Writer::lines.push_back(keepString);
		keepString = helpString;
		helpString = "";
		Writer::lines.push_back(keepString);
	}
	else 
	{
		if (keepString != "") keepString += " ";
		keepString += helpString;
		helpString = "";
		Writer::lines.push_back(keepString);
	}


	Writer::PrintLines();
}

void Writer::RemoveTimer()
{
	if (Writer::isWriting) DeleteTimerQueueTimer(NULL, Writer::printHandle, NULL);
}

void Writer::ClearOutput()
{
	CHAR_INFO chClear;
	chClear.Attributes = foregroundColorWhiteC | backgroundColorBlackC;
	chClear.Char.AsciiChar = pieceOfEvilC;
	SMALL_RECT srClear;
	srClear.Top = windowHeightC - outputHeightC - borderOffsetC + 1;
	srClear.Left = borderOffsetC + 1;
	srClear.Bottom = outputHeightC - 1;
	srClear.Right = windowWidthC - 2 * (borderOffsetC + 1);

	ScreenManager::ReplaceCharsAtRect(chClear, srClear);
}

// private methods

void Writer::PrintLines()
{

	// clear output window?

	Writer::ClearOutput();

	Writer::currentLine = 0;
	Writer::currentChar = 0;

		
	Writer::isWriting = true;
	CreateTimerQueueTimer(&Writer::printHandle, NULL, Writer::Update, NULL, 0, Writer::outputSpeed, NULL);


}

void CALLBACK Writer::Update(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{

	if (Writer::writing) return;
	
	Writer::writing = true;

	if (Writer::waitingForKey)
	{
		Writer::waitingForKey = false;
		
		//Reader::RemovePair(characterEnterC, Writer::readerHandleNumber);
		//DeleteTimerQueueTimer(NULL, Writer::waitHandle, NULL);
	}

	CHAR_INFO chInfo;
	chInfo.Attributes = foregroundColorWhiteC | backgroundColorBlackC;

	vector<CHAR_INFO> lineOfChar;
	vector<vector<CHAR_INFO> > wholeChar;


	bool *b = (bool *)LettersManager::letterMap.at(Writer::lines[Writer::currentLine][Writer::currentChar]);
	for (int k = 0; k < letterHeightC; k++)
	{
		for (int l = 0; l < letterWidthC; l++)
		{
			if (b[k * letterWidthC + l] == 1) chInfo.Char.AsciiChar = pieceOfGodC;
			else chInfo.Char.AsciiChar = pieceOfEvilC;
			lineOfChar.push_back(chInfo);
		}
		chInfo.Char.AsciiChar = pieceOfEvilC;
		lineOfChar.push_back(chInfo);
		wholeChar.push_back(lineOfChar);
		lineOfChar.clear();
	}

	SMALL_RECT sr;
	sr.Top = outputStartTopC + Writer::currentLine * letterHeightC;
	sr.Left = outputStartLeftC + Writer::currentChar * (letterWidthC + 1);
	sr.Bottom = letterHeightC;
	sr.Right = letterWidthC;

	ScreenManager::ReplaceCharsAtRect(wholeChar, sr);

	wholeChar.clear();
	Writer::currentChar++;
	if (Writer::currentChar == Writer::lines[currentLine].length())
	{
		Writer::currentChar = 0;
		Writer::currentLine++;
	}

	if (Writer::currentLine == Writer::lines.size())
	{
		// delete the timer;

		Writer::isWriting = false;
		DeleteTimerQueueTimer(NULL, Writer::printHandle, NULL);
	}
	else if (Writer::currentLine == outputUsableLinesC)
	{
		
		Writer::isWriting = false;
		DeleteTimerQueueTimer(NULL, Writer::printHandle, NULL);

		for (int i = 0; i < outputUsableLinesC; i++)
		{
			Writer::lines.pop_front();
		}
		

		if (!Writer::waitingForKey){
			Writer::waitingForKey = true;
			//readerHandleNumber = Reader::InsertPair(characterEnterC, Writer::PrintLines);
		}

		Writer::showWaitingSwitch = true;
		SMALL_RECT sr;
		sr.Left = outputStartLeftC + outputUsableWidthC - alertWidthC;
		sr.Top = outputStartTopC + outputUsableHeightC - alertHeightC;

		Writer::alertManager.CreateAndShowAlert(characterEnterC, sr, foregroundColorWhiteC | backgroundColorBlackC, commonWaitingSpeedC, Writer::PrintLines);
		//CreateTimerQueueTimer(&Writer::waitHandle, NULL, Writer::ShowWaiting, NULL, 0, Writer::waitingSpeed, NULL);
		

		//Writer::PrintLines();
	}

	Writer::writing = false;
}
