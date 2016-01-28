#include "SelectLocationPhase.h"


SelectLocationPhase::SelectLocationPhase(void) { }

SelectLocationPhase::~SelectLocationPhase(void) { }

FileLoader SelectLocationPhase::fileLoader;
vector<Location> SelectLocationPhase::locations;
size_t SelectLocationPhase::numberOfLocations;
size_t SelectLocationPhase::offset;
ScrollableSection SelectLocationPhase::locationsSection;
ScrollableSection SelectLocationPhase::bitRouteSection;

FileSaver SelectLocationPhase::fileSaver;

AlertManager SelectLocationPhase::alertManager;
SMALL_RECT SelectLocationPhase::arrowsAlertRect;
SMALL_RECT SelectLocationPhase::openAlertRect;

bool SelectLocationPhase::moving;
bool SelectLocationPhase::inMotion;
bool SelectLocationPhase::movingDown;
float SelectLocationPhase::redrawTime;
HANDLE SelectLocationPhase::moveHandle;

LocationPhase *SelectLocationPhase::chosedLocation;


void SelectLocationPhase::Initialize()
{
	// defaults

	SelectLocationPhase::offset = 0;
	SelectLocationPhase::redrawTime = redrawFrequenceC + 1;
	SelectLocationPhase::inMotion = false;

	SelectLocationPhase::arrowsAlertRect.Left = 2 * borderOffsetC;
	SelectLocationPhase::arrowsAlertRect.Top = playHeightC + borderOffsetC - alertHeightC;

	SelectLocationPhase::openAlertRect.Left = 2*borderOffsetC + 2 * (alertWidthC + 1);
	SelectLocationPhase::openAlertRect.Top = playHeightC + borderOffsetC - alertHeightC;

	// load locations from file into memory of this class

	SelectLocationPhase::Load();

	// init scrollable area for locations ...

	SelectLocationPhase::InitLocationsSection();

	// ... and for bit routes

	SelectLocationPhase::InitBitRouteSection();

	// and finally, set bit location

	SelectLocationPhase::InitializeBit();
}

void SelectLocationPhase::Load()
{
	SelectLocationPhase::fileLoader.Open(locationsFileC);

	SelectLocationPhase::numberOfLocations = SelectLocationPhase::fileLoader.GetSizeT();

	SelectLocationPhase::locations.clear();


	for (size_t i = 0; i < SelectLocationPhase::numberOfLocations; i++)
	{
		SelectLocationPhase::fileLoader.GetLine();
		string location = SelectLocationPhase::fileLoader.GetLine();
		SelectLocationPhase::fileLoader.GetSizeT(0);
		SelectLocationPhase::locations.push_back(Location(location, Tricolor(SelectLocationPhase::fileLoader.GetSizeT(1), SelectLocationPhase::fileLoader.GetSizeT(2), SelectLocationPhase::fileLoader.GetSizeT(3)), SelectLocationPhase::fileLoader.GetLine(), (SelectLocationPhase::fileLoader.GetLine() == "yes")));
		SelectLocationPhase::fileLoader.GetSizeT(-1);
	}

	

	SelectLocationPhase::fileLoader.Close();
}

