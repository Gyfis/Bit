#include "ScreenUtilities.h"

ScreenUtilities::ScreenUtilities(void) { }

ScreenUtilities::~ScreenUtilities(void) { }

SMALL_RECT ScreenUtilities::joinRect;

vector<vector<CHAR_INFO>> ScreenUtilities::JoinMaps(vector<vector<CHAR_INFO>> map1, SMALL_RECT sr1, vector<vector<CHAR_INFO>> map2, SMALL_RECT sr2)
{
	SMALL_RECT *topSmaller = sr1.Top < sr2.Top ? (&sr1) : (&sr2);
	vector<vector<CHAR_INFO>> *mapTopSmaller = sr1.Top < sr2.Top ? (&map1) : (&map2);
	SMALL_RECT *topLarger = sr1.Top < sr2.Top ? (&sr2) : (&sr1);
	vector<vector<CHAR_INFO>> *mapTopLarger = sr1.Top < sr2.Top ? (&map2) : (&map1);

	SMALL_RECT *leftSmaller = sr1.Left < sr2.Left ? (&sr1) : (&sr2);
	vector<vector<CHAR_INFO>> *mapLeftSmaller = sr1.Left < sr2.Left ? (&map1) : (&map2);
	SMALL_RECT *leftLarger = sr1.Left < sr2.Left ? (&sr2) : (&sr1);
	vector<vector<CHAR_INFO>> *mapLeftLarger = sr1.Left < sr2.Left ? (&map2) : (&map1);

	ScreenUtilities::joinRect.Top = min(sr1.Top, sr2.Top);
	ScreenUtilities::joinRect.Left = min(sr1.Left, sr2.Left);
	ScreenUtilities::joinRect.Bottom = sr1.Top == sr2.Top ? sr1.Bottom : sr1.Bottom + sr2.Bottom;
	ScreenUtilities::joinRect.Right = sr1.Left == sr2.Left ? sr1.Right : sr1.Right + sr2.Right;

	vector<vector<CHAR_INFO>> resultVector;
	vector<CHAR_INFO> rowVector;

	bool horizontal = leftLarger->Left > (leftSmaller->Left + leftSmaller->Right - 1);

	for (int i = 0; i < ScreenUtilities::joinRect.Bottom; i++) {
		for (int j = 0; j < ScreenUtilities::joinRect.Right; j++) {
			if (horizontal) {
				if (j < leftLarger->Left - leftSmaller->Left) { rowVector.push_back(mapLeftSmaller->at(i).at(j));	}
				else { rowVector.push_back(mapLeftLarger->at(i).at(j - (leftLarger->Left - leftSmaller->Left))); }
			} else {
				if (i < topLarger->Top - topSmaller->Top) { rowVector.push_back(mapTopSmaller->at(i).at(j)); }
				else { rowVector.push_back(mapTopLarger->at(i).at(j - (topLarger->Top - topSmaller->Top))); }
			}
		}

		resultVector.push_back(rowVector);
		rowVector.clear();
	}
	
	return resultVector;

}

SMALL_RECT ScreenUtilities::JoinRects(SMALL_RECT sr1, SMALL_RECT sr2)
{
	ScreenUtilities::joinRect.Top = min(sr1.Top, sr2.Top);
	ScreenUtilities::joinRect.Left = min(sr1.Left, sr2.Left);
	ScreenUtilities::joinRect.Bottom = sr1.Top == sr2.Top ? sr1.Bottom : sr1.Bottom + sr2.Bottom;
	ScreenUtilities::joinRect.Right = sr1.Left == sr2.Left ? sr1.Right : sr1.Right + sr2.Right;

	return ScreenUtilities::joinRect;
}