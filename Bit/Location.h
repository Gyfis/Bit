#pragma once

#include <string>

#include "Constants.h"
#include "Tricolor.h"


using namespace std;

class Location
{
public:

	Location(string nm, Tricolor tr, string pt, bool dn);

	Tricolor GetTricolor();
	string GetName();
	string GetPath();
	bool GetDone();

	void SetDone(bool d);

	Location(void);
	~Location(void);

private:

	Tricolor tricolor;
	string name;
	string path;
	bool done;

};

