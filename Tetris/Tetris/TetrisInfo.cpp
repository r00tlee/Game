#include "stdafx.h"
#include "TetrisInfo.h"
#include <time.h>

POINT CTetrisInfo::m_type[TETRIS_PATSIZE][4][4]={
	{	//■■■■
		{0,0,1,0,2,0,3,0},
		{0,0,0,1,0,2,0,3},
		{0,0,1,0,2,0,3,0},
		{0,0,0,1,0,2,0,3}
	},
	{	//■■
		//■■
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1},
		{0,0,1,0,0,1,1,1}
	},
	{	//  ■■
		//■■		
		{2,0,1,0,1,1,0,1},
		{0,0,0,1,1,1,1,2},
		{2,0,1,0,1,1,0,1},
		{0,0,0,1,1,1,1,2}
	},
	{	//■■
		//  ■■
		{0,0,1,0,1,1,2,1},
		{1,0,1,1,0,1,0,2},
		{0,0,1,0,1,1,2,1},
		{1,0,1,1,0,1,0,2}
	},
	{	//■
		//■■■		
		{0,0,0,1,1,1,2,1},
		{1,0,0,0,0,1,0,2},
		{0,0,1,0,2,0,2,1},
		{1,0,1,1,1,2,0,2}
	},
	{	//　　■
		//■■■
		{2,0,2,1,1,1,0,1},
		{0,0,0,1,0,2,1,2},
		{2,0,1,0,0,0,0,1},
		{0,0,1,0,1,1,1,2}
	}
	,
	{	//  ■
		//■■■
		{1,0,0,1,1,1,2,1},
		{0,0,0,1,0,2,1,1},
		{0,0,1,0,2,0,1,1},
		{0,1,1,0,1,1,1,2}
	}
}; //떨어지는 블록 패턴


CTetrisInfo::CTetrisInfo(void)
{
	for (int y=0; y<MAP_H; y++)
	{
		for (int x=0; x<MAP_W; x++)
		{
			//if (y == 0 && x != 0 && x != MAP_W-1) m_data[y][x] = MAP_TOP; 
			if (y == 0 || y == MAP_H-1 ||	x == 0 || x == MAP_W-1)  m_map[y][x] = MAP_WALL;
			else                                                   m_map[y][x] = MAP_BLANK;
		}
	}

	srand(time(NULL));
	m_patindex = rand() % TETRIS_PATSIZE;
	m_dir = rand() % 4;
	m_pos.x = 5;
	m_pos.y = 0;
	m_shawdowPos = 0;

	m_nextPatindex = rand() % 7;
	m_nextDir = 0;
}

CTetrisInfo::~CTetrisInfo(void)
{
}

void CTetrisInfo::Draw()
{
	//다음 블럭 미리보기
	for(int i=0; i<4; i++)
	{
		int x = 15 + m_type[m_nextPatindex][m_nextDir][i].x;
		int y =  5 + m_type[m_nextPatindex][m_nextDir][i].y;
		
		x = BlockSize * x;
		y = BlockSize * y;
		g_CTetrisImage->m_bufCDC.StretchBlt(x, y, 35, 35, &(g_CTetrisImage->m_aCDC[2+m_nextPatindex]), 0, 0, 35, 35, SRCCOPY);
	}

	for (int y=0; y<MAP_H; y++) //맵 정보
	{
		for (int x=0; x<MAP_W; x++)
		{
			int dx = BlockSize * x;
			int dy = BlockSize * y;

			if      (m_map[y][x] == MAP_WALL)   g_CTetrisImage->m_bufCDC.Rectangle(dx, dy, dx+BlockSize, dy+BlockSize); //벽
			else if (m_map[y][x] == MAP_BLANK)	g_CTetrisImage->m_bufCDC.TextOutW(dx+10, dy, _T(".") ); //빈공간
			else			                          g_CTetrisImage->m_bufCDC.StretchBlt(dx, dy, BlockSize, BlockSize, &(g_CTetrisImage->m_aCDC[ m_map[y][x]+2 ]), 0, 0, 35, 35, SRCCOPY); //맵에 저장된 블럭
		}
	}

	for(int i=0; i<4; i++) //현재 블럭
	{
		int x = m_pos.x + m_type[m_patindex][m_dir][i].x;
		int y = m_pos.y + m_type[m_patindex][m_dir][i].y;
		
		x = BlockSize * x;
		y = BlockSize * y;
		g_CTetrisImage->m_bufCDC.StretchBlt(x, y, 35, 35, &(g_CTetrisImage->m_aCDC[m_patindex+2]), 0, 0, 35, 35, SRCCOPY);
	}

	// 그림자
	for (int i=0; i<4; i++)
	{
		int x = m_pos.x      + m_type[m_patindex][m_dir][i].x;
		int y = m_shawdowPos + m_type[m_patindex][m_dir][i].y;

		x = BlockSize * x;
		y = BlockSize * y;
		g_CTetrisImage->m_bufCDC.AlphaBlend(x, y, 35, 35, &(g_CTetrisImage->m_aCDC[m_patindex+2]), 0, 0, 35, 35, g_CTetrisImage->m_bf);
	}
}

