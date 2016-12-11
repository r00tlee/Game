#pragma once
#define KEY_MAX 10
class CKey
{
	int m_key[KEY_MAX];
public:
	CKey(void);
	~CKey(void);
	int KeyDown(int k);
	void KeyUP(int k);
	int KeyCheck(int k);
	int KeyClearCheck(void);
};

