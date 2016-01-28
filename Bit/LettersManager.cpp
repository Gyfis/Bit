#include "LettersManager.h"


map<const int, const bool (*)[letterBitsC]> LettersManager::letterMap;

LettersManager::LettersManager(void)
{
}

LettersManager::~LettersManager(void)
{
}

void LettersManager::Initialize()
{
	
	// UPPER-CASE

	LettersManager::letterMap.insert(make_pair('A', &letterAC));
	LettersManager::letterMap.insert(make_pair('B', &letterBC));
	LettersManager::letterMap.insert(make_pair('C', &letterCC));
	LettersManager::letterMap.insert(make_pair('D', &letterDC));
	LettersManager::letterMap.insert(make_pair('E', &letterEC));
	LettersManager::letterMap.insert(make_pair('F', &letterFC));
	LettersManager::letterMap.insert(make_pair('G', &letterGC));
	LettersManager::letterMap.insert(make_pair('H', &letterHC));
	LettersManager::letterMap.insert(make_pair('I', &letterIC));
	LettersManager::letterMap.insert(make_pair('J', &letterJC));
	LettersManager::letterMap.insert(make_pair('K', &letterKC));
	LettersManager::letterMap.insert(make_pair('L', &letterLC));
	LettersManager::letterMap.insert(make_pair('M', &letterMC));
	LettersManager::letterMap.insert(make_pair('N', &letterNC));
	LettersManager::letterMap.insert(make_pair('O', &letterOC));
	LettersManager::letterMap.insert(make_pair('P', &letterPC));
	LettersManager::letterMap.insert(make_pair('Q', &letterQC));
	LettersManager::letterMap.insert(make_pair('R', &letterRC));
	LettersManager::letterMap.insert(make_pair('S', &letterSC));
	LettersManager::letterMap.insert(make_pair('T', &letterTC));
	LettersManager::letterMap.insert(make_pair('U', &letterUC));
	LettersManager::letterMap.insert(make_pair('V', &letterVC));
	LettersManager::letterMap.insert(make_pair('W', &letterWC));
	LettersManager::letterMap.insert(make_pair('X', &letterXC));
	LettersManager::letterMap.insert(make_pair('Y', &letterYC));
	LettersManager::letterMap.insert(make_pair('Z', &letterZC));

	// lower-case
	LettersManager::letterMap.insert(make_pair('a', &letteraC));
	LettersManager::letterMap.insert(make_pair('b', &letterbC));
	LettersManager::letterMap.insert(make_pair('c', &lettercC));
	LettersManager::letterMap.insert(make_pair('d', &letterdC));
	LettersManager::letterMap.insert(make_pair('e', &lettereC));
	LettersManager::letterMap.insert(make_pair('f', &letterfC));
	LettersManager::letterMap.insert(make_pair('g', &lettergC));
	LettersManager::letterMap.insert(make_pair('h', &letterhC));
	LettersManager::letterMap.insert(make_pair('i', &letteriC));
	LettersManager::letterMap.insert(make_pair('j', &letterjC));
	LettersManager::letterMap.insert(make_pair('k', &letterkC));
	LettersManager::letterMap.insert(make_pair('l', &letterlC));
	LettersManager::letterMap.insert(make_pair('m', &lettermC));
	LettersManager::letterMap.insert(make_pair('n', &letternC));
	LettersManager::letterMap.insert(make_pair('o', &letteroC));
	LettersManager::letterMap.insert(make_pair('p', &letterpC));
	LettersManager::letterMap.insert(make_pair('q', &letterqC));
	LettersManager::letterMap.insert(make_pair('r', &letterrC));
	LettersManager::letterMap.insert(make_pair('s', &lettersC));
	LettersManager::letterMap.insert(make_pair('t', &lettertC));
	LettersManager::letterMap.insert(make_pair('u', &letteruC));
	LettersManager::letterMap.insert(make_pair('v', &lettervC));
	LettersManager::letterMap.insert(make_pair('w', &letterwC));
	LettersManager::letterMap.insert(make_pair('x', &letterxC));
	LettersManager::letterMap.insert(make_pair('y', &letteryC));
	LettersManager::letterMap.insert(make_pair('z', &letterzC));

	// 9078325
	
	LettersManager::letterMap.insert(make_pair('0', &letter0C));
	LettersManager::letterMap.insert(make_pair('1', &letter1C));
	LettersManager::letterMap.insert(make_pair('2', &letter2C));
	LettersManager::letterMap.insert(make_pair('3', &letter3C));
	LettersManager::letterMap.insert(make_pair('4', &letter4C));
	LettersManager::letterMap.insert(make_pair('5', &letter5C));
	LettersManager::letterMap.insert(make_pair('6', &letter6C));
	LettersManager::letterMap.insert(make_pair('7', &letter7C));
	LettersManager::letterMap.insert(make_pair('8', &letter8C));
	LettersManager::letterMap.insert(make_pair('9', &letter9C));

	// $¶€©!@¬$

	LettersManager::letterMap.insert(make_pair(' ', &letterSpaceC));
	LettersManager::letterMap.insert(make_pair('.', &letterDotC));
	LettersManager::letterMap.insert(make_pair(',', &letterCommaC));
	LettersManager::letterMap.insert(make_pair('?', &letterQuestionC));
	LettersManager::letterMap.insert(make_pair('!', &letterExclamationC));
	LettersManager::letterMap.insert(make_pair('\r', &letterEnterC));
	LettersManager::letterMap.insert(make_pair('\b', &letterBackspaceC));
	LettersManager::letterMap.insert(make_pair('\'', &letterQuoteC));
	LettersManager::letterMap.insert(make_pair(':', &letterColonC));

	// arrows

	LettersManager::letterMap.insert(make_pair(arrowDownC + arrowHeaderC, &letterArrowDownC));
	LettersManager::letterMap.insert(make_pair(arrowRightC + arrowHeaderC, &letterArrowRightC));
	LettersManager::letterMap.insert(make_pair(arrowUpC + arrowHeaderC, &letterArrowUpC));
	LettersManager::letterMap.insert(make_pair(arrowLeftC + arrowHeaderC, &letterArrowLeftC));

}
