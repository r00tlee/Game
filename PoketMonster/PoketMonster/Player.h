#pragma once
#include "PoketMonsterImage.h"
#include "PoketMonsterMap.h"

class CPlayer : public CPoketMonsterImage, public CPoketMonsterMap
{
	POINT m_location;
	UINT m_locationState;
	const int m_AniSize;
	int m_ImageIndex;
	BOOL m_ActionState;

#ifdef _DEBUG
	CString m_prlocation;//∏  ¡¬«• ª—∑¡¡÷±‚ ¿ß«ÿº≠..
	BOOL m_ForestState;//«ÆΩ£¿Œ¡ˆ »Æ¿ŒøÎ
#endif

public:
	CPlayer(CDC* pDC);
	~CPlayer(void);
	int getXLocation(void);
	int getYLocation(void);
	void setXLocation(int x, int locationState);
	void setYLocation(int y, int locationState);
	void Draw(void);
	void actionStep(void);
	void locationPrint(void);
};

