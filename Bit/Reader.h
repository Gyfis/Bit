#pragma once

#include <functional>
#include <deque>
#include <map>
#include <conio.h>
#include <algorithm>
#include <Windows.h>
#include <string>
#include "NumberCollectionsManager.h"

using namespace std;


struct FunctionHolder
{
	function<void()> f;
	size_t id;
	bool once;
};

class Reader
{
public:
	static void Initialize();
	static void Run();

	static size_t InsertPair(const int c, function<void()> f, bool once);
	static size_t InsertPair(const int c, function<void()> f, bool once, bool front);
	static size_t InsertCombo(const int c1, const int c2, function<void()> f, bool once);
	static size_t InsertCombo(const int c1, const int c2, function<void()> f, bool once, bool front);
	static void RemovePair(const int c, size_t id);
	static void RemoveKey(const int c);

	static void Clear();

private:
	
	Reader(void);
	~Reader(void);

	static void InsertPairOnce(const int c, function<void()> f);

	static NumberCollectionsManager ncm;

	static void CallFunctions(deque<FunctionHolder> *functions);

	static map<const int, deque<FunctionHolder>> callbackFunctions;

	static bool ReadyToRemovePredicate (const FunctionHolder fh);

};

