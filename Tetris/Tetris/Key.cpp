#include "stdafx.h"
#include "Key.h"


CKey::CKey(void)
{
  for (int i=0; i<KEY_MAX; i++)
	{
		m_key[i]   = -1;
	}
}


CKey::~CKey(void)
{
}


int CKey::KeyDown(int k)
{
	//Ű�� �������� �ִ��� ������ �Ǵ�
	for (int i=0; i<KEY_MAX; i++)
		if ( m_key[i] == k ) return -1;

	//Ű�� ��� �ִ� ������ Ű�� ����
	for (int i=0; i<KEY_MAX; i++)
	{
		if (-1 == m_key[i])
		{
			m_key[i] = k;
			return 1;
		}
	}

	return 0;
}


void CKey::KeyUP(int k)
{
	for (int i=0; i<KEY_MAX; i++)
	{
		if (m_key[i] == k)
		{
			m_key[i] = -1;
			return;
		}
	}
}


int CKey::KeyCheck(int k)
{
	for (int i=0; i<KEY_MAX; i++)
	{
		if (m_key[i] == k)
		{
			return 1;
		}
	}

	return 0;
}


int CKey::KeyClearCheck(void)
{
	for (int i=0; i<KEY_MAX; i++)
	{
		if (m_key[i] != -1)
		{
			return 0;
		}
	}

	return 1;
}
