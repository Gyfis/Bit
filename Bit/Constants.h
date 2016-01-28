#pragma once
#include <string>
#include <vector>
#include <Windows.h>

using namespace std;

static const size_t redrawFrequenceC = 20;

static const char pieceOfGodC = '\xDB';
static const char pieceOfEvilC = '\x00';
static const char gradientCharHardC = '\xB2';	
static const char gradientCharMediumC = '\x2F';
static const char gradientCharSoftC = '\xB0';	

static const char borderCornerLeftUpC = '\xC9';
static const char borderCornerLeftDownC = '\xC8';
static const char borderCornerRightUpC = '\xBB';
static const char borderCornerRightDownC = '\xBC';
static const char borderEdgeHorizontalC = '\xCD';
static const char borderEdgeVerticalC = '\xBA';
static const char borderTLeftC = '\xB9';
static const char borderTDownC = '\xCB';
static const char borderTRightC = '\xCC';
static const char borderTUpC = '\xCA';
static const char borderXC = '\xCE';

static const char borderLocationsCornerLeftUpC = '\xC9';
static const char borderLocationsCornerLeftDownC = '\xC8';
static const char borderLocationsCornerRightUpC = '\xBB';
static const char borderLocationsCornerRightDownC = '\xBC';
static const char borderLocationsEdgeHorizontalC = '\xCD';
static const char borderLocationsEdgeVerticalC = '\xBA';
static const char borderLocationsTLeftC = '\xB9';
static const char borderLocationsTDownC = '\xCB';
static const char borderLocationsTRightC = '\xCC';
static const char borderLocationsTUpC = '\xCA';
static const char borderLocationsXC = '\xCE';

static const int arrowHeaderC = 224;
static const int arrowDownC = 80;
static const int arrowRightC = 77;
static const int arrowLeftC = 75;
static const int arrowUpC = 72;

static const int characterEnterC = 13;
static const int characterBackspaceC = 8;

static const string filePathC = "gameFiles/";

static const string locationsFileC = filePathC + "seznamLokaci.txt";
static const string locationsPathC = filePathC + "lokace/";
static const string monstersPathC = filePathC + "monstra/";


static const size_t selectLocationsWidthC = 215;
static const size_t selectLocationsHeightC = 21;

static const size_t selectLocationMovingSpeedC = 20;
static const size_t selectLocationsHeightSpaceC = 3;

static const size_t selectLocationsTricolorStartC = 183;
static const size_t selectLocationsTricolorC1StartC = 184;
static const size_t selectLocationsTricolorC2StartC = 187;
static const size_t selectLocationsTricolorC3StartC = 190;
static const size_t selectLocationsTricolorEndC = 193;

static const size_t selectLocationsNamesOffsetLeftC = 2;
static const size_t selectLocationsNamesOffsetRightC = 1;
static const size_t selectLocationsNamesUsableCharsC = 45; // (selectLocationsTricolorStart - selectLocationsNamesOffsetLeft - selectLocationsNamesOffsetRight) / (letterWidthC + 1)
static const size_t selectLocationsNamesNumberOfLinesC = 3;

static const WORD foregroundColorBlackC = NULL;
static const WORD foregroundColorDarkRedC = FOREGROUND_RED;
static const WORD foregroundColorDarkBlueC = FOREGROUND_BLUE;
static const WORD foregroundColorDarkGreenC = FOREGROUND_GREEN;
static const WORD foregroundColorDarkMagnetaC = FOREGROUND_RED | FOREGROUND_BLUE;
static const WORD foregroundColorDarkYellowC = FOREGROUND_RED | FOREGROUND_GREEN; // brown?
static const WORD foregroundColorDarkCyanC = FOREGROUND_BLUE | FOREGROUND_GREEN;
static const WORD foregroundColorGrayC = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN;

static const WORD foregroundColorDarkGrayC = FOREGROUND_INTENSITY;
static const WORD foregroundColorRedC = FOREGROUND_RED| FOREGROUND_INTENSITY;
static const WORD foregroundColorBlueC = FOREGROUND_BLUE| FOREGROUND_INTENSITY;
static const WORD foregroundColorGreenC = FOREGROUND_GREEN| FOREGROUND_INTENSITY;
static const WORD foregroundColorMagnetaC = FOREGROUND_RED | FOREGROUND_BLUE| FOREGROUND_INTENSITY;
static const WORD foregroundColorYellowC = FOREGROUND_RED | FOREGROUND_GREEN| FOREGROUND_INTENSITY;
static const WORD foregroundColorCyanC = FOREGROUND_BLUE | FOREGROUND_GREEN| FOREGROUND_INTENSITY;
static const WORD foregroundColorWhiteC = FOREGROUND_RED | FOREGROUND_BLUE | FOREGROUND_GREEN| FOREGROUND_INTENSITY;


