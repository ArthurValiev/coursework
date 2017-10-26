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
class DesStr:public stroka
{
public:
	DesStr();
	DesStr(char *);
	DesStr(const DesStr&);
	~DesStr();
	operator int() { return(atoi(pCh));}

	friend DesStr operator+(DesStr,DesStr);
	friend DesStr operator+(int, DesStr);
	friend DesStr operator+(DesStr,int);
	friend DesStr operator+(char*, DesStr);
	friend DesStr operator+(DesStr,char*);


	friend DesStr operator-(DesStr,DesStr);
	friend DesStr operator-(int, DesStr);
	friend DesStr operator-(DesStr,int);
	friend DesStr operator-(char*, DesStr);
	friend DesStr operator-(DesStr,char*);


	friend DesStr operator*(DesStr,DesStr);
	friend DesStr operator*(int, DesStr);
	friend DesStr operator*(DesStr,int);
	friend DesStr operator*(char*, DesStr);
	friend DesStr operator*(DesStr,char*);


	friend DesStr operator/(DesStr,DesStr);
	friend DesStr operator/(int, DesStr);
	friend DesStr operator/(DesStr,int);
	friend DesStr operator/(char*, DesStr);
	friend DesStr operator/(DesStr,char*);


	friend DesStr operator%(DesStr,DesStr);
	friend DesStr operator%(int, DesStr);
	friend DesStr operator%(DesStr,int);
	friend DesStr operator%(char*, DesStr);
	friend DesStr operator%(DesStr,char*);


	friend DesStr operator>(const DesStr &in1,const DesStr &in2);
	//	friend DesStr operator>(const DesStr &in1, const int);
	//	friend DesStr operator>(const int, const DesStr &in2);

	void operator=(stroka);
	int Int(void);
	int CanInt(void);
};



DesStr::DesStr():stroka()
{
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса DesStr::DesStr():stroka()\r\n"));
#endif 
}


DesStr::DesStr(char *sD)
{
#ifndef _DEBUG_INFO
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса DesStr::DesStr(char *sD)\r\n"));
#endif 
	if ((sD[0]=='+')||(sD[0]=='-')||((sD[0]>='0')&&(sD[0]<='9')))
	{
		len=strlen(sD);
		for (int i=1;i<len;i++)
			if (!((sD[i]>='0')&&(sD[i]<='9')))
			{
				len=0;
				pCh=new char[len+1];
				pCh[0]='\0';
				return;
			}
			pCh=new char[len+1];
			lstrcpyA(pCh,sD);
	}
	else
	{
		len=0;
		pCh=new char[len+1];
		pCh[0]='\0';
		return;
	}
}


DesStr::DesStr(const DesStr &from)
{
	char *tmpstr = from.GetStr();	
	int L=from.GetLen();
	pCh=new char[L+1];
	lstrcpyA(pCh,tmpstr);
	len=L;	
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Конструктор произв. класса DesStr::DesStr(const DesStr &from)\r\n"));
#endif 
}



DesStr::~DesStr()
{
	if (len!=0)
		delete []pCh;
	len=0;
#ifndef _DEBUG_INFO 
	SendMessage (hMemo, EM_REPLACESEL, 0, (LPARAM) ((LPSTR)L"Деструктор произв. класса DesStr::~DesStr()\r\n"));
#endif 
}




void   DesStr::operator=(stroka a)
{
	char *sD=a.GetStr();
	delete []pCh;
	if ((sD[0]=='+')||(sD[0]=='-')||((sD[0]>='0')&&(sD[0]<='9')))
	{
		len=a.GetLen();
		pCh=new char[len+1];
		for (int i=1;i<len;i++)
			if (!((sD[i]>='0')&&(sD[i]<='9')))
			{
				len=0;
				pCh=new char[len+1];
				pCh[0]='\0';
				return;
			}
			lstrcpyA(pCh,sD);
	}
	else
	{
		len=0;
		pCh=new char[len+1];
		pCh[0]='\0';
		return;
	}

	return;
}



