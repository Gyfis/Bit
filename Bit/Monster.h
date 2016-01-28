#pragma once
#include <string>
#include <vector>

using namespace std;

class Monster
{
public:

	Monster(string location, size_t offset, bool good, size_t dif, bool def, string name, string defaultText, string defetaedText, vector<vector<bool>> shape);

	Monster(void);
	~Monster(void);

	size_t GetOffset();
	bool GetGood();
	size_t GetDifficulty();
	bool GetDefeated();
	vector<vector<bool>> GetShape();
	string GetName();
	string GetDefaultText();
	string GetDefeatedText();
	string GetLocation();

	void SetDefeated(bool def);

private:
	string location;
	size_t offset;
	bool good;
	size_t difficulty;
	bool defeated;
	string name;
	string defaultText;
	string defeatedText;
	vector<vector<bool>> shape;
};