static const WORD backgroundColorBlackC = NULL;
static const WORD backgroundColorDarkRedC = BACKGROUND_RED;
static const WORD backgroundColorDarkBlueC = BACKGROUND_BLUE;
static const WORD backgroundColorDarkGreenC = BACKGROUND_GREEN;
static const WORD backgroundColorDarkMagnetaC = BACKGROUND_RED | BACKGROUND_BLUE;
static const WORD backgroundColorDarkYellowC = BACKGROUND_RED | BACKGROUND_GREEN; // brown?
static const WORD backgroundColorDarkCyanC = BACKGROUND_BLUE | BACKGROUND_GREEN;
static const WORD backgroundColorGrayC = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN;

static const WORD backgroundColorDarkGrayC = BACKGROUND_INTENSITY;
static const WORD backgroundColorRedC = BACKGROUND_RED| BACKGROUND_INTENSITY;
static const WORD backgroundColorBlueC = BACKGROUND_BLUE| BACKGROUND_INTENSITY;
static const WORD backgroundColorGreenC = BACKGROUND_GREEN| BACKGROUND_INTENSITY;
static const WORD backgroundColorMagnetaC = BACKGROUND_RED | BACKGROUND_BLUE| BACKGROUND_INTENSITY;
static const WORD backgroundColorYellowC = BACKGROUND_RED | BACKGROUND_GREEN| BACKGROUND_INTENSITY;
static const WORD backgroundColorCyanC = BACKGROUND_BLUE | BACKGROUND_GREEN| BACKGROUND_INTENSITY;
static const WORD backgroundColorWhiteC = BACKGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN| BACKGROUND_INTENSITY;


static const size_t borderOffsetC = 3;
static const size_t outputHeightC = 28;

static const size_t letterBitsC = 18;
static const size_t letterWidthC = 3;
static const size_t letterHeightC = 6;

static const size_t windowWidthC = 300;
static const size_t windowHeightC = 100;
static const size_t fontSizeC = 1;

static const size_t playHeightC = windowHeightC - outputHeightC - 3*borderOffsetC;
static const size_t playWidthC = windowWidthC - 2 * borderOffsetC;

static const size_t locationsBitRouteC = 75;
static const size_t locationsBitRouteWidthC = 240;
static const size_t locationsBitRouteOffsetC = (windowWidthC - locationsBitRouteWidthC) / 2;

static const size_t playStartTopC = borderOffsetC;
static const size_t playStartLeftC = borderOffsetC;

static const size_t outputUsableWidthC = 288;	// windowWidthC - 2 * (borderOffset + 3);
static const size_t outputUsableHeightC = 24;	// outputHeightC - 4;
static const size_t outputUsableCharsC = 72;	// (windowWidthC - 2 * (borderOffsetC + 3)) / ((letterBitsC / 6) + 1);
static const size_t outputUsableLinesC = 4;		// outputUsableHeightC / (letterBitsC / 3);

static const size_t outputStartTopC = windowHeightC - outputHeightC - borderOffsetC + 3;
static const size_t outputStartLeftC = borderOffsetC + 2;

static const size_t slowOutputSpeedC = 50;
static const size_t mediumOutputSpeetC = 25;
static const size_t fastOutputSpeedC = 10;

static const size_t badGameTickC = 40;

