#include "LayoutManager.h"


LayoutManager::LayoutManager(void)
{
}


LayoutManager::~LayoutManager(void)
{
}


void LayoutManager::Initialize()
{
	CHAR_INFO chInfo;
	vector<CHAR_INFO> vec;

	chInfo.Attributes = foregroundColorDarkGrayC;
	chInfo.Char.AsciiChar = gradientCharMediumC;

	SMALL_RECT sr;
	sr.Top = windowHeightC - outputHeightC - borderOffsetC + 1;
	sr.Left = borderOffsetC + 1;
	sr.Bottom = outputHeightC - 1;
	sr.Right = windowWidthC - 2 * (borderOffsetC + 1);

	ScreenManager::ReplaceCharsAtRect(chInfo, sr);
	
	chInfo.Attributes = foregroundColorGrayC;


	chInfo.Char.AsciiChar = borderCornerLeftUpC;
	vec.push_back(chInfo);


	chInfo.Char.AsciiChar = borderEdgeHorizontalC;

	for (int i = 0; i < windowWidthC - 2 * borderOffsetC - 2; i++)
	{
		vec.push_back(chInfo);
	}

	chInfo.Char.AsciiChar = borderCornerRightUpC;
	vec.push_back(chInfo);

	ScreenManager::ReplaceCharsAtPositionInRow(vec, (windowHeightC - outputHeightC - borderOffsetC) * windowWidthC + borderOffsetC);


	vec.clear();

	chInfo.Char.AsciiChar = borderEdgeVerticalC;

	for (int i = 0; i < outputHeightC - 1; i++) // melo by byt -2, ale je to trik, jak udelat tu mezeru cca stejne velkou - mezera dole bude o jeden znak mensi nez mezera na bocich
	{
		vec.push_back(chInfo);
	}

	ScreenManager::ReplaceCharsAtPositionInColumn(vec, (windowHeightC - outputHeightC - borderOffsetC + 1) * windowWidthC + borderOffsetC);
	ScreenManager::ReplaceCharsAtPositionInColumn(vec, (windowHeightC - outputHeightC - borderOffsetC + 1) * windowWidthC + windowWidthC - borderOffsetC - 1);


	vec.clear();

	chInfo.Char.AsciiChar = borderCornerLeftDownC;
	vec.push_back(chInfo);


	chInfo.Char.AsciiChar = borderEdgeHorizontalC;

	for (int i = 0; i < windowWidthC - 2 * borderOffsetC - 2; i++)
	{
		vec.push_back(chInfo);
	}

	chInfo.Char.AsciiChar = borderCornerRightDownC;
	vec.push_back(chInfo);

	ScreenManager::ReplaceCharsAtPositionInRow(vec, (windowHeightC - borderOffsetC) * windowWidthC + borderOffsetC); // stejne jako predtim, melo by byt spis (windowHeichC - borderOffsetC - 1)

}