DesStr operator+(DesStr a,DesStr b)
{
	int tempint=a.Int()+b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator+ (DesStr a,int b)
{
	int tempint=a.Int()+b;
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator+ (int a,DesStr b)
{
	int tempint=a+b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator+ (DesStr a,char* b)
{
	int tempint=a.Int()+atoi(b);
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator+ (char* a,DesStr b)
{
	int tempint=atoi(a)+b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator-(DesStr a,DesStr b)
{
	int tempint=a.Int()-b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator- (DesStr a,int b)
{
	int tempint=a.Int()-b;
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator- (int a,DesStr b)
{
	int tempint=a-b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator- (DesStr a,char* b)
{
	int tempint=a.Int()-atoi(b);
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator- (char* a,DesStr b)
{
	int tempint=atoi(a)-b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}




DesStr operator*(DesStr a,DesStr b)
{
	int tempint=a.Int()*b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator* (DesStr a,int b)
{
	int tempint=a.Int()*b;
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator* (int a,DesStr b)
{
	int tempint=a*b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator* (DesStr a,char* b)
{
	int tempint=a.Int()*atoi(b);
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator* (char* a,DesStr b)
{
	int tempint=atoi(a)*b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator/(DesStr a,DesStr b)
{
	int tempint=a.Int()/b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator/ (DesStr a,int b)
{
	int tempint=a.Int()/b;
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator/ (int a,DesStr b)
{
	int tempint=a/b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator/ (DesStr a,char* b)
{
	int tempint=a.Int()/atoi(b);
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator/ (char* a,DesStr b)
{
	int tempint=atoi(a)/b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator%(DesStr a,DesStr b)
{
	int tempint=a.Int()%b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator% (DesStr a,int b)
{
	int tempint=a.Int()%b;
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator% (int a,DesStr b)
{
	int tempint=a%b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator% (DesStr a,char* b)
{
	int tempint=a.Int()%atoi(b);
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator% (char* a,DesStr b)
{
	int tempint=atoi(a)%b.Int();
	char word[50];
	sprintf(word, "%d", tempint);
	DesStr temp;
	temp.len=strlen(word);
	temp.pCh=new char[strlen(word)+1];
	strcpy(temp.pCh,word);
	return(temp);
}



DesStr operator>(const DesStr &in1, const DesStr &in2)
{
	DesStr temp;
	int a;
	if(atoi(in1.pCh) >= atoi(in2.pCh) )
	{
		temp.len = 1;
		temp.pCh = new char[2];
		strcpy(temp.pCh,"1\0");	
		return(temp);
	}
	else
	{
		temp.len = 1;
		temp.pCh = new char[2];
		strcpy(temp.pCh, "0\0");
		return(temp);
	}

}


int   DesStr::Int()
{
	return(atoi(pCh));
}



int    DesStr::CanInt()
{
	if (len>=12) return(0);
	if (len<=9) return(1);
	char MAX1[11]="2147483647",MAX2[12]="+2147483647",MIN[12]="-2147483648";
	if ((!strcmp(MAX1,pCh))||(!strcmp(MAX2,pCh))||(!strcmp(MIN,pCh))) return(1);

	int max=2147483647,min=2147483648;
	if ((DesStr::Int()==max)||(DesStr::Int()==-min)) return(0); else return(1);
}


/*

DesStr operator>(const DesStr &in1, const int a)
{
DesStr temp;
if(atoi(in1.pCh) - a > 0)
{
temp.pCh = "Больше";
temp.len = strlen("Больше");
return temp;
}
else if(atoi(in1.pCh) - a == 0)
{
temp.pCh = "Равно";
temp.len = strlen("Равно");
return temp;
}
else
{
temp.pCh = "Меньше";
temp.len = strlen("Меньше");
return temp;
}
}

DesStr operator>(const int a,const DesStr &in1)
{
DesStr temp;
if(atoi(in1.pCh) - a > 0)
{
temp.pCh = "Меньше";
temp.len = strlen("Меньше");
return temp;
}
else if(atoi(in1.pCh) - a == 0)
{
temp.pCh = "Равно";
temp.len = strlen("Равно");
return temp;
}
else
{
temp.pCh = "Больше";
temp.len = strlen("Больше");
return temp;
}
}

*/

