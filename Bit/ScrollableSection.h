#pragma once
#include <Windows.h>
#include <vector>

using namespace std;

class ScrollableSection
{
public:

	ScrollableSection(vector<vector<CHAR_INFO>> content, size_t sectionW, size_t sectionH);
	ScrollableSection(void);
	~ScrollableSection(void);

	void SetContent(vector<vector<CHAR_INFO>> content);
	void SetWidth(size_t sectionW);
	void SetHeight(size_t sectionH);
	void SetSize(size_t sectionW, size_t sectionH);

	size_t GetSectionWidth();
	size_t GetSectionHeight();
	size_t GetSectionOffsetX();
	size_t GetSectionOffsetY();

	void AddOffsetX(size_t ox);
	void AddOffsetY(size_t oy);
	void SubtractOffsetX(size_t ox);
	void SubtractOffsetY(size_t oy);

	void ScrollDown();
	void ScrollUp();
	void ScrollLeft();
	void ScrollRight();

	vector<vector<CHAR_INFO>> GetSection();

private:

	size_t offsetX;
	size_t offsetY;
	size_t sectionWidth;
	size_t sectionHeight;
	size_t contentWidth;
	size_t contentHeight;

	vector<vector<CHAR_INFO>> content;
};

