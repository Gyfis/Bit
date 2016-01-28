#include "LocationPhase.h"



LocationPhase::LocationPhase(void) { }
LocationPhase::~LocationPhase(void) { }


LocationPhase::LocationPhase(Location l, function<void()> f, function<void()> g)
{
	// load location 

	LocationPhase::location = l;
	LocationPhase::returnFunction = f;
	LocationPhase::doneFunction = g;

	LocationPhase::alertRect.Left = borderOffsetC;
	LocationPhase::alertRect.Top = 18;
	
	LocationPhase::currentM = 0;

}

void LocationPhase::Start()
{
	LocationPhase::Load();
	LocationPhase::InitSection();
	LocationPhase::Draw();
	Bit::SetPosition(borderOffsetC, playHeightC + borderOffsetC - 2);
	Bit::Draw();

	LocationPhase::InitFirstKey(LocationPhase::monsters[0].GetDefeated());
	LocationPhase::MoveToM(0);
}

void LocationPhase::InitFirstKey(bool defeated)
{

	vector<Key *> keys;
	keys.push_back(new Key(arrowHeaderC, arrowRightC));
	keys.push_back(new Key(characterBackspaceC));
	if (!defeated) keys.push_back(new Key('e'));


	vector<function<void()>> f;
	f.push_back(bind(&LocationPhase::Right, this));
	f.push_back(LocationPhase::returnFunction);
	if (!defeated) f.push_back(bind(&LocationPhase::StartGame, this));

	LocationPhase::alertManager.CreateAndShowAlerts(keys, LocationPhase::alertRect, backgroundColorBlackC | (defeated ? foregroundColorCyanC : foregroundColorWhiteC), commonWaitingSpeedC, f, false);
}

void LocationPhase::InitMiddleKey(bool defeated)
{
	vector<Key *> keys;
	keys.push_back(new Key(arrowHeaderC, arrowRightC));
	keys.push_back(new Key(arrowHeaderC, arrowLeftC));
	if (!defeated) keys.push_back(new Key('e'));

	vector<function<void()>> f;
	f.push_back(bind(&LocationPhase::Right, this));
	f.push_back(bind(&LocationPhase::Left, this));
	if (!defeated) f.push_back(bind(&LocationPhase::StartGame, this));

	LocationPhase::alertManager.CreateAndShowAlerts(keys, LocationPhase::alertRect, backgroundColorBlackC | (defeated ? foregroundColorCyanC : foregroundColorWhiteC), commonWaitingSpeedC, f, false);
}

void LocationPhase::InitLastKey(bool defeated)
{
	vector<Key *> keys;
	keys.push_back(new Key(arrowHeaderC, arrowLeftC));
	if (!defeated) keys.push_back(new Key('e'));

	vector<function<void()>> f;
	f.push_back(bind(&LocationPhase::Left, this));
	if (!defeated) f.push_back(bind(&LocationPhase::StartGame, this));

	LocationPhase::alertManager.CreateAndShowAlerts(keys, LocationPhase::alertRect, backgroundColorBlackC | (defeated ? foregroundColorCyanC : foregroundColorWhiteC), commonWaitingSpeedC, f, false);
}

void LocationPhase::Right()
{
	if (LocationPhase::currentM + 1 != LocationPhase::numberOfMonsters) 
	{
		LocationPhase::MoveToM(++LocationPhase::currentM);
		
		if (LocationPhase::currentM + 1 == LocationPhase::numberOfMonsters) {
			LocationPhase::InitLastKey(LocationPhase::monsters[LocationPhase::currentM].GetDefeated());
		} else {
			LocationPhase::InitMiddleKey(LocationPhase::monsters[LocationPhase::currentM].GetDefeated());
		}
	}
}

void LocationPhase::Left()
{
	if (LocationPhase::currentM != 0) 
	{
		LocationPhase::MoveToM(--LocationPhase::currentM);

		if (LocationPhase::currentM == 0) {
			LocationPhase::InitFirstKey(LocationPhase::monsters[LocationPhase::currentM].GetDefeated());
		} else {
			LocationPhase::InitMiddleKey(LocationPhase::monsters[LocationPhase::currentM].GetDefeated());
		}
	}
}

