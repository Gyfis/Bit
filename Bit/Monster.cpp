#include "Monster.h"


Monster::Monster(void) { }
Monster::~Monster(void) { }

Monster::Monster(string location, size_t offset, bool good, size_t dif, bool def, string name, string defaultText, string defeatedText, vector<vector<bool>> shape)
{
	Monster::location = location;
	Monster::offset = offset;
	Monster::good = good;
	Monster::difficulty = dif;
	Monster::defeated = def;
	Monster::name = name;
	Monster::defaultText = defaultText;
	Monster::defeatedText = defeatedText;
	Monster::shape = shape;
}


void Monster::SetDefeated(bool def)
{
	Monster::defeated = def;
}


size_t Monster::GetOffset()
{
	return Monster::offset;
}

bool Monster::GetGood()
{
	return Monster::good;
}

size_t Monster::GetDifficulty()
{
	return Monster::difficulty;
}

bool Monster::GetDefeated()
{
	return Monster::defeated;
}

vector<vector<bool>> Monster::GetShape()
{
	return Monster::shape;
}

string Monster::GetName()
{
	return Monster::name;
}

string Monster::GetDefaultText()
{
	return Monster::defaultText;
}

string Monster::GetDefeatedText()
{
	return Monster::defeatedText;
}

string Monster::GetLocation()
{
	return Monster::location;
}
