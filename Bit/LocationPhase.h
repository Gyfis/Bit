#pragma once

#include <functional>
#include <vector>

#include "Location.h"
#include "FileLoader.h"
#include "ScreenManager.h"
#include "ScrollableSection.h"
#include "LettersManager.h"
#include "Colors.h"
#include "Monster.h"
#include "Bit.h"
#include "AlertManager.h"
#include "Writer.h"
#include "GamePhase.h"
#include "FileSaver.h"
#include "LayoutManager.h"

using namespace std;
class LocationPhase
{
public:

	LocationPhase(void);
	~LocationPhase(void);

	LocationPhase(Location l, function<void()> f, function<void()> g);

	void Start();

private:

	void Load();
	void Save();
	void InitSection();
	void Draw();
	void Left();
	void Right();
	
	void InitFirstKey(bool defeated);
	void InitMiddleKey(bool defeated);
	void InitLastKey(bool defeated);

	void MoveToM(size_t m);

	void StartGame();
	void EndGameWin();
	void EndGameLose();


	SMALL_RECT GetSectionRect();

	SMALL_RECT alertRect;

	AlertManager alertManager;

	
	ScrollableSection mainSection;

	size_t width;
	size_t numberOfMonsters;
	vector<Monster> monsters;
	Location location;
	FileLoader fileLoader;
	FileLoader monsterLoader;
	FileSaver fileSaver;
	function<void()> returnFunction;
	size_t currentM;

	function<void()> doneFunction;

	
	GamePhase *game;

	

};

