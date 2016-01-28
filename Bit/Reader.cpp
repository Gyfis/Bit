#include "Reader.h"

Reader::Reader(void)
{
}

Reader::~Reader(void)
{
}

map<const int, deque<FunctionHolder>> Reader::callbackFunctions;
NumberCollectionsManager Reader::ncm;

void Reader::Initialize()
{

}

void Reader::Run()
{
	while (true)
	{
		int j =_getch();
		Reader::CallFunctions(&Reader::callbackFunctions[j]);
	}
}

bool Reader::ReadyToRemovePredicate(const FunctionHolder fh)
{
	return fh.once;
}

void Reader::CallFunctions(deque<FunctionHolder> *functions)
{
	for (size_t i = 0; i < functions->size(); i++)
	{
		functions->at(i).f();
		if (functions->at(i).once) Reader::ncm.RemoveNumber(functions->at(i).id);
	}

	functions->erase(std::remove_if(functions->begin(), functions->end(), Reader::ReadyToRemovePredicate), functions->end());
}

size_t Reader::InsertPair(const int c, function<void()> f, bool once) 
{
	FunctionHolder fh;
	fh.f = f;
	fh.id = ncm.GetFreeNumber();
	fh.once = once;

	if (Reader::callbackFunctions.find(c) == Reader::callbackFunctions.end()) // key non-existant
	{
		deque<FunctionHolder> newVector;
		newVector.push_back(fh);
		Reader::callbackFunctions.insert(make_pair(c, newVector));
	}
	else
	{
		Reader::callbackFunctions[c].push_back(fh);
		
	}

	return fh.id;
}

size_t Reader::InsertPair(const int c, function<void()> f, bool once, bool front) {	
	FunctionHolder fh;
	fh.f = f;
	fh.id = ncm.GetFreeNumber();
	fh.once = once;

	if (Reader::callbackFunctions.find(c) == Reader::callbackFunctions.end()) // key non-existant
	{
		deque<FunctionHolder> newVector;
		newVector.push_back(fh);
		Reader::callbackFunctions.insert(make_pair(c, newVector));
	}
	else
	{
		front ? Reader::callbackFunctions[c].push_front(fh) : Reader::callbackFunctions[c].push_back(fh);
		
	}

	return fh.id;
}

void Reader::InsertPairOnce(const int c, function<void()> f)
{
	Reader::InsertPair(c, f, true);
}

size_t Reader::InsertCombo(const int c1, const int c2, function<void()> f, bool once)
{
	return Reader::InsertPair(c1, bind(Reader::InsertPairOnce, c2, f), once);
}

size_t Reader::InsertCombo(const int c1, const int c2, function<void()> f, bool once, bool front)
{
	return Reader::InsertPair(c1, bind(Reader::InsertPairOnce, c2, f), once, front);
}

void Reader::RemovePair(const int c, size_t id)
{
	for (deque<FunctionHolder>::iterator it = callbackFunctions[c].begin(); it < callbackFunctions[c].end(); it++)
	{
		if (it->id == id)
		{
			callbackFunctions[c].erase(it);
			return;
		}
	}
}

void Reader::RemoveKey(const int c)
{
	callbackFunctions[c].clear();
	callbackFunctions.erase(c);
}

void Reader::Clear()
{
	callbackFunctions.clear();
}