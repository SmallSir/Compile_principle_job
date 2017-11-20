/*词法分析源代码兴 */
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
FILE* fp1, *fp2;
void scaner();

int main()
{
	p = 0;
	printf("\n please input string :\n");
	cout<<"选择文件输入1,手动输入2??"<<endl;
	int x;
	cin>>x;
	cout<<"选择文件输出1还是控制台输出2??"<<endl;
	int y;
	cin>>y;
	if(x==1)
	{
		fp1 = fopen("in.txt","r");
			do {
			fscanf(fp1, "%c", &ch);
			prog[++p] = ch;
		} while (ch != '#');
	
	}
	else
	{do {
		scanf("%c",&ch);
		prog[++p] = ch;
	} while (ch != '#');
	}
	p = 0;
	if(y==2)
	{
		do
		{
			scaner();
			switch (syn)
			{
				case 11: printf("\n(%d, %s)", syn, token); break;
				case -1: printf("\n error"); break;
				default: printf("\n(%d, %s)", syn, token);//关键字变量
			}
		} while (syn != 0);
		printf("\n");
	}
	else if(y==1)
	{
		fp2 = fopen("out.txt","w");
		do
		{
			scaner();
			switch (syn)
			{
				case 11: fprintf(fp2,"\n(%d, %s)", syn, token); break;
				case -1: fprintf(fp2,"\n error"); break;
				default: fprintf(fp2,"\n(%d, %s)", syn, token);//关键字变量
			}
		} while (syn != 0);
		fprintf(fp2,"\n");
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
		
	if(ch == '+' || ch == '-')
 	{
 		token[m++] = ch;
		ch = prog[++p];
 	}
 	if(ch == '0' && prog[p + 1] == '.')
 	{
 		token[m++] = ch;
 		ch = prog[++p];
		token[m++] = ch;
 		ch = prog[++p];
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
	// 初始化 token 数组
	int flow;
	memset(token,0,sizeof(token));
	// 跳过空格字符
	ch = prog[++p];
	while (ch == ' ' || ch == '\n' || ch == '\t') 
	{
		ch = prog[++p];
	}
	// 读到了字母
	//cout<<endl<<ch<<endl;
	if (ch >= 'a' && ch <= 'z')
	{
		m = 0;
		// 把所有字母读到 token 数组中
		while((ch >= 'a' && ch <= 'z') ||( ch >= '0' && ch <= '9')||(ch>='A'&&ch<='Z'))
		{
			token[m++] = ch;
			ch = prog[++p];
		}
		
		ch = prog[--p];
		syn = 10;//若输出是10则是变量或是正整数
		// 判断是否匹配关键字
		for (n = 0; n < 6; n++)
		{
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;//找到相应关键字
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
				token[m ++] = ch;
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
			flow = syn;
			syn = 13; 
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			flag = 0;
			if(ch <= '9' && ch >= '0' && flow != 11)
			{
				syn = 11;
				DFA();
			}
			else
				ch = prog[--p];
			break;
		case '-': 
			flow = syn;
			syn = 14;
			m = 0;
			token[m++] = ch;
			ch = prog[++p];
			flag = 0;
			if(ch <= '9' && ch >= '0' && flow != 11)
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