#pragma once


#include <Windows.h>
#include <map>
#include <functional>
#include <sstream>

#include "ScreenManager.h"
#include "Reader.h"
#include "Alert.h"
#include "Key.h"

using namespace std;

struct AlertStruct
{
	SMALL_RECT position;
	vector<vector<CHAR_INFO>> characterData;
	Alert* alert;
};


	
class AlertManager
{

public:

	AlertManager(void);
	~AlertManager(void);

	void CreateAndShowAlert(const int c, SMALL_RECT sr, WORD color, size_t waitingSpeed, function<void()> f);
	void CreateAndShowComboAlert(const int c1, const int c2, SMALL_RECT sr, WORD color, size_t waitingSpeed, function<void()> f);

	void CreateAndShowAlerts(const vector<Key *> keys, SMALL_RECT sr, WORD color, size_t waitingSpeed, vector<function<void()>> f, bool horizontal);
	void CreateAndShowComboAlerts(const vector<int> c1, const vector<int> c2, SMALL_RECT sr, WORD color, size_t waitingSpeed, vector<function<void()>> f, bool horizontal);

private:

	bool isToBeDeleted;

	void StopAlert(size_t id, bool removePair, bool combo);
	
	size_t numberOfAlerts;

	map<size_t, AlertStruct> currentAlerts;
	
	bool IsThereAlert(vector<vector<CHAR_INFO>> vector, AlertStruct alert);

	/*
	static HANDLE waitHandle;

	static vector<Alert *> currentAlertsVector;

	static void CALLBACK Blink(PVOID lpParameter, BOOLEAN TimerOrWaitFired);*/
};
