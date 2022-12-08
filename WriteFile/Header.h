#pragma once
#include<windows.h>
#include <windowsX.h>
#include <tchar.h>
#include <fstream>
#include"resource.h"

using namespace std;

class WriteThreadDlg
{
public:
	WriteThreadDlg(void);
public:
	~WriteThreadDlg(void);
	static BOOL CALLBACK DlgProc(HWND hWnd, UINT mes, WPARAM wp, LPARAM lp);
	static WriteThreadDlg* ptr;
	void Close(HWND hwnd);
	BOOL InitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam);
	HWND hDialog;
};