void LocationPhase::MoveToM(size_t m)
{
	size_t offset = LocationPhase::monsters[m].GetOffset();
	size_t size = LocationPhase::monsters[m].GetDifficulty() * 5 + 1;

	if (offset + size > playWidthC + LocationPhase::mainSection.GetSectionOffsetX()) {
		Bit::SetX(playWidthC - size);
		LocationPhase::mainSection.AddOffsetX(offset - LocationPhase::mainSection.GetSectionOffsetX() + size - playWidthC);
	} else if (offset < LocationPhase::mainSection.GetSectionOffsetX() + borderOffsetC) {
		Bit::SetX(borderOffsetC);
		LocationPhase::mainSection.SubtractOffsetX(LocationPhase::mainSection.GetSectionOffsetX() - offset + borderOffsetC);
	} else Bit::SetX(offset - LocationPhase::mainSection.GetSectionOffsetX());

	LocationPhase::Draw();
	Bit::Draw();
	
	Writer::RemoveTimer();
	Writer::Write(LocationPhase::monsters[m].GetName() + ": " + (!LocationPhase::monsters[m].GetDefeated() ? LocationPhase::monsters[m].GetDefeatedText() : LocationPhase::monsters[m].GetDefaultText()), mediumOutputSpeetC);
}

void LocationPhase::StartGame()
{
	Writer::RemoveTimer();

	game = new GamePhase(LocationPhase::monsters[LocationPhase::currentM], bind(&LocationPhase::EndGameWin, this), bind(&LocationPhase::EndGameLose, this));
	game->Start();
}

void LocationPhase::EndGameWin()
{
	size_t m = LocationPhase::currentM;

	LocationPhase::monsters[m].SetDefeated(true);

	ScreenManager::ClearScreen();
	LayoutManager::Initialize();

	LocationPhase::InitSection();

	size_t offset = LocationPhase::monsters[m].GetOffset();
	size_t size = LocationPhase::monsters[m].GetDifficulty() * 5 + 1;

	if (offset + size > playWidthC + LocationPhase::mainSection.GetSectionOffsetX()) {
		Bit::SetX(playWidthC - size);
		LocationPhase::mainSection.AddOffsetX(offset - LocationPhase::mainSection.GetSectionOffsetX() + size - playWidthC);
	}
	else if (offset < LocationPhase::mainSection.GetSectionOffsetX() + borderOffsetC) {
		Bit::SetX(borderOffsetC);
		LocationPhase::mainSection.SubtractOffsetX(LocationPhase::mainSection.GetSectionOffsetX() - offset + borderOffsetC);
	}
	else Bit::SetX(offset - LocationPhase::mainSection.GetSectionOffsetX());

	LocationPhase::Draw();
	Bit::Draw();

	Writer::Write(LocationPhase::monsters[m].GetName() + ": Win. You are awesome. Really. I mean it.", mediumOutputSpeetC);

	LocationPhase::Save();

	bool all = true;
	for (size_t i = 0; i < LocationPhase::monsters.size(); i++)
	{
		if (!LocationPhase::monsters[i].GetDefeated())
		{
			all = false;
			break;
		}
	}

	if (all) {
		LocationPhase::doneFunction();
	}


	if (LocationPhase::currentM == 0) LocationPhase::InitFirstKey(yep);
	else if (m + 1 == LocationPhase::numberOfMonsters) LocationPhase::InitLastKey(true);
	else LocationPhase::InitMiddleKey(true);

}

void LocationPhase::EndGameLose()
{
	size_t m = LocationPhase::currentM;

	ScreenManager::ClearScreen();

	LocationPhase::InitSection();

	size_t offset = LocationPhase::monsters[m].GetOffset();
	size_t size = LocationPhase::monsters[m].GetDifficulty() * 5 + 1;

	if (offset + size > playWidthC + LocationPhase::mainSection.GetSectionOffsetX()) {
		Bit::SetX(playWidthC - size);
		LocationPhase::mainSection.AddOffsetX(offset - LocationPhase::mainSection.GetSectionOffsetX() + size - playWidthC);
	}
	else if (offset < LocationPhase::mainSection.GetSectionOffsetX() + borderOffsetC) {
		Bit::SetX(borderOffsetC);
		LocationPhase::mainSection.SubtractOffsetX(LocationPhase::mainSection.GetSectionOffsetX() - offset + borderOffsetC);
	}
	else Bit::SetX(offset - LocationPhase::mainSection.GetSectionOffsetX());

	LocationPhase::Draw();
	Bit::Draw();

	Writer::Write(LocationPhase::monsters[m].GetName() + ": Losed. Try again.", mediumOutputSpeetC);

	if (LocationPhase::currentM == 0) LocationPhase::InitFirstKey(nope);
	else if (m + 1 == LocationPhase::numberOfMonsters) LocationPhase::InitLastKey(false);
	else LocationPhase::InitMiddleKey(false);
}

