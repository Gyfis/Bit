#include "Tricolor.h"


Tricolor::Tricolor(void) { }

Tricolor::Tricolor(size_t color1, size_t color2, size_t color3) {
	Tricolor::c1 = color1;
	Tricolor::c2 = color2;
	Tricolor::c3 = color3;
}
	
size_t Tricolor::GetC1()
{
	return Tricolor::c1;
}

size_t Tricolor::GetC2()
{
	return Tricolor::c2;
}

size_t Tricolor::GetC3()
{
	return Tricolor::c3;
}

Tricolor::~Tricolor(void) { }
