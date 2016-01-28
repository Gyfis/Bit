#include "GamePhase.h"

HANDLE GamePhase::waitHandle;
pair<size_t, size_t> GamePhase::player;
pair<size_t, size_t> GamePhase::enemy;
size_t GamePhase::direction;
size_t GamePhase::enemyDirection;
size_t GamePhase::enemyCounter;
size_t GamePhase::enemyNextMove;
size_t GamePhase::up;
size_t GamePhase::left;
size_t GamePhase::down;
size_t GamePhase::right;
Monster GamePhase::monster;
vector<pair<size_t, size_t>> GamePhase::playerPath;
vector<pair<size_t, size_t>> GamePhase::enemyPath;

function<void()> GamePhase::returnFunctionCorrect;
function<void()> GamePhase::returnFunctionBad;

GamePhase::GamePhase(void) { }
GamePhase::~GamePhase(void) { }

GamePhase::GamePhase(Monster m, function<void()> correct, function<void()> bad)
{
	GamePhase::monster = m;
	GamePhase::returnFunctionCorrect = correct;
	GamePhase::returnFunctionBad = bad;
}

void GamePhase::Start()
{

	ScreenManager::ClearScreen();

	GamePhase::alertRect.Left = 10;
	GamePhase::alertRect.Top = 60;

	if (GamePhase::monster.GetGood()) GamePhase::InitGoodGame();
	else GamePhase::InitBadGame();
}