static const bool letterAC[letterBitsC] = {0,1,0,1,0,1,1,1,1,1,0,1,1,0,1,0,0,0};
static const bool letterBC[letterBitsC] = {1,1,0,1,0,1,1,1,0,1,0,1,1,1,0,0,0,0};
static const bool letterCC[letterBitsC] = {0,1,1,1,0,0,1,0,0,1,0,0,0,1,1,0,0,0};
static const bool letterDC[letterBitsC] = {1,1,0,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0};
static const bool letterEC[letterBitsC] = {1,1,1,1,0,0,1,1,1,1,0,0,1,1,1,0,0,0};
static const bool letterFC[letterBitsC] = {1,1,1,1,0,0,1,1,1,1,0,0,1,0,0,0,0,0};
static const bool letterGC[letterBitsC] = {0,1,1,1,0,0,1,1,1,1,0,1,0,1,1,0,0,0};
static const bool letterHC[letterBitsC] = {1,0,1,1,0,1,1,1,1,1,0,1,1,0,1,0,0,0};
static const bool letterIC[letterBitsC] = {1,1,1,0,1,0,0,1,0,0,1,0,1,1,1,0,0,0};
static const bool letterJC[letterBitsC] = {0,0,1,0,0,1,0,0,1,1,0,1,0,1,0,0,0,0};
static const bool letterKC[letterBitsC] = {1,0,1,1,0,1,1,1,0,1,0,1,1,0,1,0,0,0};
static const bool letterLC[letterBitsC] = {1,0,0,1,0,0,1,0,0,1,0,0,1,1,1,0,0,0};
static const bool letterMC[letterBitsC] = {1,0,1,1,1,1,1,0,1,1,0,1,1,0,1,0,0,0};
static const bool letterNC[letterBitsC] = {1,1,1,1,0,1,1,0,1,1,0,1,1,0,1,0,0,0};
static const bool letterOC[letterBitsC] = {0,1,0,1,0,1,1,0,1,1,0,1,0,1,0,0,0,0};
static const bool letterPC[letterBitsC] = {1,1,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0,0};
static const bool letterQC[letterBitsC] = {0,1,0,1,0,1,1,0,1,1,1,1,0,1,1,0,0,0};
static const bool letterRC[letterBitsC] = {1,1,0,1,0,1,1,1,1,1,1,0,1,0,1,0,0,0};
static const bool letterSC[letterBitsC] = {0,1,1,1,0,0,0,1,0,0,0,1,1,1,0,0,0,0};
static const bool letterTC[letterBitsC] = {1,1,1,0,1,0,0,1,0,0,1,0,0,1,0,0,0,0};
static const bool letterUC[letterBitsC] = {1,0,1,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0};
static const bool letterVC[letterBitsC] = {1,0,1,1,0,1,1,0,1,0,1,0,0,1,0,0,0,0};
static const bool letterWC[letterBitsC] = {1,0,1,1,0,1,1,1,1,1,1,1,1,0,1,0,0,0};
static const bool letterXC[letterBitsC] = {1,0,1,1,0,1,0,1,0,1,0,1,1,0,1,0,0,0};
static const bool letterYC[letterBitsC] = {1,0,1,1,0,1,0,1,0,0,1,0,0,1,0,0,0,0};
static const bool letterZC[letterBitsC] = {1,1,1,0,0,1,0,1,0,1,0,0,1,1,1,0,0,0};

static const bool letteraC[letterBitsC] = {0,0,0,1,1,0,0,1,1,1,0,1,1,1,1,0,0,0};
static const bool letterbC[letterBitsC] = {1,0,0,1,1,0,1,0,1,1,0,1,1,1,0,0,0,0};
static const bool lettercC[letterBitsC] = {0,0,0,0,1,1,1,0,0,1,0,0,0,1,1,0,0,0};
static const bool letterdC[letterBitsC] = {0,0,1,0,1,1,1,0,1,1,0,1,0,1,1,0,0,0};
static const bool lettereC[letterBitsC] = {0,0,0,0,1,1,1,0,1,1,1,0,0,1,1,0,0,0};
static const bool letterfC[letterBitsC] = {0,0,1,0,1,0,1,1,1,0,1,0,0,1,0,0,0,0};
static const bool lettergC[letterBitsC] = {0,0,0,0,1,1,1,0,1,1,1,1,0,0,1,0,1,0};
static const bool letterhC[letterBitsC] = {1,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0};
static const bool letteriC[letterBitsC] = {0,1,0,0,0,0,0,1,0,0,1,0,0,1,0,0,0,0};
static const bool letterjC[letterBitsC] = {0,0,1,0,0,0,0,0,1,0,0,1,1,0,1,0,1,0};
static const bool letterkC[letterBitsC] = {1,0,0,1,0,1,1,1,0,1,1,0,1,0,1,0,0,0};
static const bool letterlC[letterBitsC] = {1,1,0,0,1,0,0,1,0,0,1,0,1,1,1,0,0,0};
static const bool lettermC[letterBitsC] = {0,0,0,1,1,1,1,1,1,1,1,1,1,0,1,0,0,0};
static const bool letternC[letterBitsC] = {0,0,0,1,1,0,1,0,1,1,0,1,1,0,1,0,0,0};
static const bool letteroC[letterBitsC] = {0,0,0,0,1,0,1,0,1,1,0,1,0,1,0,0,0,0};
static const bool letterpC[letterBitsC] = {0,0,0,1,1,0,1,0,1,1,0,1,1,1,0,1,0,0};
static const bool letterqC[letterBitsC] = {0,0,0,0,1,1,1,0,1,1,0,1,0,1,1,0,0,1};
static const bool letterrC[letterBitsC] = {0,0,0,0,1,1,1,0,0,1,0,0,1,0,0,0,0,0};
static const bool lettersC[letterBitsC] = {0,0,0,0,1,1,1,1,0,0,1,1,1,1,0,0,0,0};
static const bool lettertC[letterBitsC] = {0,1,0,1,1,1,0,1,0,0,1,0,0,1,1,0,0,0};
static const bool letteruC[letterBitsC] = {0,0,0,1,0,1,1,0,1,1,0,1,0,1,1,0,0,0};
static const bool lettervC[letterBitsC] = {0,0,0,1,0,1,1,0,1,1,1,1,0,1,0,0,0,0};
static const bool letterwC[letterBitsC] = {0,0,0,1,0,1,1,1,1,1,1,1,1,1,1,0,0,0};
static const bool letterxC[letterBitsC] = {0,0,0,1,0,1,0,1,0,0,1,0,1,0,1,0,0,0};
static const bool letteryC[letterBitsC] = {0,0,0,1,0,1,1,0,1,0,1,1,0,0,1,0,1,0};
static const bool letterzC[letterBitsC] = {0,0,0,1,1,1,0,1,1,1,1,0,1,1,1,0,0,0};