void LocationPhase::InitSection()
{

	vector<vector<CHAR_INFO>> contentVector;
	vector<CHAR_INFO> rowVector;

	CHAR_INFO chInfo;

	string name = LocationPhase::location.GetName();
	LocationPhase::location.GetTricolor();

	size_t currentMonster = 0;

	bool mDraw = true;

	size_t monsterOffset = 0;
	size_t monsterWidth = 0;

	for (size_t i = 0; i < playHeightC; i++)
	{
		for (size_t j = 0; j < max(LocationPhase::width, playWidthC); j++)
		{
			chInfo.Char.AsciiChar = pieceOfEvilC;
			chInfo.Attributes = foregroundColorGrayC | backgroundColorBlackC;
			if (i == 0 || i == 11) {
				chInfo.Char.AsciiChar = pieceOfGodC;
				chInfo.Attributes = backgroundColorBlackC | Colors::ColorFromID(LocationPhase::location.GetTricolor().GetC3());
			} else if (i == 1 || i == 12) {
				chInfo.Char.AsciiChar = pieceOfGodC;
				chInfo.Attributes = backgroundColorBlackC | Colors::ColorFromID(LocationPhase::location.GetTricolor().GetC2());
			} else if (i == 2 || i == 13) {
				chInfo.Char.AsciiChar = pieceOfGodC;
				chInfo.Attributes = backgroundColorBlackC | Colors::ColorFromID(LocationPhase::location.GetTricolor().GetC1());
			} else if (i > 3 && i < 10) { // text
				
				chInfo.Attributes = foregroundColorWhiteC | backgroundColorBlackC;
				if (j < 3) chInfo.Char.AsciiChar = pieceOfEvilC;
				else {
					size_t currentChar = (j - 3) / 4;
					size_t currentX = (j - 3) % 4;
					size_t currentY = (i - 4) % 6;

					if (currentX == 3) chInfo.Char.AsciiChar = pieceOfEvilC;
					else {
						if (currentChar < name.length()) {
						
							bool *character = (bool *)LettersManager::letterMap[name[currentChar]];
							if (character[(currentY - 1) * letterWidthC + currentX] == 1) chInfo.Char.AsciiChar = pieceOfGodC;
							else chInfo.Char.AsciiChar = pieceOfEvilC;

						} else chInfo.Char.AsciiChar = pieceOfEvilC;
					}
				}
			} else if (i == playHeightC - 3 || i == playHeightC - 1) {
				chInfo.Char.AsciiChar = borderEdgeHorizontalC;
			} else if (j == LocationPhase::monsters.at(currentMonster).GetOffset() - 1) {
				mDraw = true;

				monsterWidth = 5 * LocationPhase::monsters.at(currentMonster).GetDifficulty();
				monsterOffset = LocationPhase::monsters.at(currentMonster).GetOffset() - 1;

				if (i >= playHeightC - 3 - monsterWidth && i < playHeightC - 3) {
					size_t mx = 0;//j - monsterOffset;
					size_t my = i + 3 + monsterWidth - playHeightC;

					chInfo.Char.AsciiChar = LocationPhase::monsters.at(currentMonster).GetShape()[my][mx] ? pieceOfGodC : pieceOfEvilC;
					chInfo.Attributes = LocationPhase::monsters.at(currentMonster).GetDefeated() ? (backgroundColorWhiteC | foregroundColorCyanC) : LocationPhase::monsters.at(currentMonster).GetGood() ? (backgroundColorGrayC | foregroundColorGreenC) : (backgroundColorDarkGrayC | foregroundColorRedC);
				}

			} else if (mDraw) {

				if (i >= playHeightC - 3 - monsterWidth && i < playHeightC - 3) {
					size_t mx = j - monsterOffset;
					size_t my = i + 3 + monsterWidth - playHeightC;

					chInfo.Char.AsciiChar = LocationPhase::monsters.at(currentMonster).GetShape()[my][mx] ? pieceOfGodC : pieceOfEvilC;
					chInfo.Attributes = LocationPhase::monsters.at(currentMonster).GetDefeated() ? (backgroundColorWhiteC | foregroundColorCyanC) : LocationPhase::monsters.at(currentMonster).GetGood() ? (backgroundColorGrayC | foregroundColorGreenC) : (backgroundColorDarkGrayC | foregroundColorRedC);
				}

				if (j == monsterOffset + monsterWidth - 1)
				{
					mDraw = false;
					currentMonster++;
					if (currentMonster == LocationPhase::monsters.size()) currentMonster = 0;
				}
			}



			rowVector.push_back(chInfo);
		}
		contentVector.push_back(rowVector);
		rowVector.clear();
	}


	LocationPhase::mainSection = ScrollableSection(contentVector, playWidthC, playHeightC);

}