void GamePhase::InitGoodGame()
{
	// 3x 10x10 policka, ctvrte na vyber

	// width,height = 50, + borders: 52

	vector<vector<CHAR_INFO>> contentVector;
	vector<CHAR_INFO> rowVector;

	CHAR_INFO chInfo;

	
	chInfo.Attributes = backgroundColorBlackC | foregroundColorGrayC;


	for (size_t i = 0; i < 42; i++)
	{
		for (size_t j = 0; j < 42; j++)
		{
			chInfo.Char.AsciiChar = pieceOfEvilC;
			if (i == 0)
			{
				if (j == 0) chInfo.Char.AsciiChar = borderCornerLeftUpC;
				else if (j == 41) chInfo.Char.AsciiChar = borderCornerRightUpC;
				else chInfo.Char.AsciiChar = borderEdgeHorizontalC;
			}
			else if (i == 41)
			{
				if (j == 0) chInfo.Char.AsciiChar = borderCornerLeftDownC;
				else if (j == 41) chInfo.Char.AsciiChar = borderCornerRightDownC;
				else chInfo.Char.AsciiChar = borderEdgeHorizontalC;
			}
			else if (j == 0 || j == 41) chInfo.Char.AsciiChar = borderEdgeVerticalC;

			rowVector.push_back(chInfo);
		}
		contentVector.push_back(rowVector);
		rowVector.clear();
	}

	
	SMALL_RECT sr;
	sr.Bottom = 42;
	sr.Right = 42;

	for (size_t k = 0; k < 8; k++)
	{
		sr.Top = 5 + (k / 4) * 47;
		sr.Left = 51 + (k % 4) * 52;
	
		ScreenManager::ReplaceCharsAtRect(contentVector, sr);
	}


	//bool *rndStart = new bool[40, 40];

	bool *rndStart = new bool[1600];
	
	random_device rd;
	mt19937 engine(rd());
	uniform_int_distribution<unsigned> dist(0, 39);

	for (size_t i = 0; i < 40; i++)
	{
		for (size_t j = 0; j < 40; j++)
		{
			//rndStart.push_back(nope);
			rndStart[i * 40 + j] = nope;
		}
	}

	vector<pair<size_t, size_t>> bits;

	
	for (size_t i = 0; i < 50; i++)
	{
		bits.push_back(make_pair(dist(engine), dist(engine)));
		rndStart[bits[i].first * 40 + bits[i].second] = yep;
	}

	dist = uniform_int_distribution<unsigned>(0, 49);
	uniform_int_distribution<unsigned> fourty(0, 39);
	uniform_int_distribution<unsigned> four(0, 3);

	vector<pair<size_t, size_t>> chosenBits;
	for (size_t i = 0; i < 4 * monster.GetDifficulty(); i++)
	{
		chosenBits.push_back(make_pair(dist(engine), four(engine)));
	}



	// game panels

	size_t loc = four(engine);


	for (size_t k = 0; k < 8; k++)
	{
		contentVector.clear();
		rowVector.clear();

		if (k < 3)
		{

			for (size_t i = 0; i < 40; i++)
			{
				for (size_t j = 0; j < 40; j++)
				{
					chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
					chInfo.Char.AsciiChar = rndStart[i * 40 + j] ? pieceOfGodC : pieceOfEvilC;
					rowVector.push_back(chInfo);
				}
				contentVector.push_back(rowVector);
				rowVector.clear();
			}
	
		} else if (k == 3) {
			
			for (size_t i = 0; i < 40; i++)
			{
				for (size_t j = 0; j < 40; j++)
				{
					chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
					chInfo.Char.AsciiChar = (i + j) % 2 == 0 ? pieceOfEvilC : pieceOfGodC;
					rowVector.push_back(chInfo);
				}
				contentVector.push_back(rowVector);
				rowVector.clear();
			}
		}
		else if (k == 4 + loc) {
			
			for (size_t i = 0; i < 40; i++)
			{
				for (size_t j = 0; j < 40; j++)
				{
					chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
					chInfo.Char.AsciiChar = rndStart[i * 40 + j] ? pieceOfGodC : pieceOfEvilC;
					rowVector.push_back(chInfo);
				}
				contentVector.push_back(rowVector);
				rowVector.clear();
			}
		} else {
			
			vector<pair<size_t, size_t>> rndBits;

			for (size_t i = 0; i < 50; i++)
			{
				rndStart[bits[i].first * 40 + bits[i].second] = nope;
			}

			for (size_t i = 0; i < 50; i++)
			{
				rndBits.push_back(make_pair(fourty(engine), fourty(engine)));
				rndStart[rndBits[i].first * 40 + rndBits[i].second] = yep;
			}
			
			for (size_t i = 0; i < 40; i++)
			{
				for (size_t j = 0; j < 40; j++)
				{
					chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
					chInfo.Char.AsciiChar = rndStart[i * 40 + j] ? pieceOfGodC : pieceOfEvilC;
					rowVector.push_back(chInfo);
				}
				contentVector.push_back(rowVector);
				rowVector.clear();
			}
			
			for (size_t i = 0; i < 50; i++)
			{
				rndStart[rndBits[i].first * 40 + rndBits[i].second] = nope;
			}


			for (size_t i = 0; i < 50; i++)
			{
				rndStart[bits[i].first * 40 + bits[i].second] = yep;
			}
		}

		sr.Left = 51 + 1 + (k % 4) * 52;
		sr.Top = 5 + 1 + (k / 4) * 47;
		sr.Bottom = 40;
		sr.Right = 40;

		ScreenManager::ReplaceCharsAtRect(contentVector, sr);
		

		if (k < 3)
		{
			for (size_t i = 0; i < 50; i++)
			{
				rndStart[bits[i].first * 40 + bits[i].second] = nope;
			}

			for (size_t i = 0; i < chosenBits.size(); i++)
			{
				switch (chosenBits[i].second)
				{
				case 0: //+,0
				
					if (bits[chosenBits[i].first].first < 39) bits[chosenBits[i].first] = make_pair(bits[chosenBits[i].first].first + 1, bits[chosenBits[i].first].second);			
					break;
				case 1: //0,+
					if (bits[chosenBits[i].first].second < 39) bits[chosenBits[i].first] = make_pair(bits[chosenBits[i].first].first, bits[chosenBits[i].first].second - 1);			
					break;
				case 2: //-,0
					if (bits[chosenBits[i].first].first > 0) bits[chosenBits[i].first] = make_pair(bits[chosenBits[i].first].first - 1, bits[chosenBits[i].first].second);			
					break;
				case 3: //0,-
					if (bits[chosenBits[i].first].second > 0) bits[chosenBits[i].first] = make_pair(bits[chosenBits[i].first].first, bits[chosenBits[i].first].second + 1);			
					break;
				}
			}

			for (size_t i = 0; i < 50; i++)
			{
				rndStart[bits[i].first * 40 + bits[i].second] = yep;
			}
		}
	
	}

	vector<Key *> keys;

	keys.push_back(new Key('a'));
	keys.push_back(new Key('b'));
	keys.push_back(new Key('c'));
	keys.push_back(new Key('d'));


	vector<function<void()>> f;
	for (size_t i = 0; i < 4; i++)
	{
		if (i == loc) f.push_back(GamePhase::returnFunctionCorrect);
		else f.push_back(GamePhase::returnFunctionBad);
	}

	GamePhase::alertManager.CreateAndShowAlerts(keys, GamePhase::alertRect, backgroundColorBlackC | foregroundColorWhiteC, commonWaitingSpeedC, f, false);
	
	delete[] rndStart;

}

