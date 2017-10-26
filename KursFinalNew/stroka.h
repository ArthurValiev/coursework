#ifndef HEADER_INCLUDED
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include <algorithm>
#define HEADER_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
HWND hMemo;

extern "C" void sum(char*, char*,char*);   // assembler

class stroka
{

protected:
	char *pCh;
	int len;
public:
	stroka();
	stroka(const char ch);
	stroka(const char *s);
	stroka(const stroka&);
	virtual ~stroka();
	int empty(void);
	char* GetStr(void) const { pCh[len] = '\0'; return pCh; }
	int GetLen(void) const { return len; }
	void Show(void) const;
	char* str(void);

	operator int() {return len;}
	operator char*() {return pCh;}

	friend stroka operator+(stroka,stroka);
	friend stroka operator+(stroka,char*);
	friend stroka operator+(char*,stroka);

	friend stroka operator-(stroka,stroka);
	friend stroka operator-(stroka,char*);
	friend stroka operator-(char*,stroka);
	friend stroka operator~(stroka &);
	virtual void operator=(stroka);

	char operator[](int);

	virtual char* ToDown(void);
	virtual void  Down(void);
	friend stroka FindChar(stroka a,char find);
	virtual int  Int(void);
	virtual int   CanInt(void);
};


stroka::stroka()
{
	len=0;
	pCh=new char [len+1];
	pCh[0]='\0';
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор класса stroka::stroka()\r\n"));
#endif 
}


stroka::stroka(const char ch)
{
	len = 1;
	pCh = new char [len + 1];
	pCh [0] = ch;
	pCh [1] = '\0';
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор класса stroka::Stroka(const char ch)\r\n"));
#endif 
}


stroka::stroka(const char *s)
{
	pCh=new char[strlen(s)+1];
	strcpy(pCh,s);
	len=strlen(s);
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор класса stroka::stroka()\r\n"));
#endif 
}


stroka::stroka(const stroka &from)
{
	char *tmpstr=from.GetStr();
	int L=from.GetLen();
	pCh=new char[L+1];
	strcpy(pCh,tmpstr);
	len=L;
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор класса stroka::stroka(const stroka& from)\r\n"));
#endif 
}


stroka::~stroka()
{
	if(len != 0)
		delete []pCh;
	len=0;
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Деструктор класса stroka::~stroka()\r\n"));
#endif 
}


void stroka::Show(void) const
{
	int i;
	for (i=0;i<len;i++) 
		printf("%c",pCh[i]);
	printf(" %d\n",len);
}


char* stroka::str(void)
{
	return(pCh);
}


int stroka::empty(void)
{
	if (len==0) return(1); else return(0);
}


stroka operator+(stroka a,stroka b)
{
	stroka temp;
	temp.len=a.GetLen()+b.GetLen();
	temp.pCh=new char[temp.len+1];	
	sum(a.pCh,b.pCh,temp.pCh);	
	return temp;

}


stroka operator+(stroka a,char* b)
{
	stroka temp;
	temp.len=a.GetLen()+strlen(b);
	temp.pCh=new char[temp.len+1];
	sum(a.pCh,b,temp.pCh);			 
	return temp;
}


stroka operator+ (char* a,stroka b)
{
	stroka temp;
	temp.len=strlen(a)+b.GetLen();
	temp.pCh=new char[temp.len+1];
	sum(a,b.pCh,temp.pCh);				 
	return(temp);
}


stroka operator-(stroka a,stroka b)
{
	stroka temp1;
	char *temp=new char[a.len];
	int length=0,i,j,proverka=1;
	for (i=0;i<a.len;i++)
	{
		proverka=1;
		for (j=0;j<b.len;j++)
			if (a.pCh[i]==b.pCh[j]) {proverka=0;break;}

			if (proverka==1) {
				temp[length]=a.pCh[i];length++;proverka=0;}
	}
	temp1.pCh=new char[length+1];
	for (i=0;i<length;i++) temp1.pCh[i]=temp[i];
	temp1.len=length;
	delete []temp;
	return(temp1);
}


stroka operator-(stroka a,char* b)
{
	stroka temp1(b);
	stroka temp=a-temp1;
	return temp;
}


stroka operator-(char* a,stroka b)
{
	stroka temp1(a);
	stroka temp=temp1-b;
	return temp;
}


void stroka::operator=(stroka a)
{
	len=a.GetLen();
	delete []pCh;
	pCh=new char[len+1];
	strcpy(pCh,a.pCh);
	return;
}

char stroka::operator[](int L)
{
	L--;
	try
	{
		if (L<0)    throw 1;
		if (L>=len) throw 2;
	}
	catch (int)
	{
		SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"ERROR!!!\r\n"));
		return NULL;
	}
	return pCh[L];
}

stroka operator~(stroka &a)
{
	stroka temp;
	temp.len = a.len;
	temp.pCh = new char[temp.len + 1];
	strcpy(temp.pCh, a.pCh);
	std::reverse(&temp.pCh[0], &temp.pCh[temp.len]);
	return(temp);
}

char* stroka::ToDown(void) {return(NULL);};

void  stroka::Down(void) {};



int  stroka::Int(void)
{
	return(atoi(pCh));
};


int   stroka::CanInt(void)
{
	return(NULL);
};


stroka FindChar(stroka a,char find)
{
	int position = 500;
	for(int i=strlen(a.pCh);i>=0;i--)
	{
		if(a.pCh[i] == find)
		{
			position = i;
			break;
		}
	}
	stroka temp;
	int number=0,temp_int=position;
	while(temp>0)
	{
		number++;
		temp_int=temp_int/10;
	}
	if(position!=500)
	{
		temp.len = number;
		temp.pCh = new char[number + 6];
		char* b = new char[7];
		sprintf(b,"Index_%d",position+1);	
		strcpy(temp.pCh,b);
	}
	else
	{
		temp.len = 9;
		temp.pCh = new char[temp.len + 1];
		strcpy(temp.pCh,"Not found\0");
	}
	return(temp);
}

#endif