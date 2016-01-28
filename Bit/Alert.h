#pragma once
#include <Windows.h>
#include <functional>
#include "LettersManager.h"
#include "ScreenManager.h"
#include "Constants.h"

class Alert
{
public:
	Alert(void);
	~Alert(void);

	Alert(int c, SMALL_RECT pos, WORD color, size_t waitingSpeed);
	Alert(int c1, int c2, SMALL_RECT pos, WORD ocllor, size_t waitingSpeed);

	int GetChar();
	int GetAltChar();
	bool IsCombo();

private:
	
	size_t waitingSpeed;
	bool colorSwitch;
	WORD alertColor;
	int alertCharacter;
	int alertAltCharacter;
	bool comboAlert;
	SMALL_RECT alertPosition;

	static HANDLE waitHandle;
	static vector<Alert *> currentAlerts;

	static void CALLBACK Blink(PVOID lpParameter, BOOLEAN TimerOrWaitFired);
};

