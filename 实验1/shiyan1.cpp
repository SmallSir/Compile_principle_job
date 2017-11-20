/*�ʷ�����Դ������ */
#define _CRT_SECURE_NO_WARNINGS
#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <set>
#include <map>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
using namespace std;

char prog[100000], token[100000];
char ch;
bool flag;
int syn, p, m, n, sum;
char* rwtab[6] = { "function","if","then","while","do", "endfunc" };

void scaner();

int main()
{
	p = 0;
	printf("\n please input string :\n");
	cout<<"ѡ���ļ�����1,�ֶ�����2??"<<endl;
	int x;
	cin>>x;
	if(x==1)
	{
		freopen("in.txt","r",stdin);
	}
	do {
		cin>>ch;
		prog[++p] = ch;
	} while (ch != '#');
	getchar();
	getchar();
	cout<<"ѡ���ļ����1���ǿ���̨���2??"<<endl;
	int y;
	cin>>y;
	p = 0;
	if(y==1)
	{
		freopen("out.txt","w",stdout);
	}
	else
	{
		do
		{
			scaner();
			switch (syn)
			{
				case 11: printf("\n(%d, %s)", syn, token); break;
				case -1: printf("\n error"); break;
				default: printf("\n(%d, %s)", syn, token);//�ؼ��ֱ���
			}
		} while (syn != 0);
		printf("\n");
	}
}
void check()
{
	if((ch <= '9' && ch >= '1')||ch == '+'||ch == '-')
	{
		token[m++] = ch;
		ch = prog[++p];
	}
	else
	{
		syn = -1;
		while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
		{
			ch = prog[++p];
		}
		ch = prog[--p];
		return;
	}
	while((ch <= '9' && ch >= '0')||ch == '.')
	{
		if(ch == '.')
		{
			syn = -1;
			ch = prog[++p];
			while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
			{
				ch = prog[++p];
			}
			ch = prog[--p];
			return;
		}
		else
		{
			token[m++] = ch;
			ch = prog[++p];
		}
	}
	ch = prog[--p];
}
void DFA()
{
	if((ch <= '9' && ch >= '1')||ch == '+'||ch == '-')
	{
		token[m++] = ch;
		ch = prog[++p];
	}
	else
	{
		syn = -1;
		while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
		{
			ch = prog[++p];
		}
		ch = prog[--p];
		return;
	}
	while((ch <= '9' && ch >= '0')||ch == '.')
	{
		if(ch == '.')
		{
			if(flag)
			{
				syn = -1;
				ch = prog[++p];
				while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
				{
					ch = prog[++p];
				}
				ch = prog[--p];
				return;
			}
			else
				flag = 1;
		}
		//cout<<endl<<"----"<<ch<<endl;
		token[m++] = ch;
		ch = prog[++p];
		//cout<<endl<<"----"<<token<<endl;
	}
	if(ch == 'e')
	{
		if(token[m-1] == '.')
		{
			syn = -1;
			while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
			{
				ch = prog[++p];
			}
			ch = prog[--p];
			return;
		}
		token[m++] = ch;
		ch = prog[++p];
		check();
	}
	else
	{
		if(token[m-1] == '.')
		{
			syn = -1;
			while((ch <= '9 '&& ch >= '0')||(ch <= 'z' && ch >= 'a')||ch == '.')
			{
				ch = prog[++p];
			}
			ch = prog[--p];
			return;
		}
		else
		{
			ch = prog[--p];
			return;
		}
	}
}
void scaner()
{
	// ��ʼ�� token ����
	memset(token,0,sizeof(token));
	// �����ո��ַ�
	ch = prog[++p];
	while (ch == ' ' || ch == '\n' || ch == '\t') 
		ch = prog[++p];
	// ��������ĸ
	//cout<<endl<<ch<<endl;
	if (ch >= 'a' && ch <= 'z')
	{
		m = 0;
		// ��������ĸ���� token ������
		while((ch >= 'a' && ch <= 'z') ||( ch >= '0' && ch <= '9')||(ch>='A'&&ch<='Z'))
		{
			token[m++] = ch;
			ch = prog[++p];
		}
		
		ch = prog[--p];
		syn = 10;//�������10���Ǳ�������������
		// �ж��Ƿ�ƥ��ؼ���
		for (n = 0; n < 6; n++)
		{
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;//�ҵ���Ӧ�ؼ���
				break;
			}
		}
	}
	else if (ch >= '0' && ch <= '9')
	{
		m=0;
		flag = 0;
		syn = 11;
		DFA();	
	}
	else
	{
		switch (ch)
		{
		case'<':
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			if (ch == '=')
			{
				syn = 21;
				token[m + 1] = ch;
			}
			else {
				syn = 20;
				ch = prog[--p];
			}
			break;
		case'>':
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			if (ch == '=')
			{
				syn = 24;
				token[m++] = ch;
			}
			else
			{
				syn = 23;
				ch = prog[--p];
			}
			break;
		case'=':
			m = 0; 
			token[m++] = ch;
			ch = prog[++p];
			if (ch == '=')
			{
				syn = 25;
				token[m++] = ch;
			}
			else
			{
				syn = 18;
				ch = prog[--p];
			}
			break;
		case '!':
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			if (ch == '=')
			{
				syn = 22;
				token[m++] = ch;
			}
			else
			{
				syn = -1;
			}
			break;
		case '+':
			syn = 13; 
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			flag = 0;
			if(ch <= '9' && ch >= '0')
			{
				syn = 11;
				DFA();
			}
			else
				ch = prog[--p];
			break;
		case '-': 
			syn = 14;
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			flag = 0;
			if(ch <= '9' && ch >= '0')
			{
				syn = 11;
				DFA();
			}
			else
				ch = prog[--p];
			break;
		case '*': 
			syn = 15; 
			token[0] = ch; 
			break;
		case '/': 
			syn = 16; 
			token[0] = ch;
			break;
		case ';': 
			syn = 26; 
			token[0] = ch; 
			break;
		case '(': 
			syn = 27; 
			token[0] = ch; 
			break;
		case ')': 
			syn = 28; 
			token[0] = ch; 
			break;
		case '#': 
			syn = 0; 
			token[0] = ch;
			break;
		default:
			syn = -1;
		}
	}
}
