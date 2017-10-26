#include <windows.h>
#include <stdlib.h>
#include <string.h>
#include <tchar.h>
#include <commctrl.h>
#include <stdio.h>
#include "stroka.h"
#include "IdentStr.h"
#include "DesStr.h"


#define _CRT_SECURE_NO_WARNINGS
#define _CRT_NON_CONFORMING_SWPRINTFS

#define HEADER_INCLUDED
#define UNICOD
#define ID_INI_NUMBER 40001
#define ID_INI_START 40002
#define ID_TEST_STRING 40003
#define ID_TEST_IDEN 40004
#define ID_TEST_DES 40005
#define ID_TEST_OPER 40006
#define ID_TEST_STRING_FOOL 40007
#define ID_TEST_IDEN_REG 40008
#define ID_TEST_DES_INT 40009

#pragma comment(lib,"comctl32.lib")



HMENU hIni,hTest,hMenu,hStroka,hIdent,hDes;
int Esc=0;
static TCHAR szWindowClass[] = _T("Stroka[winapi]");
static TCHAR szTitle[] = _T("Курсовая работа");

HINSTANCE hInst;
UINT wId;
HWND hStatusWindow;

int i=0;

//ИНТЕРФЕЙС
HWND hText1,hButton1,hEdit1,hGroup1;  //начальные значения
HWND *hTextArray1,*hEditArray1,*hStatus,*hAnswer,hInfo[10],hBox1; //после ввода N
HWND hBox; //КОНСТРУКТОРЫ ДЕСТРУКТОРЫ (окно)
HWND hText2,hEdit2,hComboBox2,hButton2,hBox2,hClose2,hButtonClear; //ИНИЦИАЛИЗАЦИЯ; //инициализация
HWND hText3[4],hEdit3[5],hBox3,hClose3,hOAnswer,hButton3; //операнды

wchar_t string[100];wchar_t msg[100];wchar_t buff1[100];wchar_t buff2[100];wchar_t tempstring[100];
char *oper1,*oper2;char buffO[100];char cbuff[100];int otstup=30;
int otsupY=0;int Nmax=0;int update=1;int init=0,oper=0;
int Answer=0;int PrewParam=0;int OAnswer=0;
int Operand1,Operand2,Operand3;int RW=0;int first=0;int mode=0; //класс+класс

