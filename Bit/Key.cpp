#include "Key.h"


Key::Key(void) { }
Key::~Key(void) { }

Key::Key(const int prekey, const int key) 
{
	Key::combo = true;
	Key::prekey = prekey;
	Key::key = key;
}

Key::Key(const int key)
{
	Key::combo = false;
	Key::key = key;
}

const int Key::getKey()
{
	return Key::key;
}

const int Key::getPrekey()
{
	return Key::prekey;
}

const bool Key::getCombo()
{
	return Key::combo;
}
