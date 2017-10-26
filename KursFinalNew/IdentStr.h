#ifdef HEADER_INCLUDED
#include <stdio.h>
#include <string.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "stroka.h"
#define HEADER_INCLUDED

#endif
#define _CRT_SECURE_NO_WARNINGS


class IdentStr:public stroka
{
public:
	IdentStr();
	IdentStr(char *);
	IdentStr(char sI);
	IdentStr(const IdentStr&);
	~IdentStr();	
	char* ToDown(void);
	void Down(void);
	void operator=(stroka);

	friend IdentStr operator+(IdentStr&,IdentStr&);
	friend IdentStr operator+(IdentStr&,char*);
	friend IdentStr operator+(char*,IdentStr&);

	friend IdentStr operator-(IdentStr&,IdentStr&);
	friend IdentStr operator-(IdentStr&,char*);  
	friend IdentStr operator-(char*,IdentStr&);

	friend IdentStr operator~(IdentStr &);
	friend IdentStr operator>(const IdentStr&,const IdentStr&);
	//	friend IdentStr operator>(const char *b,const IdentStr &a);
	//	friend IdentStr operator>(const IdentStr &a,const char *b);

	IdentStr FindChar(char find);
};


IdentStr::IdentStr():stroka()
{
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса IdentStr::IdentStr():stroka()\r\n"));
#endif 
}


IdentStr::IdentStr(char sI)
{
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса IdentStr::IdentStr(char sI)\r\n"));
#endif 
	if (!(((sI>='a')&&(sI<='z'))||((sI>='A')&&(sI<='Z'))||((sI>='0')&&(sI<='9'))||(sI=='_')))
	{
		len=0;
		pCh=new char[len+1];
		pCh[0]='\0';
		return;
	}
	len=1;
	pCh = new char[len+1];
	pCh[0] = sI;
	pCh[1] = '\0';
}


IdentStr::IdentStr(char *sI)
{
	int i=0;

	if (strlen(sI)<20)
	{
		char proverka[20];
		proverka[0]=' ';
		int j=strlen(sI);
		for (i=0;i<j;i++)
			proverka[i+1]=sI[i];
		proverka[strlen(sI)+1]=' ';
		proverka[strlen(sI)+2]='\0';
		//printf("\n\n-----------------\n--------%s---(%d)-----\n-------------%s----(%d)-----\n\n",proverka,strlen(proverka),sI,strlen(sI));
		char *sReserved=" asm auto bad_cast bad_typeid bool break case catch char class const const_cast continue default delete  do double dynamic_cast else enum except explicit extern false finally float for friend goto if inline int int mutable namespace new operator private protected public register reinterpret_cast return short signed sizeof static static_cast struct switch  template this throw true try type_info typedef typeid typename union unsigned using virtual void volatile while "; 
		if (strstr(sReserved,proverka)!=NULL)
		{
			len=0;
			pCh=new char[len+1];
			pCh[0]='\0';
			return;
		}
	}

#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса IdentStr::IdentStr(char *sI)\r\n"));
#endif 
	if (!(((sI[0]>='a')&&(sI[0]<='z'))||((sI[0]>='A')&&(sI[0]<='Z'))||(sI[0]=='_')))
	{
		len=0;
		pCh=new char[len+1];
		pCh[0]='\0';
		return;
	}
	int j;
	len=strlen(sI);
	for (j=1;j<len;j++)
		if (!(((sI[j]>='a')&&(sI[j]<='z'))||((sI[j]>='A')&&(sI[j]<='Z'))||((sI[j]>='0')&&(sI[j]<='9'))||(sI[j]=='_')))
		{
			len=0;
			pCh=new char[len+1];
			pCh[0]='\0';
			return;
		}
		len=0;
		while (sI[len])len++;
		pCh=new char[len+1];
		for (int i=0;i<len;i++)
			pCh[i]=sI[i];
		pCh[len]='\0';
}


IdentStr::IdentStr(const IdentStr &from)
{		
	char *tmpstr = from.GetStr();	
	int L=from.GetLen();
	pCh=new char[L+1];
	strcpy(pCh,tmpstr);
	len=L;
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса IdentStr::IdentStr(const IdentStr &from)\r\n"));
#endif 
}


IdentStr::~IdentStr()
{
	if(len != 0)
	{
		delete []pCh;
	}
	len=0;
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Деструктор произв. класса IdentStr::~IdentStr()\r\n"));
#endif 
}


char* IdentStr::ToDown(void)
{
	char *temp=new char[len];
	int i;
	for (i=0;i<len;i++)
	{
		if ((pCh[i]>='A')&&(pCh[i]<='Z')) temp[i]=char(pCh[i]+32); else temp[i]=pCh[i];
	}
	temp[len]='\0';
	return temp;
	delete [] temp;
}


void IdentStr::Down(void)
{
	int i;
	for (i=0;i<len;i++)
	{
		if ((pCh[i]>='A')&&(pCh[i]<='Z')) pCh[i]=char(pCh[i]+32);
	}
}

void IdentStr::operator=(stroka a)
{
	IdentStr temp(a.GetStr());
	len=temp.GetLen();
	delete []pCh;
	pCh=new char[len+1];
	strcpy(pCh,temp.pCh);
	return;
}