int CTetrisInfo::key(UINT nChar)
{
	if (nChar == VK_UP)
	{
 		int dir = m_dir;
		dir++;
		if (3 < dir) dir = 0;
		if (0 == CheckBlockMove(dir, m_pos.x, m_pos.y))  m_dir = dir;
	}
	else if (nChar == VK_DOWN)
	{
		if ( -1 == MoveBlockDown() )
		{
			CopyBlockToData();
			CheckSameBlock();
			GetNewBlock();
			if ( -1 == MoveBlockDown() )
			{
					return -1;
			}
		}
	}
	else if (nChar == VK_LEFT)
	{
		if (0 == CheckBlockMove(m_dir, m_pos.x-1, m_pos.y))  m_pos.x -= 1;
	}
	else if (nChar == VK_RIGHT)
	{
		if (0 == CheckBlockMove(m_dir, m_pos.x+1, m_pos.y))  m_pos.x += 1;
	}
	else if (nChar == VK_SPACE)
	{
		MoveToEnd();
	}
	ShawDowBlock();

	return 1;
}


int CTetrisInfo::CheckBlockMove(int dir, int dx, int dy)
{
	for (int i=0; i<4; i++)
	{
	  int x = dx + m_type[m_patindex][dir][i].x;
		int y = dy + m_type[m_patindex][dir][i].y;
		
		if ( (MAP_BLANK != m_map[y][x]) && (MAP_TOP != m_map[y][x]) )
		{
			return -1;
		}
	}

	return 0;
}

void CTetrisInfo::MoveToEnd(void)
{
	while (1)
	{
		if ( -1 == MoveBlockDown() )
		{
			CopyBlockToData();
			CheckSameBlock();
			GetNewBlock();
			break;
		}
	}
}


int CTetrisInfo::MoveBlockDown(void)
{
	if ( 0 == CheckBlockMove(m_dir, m_pos.x, m_pos.y+1) )
	{
		m_pos.y++;
		return 0;
	}

	return -1;
}


void CTetrisInfo::CopyBlockToData(void)
{
	for (int i=0; i<4; i++)
	{
		int x = m_pos.x + m_type[m_patindex][m_dir][i].x;
		int y = m_pos.y + m_type[m_patindex][m_dir][i].y;

		m_map[y][x] = m_patindex;
	}
}


void CTetrisInfo::GetNewBlock(void)
{
	m_pos.x = 5;//1 + rand() % (MAP_W-5);
	m_pos.y = 1;
	m_patindex = m_nextPatindex;
	m_dir = m_nextDir;

	m_nextPatindex = rand() % TETRIS_PATSIZE;
	m_nextDir = rand() % 4;
}


void CTetrisInfo::CheckSameBlock(void)
{
	for (int y=MAP_H-2; 0<y; y--)
	{
		int same = 0;
		for (int x=1; x<MAP_W-1; x++)
		{
			if (7 < m_map[y][x])
			{
				same = -1;
				break;
			}
		}

		if (0 == same)
		{
			DownBlock(y);
			y++;
		}
	}
}


void CTetrisInfo::DownBlock(int y)
{
	for (;1<=y; y--)
	{
		for (int x=1; x<MAP_W-1; x++)
		{
			if(1 == y) m_map[y][x] = MAP_BLANK;
			else       m_map[y][x] = m_map[y-1][x];
		}
	}
}


void CTetrisInfo::ShawDowBlock(void)
{
	m_shawdowPos = m_pos.y;
	while (1)
	{
		if ( 0 == CheckBlockMove(m_dir, m_pos.x, m_shawdowPos+1) )
	  {
		  m_shawdowPos++;
	  }
		else break;
	}
}