void GamePhase::InitBadGame()
{
	// jedno pole, ty se vzdy hybes jednim smerem, nepritel nahodne, rychlost podle obtiznosti, musis ho obkrouzit aby narazil, je to jednoduche..


	vector<vector<CHAR_INFO>> contentVector;
	vector<CHAR_INFO> rowVector;

	CHAR_INFO chInfo;

	chInfo.Attributes = backgroundColorBlackC | foregroundColorGrayC;

	for (size_t i = 3; i < windowHeightC - 3; i++)
	{
		for (size_t j = 3; j < windowWidthC - 3; j++)
		{
			chInfo.Char.AsciiChar = pieceOfEvilC;
			if (i == 3)
			{
				if (j == 3) chInfo.Char.AsciiChar = borderCornerLeftUpC;
				else if (j == windowWidthC - 4) chInfo.Char.AsciiChar = borderCornerRightUpC;
				else chInfo.Char.AsciiChar = borderEdgeHorizontalC;
			}
			else if (i == windowHeightC - 4)
			{
				if (j == 3) chInfo.Char.AsciiChar = borderCornerLeftDownC;
				else if (j == windowWidthC - 4) chInfo.Char.AsciiChar = borderCornerRightDownC;
				else chInfo.Char.AsciiChar = borderEdgeHorizontalC;
			}
			else if (j == 3 || j == windowWidthC - 4) chInfo.Char.AsciiChar = borderEdgeVerticalC;

			rowVector.push_back(chInfo);
		}
		contentVector.push_back(rowVector);
		rowVector.clear();
	}

	SMALL_RECT sr;
	sr.Top = 3;
	sr.Bottom = windowHeightC - 6;
	sr.Left = 3;
	sr.Right = windowWidthC - 6;

	ScreenManager::ReplaceCharsAtRect(contentVector, sr); // jednoduchy ramecek
	contentVector.clear();

	// position: 10 10
	// enemy: windowWidthC - 30, windowHeightC - 30

	GamePhase::player = make_pair(30, 30);
	GamePhase::playerPath.clear();
	GamePhase::playerPath.push_back(GamePhase::player);
	GamePhase::enemy = make_pair(windowWidthC - 30, windowHeightC - 30);
	GamePhase::enemyPath.clear();
	GamePhase::enemyPath.push_back(GamePhase::enemy);
	GamePhase::enemyCounter = 0;
	GamePhase::enemyDirection = 2;
	GamePhase::enemyNextMove = 10;
	GamePhase::direction = 2;

	up = false;
	down = false;
	right = false;
	left = true;

	GamePhase::InitKey();
	GamePhase::Draw();

	CreateTimerQueueTimer(&(GamePhase::waitHandle), NULL, GamePhase::Blink, NULL, 0, badGameTickC, NULL);

}

void GamePhase::InitKey()
{
	Reader::InsertPair('w', bind(&GamePhase::Up, this), false);
	Reader::InsertPair('a', bind(&GamePhase::Left, this), false);
	Reader::InsertPair('s', bind(&GamePhase::Down, this), false);
	Reader::InsertPair('d', bind(&GamePhase::Right, this), false);

}

void GamePhase::Up()
{
	if (GamePhase::direction == 3) GamePhase::direction = -1;
	else GamePhase::direction = 1;
}

void GamePhase::Right()
{
	if (GamePhase::direction == 2) GamePhase::direction = -1;
	else GamePhase::direction = 0;
}

void GamePhase::Down()
{
	if (GamePhase::direction == 1) GamePhase::direction = -1;
	else GamePhase::direction = 3;
}

void GamePhase::Left()
{
	if (GamePhase::direction == 0) GamePhase::direction = -1;
	else GamePhase::direction = 2;
}

void GamePhase::Draw()
{
	CHAR_INFO chInfo;
	chInfo.Char.AsciiChar = pieceOfGodC;

	chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
	ScreenManager::ReplaceCharAtPosition(chInfo, (4 + GamePhase::player.second) * windowWidthC + 4 + GamePhase::player.first);

	chInfo.Attributes = backgroundColorBlackC | foregroundColorRedC;
	ScreenManager::ReplaceCharAtPosition(chInfo, (4 + GamePhase::enemy.second) * windowWidthC + 4 + GamePhase::enemy.first);
}

void GamePhase::RemoveTail(pair<size_t, size_t> location)
{
	CHAR_INFO chInfo;
	chInfo.Attributes = backgroundColorBlackC | foregroundColorWhiteC;
	chInfo.Char.AsciiChar = pieceOfEvilC;

	ScreenManager::ReplaceCharAtPosition(chInfo, (4 + location.second) * windowWidthC + 4 + location.first);
}