IdentStr operator+(IdentStr &a,IdentStr &b)
{
	int i;
	int length=a.GetLen()+b.GetLen();
	char *str=new char[length];

	for (i=0;i<a.len;i++)
		str[i]=a.pCh[i];
	for (i=0;i<b.len;i++)
		str[i+a.len]=b.pCh[i];
	str[length]='\0';
	IdentStr temp(str);
	return(temp);
}


IdentStr operator+(IdentStr &a,char* b)
{
	int i; int charlen=strlen(b);
	int length=a.GetLen()+strlen(b);
	char* str=new char[length];
	for (i=0;i<a.GetLen();i++)
		str[i]=a.pCh[i];
	for (i=0;i<charlen;i++)
		str[i+a.len]=b[i];
	str[length]='\0';
	IdentStr temp(str);
	return(temp);
}


IdentStr operator+ (char* a,IdentStr &b)
{
	int i; int charlen=strlen(a);
	int length=b.GetLen()+strlen(a);
	char* str=new char[length];
	for (i=0;i<charlen;i++)
		str[i]=a[i];
	for (i=0;i<b.GetLen();i++)
		str[i+strlen(a)]=b.pCh[i];
	str[length]='\0';
	IdentStr temp(str);
	return(temp);
}


IdentStr operator-(IdentStr &a,IdentStr &b)
{
	if (b.GetLen()==0) return(a);
	if (a.GetLen()==0) return(a);

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
	temp[length]='\0';
	IdentStr temp1(temp);
	delete []temp;
	return(temp1);
}


IdentStr operator-(IdentStr &a,char* b)
{
	int charlen=strlen(b);
	if (strlen(b)==0) return(a);
	if (a.len==0) return(a);

	char *temp=new char[a.len];
	int length=0,i,j,proverka=1;
	for (i=0;i<a.len;i++)
	{
		proverka=1;
		for (j=0;j<charlen;j++)
			if (a.pCh[i]==b[j]) {proverka=0;break;}

			if (proverka==1) {
				temp[length]=a.pCh[i];length++;proverka=0;}

	}
	temp[length]='\0';
	IdentStr temp1(temp);
	delete []temp;
	return(temp1);
}


IdentStr operator-(char* a,IdentStr &b)
{
	int charlen=strlen(a);
	if (strlen(a)==0) return(a);
	if (b.len==0) return(a);

	char *temp=new char[charlen];
	int length=0,i,j,proverka=1;
	for (i=0;i<charlen;i++)
	{
		proverka=1;
		for (j=0;j<b.len;j++)
			if (a[i]==b.pCh[j]) {proverka=0;break;}

			if (proverka==1) {
				temp[length]=a[i];length++;proverka=0;}

	}
	temp[length]='\0';
	IdentStr temp1(temp);
	delete []temp;
	return(temp1);
}

IdentStr operator>(const IdentStr &a,const IdentStr &b)
{
	IdentStr temp;	


	if( strcmp(a.pCh, b.pCh) > 0 )
	{
		temp.len = 6;
		temp.pCh = new char[temp.len + 1];
		strcpy(temp.pCh,"Bigger\0");			
		return(temp);
	}
	else if ( strcmp(a.pCh, b.pCh) == 0 )
	{
		temp.len = 5;
		temp.pCh = new char[temp.len + 1];
		strcpy(temp.pCh,"Equal\0");			
		return(temp);
	}

	temp.len = 6;
	temp.pCh = new char[temp.len + 1];
	strcpy(temp.pCh,"Less\0");
	return(temp);
}


IdentStr operator~(IdentStr &a)
{	
	IdentStr temp;
	temp.len = a.len;
	temp.pCh = new char[temp.len + 1];
	strcpy(temp.pCh, a.pCh);
	std::reverse(&temp.pCh[0], &temp.pCh[temp.len]);
	return(temp);
}


IdentStr IdentStr::FindChar(char find)
{
	int position = 500;
	for(int i=strlen(pCh);i>=0;i--)
	{
		if(pCh[i] == find)
		{
			position = i;
			break;
		}
	}
	IdentStr temp;
	int number=0,temp_int=position;
	while(temp>0)
	{
		number++;
		temp_int=temp_int/10;
	}
	if(position<500)
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




/*
IdentStr operator>(const IdentStr &a,const char *b)
{
IdentStr temp;	


if( strcmp(a.pCh, b) > 0 )
{
temp.len = 6;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Bigger\0");			
return(temp);
}
else
{
if ( strcmp(a.pCh, b) == 0 )
{
temp.len = 5;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Equal\0");			
return(temp);
}
}
temp.len = 6;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Less\0");
return(temp);
}

IdentStr operator>(const char *b,const IdentStr &a)
{
IdentStr temp;	

if( strcmp(b,a.pCh) > 0 )
{
temp.len = 6;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Bigger\0");			
return(temp);
}
else
{
if ( strcmp(b,a.pCh) == 0 )
{
temp.len = 5;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Equal\0");			
return(temp);
}
}
temp.len = 6;
temp.pCh = new char[temp.len + 1];
strcpy(temp.pCh,"Less\0");
return(temp);
}

*/