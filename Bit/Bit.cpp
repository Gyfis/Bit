#include "Bit.h"


Bit::Bit(void) { }

Bit::~Bit(void) { }

size_t Bit::x;
size_t Bit::y;
size_t Bit::lastX;
size_t Bit::lastY;
CHAR_INFO Bit::underBit;
CHAR_INFO Bit::bit;

void Bit::Initialize()
{

	Bit::bit.Attributes = foregroundColorWhiteC | backgroundColorBlackC;
	Bit::bit.Char.AsciiChar = pieceOfGodC;

	Bit::x = 0;
	Bit::y = 0;
	Bit::lastX = 0;
	Bit::lastY = 0;
	Bit::underBit = ScreenManager::GetCharAtPosition(Bit::GetPosition());
	//Bit::Draw();
}
	
void Bit::MoveDown()
{
	Bit::lastY++;
}

void Bit::MoveUp()
{
	Bit::lastY--;
}

void Bit::MoveLeft()
{
	Bit::lastX--;
}

void Bit::MoveRight()
{
	Bit::lastX++;
}

size_t Bit::GetX()
{
	return Bit::x;
}

size_t Bit::GetY()
{
	return Bit::y;
}

size_t Bit::GetLastY()
{
	return Bit::lastY;
}

void Bit::SetX(size_t x)
{
	Bit::lastX = x;
}

void Bit::SetY(size_t y)
{
	Bit::lastY = y;
}

void Bit::SetPosition(size_t x, size_t y)
{
	Bit::lastX = x;
	Bit::lastY = y;
}

void Bit::Draw()
{
	if ((Bit::x != Bit::lastX) || (Bit::y != Bit::lastY))
	{

		ScreenManager::ReplaceCharAtPosition(Bit::underBit, Bit::GetPosition());

		Bit::x = Bit::lastX;
		Bit::y = Bit::lastY;

		Bit::underBit = ScreenManager::GetCharAtPosition(Bit::GetPosition());

		ScreenManager::ReplaceCharAtPosition(Bit::bit, Bit::GetPosition());
	}
	else
	{
		ScreenManager::ReplaceCharAtPosition(Bit::bit, Bit::GetPosition());
	}
}

size_t Bit::GetPosition()
{
	return Bit::y * windowWidthC + Bit::x;
}

size_t Bit::GetLastPosition()
{
	return Bit::lastY * windowWidthC + Bit::lastX;
}

