#pragma once
#include <Windows.h>
#include "ScreenManager.h"
#include "Constants.h"

class Bit
{
public:

	static void Initialize();

	static void MoveDown();
	static void MoveUp();
	static void MoveLeft();
	static void MoveRight();

	static size_t GetX();
	static size_t GetY();
	static size_t GetLastY();
	static size_t GetPosition();
	static size_t GetLastPosition();

	static void SetX(size_t x);
	static void SetY(size_t y);
	static void SetPosition(size_t x, size_t y);

	static void Draw();

private:

	static size_t x;
	static size_t y;
	
	static size_t lastX;
	static size_t lastY;


	static CHAR_INFO underBit;
	static CHAR_INFO bit;

	Bit(void);
	~Bit(void);
};

