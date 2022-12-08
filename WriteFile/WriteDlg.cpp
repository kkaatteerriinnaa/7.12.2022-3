#include "Header.h"

WriteThreadDlg* WriteThreadDlg::ptr = NULL;

WriteThreadDlg::WriteThreadDlg(void)
{
	ptr = this;
}

WriteThreadDlg::~WriteThreadDlg(void)
{

}

void WriteThreadDlg::Close(HWND hwnd)
{
	EndDialog(hwnd, 0);
}

DWORD WINAPI Write_Thread(LPVOID lp)
{
	WriteThreadDlg* ptr = (WriteThreadDlg*)lp;
	char buf[4096];
	ifstream in(TEXT("file.txt"), ios::binary | ios::in);
	if (!in)
	{
		MessageBox(ptr->hDialog, TEXT("Ошибка открытия файла!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
		return 1;
	}
	HANDLE hMutex = OpenMutex(MUTEX_ALL_ACCESS, false, TEXT("{B8A2C367-10FE-494d-A869-841B2AF972E0}"));

	DWORD dwAnswer = WaitForSingleObject(hMutex, INFINITE);
	if (dwAnswer == WAIT_OBJECT_0)
	{
		ofstream out(TEXT("file.txt"));
		if (!out.is_open())
		{
			MessageBox(0, TEXT("Error"), TEXT("Критическая секция"), MB_OK);
			return 1;
		}
		int A[100];
		for (int i = 0; i < 100; i++)
		{
			A[i] = rand() % 50;
			out << A[i] << ' ';
		}
		out.close();

		ReleaseMutex(hMutex);

		MessageBox(ptr->hDialog, TEXT("Запись данных в файл file.txt завершена!"), TEXT("Мьютекс"), MB_OK | MB_ICONINFORMATION);
	}
	in.close();
	return 0;
}

BOOL WriteThreadDlg::InitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam)
{
	hDialog = hwnd;
	CreateThread(NULL, 0, Write_Thread, this, 0, NULL);
	return TRUE;
}


BOOL CALLBACK WriteThreadDlg::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Close);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->InitDialog);
	}
	return FALSE;
}