#include "Colors.h"


Colors::Colors(void) { }

Colors::~Colors(void) { }

WORD Colors::ColorFromID(size_t id) 
{
	switch (id) 
	{
		case 0:
			return foregroundColorBlackC;
			break;
		case 1:
			return foregroundColorDarkRedC;
			break;
		case 2:
			return foregroundColorDarkBlueC;
			break;
		case 3:
			return foregroundColorDarkGreenC;
			break;
		case 4:
			return foregroundColorDarkMagnetaC;
			break;
		case 5:
			return foregroundColorDarkYellowC;
			break;
		case 6:
			return foregroundColorDarkCyanC;
			break;
		case 7:
			return foregroundColorGrayC;
			break;
		case 8:
			return foregroundColorDarkGrayC;
			break;
		case 9:
			return foregroundColorRedC;
			break;
		case 10:
			return foregroundColorBlueC;
			break;
		case 11:
			return foregroundColorGreenC;
			break;
		case 12:
			return foregroundColorMagnetaC;
			break;
		case 13:
			return foregroundColorYellowC;
			break;
		case 14:
			return foregroundColorCyanC;
			break;
		case 15:
			return foregroundColorWhiteC;
			break;
	}
	return foregroundColorWhiteC;
}
