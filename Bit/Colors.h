#pragma once
#include <Windows.h>
#include "Constants.h"

using namespace std;
class Colors
{
public:

	static WORD ColorFromID(size_t id);

private:
	Colors(void);
	~Colors(void);
};

