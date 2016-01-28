#include "ScrollableSection.h"


ScrollableSection::ScrollableSection(void) {
	ScrollableSection::offsetX = 0;
	ScrollableSection::offsetY = 0;
}
ScrollableSection::~ScrollableSection(void) { }

ScrollableSection::ScrollableSection(vector<vector<CHAR_INFO>> content, size_t sectionW, size_t sectionH)
{
	ScrollableSection::offsetX = 0;
	ScrollableSection::offsetY = 0;

	ScrollableSection::content = content;
	ScrollableSection::sectionWidth = sectionW;
	ScrollableSection::sectionHeight = sectionH;

	ScrollableSection::contentWidth = content[0].size();
	ScrollableSection::contentHeight = content.size();
}

void ScrollableSection::SetContent(vector<vector<CHAR_INFO>> content)
{
	ScrollableSection::content = content;
}

void ScrollableSection::SetWidth(size_t sectionW)
{
	ScrollableSection::sectionWidth = sectionW;
}

void ScrollableSection::SetHeight(size_t sectionH)
{
	ScrollableSection::sectionHeight = sectionH;
}

void ScrollableSection::SetSize(size_t sectionW, size_t sectionH)
{
	ScrollableSection::sectionWidth = sectionW;
	ScrollableSection::sectionHeight = sectionH;
}

void ScrollableSection::AddOffsetX(size_t ox)
{
	if (ScrollableSection::offsetX + ox < ScrollableSection::contentWidth - ScrollableSection::sectionWidth) ScrollableSection::offsetX += ox;
}

void ScrollableSection::AddOffsetY(size_t oy)
{	
	if (ScrollableSection::offsetY + oy < ScrollableSection::contentHeight - ScrollableSection::sectionHeight) ScrollableSection::offsetY += oy;
}

void ScrollableSection::SubtractOffsetX(size_t ox)
{
	if (ScrollableSection::offsetX - ox < ScrollableSection::contentWidth - ScrollableSection::sectionWidth) ScrollableSection::offsetX -= ox;
}

void ScrollableSection::SubtractOffsetY(size_t oy)
{	
	if (ScrollableSection::offsetY - oy < ScrollableSection::contentHeight - ScrollableSection::sectionHeight) ScrollableSection::offsetY -= oy;
}

void ScrollableSection::ScrollDown()
{
	if (ScrollableSection::offsetY < ScrollableSection::contentHeight - ScrollableSection::sectionHeight) ScrollableSection::offsetY++;
}

void ScrollableSection::ScrollUp()
{
	if (ScrollableSection::offsetY > 0) ScrollableSection::offsetY--;
}

void ScrollableSection::ScrollLeft()
{
	if (ScrollableSection::offsetX > 0) ScrollableSection::offsetX--;
}

void ScrollableSection::ScrollRight()
{
	if (ScrollableSection::offsetX < ScrollableSection::contentWidth - ScrollableSection::sectionWidth) ScrollableSection::offsetX++;
}

vector<vector<CHAR_INFO>> ScrollableSection::GetSection()
{
	vector<vector<CHAR_INFO>> returnVec;
	vector<CHAR_INFO> returnRow;

	for (size_t i = ScrollableSection::offsetY; i < ScrollableSection::offsetY + min(ScrollableSection::sectionHeight, ScrollableSection::contentHeight); i++)
	{
		returnRow.clear();
		for (size_t j = ScrollableSection::offsetX; j < ScrollableSection::offsetX + min(ScrollableSection::sectionWidth, ScrollableSection::contentWidth); j++)
		{
			returnRow.push_back(ScrollableSection::content[i][j]);
		}
		returnVec.push_back(returnRow);
	}

	return returnVec;
}

size_t ScrollableSection::GetSectionWidth()
{
	return min(ScrollableSection::sectionWidth, ScrollableSection::contentWidth);
}

size_t ScrollableSection::GetSectionHeight()
{
	return min(ScrollableSection::sectionHeight, ScrollableSection::contentHeight);
}

size_t ScrollableSection::GetSectionOffsetX()
{
	return ScrollableSection::offsetX;
}

size_t ScrollableSection::GetSectionOffsetY()
{
	return ScrollableSection::offsetY;
}