void SelectLocationPhase::InitLocationsSection()
{
	vector<vector<CHAR_INFO>> contentVector;
	vector<CHAR_INFO> rowVector;

	CHAR_INFO chInfo;
	chInfo.Attributes = foregroundColorGrayC | backgroundColorBlackC;

	for (size_t i = 0; i < SelectLocationPhase::locations.size(); i++)
	{

		vector<string> nameLines;
		string helpString = "";
		string keepString = "";
		string name = SelectLocationPhase::locations[i].GetName();

		for (size_t s = 0; s < name.size(); s++) // predpoklad - min znaku nez .., jinak se to asi usekne nebo tak
		{
			if (name[s] != ' ') helpString += name[s];
			else if (keepString.length() + helpString.length() > selectLocationsNamesUsableCharsC) 
			{
				nameLines.push_back(keepString);
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
			nameLines.push_back(keepString);
			keepString = helpString;
			helpString = "";
			nameLines.push_back(keepString);
		}
		else 
		{
			if (keepString != "") keepString += " ";
			keepString += helpString;
			helpString = "";
			nameLines.push_back(keepString);
		}



		for (size_t j = 0; j < selectLocationsHeightC; j++)
		{
			rowVector.clear();
			for (size_t k = 0; k < selectLocationsWidthC; k++)
			{
				chInfo.Attributes = foregroundColorGrayC | (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC);
				if (j == 0)
				{
					if (i == 0 && k == 0) chInfo.Char.AsciiChar = borderLocationsTDownC;
					else if (k == 0) chInfo.Char.AsciiChar = borderLocationsCornerLeftUpC;
					else if (k == selectLocationsWidthC - 1) 
					{
						if (i != 0) chInfo.Char.AsciiChar = borderLocationsTLeftC;
						else chInfo.Char.AsciiChar = borderLocationsCornerRightUpC;
					}
					else chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				}
				else if (j == selectLocationsHeightC - 1)
				{
					if (i == SelectLocationPhase::locations.size() - 1) chInfo.Char.AsciiChar = borderLocationsTUpC;
					if (k == 0) chInfo.Char.AsciiChar = borderLocationsCornerLeftDownC;
					else if (k == selectLocationsWidthC - 1)
					{
						if (i != SelectLocationPhase::locations.size() - 1)	chInfo.Char.AsciiChar = borderLocationsTLeftC;
						else chInfo.Char.AsciiChar = borderLocationsCornerRightDownC;
					}
					else chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				}
				else if (k == 0 || k == selectLocationsWidthC - 1) 
				{
					if (k == 0 && (j == 9 || j == 11)) chInfo.Char.AsciiChar = borderLocationsTLeftC;
					else chInfo.Char.AsciiChar = borderLocationsEdgeVerticalC;
				}
				else
				{
					if (k - j == selectLocationsTricolorStartC || k - j == selectLocationsTricolorEndC)
					{
						chInfo.Attributes = (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC) | foregroundColorBlackC;
						chInfo.Char.AsciiChar = pieceOfGodC;
					}
					else if (k - j == selectLocationsTricolorC1StartC || k - j == selectLocationsTricolorC1StartC + 1 || k - j == selectLocationsTricolorC1StartC + 2)
					{
						chInfo.Attributes = (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC) | Colors::ColorFromID(SelectLocationPhase::locations[i].GetTricolor().GetC1());
						chInfo.Char.AsciiChar = pieceOfGodC;
					}
					else if (k - j == selectLocationsTricolorC2StartC || k - j == selectLocationsTricolorC2StartC + 1 || k - j == selectLocationsTricolorC2StartC + 2)
					{
						chInfo.Attributes = (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC) | Colors::ColorFromID(SelectLocationPhase::locations[i].GetTricolor().GetC2());
						chInfo.Char.AsciiChar = pieceOfGodC;
					}
					else if (k - j == selectLocationsTricolorC3StartC || k - j == selectLocationsTricolorC3StartC + 1 || k - j == selectLocationsTricolorC3StartC + 2)
					{
						chInfo.Attributes = (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC) | Colors::ColorFromID(SelectLocationPhase::locations[i].GetTricolor().GetC3());
						chInfo.Char.AsciiChar = pieceOfGodC;
					}
					else
					{

						chInfo.Attributes = (SelectLocationPhase::locations[i].GetDone() ? backgroundColorDarkGrayC : backgroundColorBlackC) | foregroundColorWhiteC;

						if (k > selectLocationsNamesOffsetLeftC && k < selectLocationsNamesUsableCharsC * 4 + selectLocationsNamesOffsetRightC)
						{
							size_t currentLine = (j - 1) / 6;
							size_t currentChar = (k - 3) / 4;

							size_t currentY = (j - 1) % 6;
							size_t currentX = (k - 3) % 4;

							if (currentX == 3) chInfo.Char.AsciiChar = pieceOfEvilC;
							else if (currentLine < nameLines.size())
							{
								//const bool (*x)[letterBitsC]  = LettersManager::letterMap[nameLines[currentLine][currentChar]];
								//bool pravda = x[currentY * (letterWidthC + 1) + currentX];

								if (currentChar < nameLines[currentLine].size()) 
								{
									bool *character = (bool *)LettersManager::letterMap[nameLines[currentLine][currentChar]];
									if (character[(currentY - 1) * letterWidthC + currentX] == 1) chInfo.Char.AsciiChar = pieceOfGodC;
									else chInfo.Char.AsciiChar = pieceOfEvilC;
									//chInfo.Char.AsciiChar = character[(currentY - 1) * (letterWidthC + 1) + currentX] ? pieceOfGodC : pieceOfEvilC;
								}
								else chInfo.Char.AsciiChar = pieceOfEvilC;
							}
							else chInfo.Char.AsciiChar = pieceOfEvilC;
						}
						else chInfo.Char.AsciiChar = pieceOfEvilC;
					}
				}

				rowVector.push_back(chInfo);
			}
			contentVector.push_back(rowVector);
		}

		rowVector.clear();

		if (i < SelectLocationPhase::locations.size() - 1)
		{
			chInfo.Attributes = foregroundColorDarkGrayC | backgroundColorBlackC;
			chInfo.Char.AsciiChar = gradientCharSoftC;
			for (size_t l = 0; l < selectLocationsWidthC; l++)
			{
				chInfo.Attributes = foregroundColorDarkGrayC | backgroundColorBlackC;
				chInfo.Char.AsciiChar = gradientCharSoftC;
				if (l == selectLocationsWidthC - 1) 
				{
					chInfo.Attributes = foregroundColorGrayC | backgroundColorBlackC;
					chInfo.Char.AsciiChar = borderLocationsEdgeVerticalC;
				}
				rowVector.push_back(chInfo);
			}
			for (size_t k = 0; k < selectLocationsHeightSpaceC; k++)
			{
				contentVector.push_back(rowVector);
			}
			rowVector.clear();
		}
	}

	SelectLocationPhase::locationsSection = ScrollableSection(contentVector, windowWidthC - locationsBitRouteC - 2*borderOffsetC, playHeightC);

}

SMALL_RECT SelectLocationPhase::GetLocationSectionRect()
{
	SMALL_RECT sr;
	sr.Top = borderOffsetC;
	sr.Left = borderOffsetC + locationsBitRouteC;
	sr.Bottom = SelectLocationPhase::locationsSection.GetSectionHeight();
	sr.Right = SelectLocationPhase::locationsSection.GetSectionWidth();

	return sr;
}

void SelectLocationPhase::InitBitRouteSection()
{
	vector<vector<CHAR_INFO>> contentVector;
	vector<CHAR_INFO> rowVector;

	CHAR_INFO chInfo;
	chInfo.Attributes = foregroundColorGrayC | backgroundColorBlackC;
	
	for (size_t i = 0; i < SelectLocationPhase::locations.size(); i++)
	{
		for (size_t j = 0; j < selectLocationsHeightC + selectLocationsHeightSpaceC; j++)
		{
			if (i == SelectLocationPhase::locations.size() - 1 && j == selectLocationsHeightC) break;

			rowVector.clear();
			for (size_t k = 0; k < locationsBitRouteC; k++)
			{
				chInfo.Attributes = foregroundColorGrayC | backgroundColorBlackC;

				if (k == 0 && (j == 0 && i == 0)) chInfo.Char.AsciiChar = borderLocationsCornerLeftUpC;
				else if (k == 0 && (i == SelectLocationPhase::locations.size() - 1 && j == selectLocationsHeightC - 1)) chInfo.Char.AsciiChar = borderLocationsCornerLeftDownC;
				else if (k == 0 && (i == 0 && j == 9)) chInfo.Char.AsciiChar = borderLocationsTRightC;
				else if (k == 0 && (i == SelectLocationPhase::locations.size() - 1 && j == 11)) chInfo.Char.AsciiChar = borderLocationsTRightC;
				else if (k == 0) chInfo.Char.AsciiChar = borderLocationsEdgeVerticalC;
				else if ((j == 0 && i == 0) || (i == SelectLocationPhase::locations.size() - 1 && j == selectLocationsHeightC - 1)) chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				else if (k == 1 && i == 0 && j == 9) chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				else if (k == 1 && ((i != 0 || j > 9) && (i != SelectLocationPhase::locations.size() - 1 || j < 11))) chInfo.Char.AsciiChar = pieceOfEvilC;
				else if (k == 2 && (j == 9 && i == 0) || (j == 11 && i == SelectLocationPhase::locations.size() - 1)) chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				else if (k == 2 && j == 9) chInfo.Char.AsciiChar = borderLocationsCornerLeftDownC;
				else if (k == 2 && j == 11) chInfo.Char.AsciiChar = borderLocationsCornerLeftUpC;
				else if (j == 9 || j == 11) chInfo.Char.AsciiChar = borderLocationsEdgeHorizontalC;
				else if (k == 2 && (j != 10 && (i != 0 || j > 9) && (i != SelectLocationPhase::locations.size() - 1 || j < 11))) chInfo.Char.AsciiChar = borderLocationsEdgeVerticalC;
				else if (j != 10) 
				{
					chInfo.Attributes = foregroundColorDarkGrayC | backgroundColorBlackC;
					chInfo.Char.AsciiChar = gradientCharSoftC;
				}
				else chInfo.Char.AsciiChar = pieceOfEvilC;
				rowVector.push_back(chInfo);
			}
			contentVector.push_back(rowVector);
		}

		rowVector.clear();

	}

	SelectLocationPhase::bitRouteSection = ScrollableSection(contentVector, locationsBitRouteC, playHeightC);
}

SMALL_RECT SelectLocationPhase::GetBitRouteSectionRect()
{
	SMALL_RECT sr;
	sr.Top = borderOffsetC;
	sr.Left = borderOffsetC;
	sr.Bottom = SelectLocationPhase::bitRouteSection.GetSectionHeight();
	sr.Right = SelectLocationPhase::bitRouteSection.GetSectionWidth();

	return sr;
}

void SelectLocationPhase::InitializeBit()
{
	Bit::SetPosition(borderOffsetC + 1, borderOffsetC + 10 + 0 * (selectLocationsHeightC + selectLocationsHeightSpaceC));
}

void SelectLocationPhase::SetActivated()
{

	// show locations

	SelectLocationPhase::Draw();

	// add key handlers (moving, chosing, ..)
				
	vector<Key *> keys;
	keys.push_back(new Key(arrowHeaderC, arrowDownC));
	keys.push_back(new Key(characterEnterC));

	vector<function<void()>> f;
	f.push_back(SelectLocationPhase::MoveDown);
	f.push_back(SelectLocationPhase::DoorOpened);

	SelectLocationPhase::alertManager.CreateAndShowAlerts(keys, SelectLocationPhase::arrowsAlertRect, backgroundColorDarkBlueC | foregroundColorWhiteC, commonWaitingSpeedC, f, true);

}

void SelectLocationPhase::Draw()
{

	SelectLocationPhase::redrawTime += selectLocationMovingSpeedC;
	if (SelectLocationPhase::redrawTime >= redrawFrequenceC)
	{
		SelectLocationPhase::redrawTime = 0;
		ScreenManager::ReplaceCharsAtRect(SelectLocationPhase::bitRouteSection.GetSection(), SelectLocationPhase::locationsSection.GetSection(), SelectLocationPhase::GetBitRouteSectionRect(), SelectLocationPhase::GetLocationSectionRect(), true);
		Bit::Draw();
	}
}

void SelectLocationPhase::MoveDown()
{
	if (!SelectLocationPhase::moving)
	{
		if ((SelectLocationPhase::offset / (selectLocationsHeightC + selectLocationsHeightSpaceC)) != SelectLocationPhase::numberOfLocations - 1)
		{
			SelectLocationPhase::moving = true;
			SelectLocationPhase::movingDown = true;

			CreateTimerQueueTimer(&SelectLocationPhase::moveHandle, NULL, SelectLocationPhase::Move, NULL, 0, selectLocationMovingSpeedC, NULL);
		
			SelectLocationPhase::Move(0, 0); // zacina az po offsetu mam pocit...
		}
	}
}

void SelectLocationPhase::MoveUp()
{	
	if (!SelectLocationPhase::moving)
	{
		if ((SelectLocationPhase::offset / (selectLocationsHeightC + selectLocationsHeightSpaceC)) != 0)
		{
			SelectLocationPhase::moving = true;
			SelectLocationPhase::movingDown = false;

			CreateTimerQueueTimer(&SelectLocationPhase::moveHandle, NULL, SelectLocationPhase::Move, NULL, 0, selectLocationMovingSpeedC, NULL);
		
			SelectLocationPhase::Move(0, 0); // zacina az po offsetu mam pocit...
		}
	}
}


void CALLBACK SelectLocationPhase::Move(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	if (SelectLocationPhase::movingDown)
	{
		if (SelectLocationPhase::inMotion) return;
		
		SelectLocationPhase::inMotion = true;

		if (Bit::GetY() < playHeightC + borderOffsetC - selectLocationsHeightC / 2 - 1)
		{
			Bit::MoveDown();
		}
		else 
		{
			SelectLocationPhase::locationsSection.ScrollDown();
			SelectLocationPhase::bitRouteSection.ScrollDown();
		}
		SelectLocationPhase::Draw();
		
		//SelectLocationPhase::offset++;
		SelectLocationPhase::offset = Bit::GetLastY() + SelectLocationPhase::locationsSection.GetSectionOffsetY() - selectLocationsHeightSpaceC - (selectLocationsHeightC / 2) ;
		if ((SelectLocationPhase::offset % (selectLocationsHeightC + selectLocationsHeightSpaceC)) == 0) 
		{
			if (!SelectLocationPhase::moving) return;
			SelectLocationPhase::inMotion = false;
			SelectLocationPhase::moving = false;
			DeleteTimerQueueTimer(NULL, SelectLocationPhase::moveHandle, NULL);
	
			if ((SelectLocationPhase::offset / (selectLocationsHeightC + selectLocationsHeightSpaceC)) != SelectLocationPhase::numberOfLocations - 1) 
			{
				
				vector<Key *> keys;
				keys.push_back(new Key(arrowHeaderC, arrowDownC));
				keys.push_back(new Key(arrowHeaderC, arrowUpC));
				keys.push_back(new Key(characterEnterC));

				vector<function<void()>> f;
				f.push_back(SelectLocationPhase::MoveDown);
				f.push_back(SelectLocationPhase::MoveUp);
				f.push_back(SelectLocationPhase::DoorOpened);

				SelectLocationPhase::alertManager.CreateAndShowAlerts(keys, SelectLocationPhase::arrowsAlertRect, backgroundColorDarkBlueC | foregroundColorWhiteC, commonWaitingSpeedC, f, true);
				
			}
			else 
			{
				
				vector<Key *> keys;
				keys.push_back(new Key(arrowHeaderC, arrowUpC));
				keys.push_back(new Key(characterEnterC));

				vector<function<void()>> f;
				f.push_back(SelectLocationPhase::MoveUp);
				f.push_back(SelectLocationPhase::DoorOpened);

				SelectLocationPhase::alertManager.CreateAndShowAlerts(keys, SelectLocationPhase::arrowsAlertRect, backgroundColorDarkBlueC | foregroundColorWhiteC, commonWaitingSpeedC, f, true);
				
			}

			return;
		} else SelectLocationPhase::inMotion = false;
	}
	else
	{
		
		if (SelectLocationPhase::inMotion) return;
		
		SelectLocationPhase::inMotion = true;

		if (Bit::GetY() > selectLocationsHeightC / 2 + borderOffsetC)
		{
			Bit::MoveUp();
		}
		else 
		{
			SelectLocationPhase::locationsSection.ScrollUp();
			SelectLocationPhase::bitRouteSection.ScrollUp();
		}
		SelectLocationPhase::Draw();
		
		//SelectLocationPhase::offset--;
		SelectLocationPhase::offset = Bit::GetLastY() + SelectLocationPhase::locationsSection.GetSectionOffsetY() - selectLocationsHeightSpaceC - (selectLocationsHeightC / 2) ;
		if ((SelectLocationPhase::offset % (selectLocationsHeightC + selectLocationsHeightSpaceC)) == 0) 
		{

			if (!SelectLocationPhase::moving) return;
			
			DeleteTimerQueueTimer(NULL, SelectLocationPhase::moveHandle, NULL);

			if ((SelectLocationPhase::offset / (selectLocationsHeightC + selectLocationsHeightSpaceC)) != 0) 
			{
				vector<Key *> keys;
				keys.push_back(new Key(arrowHeaderC, arrowDownC));
				keys.push_back(new Key(arrowHeaderC, arrowUpC));
				keys.push_back(new Key(characterEnterC));

				vector<function<void()>> f;
				f.push_back(SelectLocationPhase::MoveDown);
				f.push_back(SelectLocationPhase::MoveUp);
				f.push_back(SelectLocationPhase::DoorOpened);

				SelectLocationPhase::alertManager.CreateAndShowAlerts(keys, SelectLocationPhase::arrowsAlertRect, backgroundColorDarkBlueC | foregroundColorWhiteC, commonWaitingSpeedC, f, true);
			}
			else 
			{	

				vector<Key *> keys;
				keys.push_back(new Key(arrowHeaderC, arrowDownC));
				keys.push_back(new Key(characterEnterC));

				vector<function<void()>> f;
				f.push_back(SelectLocationPhase::MoveDown);
				f.push_back(SelectLocationPhase::DoorOpened);

				SelectLocationPhase::alertManager.CreateAndShowAlerts(keys, SelectLocationPhase::arrowsAlertRect, backgroundColorDarkBlueC | foregroundColorWhiteC, commonWaitingSpeedC, f, true);

			}

			SelectLocationPhase::inMotion = false;
			SelectLocationPhase::moving = false;
			
			//SelectLocationPhase::OpenDoor();
			return;
		} else SelectLocationPhase::inMotion = false;
	}
}

void SelectLocationPhase::DoorOpened()
{

	// potrebuju zjistit ktere dvere

	size_t selectedLocation = (SelectLocationPhase::offset + 5) / (selectLocationsHeightC + selectLocationsHeightSpaceC);

	// potrebuju nekam nacist data, idealne do LocationPhase nejak to prevest / alokovat

	SelectLocationPhase::chosedLocation = new LocationPhase(SelectLocationPhase::locations.at(selectedLocation), SelectLocationPhase::ReturnFromLocation, SelectLocationPhase::LocationDone);

	// neudelat animaci a pustit LocationPhase

	SelectLocationPhase::chosedLocation->Start();
}

void SelectLocationPhase::ReturnFromLocation()
{
	// init
	OutputDebugString("return");

	delete SelectLocationPhase::chosedLocation;

	SelectLocationPhase::offset = 0;
	SelectLocationPhase::inMotion = false;

	Writer::ClearOutput();
	SelectLocationPhase::InitBitRouteSection();
	SelectLocationPhase::InitLocationsSection();
	SelectLocationPhase::InitializeBit();
	SelectLocationPhase::SetActivated();
}

void SelectLocationPhase::LocationDone()
{
	size_t selectedLocation = (SelectLocationPhase::offset + 5) / (selectLocationsHeightC + selectLocationsHeightSpaceC);

	SelectLocationPhase::locations[selectedLocation].SetDone(true);

	SelectLocationPhase::Save();
}

void SelectLocationPhase::Save()
{
	SelectLocationPhase::fileSaver.Open(locationsFileC);
	SelectLocationPhase::fileSaver.WriteLine(SelectLocationPhase::numberOfLocations);

	for (size_t i = 0; i < SelectLocationPhase::numberOfLocations; i++)
	{
		SelectLocationPhase::fileSaver.WriteLine("");
		SelectLocationPhase::fileSaver.WriteLine(SelectLocationPhase::locations[i].GetName());

		stringstream s;
		s.clear();
		s << SelectLocationPhase::locations[i].GetTricolor().GetC1() << " " << SelectLocationPhase::locations[i].GetTricolor().GetC2() << " " << SelectLocationPhase::locations[i].GetTricolor().GetC3();

		SelectLocationPhase::fileSaver.WriteLine(s.str());
		SelectLocationPhase::fileSaver.WriteLine(SelectLocationPhase::locations[i].GetDone() ? "yes" : "no");
		SelectLocationPhase::fileSaver.WriteLine(SelectLocationPhase::locations[i].GetPath());
	}
	SelectLocationPhase::fileSaver.Close();
}

vector<vector<CHAR_INFO>> SelectLocationPhase::GetCurrentView()
{
	// cary, nastaveni, ..
	vector<vector<CHAR_INFO>> full;
	vector<CHAR_INFO> row;

	CHAR_INFO chInfo;
	chInfo.Attributes = foregroundColorCyanC | backgroundColorBlackC;
	chInfo.Char.AsciiChar = 'a';

	for (size_t i = 0; i < playHeightC; i++)
	{
		row.clear();
		for (size_t j = 0; j < windowWidthC - 2 * borderOffsetC; j++)
		{
			row.push_back(chInfo);
		}
		full.push_back(row);
	}

	return full;
}

SMALL_RECT SelectLocationPhase::GetRect()
{
	SMALL_RECT sr;
	sr.Top = playStartTopC;
	sr.Left = playStartLeftC;
	sr.Bottom = playHeightC;
	sr.Right = windowWidthC - 2*borderOffsetC;
	return sr;
}

