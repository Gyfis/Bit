#include "NumberCollectionsManager.h"


NumberCollectionsManager::NumberCollectionsManager(void)
{
}

NumberCollectionsManager::~NumberCollectionsManager(void)
{
}

size_t NumberCollectionsManager::GetFreeNumber()
{
	size_t id = 0;
	while (numbers.find(id) != numbers.end()) id++;
	numbers.insert(id);
	return id;
}

void NumberCollectionsManager::RemoveNumber(size_t id)
{
	numbers.erase(id);
	/*
	for (set<size_t>::iterator i = numbers.begin(); i != numbers.end(); i++)
	{
		if (*i == id) 
		{
			numbers.erase(*i);
			return;
		}
	}*/
}