//ТЕСТИРОВАНИЕ
stroka **Stroka;  //массив указателей на базовый класс
int *klass;
char** input;
int N=0,Pos=0;
int current=1;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK InitProc(HWND hDlg,UINT message, WPARAM wParam,LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	WNDCLASSEX wcex;
	wcex.cbSize         = sizeof(WNDCLASSEX);
	wcex.style          = CS_VREDRAW; //CS_HREDRAW | 
	wcex.lpfnWndProc    = WndProc;
	wcex.cbClsExtra     = 0;
	wcex.cbWndExtra     = 0;
	wcex.hInstance      = hInstance;
	wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hCursor        = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground  = (HBRUSH)(DC_BRUSH);//CreateSolidBrush(RGB(22,121,242));//(HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName   = NULL;
	wcex.lpszClassName  = szWindowClass;
	wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wcex))
	{
		MessageBox(NULL, _T("Call to RegisterClassEx failed!"), _T("Win32 Guided Tour"), NULL);
		return 1;
	}

	hInst = hInstance; 
	HWND hWnd = CreateWindow(   //главное окошко
		szWindowClass,
		szTitle,
		//WS_OVERLAPPEDWINDOW|
		CS_HREDRAW|CS_VREDRAW|WS_SYSMENU|WS_VSCROLL,
		//WS_OVERLAPPED | WS_SYSMENU,// |  WS_MINIMIZEBOX,               // WS_OVERLAPPEDWINDOW,  //СТИЛЬ
		0,140,//CW_USEDEFAULT, CW_USEDEFAULT,    //относительно экрана/родителя
		1300, 510,                                  //размер окна
		NULL,               //дескриптор родителя
		NULL,               //hMenu
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL, _T("Call to CreateWindow failed!"), _T("Win32 Guided Tour"), MB_ICONEXCLAMATION);
		return 1;
	}

	hStatusWindow=CreateStatusWindow(WS_CHILD|WS_VISIBLE, (LPTSTR)(L"Валиев Артур БИТ 1130"),hWnd, wId);
	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	//МЕНЮ
	hIni=CreatePopupMenu();
	hTest=CreatePopupMenu();
	hMenu=CreateMenu();
	hStroka=CreateMenu();
	hIdent=CreateMenu();
	hDes=CreateMenu();

	AppendMenu(hIni,MF_ENABLED|MFT_STRING,ID_INI_NUMBER,_T("Число элементов"));
	AppendMenu(hIni,MF_GRAYED|MFT_STRING,ID_INI_START,_T("Проинициализировать"));



	AppendMenu(hStroka,MF_ENABLED|MFT_STRING,ID_TEST_STRING_FOOL,_T("Пуста ли строка?"));
	AppendMenu(hStroka,MF_ENABLED|MFT_STRING,1001,_T("Сложение"));
	AppendMenu(hStroka,MF_ENABLED|MFT_STRING,1002,_T("Вычитание"));
	AppendMenu(hStroka,MF_ENABLED|MFT_STRING,1003,_T("[ ]"));
	AppendMenu(hStroka,MF_ENABLED|MFT_STRING,1005,_T("String Reverse"));




	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,ID_TEST_IDEN_REG,_T("Перевод в нижний регистр"));
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2001,_T("Сложение"));
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2002,_T("Вычитание"));	
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2003,_T("[ ]"));
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2004,_T("Проверка на больше"));
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2005,_T("Поиск символа"));
	AppendMenu(hIdent,MF_ENABLED|MFT_STRING,2006,_T("String Reverse"));


	AppendMenu(hDes,MF_ENABLED|MFT_STRING,ID_TEST_DES_INT,_T("Можно ли представить в формате int?"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3001,_T("Сложение"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3002,_T("Вычитание"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3003,_T("Умножение"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3004,_T("Деление"));
	//	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3005,_T("Остаток от деления"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3006,_T("[ ]"));
	AppendMenu(hDes,MF_ENABLED|MFT_STRING,3007,_T("Проверка на больше"));



	AppendMenu(hTest,MF_ENABLED|MF_POPUP,(UINT_PTR)hStroka,_T("Строка"));
	AppendMenu(hTest,MF_ENABLED|MF_POPUP,(UINT_PTR)hIdent,_T("Строка идентификатор"));
	AppendMenu(hTest,MF_ENABLED|MF_POPUP,(UINT_PTR)hDes,_T("Десятичная строка"));
	AppendMenu(hTest,MF_ENABLED|MF_POPUP,1004,_T("Присваивание"));
	AppendMenu(hTest,MF_ENABLED|MFT_STRING,ID_TEST_OPER,_T("Задать операнд"));



	AppendMenu(hMenu,MF_ENABLED|MF_POPUP,(UINT_PTR)hIni,_T("Инициализация"));
	AppendMenu(hMenu,MF_GRAYED|MF_POPUP,(UINT_PTR)hTest,_T("Тестирование"));
	AppendMenu(hMenu,MF_ENABLED|MF_POPUP,(UINT_PTR)12,_T("О программе"));
	AppendMenu(hMenu,MF_ENABLED|MF_POPUP,(UINT_PTR)11,_T("Выход"));


	SetMenu(hWnd,hMenu);


	// Main message loop:
	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);    //клавиатура
		DispatchMessage(&msg);     //
	}

	return (int) msg.wParam;
}

void Operand(int kl,int operation)   //ОПЕРАЦИИ НАД ОПЕРАНДАМИ 
{
	mode=0;
	GetWindowTextA(hEdit3[0], buffO, 100); 
	if (buffO[0]=='"') 
	{ 
		oper1=new char[strlen(buffO)+1];
		mode=mode+1;
		for (i=0;i<(int)strlen(buffO)-1;i++) oper1[i]=buffO[i+1];
		oper1[strlen(buffO)-2]='\0';
	}

	Operand1=atoi(buffO); 

	if (klass[Operand1-1]==0) 
	{ 
		SetWindowText(hOAnswer,L"Ошибка. Один из операндов не определён!");
		return;
	}

	GetWindowTextA(hEdit3[1], buffO, 100);

	if (buffO[0]=='"') 
	{
		oper2=new char[strlen(buffO)];
		mode=mode+2;
		for (i=0;i<(int)strlen(buffO)-1;i++) oper2[i]=buffO[i+1];
		oper2[strlen(buffO)-2]='\0';
	}

	Operand2=atoi(buffO); 

	if (((operation==3)&&(kl!=3))||((operation==6)&&(kl==3))) {} else

		if ((kl!=1)&&(operation!=4)) if (klass[Operand2-1]==0) 
		{
			SetWindowText(hOAnswer,L"Ошибка. Один из операндов не определён!");
			return;
		}

		GetWindowText(hEdit3[2], string, 100); 

		Operand3=_wtoi(string); 

		if (wcscmp(string,L"")!=0) RW=1; 
		else Operand3=N+1;

		if (klass[Operand3-1]==0)
		{
			Stroka[Operand3-1]=new stroka();
			klass[Operand3-1]=1;
		}
		if (RW==1) if (Operand3-1>N) 
		{
			SetWindowText(hOAnswer,L"Ошибка. Операнда с таким номером не существует!");
			return;
		}

		switch (kl)
		{
		case 1:
			switch (operation)
			{
			case 1: switch (mode) {
			case 0:*Stroka[Operand3-1]=*Stroka[Operand1-1]+*Stroka[Operand2-1];break;
			case 1:*Stroka[Operand3-1]=oper1+*Stroka[Operand2-1];break;
			case 2:*Stroka[Operand3-1]=*Stroka[Operand1-1]+oper2;break;
			case 3:*Stroka[Operand3-1]=(stroka)oper1+oper2;break;
					}break;
			case 2:switch (mode) {
			case 0:*Stroka[Operand3-1]=*Stroka[Operand1-1]-*Stroka[Operand2-1];break;
			case 1:*Stroka[Operand3-1]=oper1-*Stroka[Operand2-1];break;
			case 2:*Stroka[Operand3-1]=*Stroka[Operand1-1]-oper2;break;
			case 3:*Stroka[Operand3-1]=(stroka)oper1-oper2;break;
				   }break;
			case 3:switch (mode) {
			case 0:*Stroka[Operand3-1]=(*Stroka[Operand1-1])[Operand2];break;
			case 1:SetWindowText(hOAnswer,L"Ошибка. 1-ый операнд не правильный!");return; break;
			case 2:SetWindowText(hOAnswer,L"Ошибка. 2-ой операнд не правильный!");return; break;
			case 3:SetWindowText(hOAnswer,L"Ошибка. Операнды не правильные!");return; break;
				   }break;
			case 4:SetWindowText(hEdit3[1],L"Операнд не используется!");
				switch (mode) {
				case 0:*Stroka[Operand3-1]=*Stroka[Operand1-1];break;
				case 1:*Stroka[Operand3-1]=oper1;break;
				case 2:*Stroka[Operand3-1]=*Stroka[Operand1-1];break;
				case 3:*Stroka[Operand3-1]=oper1;break;
				}break;
			case 5:SetWindowText(hEdit3[1],L"Операнд не используется!");
				switch (mode) {
				case 0:*Stroka[Operand3-1]=~*Stroka[Operand1-1];break;											
				}break;
			}
			break;
		case 2:		switch (operation)
					{
		case 1: switch (mode) {
		case 0:*Stroka[Operand3-1]=(IdentStr)*Stroka[Operand1-1]+(IdentStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1+(IdentStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(IdentStr)*Stroka[Operand1-1]+oper2;break;
		case 3:*Stroka[Operand3-1]=(IdentStr)oper1+oper2;break;
				}break;
		case 2:switch (mode) {
		case 0:*Stroka[Operand3-1]=(IdentStr)*Stroka[Operand1-1]-(IdentStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1-(IdentStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(IdentStr)*Stroka[Operand1-1]-oper2;break;
		case 3:*Stroka[Operand3-1]=(IdentStr)oper1-oper2;break;
			   }break;
		case 3:switch (mode) {
		case 0:*Stroka[Operand3-1]=(*Stroka[Operand1-1])[Operand2];break;
		case 1:SetWindowText(hOAnswer,L"Ошибка. 1-ый операнд не правильный!");return; break;
		case 2:SetWindowText(hOAnswer,L"Ошибка. 2-ой операнд не правильный!");return; break;
		case 3:SetWindowText(hOAnswer,L"Ошибка. Операнды не правильные!");return; break;
			   }break;
		case 4: switch(mode){
		case 0:	*Stroka[Operand3-1]=(IdentStr)*Stroka[Operand1-1]>(IdentStr)*Stroka[Operand2-1];break;
				}break;	
		case 5: switch(mode){
		case 0: *Stroka[Operand3-1]=FindChar(*Stroka[Operand1-1],*Stroka[Operand2][0]);break;
				}break;	
		case 6:SetWindowText(hEdit3[1],L"Операнд не используется!");
			switch(mode){
			case 0: *Stroka[Operand3-1]=~*Stroka[Operand1-1];break;	
			}break;
					}
					break;


		case 3:		switch (operation)
					{
		case 1:switch (mode) {
		case 0:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]+(DesStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1+(DesStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]+oper2;break;
		case 3:*Stroka[Operand3-1]=(DesStr)oper1+oper2;break;
			   }break;
		case 2:switch (mode) {
		case 0:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]-(DesStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1-(DesStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]-oper2;break;
		case 3:*Stroka[Operand3-1]=(DesStr)oper1-oper2;break;
			   }break;
		case 3:switch (mode) {
		case 0:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]*(DesStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1*(DesStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]*oper2;break;
		case 3:*Stroka[Operand3-1]=(DesStr)oper1*oper2;break;
			   }break;
		case 4:switch (mode) {
		case 0:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]/(DesStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1/(DesStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]/oper2;break;
		case 3:*Stroka[Operand3-1]=(DesStr)oper1/oper2;break;
			   }break;
		case 5:switch (mode) {
		case 0:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]%(DesStr)*Stroka[Operand2-1];break;
		case 1:*Stroka[Operand3-1]=oper1%(DesStr)*Stroka[Operand2-1];break;
		case 2:*Stroka[Operand3-1]=(DesStr)*Stroka[Operand1-1]%oper2;break;
		case 3:*Stroka[Operand3-1]=(DesStr)oper1%oper2;break;
			   }break;
		case 6:switch (mode) {
		case 0:*Stroka[Operand3-1]=(*Stroka[Operand1-1])[Operand2];break;
		case 1:SetWindowText(hOAnswer,L"Ошибка. 1-ый операнд не правильный!");return; break;
		case 2:SetWindowText(hOAnswer,L"Ошибка. 2-ой операнд не правильный!");return; break;
		case 3:SetWindowText(hOAnswer,L"Ошибка. Операнды не правильные!");return; break;
			   }break;
		case 7:switch(mode){
		case 0:*Stroka[Operand3-1]=operator>((DesStr)*Stroka[Operand1-1],(DesStr)*Stroka[Operand2-1]);break;									

			   }break; 
					}
					break;
		}

		SetWindowTextA(hOAnswer,Stroka[Operand3-1]->GetStr());
		if (RW==1) 
		{
			if ((Operand3-1-Pos>=0)&&(Operand3-1-Pos<=15))  
			{
				SetWindowTextA(hEditArray1[Operand3-1-Pos],Stroka[Operand3-1]->GetStr());
				switch (klass[Operand3-1])
				{
				case 0:swprintf(msg,L" ");break;
				case 1:swprintf(msg,L"stroka");break;
				case 3:swprintf(msg,L"IdentStr");break;
				case 2:swprintf(msg,L"DesStr");break;
				}
				SetWindowText(hStatus[Operand3-1-Pos],msg);
			}

		} else RW=0; 
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:

		hdc = BeginPaint(hWnd, &ps);

		SetScrollRange(hWnd,SB_VERT,0,N-Nmax,TRUE);
		SetTextColor(hdc, RGB(254, 254, 254));
		SetBkColor(hdc, RGB(22,121,242));

		EndPaint(hWnd, &ps);
		break;

	case WM_CLOSE:
		if (Esc==1)
		{if (MessageBox(hWnd,_T("Вы уверены, что хотите выйти из приложения?"),_T("Выход"), MB_OKCANCEL | MB_ICONQUESTION)==IDOK)
		DestroyWindow(hWnd); else Esc=0;}
		else DestroyWindow(hWnd);
		break;


	case WM_KEYDOWN:

		switch(wParam)
		{
		case VK_ESCAPE:
			Esc=1;
			SendMessage(hWnd,WM_CLOSE,0,0);
		default: Esc=2;SendMessage(hWnd,WM_PAINT,0,0);
			break;

		}break;


	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	case WM_VSCROLL:   //ПРОКРУТКА
		update=1;
		wchar_t tempbuff[50];
		switch(LOWORD(wParam))
		{
		case SB_LINEDOWN: if (Pos<N-Nmax) {Pos++;} else update=0; break;
		case SB_LINEUP: if (Pos>0)	{Pos--;} else update=0;break;
		case SB_THUMBTRACK:
			Pos=HIWORD(wParam);break;
		}
		SetScrollPos(hWnd,SB_VERT,Pos,TRUE);

		if (update==1) 
			for (i=0;i<Nmax;i++)
			{
				swprintf(msg,L"%d",i+Pos+1);
				SetWindowText(hTextArray1[i],msg);
				if (klass[i+Pos]!=0) SetWindowTextA(hEditArray1[i],Stroka[i+Pos]->GetStr());
				else  SetWindowTextA(hEditArray1[i],"");
				switch (klass[i+Pos])
				{	
				case 0:swprintf(msg,L" ");break;
				case 1:swprintf(msg,L"stroka");break;
				case 3:swprintf(msg,L"IdentStr");break;
				case 2:swprintf(msg,L"DesStr");break;
				}
				GetWindowText(hStatus[i],tempbuff,50);
				if (wcscmp(tempbuff,msg)!=0)
					SetWindowText(hStatus[i],msg);
				if (Answer==1)
				{
					GetWindowText(hAnswer[i],tempbuff,50);
					if (klass[i+Pos]==0) swprintf(msg,L""); else if (Stroka[i+Pos]->empty()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
					if (wcscmp(tempbuff,msg)!=0)
						SetWindowText(hAnswer[i],msg);
				}
				else
					if (Answer==2)
					{
						GetWindowText(hAnswer[i],tempbuff,50);
						if (klass[i+Pos]!=2) swprintf(msg,L""); else if (Stroka[i+Pos]->CanInt()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
						if (wcscmp(tempbuff,msg)!=0)
							SetWindowText(hAnswer[i],msg);
					}
			}
			break;
			break;

	case WM_MOUSEWHEEL:
		if (((short) HIWORD(wParam))<0)
			SendMessage (hWnd,WM_VSCROLL,SB_LINEDOWN,NULL);
		else
			SendMessage (hWnd,WM_VSCROLL,SB_LINEUP,NULL);
		break;

	case WM_COMMAND:
		switch (LOWORD(wParam))
		{

		case ID_INI_NUMBER:  //Число элементов																											//Число элементов

			SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM)0,(LPARAM)(L"Введите число элементов"));

			if (oper==1) SendMessage(hWnd,WM_COMMAND,50000,NULL);
			if (init==1) SendMessage(hWnd,WM_COMMAND,50001,NULL);
			if (first==1) SendMessage(hWnd,WM_COMMAND,50002,NULL);
			for (i=0; i<N;i++) if (klass[i]!=0) {delete Stroka[i];}


			hGroup1= CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE |BS_GROUPBOX, 10, 10, 360, 50, hWnd, NULL, hInst, NULL);
			hText1 = CreateWindow(L"STATIC",L"Количество элементов:",WS_CHILD|WS_VISIBLE|SS_LEFT,30,30,230,20,hWnd,NULL,hInst,NULL);
			hButton1 = CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 260, 30, 80, 20, hWnd, (HMENU)10, hInst, NULL);
			hEdit1 = CreateWindow(L"EDIT", NULL, WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_MULTILINE|ES_NUMBER,200,30,50,20,hWnd,NULL,hInst,NULL);

			break;


		case 10:  //button "OK"					//button "OK

			GetWindowText(hEdit1, string, 100);
			N=_wtoi(string);
			if (N<2) N=2;
			if (N>=1000) N=999;

			if (N>15) Nmax=15; else Nmax=N;

			Stroka = new stroka*[N+1];
			klass  = new int[N+1];

			for (i=0;i<N+1;i++)
			{
				klass[i]=0;
			}

			hTextArray1= new HWND[Nmax];
			hEditArray1= new HWND[Nmax];
			hStatus=new HWND[Nmax];
			hAnswer=new HWND[Nmax];


			swprintf(msg,L"%d элементов",N);
			SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM)0,(LPARAM)(msg)); 

			DestroyWindow(hEdit1);
			DestroyWindow(hButton1);
			DestroyWindow(hText1);
			DestroyWindow(hGroup1);

			EnableMenuItem(hIni,ID_INI_START,MF_BYCOMMAND|MF_ENABLED);
			hBox1=CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE |BS_GROUPBOX, 10, 10, 420, 420, hWnd, NULL, hInst, NULL);
			hInfo[0]=CreateWindow(L"STATIC", L"№", WS_CHILD|WS_VISIBLE|SS_LEFT,20,20,40,20,hWnd,NULL,hInst,NULL);
			hInfo[1]=CreateWindow(L"STATIC", L"Ввод", WS_CHILD|WS_VISIBLE|SS_LEFT,10+50,20,160,20,hWnd,NULL,hInst,NULL);
			hInfo[2]=CreateWindow(L"STATIC", L"Класс", WS_CHILD|WS_VISIBLE|SS_LEFT,10+50+170,20,160,20,hWnd,NULL,hInst,NULL);
			for (i=0;i<Nmax;i++)
			{
				swprintf(msg,L"%d",i+1);
				hTextArray1[i]= CreateWindow(L"STATIC",(LPCWSTR)msg,WS_CHILD|WS_VISIBLE|SS_LEFT,20,otstup+20+i*25,40,20,hWnd,NULL,hInst,NULL);
				if (klass[i+Pos]!=0) hEditArray1[i]= CreateWindowA("EDIT", Stroka[i+Pos]->GetStr(),ES_AUTOHSCROLL|WS_CHILD|WS_VISIBLE|WS_TABSTOP,60,otstup+20+i*25,160,20,hWnd,(HMENU)(101+i),hInst,NULL);//ES_READONLY|
				else hEditArray1[i]= CreateWindowA("EDIT", NULL,ES_AUTOHSCROLL|WS_CHILD|WS_VISIBLE|WS_TABSTOP,60,otstup+20+i*25,160,20,hWnd,(HMENU)(101+i),hInst,NULL);

				switch (klass[i+Pos])
				{
				case 0:swprintf(msg,L" ");break;
				case 1:swprintf(msg,L"stroka");break;
				case 3:swprintf(msg,L"IdentStr");break;
				case 2:swprintf(msg,L"DesStr");break;
				}
				hStatus[i]= CreateWindow(L"EDIT",msg,ES_READONLY|WS_CHILD|WS_VISIBLE|WS_TABSTOP,60+170,otstup+20+i*25,50,20,hWnd,NULL,hInst,NULL);
			}

			hBox= CreateWindow(L"button", L"", WS_CHILD | WS_VISIBLE |BS_GROUPBOX, 835, 10, 420, 420, hWnd, NULL, hInst, NULL);
			if (first==0) hMemo=CreateWindow(L"EDIT",msg,ES_READONLY|WS_VSCROLL|ES_MULTILINE|WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_AUTOVSCROLL,840,20,410,400,hWnd,NULL,hInst,NULL);

			first=1;

			break;


		case ID_INI_START:  //ИНИЦИАЛИЗАЦИЯ ОКНО	

			EnableMenuItem(hTest,(UINT_PTR)hTest,MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hMenu,(UINT_PTR)hTest,MF_BYCOMMAND|MF_ENABLED);			
			EnableMenuItem(hTest,ID_TEST_IDEN,MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hTest,ID_TEST_DES,MF_BYCOMMAND|MF_ENABLED);
			EnableMenuItem(hTest,ID_TEST_OPER,MF_BYCOMMAND|MF_ENABLED);

			if (init==1) break; else
			{
				init=1;
				hComboBox2=CreateWindow(L"listbox", NULL,WS_CHILD | WS_VISIBLE | LBS_STANDARD |LBS_WANTKEYBOARDINPUT,otsupY+520,90, 180, 50,hWnd, (HMENU)14, hInst, NULL);

				SendMessage(hComboBox2, LB_ADDSTRING, 0,(LPARAM)(LPSTR)L"Cтрока");
				SendMessage(hComboBox2, LB_ADDSTRING, 0,(LPARAM)(LPSTR)L"Десятичная строка");
				SendMessage(hComboBox2, LB_ADDSTRING, 0,(LPARAM)(LPSTR)L"Строка идентификатор");
				SendMessage(hComboBox2, CB_SETCURSEL, 0, 0L);

				swprintf(buff1,L"№%d",current);

				hBox2=CreateWindow(L"button", L"Инициализация", WS_CHILD | WS_VISIBLE |BS_GROUPBOX, otsupY+450, 10, 360, 200, hWnd, NULL, hInst, NULL);
				hClose2= CreateWindow(L"button", L"Закрыть", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, otsupY+749, 11, 61, 20, hWnd, (HMENU)50001, hInst, NULL);
				hText2= CreateWindow(L"STATIC", buff1,WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+470,15+40,40,20,hWnd,NULL,hInst,NULL);
				hEdit2= CreateWindow(L"EDIT",NULL,ES_AUTOHSCROLL|WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+520,15+40,180,20,hWnd,NULL,hInst,NULL);
				hButton2= CreateWindow(L"button", L"OK", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, otsupY+720,15+ 40, 80, 20, hWnd, (HMENU)5000, hInst, NULL);
				hButtonClear=CreateWindow(L"button", L"Очистить", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, otsupY+720,25+15+ 40, 80, 20, hWnd, (HMENU)5005, hInst, NULL);
			}

			break;



		case 5000:  //ПРОИНИЦИАЛИЗИРОВАТЬ
			if (klass[current-1]!=0) {delete Stroka[current-1];}
			klass[current-1]= (int)SendMessage(hComboBox2,LB_GETCURSEL, 0, 0L)+1;
			GetWindowTextA(hEdit2,cbuff,100);
			//if (klass[current-1]!=0) {delete Stroka[current-1];}
			switch (klass[current-1])
			{
			case 0:	Stroka[current-1]=new stroka(cbuff);klass[current-1]=1;break;
			case 1:	Stroka[current-1]=new stroka(cbuff);break;
			case 3:	Stroka[current-1]=new IdentStr(cbuff);break;
			case 2:	Stroka[current-1]=new DesStr(cbuff);break;
			}
			switch (klass[current-1])
			{
			case 0:swprintf(msg,L" ");break;
			case 1:swprintf(msg,L"stroka");break;
			case 3:swprintf(msg,L"IdentStr");break;
			case 2:swprintf(msg,L"DesStr");break;
			}
			if ((current-1-Pos>=0)&&(current-1-Pos<=15)) SetWindowText(hStatus[current-1-Pos],msg);
			if ((current-1-Pos>=0)&&(current-1-Pos<=15)) SetWindowTextA(hEditArray1[current-1-Pos],Stroka[current-1]->GetStr());
			if (current<N) current++;
			swprintf(buff2,L"№%d",current);
			SetWindowText(hText2,buff2);
			break;

		case 5005:   // ОЧИСТИТЬ
			if (klass[current-1]!=0)
			{
				klass[current-1]=0;
				delete Stroka[current-1];
				if ((current-1-Pos>=0)&&(current-1-Pos<=15)) 
				{SetWindowText(hStatus[current-1-Pos],L"");
				SetWindowText(hEditArray1[current-1-Pos],L"");}
			}
			else SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Удаление не возможно\r\n"));
			break;

		case (UINT)11:      // MENU: Exit
			SendMessage(hStatusWindow,SB_SETTEXT,(WPARAM)0,(LPARAM)(L"Выход"));
			Esc=1;SendMessage(hWnd,WM_CLOSE,0,0);break;

		case 12:      // MENU: About
			MessageBox(hWnd,L"Курсовая работа\nСтудента группы №1130\nВалиева А.А.\nВариант №4",L"О программе",MB_ICONINFORMATION);

			break;



		case ID_TEST_STRING_FOOL:   //пуста ли строка
			if (Answer==0)
			{
				hInfo[3]=CreateWindow(L"STATIC", L"Пустая?", WS_CHILD|WS_VISIBLE|SS_LEFT,170+20+140,20,60,20,hWnd,NULL,hInst,NULL);
				for (i=0;i<Nmax;i++)
				{
					if (klass[i+Pos]==0) swprintf(msg,L""); else
						if (Stroka[i+Pos]->empty()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
					hAnswer[i]=CreateWindow(L"STATIC", msg, WS_CHILD|WS_VISIBLE|SS_LEFT,20+170+140,otstup+20+i*25,60,20,hWnd,NULL,hInst,NULL);
				}
			} else 
			{
				SetWindowText(hInfo[3],L"Пустая?");
				for (i=0;i<Nmax;i++)
				{
					if (klass[i+Pos]==0) swprintf(msg,L""); else
						if (Stroka[i+Pos]->empty()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
					SetWindowText(hAnswer[i],msg);	
				}

			}
			Answer=1;

			break;


		case ID_TEST_IDEN_REG:    //в нижний регистр
			if (Answer==1)
			{
				Answer=0;
				DestroyWindow(hInfo[3]);
				for (i=0;i<Nmax;i++)
					DestroyWindow(hAnswer[i]);
			}
			for (i=0;i<N;i++)
			{
				if (klass[i]==3) Stroka[i]->Down();
			}
			for (i=0;i<Nmax;i++)
			{
				if (klass[i+Pos]==3) SetWindowTextA(hEditArray1[i],Stroka[i+Pos]->GetStr());
			}

			break;


		case ID_TEST_DES_INT:   // можно ли в Int
			if (Answer==0)
			{
				hInfo[3]=CreateWindow(L"STATIC", L"Int?", WS_CHILD|WS_VISIBLE|SS_LEFT,170+20+140,20,60,20,hWnd,NULL,hInst,NULL);
				for (i=0;i<Nmax;i++)
				{
					if (klass[i+Pos]!=2) swprintf(msg,L""); else
						if (Stroka[i+Pos]->CanInt()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
					hAnswer[i]=CreateWindow(L"STATIC", msg, WS_CHILD|WS_VISIBLE|SS_LEFT,20+170+140,otstup+20+i*25,60,20,hWnd,NULL,hInst,NULL);
				}
			} else 
			{
				SetWindowText(hInfo[3],L"Int?");
				for (i=0;i<Nmax;i++)
				{
					if (klass[i+Pos]!=2) swprintf(msg,L""); else
						if (Stroka[i+Pos]->CanInt()==1) swprintf(msg,L"Да"); else swprintf(msg,L"Нет");
					SetWindowText(hAnswer[i],msg);	
				}

			}
			Answer=2;
			break;


		case ID_TEST_OPER: //  выбрать операнд

			if (oper==1) break; 
			else
			{
				oper=1;
				hBox3=      CreateWindow(L"button", L"Выбор операндов", WS_CHILD | WS_VISIBLE |BS_GROUPBOX, otsupY+450, 227, 360, 202, hWnd, NULL, hInst, NULL);
				hClose3=    CreateWindow(L"button", L"Закрыть", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, otsupY+751, 228, 60, 20, hWnd, (HMENU)50000, hInst, NULL);
				hText3[0] = CreateWindow(L"STATIC",L"1-ый операнд",WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+470,255,100,20,hWnd,NULL,hInst,NULL);
				hEdit3[0] = CreateWindow(L"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+575,255,200,20,hWnd,NULL,hInst,NULL);
				hText3[1] = CreateWindow(L"STATIC",L"2-ой операнд",WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+470,280,100,20,hWnd,NULL,hInst,NULL);
				hEdit3[1] = CreateWindow(L"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+575,280,200,20,hWnd,NULL,hInst,NULL);
				hText3[2] = CreateWindow(L"STATIC",L"3-ий операнд",WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+470,305,100,20,hWnd,NULL,hInst,NULL);
				hEdit3[2] = CreateWindow(L"EDIT",NULL,WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_NUMBER,otsupY+575,305,200,20,hWnd,NULL,hInst,NULL);
				hText3[3] = CreateWindow(L"STATIC",L"Результат",WS_CHILD|WS_VISIBLE|WS_TABSTOP,otsupY+470,370,100,20,hWnd,NULL,hInst,NULL);
				hOAnswer  = CreateWindow(L"EDIT",NULL,ES_AUTOHSCROLL|WS_CHILD|WS_VISIBLE|WS_TABSTOP|ES_NUMBER,otsupY+470,395,310,20,hWnd,NULL,hInst,NULL);

			}

			break;

		case 50000:  //КНОПКА ЗАКРЫТЬ ОПЕРАНДЫ
			oper=0;
			DestroyWindow(hBox3);
			for (i=0;i<=2;i++)
			{DestroyWindow(hText3[i]);DestroyWindow(hEdit3[i]);}
			DestroyWindow(hClose3);
			DestroyWindow(hOAnswer);
			DestroyWindow(hText3[3]);


			break;



		case 50001: //КНОПКА ЗАКРЫТЬ ИНИЦИАЛИЗАЦИЯ
			init=0;
			DestroyWindow(hComboBox2);
			DestroyWindow(hBox2);
			DestroyWindow(hClose2);
			DestroyWindow(hText2);
			DestroyWindow(hEdit2);
			DestroyWindow(hButton2);
			DestroyWindow(hButtonClear);
			break;

		case 50002:  //ЗАКРЫТЬ ВСЕ
			for (i=0;i<=3;i++)
				DestroyWindow(hInfo[i]);
			for (i=0;i<=Nmax;i++)
			{
				DestroyWindow(hTextArray1[i]);
				DestroyWindow(hEditArray1[i]);
				DestroyWindow(hStatus[i]);
				DestroyWindow(hAnswer[i]);
			}
			DestroyWindow(hBox1);
			Answer=0;
			break;





		case 1001:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(1,1); break;

		case 1002:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(1,2); break;

		case 1003:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(1,3); break;

		case 1005:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(1,5); break;




		case 2001:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,1); break;

		case 2002:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,2); break;

		case 2003:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,3); break;

		case 2004:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,4); break;

		case 2005:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,5); break;

		case 2006:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(2,6); break;


		case 3001:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,1); break;

		case 3002:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,2); break;

		case 3003:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,3); break;

		case 3004:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,4); break;

		case 3005:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,5); break;

		case 3006:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,6); break;

		case 3007:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(3,7); break;

		case 1004:if (oper==0) SendMessage(hWnd,WM_COMMAND,ID_TEST_OPER,NULL); else Operand(1,4); break;

			break;

		default: 
			int temp=wParam-16777317;  //ИМЕННО НАЖАТИЕ НА Edit. 16777317- опытным путем
			if ((temp<16)&&(temp>=0))
			{				
				SendMessage(hWnd,WM_COMMAND,ID_INI_START,NULL);				
				current=temp+Pos+1;
				swprintf(buff2,L"№%d",current);
				SetWindowText(hText2,buff2);
				GetWindowText(hEditArray1[current-1],buff2,100);
				SetWindowText(hEdit2,buff2);		
			}
			break;

		}

	case WM_SIZE: SendMessage(hStatusWindow,WM_SIZE,wParam,lParam);
		break;		

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}