#pragma once
class Tricolor
{
public:
	
	Tricolor(void);
	Tricolor(size_t color1, size_t color2, size_t color3);
	~Tricolor(void);

	size_t GetC1();
	size_t GetC2();
	size_t GetC3();

private:

	size_t c1;
	size_t c2;
	size_t c3;

};

