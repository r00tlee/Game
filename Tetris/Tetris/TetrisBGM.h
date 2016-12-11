#pragma once
#pragma comment(lib, "winmm")
#include <mmsystem.h>

enum g_BGM{
	BGM_MAIN = 0,
	BGM_PLAY
};

class CTetrisBGM
{
	CArray<LPCWSTR> m_aBgmPath;
public:
	CTetrisBGM(void);
	~CTetrisBGM(void);
	void playBGM(int bgmNumber);
};

