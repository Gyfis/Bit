#pragma once

#include <functional>
#include <random>
#include <sstream>

#include "Monster.h"
#include "ScreenManager.h"
#include "AlertManager.h"
#include "Reader.h"

using namespace std;

#define yep true
#define nope false

class GamePhase
{
public:

	GamePhase(void);
	~GamePhase(void);
	
	GamePhase(Monster m, function<void()> correct, function<void()> bad);

	void Start();

private:
	
	void InitGoodGame();
	void InitBadGame();

	void CorrectAnswer();
	void BadAnswer();

	SMALL_RECT alertRect;

	static Monster monster;
	static function<void()> returnFunctionCorrect;
	static function<void()> returnFunctionBad;

	AlertManager alertManager;

	void Up();
	void Right();
	void Down();
	void Left();

	void InitKey();

	static size_t up;
	static size_t right;
	static size_t down;
	static size_t left;

	static void Draw();

	static pair<size_t, size_t> player;
	static pair<size_t, size_t> enemy;
	static size_t direction;
	static size_t enemyDirection;
	static size_t enemyCounter;
	static size_t enemyNextMove;

	static vector<pair<size_t, size_t>> playerPath;
	static vector<pair<size_t, size_t>> enemyPath;

	static void RemoveTail(pair<size_t, size_t> p);
	static void CheckCollision();

	static HANDLE waitHandle;
	static void CALLBACK Blink(PVOID lpParameter, BOOLEAN TimerOrWaitFired);

};

