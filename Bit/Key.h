#pragma once
class Key
{
public:
	Key(void);
	Key(const int prekey, const int key);
	Key (const int key);
	~Key(void);

	const bool getCombo();
	const int getKey();
	const int getPrekey();

private:
	bool combo;
	int prekey;
	int key;
};

