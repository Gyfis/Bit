#pragma once

#include <vector>
#include <Windows.h>

#include "Constants.h"
#include "Colors.h"

#include "LayoutManager.h"
#include "ScreenManager.h"
#include "FileLoader.h"
#include "Location.h"
#include "Reader.h"
#include "ScrollableSection.h"
#include "ScreenUtilities.h"
#include "AlertManager.h"
#include "LocationPhase.h"
#include "FileSaver.h"

#include "Bit.h"


class SelectLocationPhase
{
public:
	

	static void Initialize();
	static void Load();
	static void SetActivated();

private:

	static void InitializeBit();

	static void MoveDown();
	static void MoveRight();
	static void MoveLeft();
	static void MoveUp();

	static void OpenDoor();
	static void DoorOpened();

	static void ReturnFromLocation();
	static void LocationDone();
	static void Save();

	static void Draw();
	static vector<vector<CHAR_INFO>> GetCurrentView();
	static SMALL_RECT GetRect();

	static ScrollableSection bitRouteSection;
	static void InitBitRouteSection();
	static SMALL_RECT GetBitRouteSectionRect();

	static ScrollableSection locationsSection;
	static void InitLocationsSection();
	static SMALL_RECT GetLocationSectionRect();

	static bool moving;
	static bool inMotion;
	static bool movingDown;
	static float redrawTime;
	static HANDLE moveHandle;
	static void CALLBACK Move(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

	static size_t offset;
	static FileLoader fileLoader;
	static vector<Location> locations;
	static size_t numberOfLocations;

	static FileSaver fileSaver;

	static AlertManager alertManager;
	static SMALL_RECT arrowsAlertRect;
	static SMALL_RECT openAlertRect;

	static LocationPhase *chosedLocation;

	//static LocationPhase

	SelectLocationPhase(void);
	~SelectLocationPhase(void);

};

