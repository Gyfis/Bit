#pragma once

#include <map>
#include "Constants.h"


class LettersManager
{
public:

	static void Initialize();
	static map<const int, const bool (*)[letterBitsC]> letterMap;

private:
	LettersManager(void);
	~LettersManager(void);
};