static const bool letter0C[letterBitsC] = {0,1,1,1,0,1,1,0,1,1,0,1,1,1,0,0,0,0};
static const bool letter1C[letterBitsC] = {0,1,0,1,1,0,0,1,0,0,1,0,0,1,0,0,0,0};
static const bool letter2C[letterBitsC] = {1,1,0,0,0,1,0,1,0,1,0,0,1,1,1,0,0,0};
static const bool letter3C[letterBitsC] = {1,1,0,0,0,1,0,1,0,0,0,1,1,1,0,0,0,0};
static const bool letter4C[letterBitsC] = {1,0,1,1,0,1,1,1,1,0,0,1,0,0,1,0,0,0};
static const bool letter5C[letterBitsC] = {1,1,1,1,0,0,1,1,0,0,0,1,1,1,0,0,0,0};
static const bool letter6C[letterBitsC] = {0,1,1,1,0,0,1,1,1,1,0,1,1,1,1,0,0,0};
static const bool letter7C[letterBitsC] = {1,1,1,0,0,1,0,1,0,1,0,0,1,0,0,0,0,0};
static const bool letter8C[letterBitsC] = {1,1,1,1,0,1,1,1,1,1,0,1,1,1,1,0,0,0};
static const bool letter9C[letterBitsC] = {1,1,1,1,0,1,1,1,1,0,0,1,1,1,0,0,0,0};

static const bool letterSpaceC[letterBitsC] =		{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
static const bool letterDotC[letterBitsC] =			{0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0};
static const bool letterCommaC[letterBitsC] =		{0,0,0,0,0,0,0,0,0,0,1,0,1,0,0,0,0,0};
static const bool letterQuestionC[letterBitsC] =	{1,1,1,0,0,1,0,1,0,0,0,0,0,1,0,0,0,0};
static const bool letterExclamationC[letterBitsC] = {0,1,0,0,1,0,0,1,0,0,0,0,0,1,0,0,0,0};
static const bool letterEnterC[letterBitsC] =		{0,0,0,0,0,0,0,0,1,1,1,1,0,0,0,0,0,0};
static const bool letterBackspaceC[letterBitsC] =	{0,0,0,1,1,1,0,0,1,0,0,1,0,0,1,0,0,0};
static const bool letterQuoteC[letterBitsC] =		{0,1,0,0,1,0,1,0,0,0,0,0,0,0,0,0,0,0};
static const bool letterColonC[letterBitsC] =		{0,0,0,0,0,0,0,1,0,0,0,0,0,1,0,0,0,0};

static const bool letterArrowDownC[letterBitsC] =	{0,0,0,0,0,0,1,1,1,0,1,0,0,0,0,0,0,0};
static const bool letterArrowLeftC[letterBitsC] =	{0,0,0,0,1,0,1,1,0,0,1,0,0,0,0,0,0,0};
static const bool letterArrowRightC[letterBitsC] =	{0,0,0,0,1,0,0,1,1,0,1,0,0,0,0,0,0,0};
static const bool letterArrowUpC[letterBitsC] =		{0,0,0,0,0,0,0,1,0,1,1,1,0,0,0,0,0,0};

static const int alertWidthC = 7;
static const int alertHeightC = 8;
static const int alertBorderC[alertWidthC*alertHeightC] = {3,1,1,1,1,1,4,2,-1,0,0,0,-1,2,2,-1,0,0,0,-1,2,2,-1,0,0,0,-1,2,2,-1,0,0,0,-1,2,2,-1,0,0,0,-1,2,2,-1,0,0,0,-1,2,5,1,1,1,1,1,6};

static const size_t commonWaitingSpeedC = 350;