#include "Location.h"

Location::Location(void) { }

Location::~Location(void) { }


Location::Location(string nm, Tricolor tr, string pt, bool dn)
{
	Location::name = nm;
	Location::tricolor = tr;
	Location::path = pt;
	Location::done = dn;
}

bool Location::GetDone()
{
	return Location::done;
}

void Location::SetDone(bool d)
{
	Location::done = d;
}

Tricolor Location::GetTricolor()
{
	return tricolor;
}

string Location::GetName()
{
	return name;
}

string Location::GetPath()
{
	return path;
}



