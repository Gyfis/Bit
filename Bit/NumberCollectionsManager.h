#pragma once
#include <set>

using namespace std;

class NumberCollectionsManager
{
public:
	NumberCollectionsManager(void);
	~NumberCollectionsManager(void);

	size_t GetFreeNumber();
	void RemoveNumber(size_t id);

private:

	set<size_t> numbers;
};