void GamePhase::CheckCollision()
{
	
	for (size_t i = 0; i < GamePhase::playerPath.size() - 1; i++)
	{
		if (GamePhase::enemy.first == GamePhase::playerPath[i].first && GamePhase::enemy.second == GamePhase::playerPath[i].second)
		{
			// enemy fail

			// klavesy
			Reader::RemovePair('w', GamePhase::up);
			Reader::RemovePair('a', GamePhase::left);
			Reader::RemovePair('s', GamePhase::down);
			Reader::RemovePair('d', GamePhase::right);

			// timer
			DeleteTimerQueueTimer(NULL, GamePhase::waitHandle, NULL);

			GamePhase::returnFunctionCorrect();

			return;
		}
	}
	
	for (size_t i = 0; i < GamePhase::enemyPath.size() - 1; i++)
	{
		if (GamePhase::player.first == GamePhase::enemyPath[i].first && GamePhase::player.second == GamePhase::enemyPath[i].second)
		{
			// player fail

			// klavesy
			Reader::RemovePair('w', GamePhase::up);
			Reader::RemovePair('a', GamePhase::left);
			Reader::RemovePair('s', GamePhase::down);
			Reader::RemovePair('d', GamePhase::right);

			// timer
			DeleteTimerQueueTimer(NULL, GamePhase::waitHandle, NULL);

			GamePhase::returnFunctionBad();

			return;
		}
	}
}

void CALLBACK GamePhase::Blink(PVOID lpParameter, BOOLEAN TimerOrWaitFired)
{
	// player posun o 1, enemy++ a pokud % dif = 0, pak taky posun o 1 random smerem
	
	switch (GamePhase::direction) {
		case 0: // doprava
			GamePhase::player = make_pair(GamePhase::player.first + 1, GamePhase::player.second);
			if (GamePhase::player.first == windowWidthC - 8) GamePhase::player = make_pair(0, GamePhase::player.second);
			break;
		case 1: // nahoru
			GamePhase::player = make_pair(GamePhase::player.first, GamePhase::player.second - 1);
			if (GamePhase::player.second == -1) GamePhase::player = make_pair(GamePhase::player.first, windowHeightC - 9);
			break;
		case 2: // doleva
			GamePhase::player = make_pair(GamePhase::player.first - 1, GamePhase::player.second);
			if (GamePhase::player.first == -1) GamePhase::player = make_pair(windowWidthC - 9, GamePhase::player.second);
			break;
		case 3: // dolu
			GamePhase::player = make_pair(GamePhase::player.first, GamePhase::player.second + 1);
			if (GamePhase::player.second == windowHeightC - 8) GamePhase::player = make_pair(GamePhase::player.first, 0);
			break;
	}

	GamePhase::playerPath.push_back(GamePhase::player);
	if (GamePhase::playerPath.size() >= 100)
	{
		GamePhase::RemoveTail(*GamePhase::playerPath.begin());
		GamePhase::playerPath.erase(GamePhase::playerPath.begin());
	}

	switch (GamePhase::enemyDirection) {
	case 0: // doprava
		GamePhase::enemy = make_pair(GamePhase::enemy.first + 1, GamePhase::enemy.second);
		if (GamePhase::enemy.first == windowWidthC - 8) GamePhase::enemy = make_pair(0, GamePhase::enemy.second);
		break;
	case 1: // nahoru
		GamePhase::enemy = make_pair(GamePhase::enemy.first, GamePhase::enemy.second - 1);
		if (GamePhase::enemy.second == -1) GamePhase::enemy = make_pair(GamePhase::enemy.first, windowHeightC - 9);
		break;
	case 2: // doleva
		GamePhase::enemy = make_pair(GamePhase::enemy.first - 1, GamePhase::enemy.second);
		if (GamePhase::enemy.first == -1) GamePhase::enemy = make_pair(windowWidthC - 9, GamePhase::enemy.second);
		break;
	case 3: // dolu
		GamePhase::enemy = make_pair(GamePhase::enemy.first, GamePhase::enemy.second + 1);
		if (GamePhase::enemy.second == windowHeightC - 8) GamePhase::enemy = make_pair(GamePhase::enemy.first, 0);
		break;
	}

	GamePhase::enemyPath.push_back(GamePhase::enemy);
	if (GamePhase::enemyPath.size() >= 100)
	{
		GamePhase::RemoveTail(*GamePhase::enemyPath.begin());
		GamePhase::enemyPath.erase(GamePhase::enemyPath.begin());
	}

	GamePhase::enemyCounter++;
	if (GamePhase::enemyCounter == GamePhase::enemyNextMove)
	{
		GamePhase::enemyCounter = 0;

		random_device rd;
		mt19937 engine(rd());
		uniform_int_distribution<unsigned> dist(10, 20);
		GamePhase::enemyNextMove = dist(engine);

		uniform_int_distribution<unsigned> four(0, 1);

		GamePhase::enemyDirection += 1 - 2 * four(engine);
		if (GamePhase::enemyDirection < 0) GamePhase::enemyDirection = 3;
		else if (GamePhase::enemyDirection > 3) GamePhase::enemyDirection = 0;
	}

	GamePhase::Draw();

	GamePhase::CheckCollision();

}