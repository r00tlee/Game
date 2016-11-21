#include "stdafx.h"
#include "PoketMonsterMap.h"

char CPoketMonsterMap::m_aMap[MAP_Y_MAX][MAP_X_MAX] = {-1};

CPoketMonsterMap::CPoketMonsterMap(CDC* pDC)
	: CPoketMonsterImage(pDC)
{
#ifdef _DEBUG
	FILE* fp = fopen("C:\\Users\\r00tlee\\Documents\\Visual Studio 2012\\Projects\\PoketMonster\\PoketMonster\\PoketMonsterMap.txt", "r");
	if (NULL == fp)
	{
	}
	int count = 0;
	while(1)
	{
		if ( NULL == fgets(m_aMap[count++], 100, fp) )
		{
			break;
		}
	}
	fclose(fp);
#endif
}


CPoketMonsterMap::~CPoketMonsterMap(void)
{
}


void CPoketMonsterMap::Draw(void)
{
#ifdef _DEBUG
	for (int y=0; y<10; y++)
	{
		for (int x=0; x<10; x++)
		{
			int dx = x*100;
			int dy = y*100;
			
			if ( '1' == m_aMap[y][x] )
			{
				m_bufCDC.StretchBlt(dx, dy, 100, 100, &m_aCDC[4], 0, 0, 200, 200, SRCCOPY);
				continue;
			}
			m_bufCDC.Rectangle(dx, dy, dx+100, dy+100);
			m_strMapLocation.Format( _T("[%d][%d]"), y, x);
			m_bufCDC.TextOutW(dx+35, dy+35, m_strMapLocation);
		}
	}
#endif
}
