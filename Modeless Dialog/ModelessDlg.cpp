#include "ModelessDlg.h"

CModelessDialog* CModelessDialog::ptr = NULL;
HWND CModelessDialog::hAddDialog = NULL;

CModelessDialog::CModelessDialog(void)
{
	ptr = this;
}

CModelessDialog::~CModelessDialog(void)
{
	
}

void CModelessDialog::Cls_OnClose(HWND hwnd)
{
	// Разрушаем немодальное диалоговое окно
	DestroyWindow(hwnd); 
	hAddDialog = NULL;
}





void CModelessDialog::SetText(LPCTSTR str)
{
	/*TCHAR text[100];
	_tcscpy(text, str);
	SetWindowText(hStatic,text);*/
	SetWindowText(hStatic, str);
}




BOOL CModelessDialog::Cls_OnInitDialog(HWND hwnd, HWND hwndFocus, LPARAM lParam) 
{
	hStatic = GetDlgItem(hwnd, IDC_STATIC1);
	SetWindowText(hwnd, TEXT("Дополнительный немодальный диалог"));
	//SetWindowText(GetDlgItem(hwnd, IDC_EDIT1), TEXT("Передача данных главному диалогу!"));
	return TRUE;
}


void CModelessDialog::Cls_OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	if(id == IDOK)
	{
		TCHAR buffer[200];
		// Получаем текст с текстового поля ввода
		GetWindowText(GetDlgItem(hwnd, IDC_EDIT1), buffer, 200);
		// Получаем дескриптор родительского (главного) окна
		HWND hParent = GetParent(hwnd);
		if (hParent != NULL)
		{
			HWND hList = GetDlgItem(hParent, IDC_LIST2);
			SendMessage(hList, LB_ADDSTRING, 0, (LPARAM)buffer);

		}
		//// Получаем дескриптор статика главного диалога
		//HWND hStatic = GetDlgItem(hParent, IDC_STATIC1);
		//// Отображаем текст на статике главного диалога
		//SetWindowText(hStatic, buffer);
	}
	else if(id == IDCANCEL)
	{
		// Разрушаем немодальное диалоговое окно
		DestroyWindow(hwnd); 
		//hAddDialog = NULL;
	}
}

BOOL CALLBACK CModelessDialog::DlgProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		HANDLE_MSG(hwnd, WM_CLOSE, ptr->Cls_OnClose);
		HANDLE_MSG(hwnd, WM_INITDIALOG, ptr->Cls_OnInitDialog);
		HANDLE_MSG(hwnd, WM_COMMAND, ptr->Cls_OnCommand);
	}
	return FALSE;
}