void LocationPhase::Draw() 
{
	ScreenManager::ReplaceCharsAtRect(LocationPhase::mainSection.GetSection(), LocationPhase::GetSectionRect());
}

SMALL_RECT LocationPhase::GetSectionRect()
{
	SMALL_RECT sr;
	sr.Top = borderOffsetC;
	sr.Left = borderOffsetC;
	sr.Bottom = LocationPhase::mainSection.GetSectionHeight();
	sr.Right = LocationPhase::mainSection.GetSectionWidth();
	return sr;	
}

void LocationPhase::Load()
{
	LocationPhase::fileLoader.Open(locationsPathC + LocationPhase::location.GetPath());

	LocationPhase::width = LocationPhase::fileLoader.GetSizeT();
	LocationPhase::numberOfMonsters = LocationPhase::fileLoader.GetSizeT();
	
	for (size_t i = 0; i < LocationPhase::numberOfMonsters; i++)
	{
		LocationPhase::fileLoader.GetLine();
		string monsterLocation = LocationPhase::fileLoader.GetLine();
		bool isDefeated = LocationPhase::fileLoader.GetLine() == "yes";
		size_t monsterOffset = LocationPhase::fileLoader.GetSizeT();

		
		LocationPhase::monsterLoader.Open(monstersPathC + monsterLocation);

		size_t monsterDifficulty = LocationPhase::monsterLoader.GetSizeT();

		size_t monsterWidth = 5 * monsterDifficulty;

		string line = LocationPhase::monsterLoader.GetLine();
		

		vector<vector<bool>> shape;
		vector<bool> rowShape;
		for (int i = 0; i < monsterWidth; i++)
		{
			line = LocationPhase::monsterLoader.GetLine();
			for (int j = 0; j < monsterWidth; j++)
			{
				rowShape.push_back(line[j] == '0' ? false : true);
			}
			shape.push_back(rowShape);
			rowShape.clear();
		}
		LocationPhase::monsterLoader.GetLine();

		bool isGood = LocationPhase::monsterLoader.GetLine() == "good";

		LocationPhase::monsters.push_back(Monster(monsterLocation, monsterOffset, isGood, monsterDifficulty, isDefeated, LocationPhase::monsterLoader.GetLine(), LocationPhase::monsterLoader.GetLine(), LocationPhase::monsterLoader.GetLine(), shape));

		LocationPhase::monsterLoader.Close();
	}


	LocationPhase::fileLoader.Close();
}

void LocationPhase::Save()
{
	LocationPhase::fileSaver.Open(locationsPathC + LocationPhase::location.GetPath());
	LocationPhase::fileSaver.WriteLine(LocationPhase::width);
	LocationPhase::fileSaver.WriteLine(LocationPhase::numberOfMonsters);

	for (size_t i = 0; i < LocationPhase::numberOfMonsters; i++)
	{
		LocationPhase::fileSaver.WriteLine("");
		LocationPhase::fileSaver.WriteLine(LocationPhase::monsters[i].GetLocation());
		LocationPhase::fileSaver.WriteLine(LocationPhase::monsters[i].GetDefeated() ? "yes" : "no");
		LocationPhase::fileSaver.WriteLine(LocationPhase::monsters[i].GetOffset());		
	}

	LocationPhase::fileSaver.Close();


}