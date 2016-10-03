#include "stdafx.h"
#include "TetrisMap.h"

CTetrisMap::CTetrisMap(void) //맵 초기화
{
	for (int y=0; y<MAP_H; y++)
	{
		for (int x=0; x<MAP_W; x++)
		{
			//if (y == 0 && x != 0 && x != MAP_W-1) m_data[y][x] = MAP_TOP; 
			if (y == 0 || y == MAP_H-1 ||
				   x == 0 || x == MAP_W-1)  m_data[y][x] = MAP_WALL;
			else                         m_data[y][x] = MAP_BLANK;
		}
	}
}


CTetrisMap::~CTetrisMap(void)
{
}


void CTetrisMap::Draw(CTetrisImage* Image)
{
	int dx = 0;
	int dy = 0;	

	for (int y=0; y<MAP_H; y++) //화면 출력
	{
		for (int x=0; x<MAP_W; x++)
		{
			dx = BlockSize * x;
			dy = BlockSize * y;
			if (m_data[y][x] == MAP_WALL)
			{
				Image->m_bufCDC.Rectangle(dx, dy, dx+BlockSize, dy+BlockSize); //벽
			}
			else if (m_data[y][x] == MAP_BLANK)
			{
				Image->m_bufCDC.TextOutW(dx+10, dy, _T(".") ); //빈공간
			}
			else
			{
			  Image->m_bufCDC.StretchBlt(dx, dy, BlockSize, BlockSize, &(Image->m_aCDC[ m_data[y][x]+2 ]), 0, 0, 35, 35, SRCCOPY); //맵에 저장된 블럭
			}
		}
	}
}


int CTetrisMap::copyToData(POINT (*type)[4][4], int patIndex, int dir, POINT pos)
{
	int x=0;
	int y=0;
	for (int i=0; i<4; i++)
	{
		x = pos.x + type[patIndex][dir][i].x;
		y = pos.y + type[patIndex][dir][i].y;

		m_data[y][x] = patIndex;
	}

	return 0;
}


int CTetrisMap::sameBlock(void)
{
	for (int y=1; y<MAP_H-1; y++)
	{
		int state = lineClearCheck(y);
		if (-1 != state)
		{
			lineClear(y);
		}
	}
	return 0;
}


int CTetrisMap::lineClearCheck(int y)
{
	for (int x=1; x<MAP_W-1; x++)
	{
		if (MAP_BLANK == m_data[y][x])
		{
			return -1;
		}
	}
	return 0;
}


int CTetrisMap::lineClear(int y)
{
	for (;1<y; y--)
	{
		for (int x=1; x<MAP_W-1; x++)
		{
			m_data[y][x] = m_data[y-1][x];
		}
	}

	return 0;
}
