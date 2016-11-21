#pragma once
#include "PoketMonsterImage.h"
#define MAP_X_MAX (10+1)
#define MAP_Y_MAX (10+1)
class CPoketMonsterMap : public CPoketMonsterImage
{
private:
	CString m_strMapLocation;
protected:
	static char m_aMap[MAP_Y_MAX][MAP_X_MAX];
public:
	CPoketMonsterMap(CDC* pDC);
	~CPoketMonsterMap(void);
	void Draw(void);
};

