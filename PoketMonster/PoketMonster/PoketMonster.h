
// PoketMonster.h : PoketMonster ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.


// CPoketMonsterApp:
// �� Ŭ������ ������ ���ؼ��� PoketMonster.cpp�� �����Ͻʽÿ�.
//

class CPoketMonsterApp : public CWinApp
{
public:
	CPoketMonsterApp();


// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CPoketMonsterApp theApp;
