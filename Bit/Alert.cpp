#include "Alert.h"


// napsat mail panu Brabcovi, abych se zeptal, proc sakra! nemuzu definovat v headeru Handle a pak ten callback, kdyz je to object member, ale kdyz to napisu takhle hovadsky tak to funguje tak jak ma
// == friend function, look it up !
// !! friend neni spravny, proste budu static volat callback porad stejne, projede to mnozinou alertu, a bude



vector<Alert *> Alert::currentAlerts;
HANDLE Alert::waitHandle;

Alert::Alert(void)
{
}


Alert::~Alert(void)
{
	for (vector<Alert *>::iterator it = Alert::currentAlerts.begin(); it != Alert::currentAlerts.end(); it++)
	{
		if (*it == this)
		{
			Alert::currentAlerts.erase(it);
			break;
		}
	}

	if (Alert::currentAlerts.size() == 0) DeleteTimerQueueTimer(NULL, Alert::waitHandle, NULL);
}

Alert::Alert(int c, SMALL_RECT pos, WORD color, size_t waitingSpeed)
{
	
	Alert::alertPosition = pos;
	Alert::alertCharacter = c;
	Alert::alertAltCharacter = 0;
	Alert::comboAlert = false;
	Alert::alertColor = color;

	Alert::waitingSpeed = waitingSpeed;

	
	Alert::currentAlerts.push_back(this);
	
	if (Alert::currentAlerts.size() == 1) CreateTimerQueueTimer(&(Alert::waitHandle), NULL, Alert::Blink, NULL, 0, Alert::waitingSpeed, NULL);
	
}

Alert::Alert(int c1, int c2, SMALL_RECT pos, WORD color, size_t waitingSpeed)
{
	
	Alert::alertPosition = pos;
	Alert::alertAltCharacter = c1;
	Alert::alertCharacter = c2;
	Alert::comboAlert = true;
	Alert::alertColor = color;

	Alert::waitingSpeed = waitingSpeed;
	
	Alert::currentAlerts.push_back(this);

	if (Alert::currentAlerts.size() == 1) CreateTimerQueueTimer(&(Alert::waitHandle), NULL, Alert::Blink, NULL, 0, Alert::waitingSpeed, NULL);
	
}

int Alert::GetChar() {
	return Alert::alertCharacter;
}

int Alert::GetAltChar() {
	return Alert::alertAltCharacter;
}

bool Alert::IsCombo() {
	return Alert::comboAlert;
}


void CALLBACK Alert::Blink(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{

	for (size_t i = 0; i < Alert::currentAlerts.size(); i++)
	{
		Alert *a = Alert::currentAlerts[i];

		CHAR_INFO chInfo;
		a->colorSwitch = !a->colorSwitch;
		
		vector<CHAR_INFO> lineOfChar;
		vector<vector<CHAR_INFO> > wholeChar;

		for (int i = 0; i < alertHeightC; i++)
		{
			for (int j = 0; j < alertWidthC; j++)
			{
				chInfo.Attributes = a->colorSwitch ? (foregroundColorGrayC | backgroundColorBlackC) : (foregroundColorWhiteC | backgroundColorBlackC);

				switch (alertBorderC[i * alertWidthC + j])
				{
				case 0:
					{
					chInfo.Attributes = a->alertColor;
					chInfo.Char.AsciiChar = (* LettersManager::letterMap[a->alertCharacter + (a->comboAlert ? arrowHeaderC : 0)])[(i - 1) * (alertWidthC - 4) + (j - 2)] ? pieceOfGodC : pieceOfEvilC;
					}
					break;
				case 1: chInfo.Char.AsciiChar = borderEdgeHorizontalC;
					break;
				case 2: chInfo.Char.AsciiChar = borderEdgeVerticalC;
					break;
				case 3: chInfo.Char.AsciiChar = borderCornerLeftUpC;
					break;
				case 4: chInfo.Char.AsciiChar = borderCornerRightUpC;
					break; 
				case 5: chInfo.Char.AsciiChar = borderCornerLeftDownC;
					break;
				case 6: chInfo.Char.AsciiChar = borderCornerRightDownC;
					break;
				default: chInfo.Char.AsciiChar = pieceOfEvilC;
					chInfo.Attributes = foregroundColorBlackC | backgroundColorBlackC;
					break;
				}

				lineOfChar.push_back(chInfo);
			}
			wholeChar.push_back(lineOfChar);
			lineOfChar.clear();
		}

		SMALL_RECT sr;
		sr.Top = a->alertPosition.Top;
		sr.Left = a->alertPosition.Left;
		sr.Bottom = alertHeightC;
		sr.Right = alertWidthC;

		ScreenManager::ReplaceCharsAtRect(wholeChar, sr);

	}

/*
	CHAR_INFO chInfo;
	Alert::colorSwitch = !Alert::colorSwitch;
	

	vector<CHAR_INFO> lineOfChar;
	vector<vector<CHAR_INFO> > wholeChar;

	for (int i = 0; i < alertHeightC; i++)
	{
		for (int j = 0; j < alertWidthC; j++)
		{
			chInfo.Attributes =  colorSwitch ? (foregroundColorGrayC | backgroundColorBlackC) : (foregroundColorWhiteC | backgroundColorBlackC);

			switch (alertBorderC[i * alertWidthC + j])
			{
			case 0:
				{
				chInfo.Attributes = alertColor;
				chInfo.Char.AsciiChar = (* LettersManager::letterMap[alertCharacter - (comboAlert ? 128 : 0)])[(i - 1) * (alertWidthC - 4) + (j - 2)] ? pieceOfGodC : pieceOfEvilC;
				}
				break;
			case 1: chInfo.Char.AsciiChar = borderEdgeHorizontalC;
				break;
			case 2: chInfo.Char.AsciiChar = borderEdgeVerticalC;
				break;
			case 3: chInfo.Char.AsciiChar = borderCornerLeftUpC;
				break;
			case 4: chInfo.Char.AsciiChar = borderCornerRightUpC;
				break; 
			case 5: chInfo.Char.AsciiChar = borderCornerLeftDownC;
				break;
			case 6: chInfo.Char.AsciiChar = borderCornerRightDownC;
				break;
			default: chInfo.Char.AsciiChar = pieceOfEvilC;
				chInfo.Attributes = foregroundColorBlackC | backgroundColorBlackC;
				break;
			}

			lineOfChar.push_back(chInfo);
		}
		wholeChar.push_back(lineOfChar);
		lineOfChar.clear();
	}

	SMALL_RECT sr;
	sr.Top = alertPosition.Top;
	sr.Left = alertPosition.Left;
	sr.Bottom = alertHeightC;
	sr.Right = alertWidthC;

	ScreenManager::ReplaceCharsAtRect(wholeChar, sr);
*/
}
