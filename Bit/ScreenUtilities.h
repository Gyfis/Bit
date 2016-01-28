#pragma once

#include <Windows.h>
#include <vector>

using namespace std;
class ScreenUtilities
{
public:

	static vector<vector<CHAR_INFO>> JoinMaps(vector<vector<CHAR_INFO>> map1, SMALL_RECT sr1, vector<vector<CHAR_INFO>> map2, SMALL_RECT sr2);
	static SMALL_RECT JoinRects(SMALL_RECT sr1, SMALL_RECT sr2);

private:

	static SMALL_RECT joinRect;
	ScreenUtilities(void);
	~ScreenUtilities(void);
};

