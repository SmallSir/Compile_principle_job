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
char prog[500], token[200];
char ch;
int syn, p, m = 0, n, sum, kk = 0;
int y;
int num=0;
FILE* fp1, *fp2;
char * rwtab[6] = { "function", "if", "then", "while", "do", "endfunc" };

void yucu();
void statement();
void expression();
void term();
void factor();

void scaner()
{
	for (n = 0; n < 150; n++)
		token[n] = NULL;
	while (ch == ' '||ch == '\t'||ch == '\n')
	{
		ch = prog[p++];
	}
	m = 0;
	if ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A'))
	{
		while ((ch <= 'z' && ch >= 'a') || (ch <= 'Z' && ch >= 'A') || (ch <= '9' && ch >= '0'))
		{
			token[m++] = ch;
			ch = prog[p++];
		}
		syn = 10;
		for (n = 0; n < 6; n++)
			if (strcmp(token, rwtab[n]) == 0)
			{
				syn = n + 1;
				break;
			}
		token[m++] = '\0';
	}
	else if (ch <= '9' && ch >= '0')
	{
		sum = 0;
		while (ch <= '9' && ch >= '0')
		{
			sum = sum * 10 + ch - '0';
			ch = prog[p++];
		}
		syn = 11;
	}
	else
	{
		switch (ch)
		{
			case'<':
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
				if (ch == '=')
				{
					syn = 22;
					token[m + 1] = ch;
				}
				else {
					syn = 20;
					ch = prog[p--];
				}
				break;
			case'>':
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
				if (ch == '=')
				{
					syn = 24;
					token[m++] = ch;
				}
				else
				{
					syn = 23;
					ch = prog[p--];
				}
				break;
			case'=':
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
				if (ch == '=')
				{
					syn = 25;
					token[m++] = ch;
				}
				else
				{
					syn = 18;
					ch = prog[p--];
				}
				break;
			case '!':
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
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
			case '+': syn = 13; token[0] = ch; break;
			case '-': syn = 14; token[0] = ch; break;
			case '*': syn = 15; token[0] = ch; break;
			case '/': syn = 16; token[0] = ch; break;
			case ';': syn = 26; token[0] = ch; break;
			case '(': syn = 27; token[0] = ch; break;
			case ')': syn = 28; token[0] = ch; break;
			case '#': syn = 0; token[0] = ch; break;
			default:
					  syn = -1;
		}
		ch = prog[p++];
	}
}

void lrparser()
{
	if (syn == 1)//判断是否有function作为整段程序的开始
	{
		scaner();
		yucu();
		if (syn == 6)
		{
			scaner();
			if (syn == 0 && kk == 0)    // 程序分析识别完
			{
				if(y==2)
					printf("编译成功\n");
				else
				{
					fp2 = fopen("out.txt","w");
					fprintf(fp2,"编译成功\n");
				}
			}
			else{
				if(y==2)
					printf("编译失败\n");
				else
				{
					fp2 = fopen("out.txt","w");
					fprintf(fp2,"编译失败\n");
				}
			}
		}
		else
		{
			if (kk != 1) // 没以 endfunc 结束
			{
				if(y==2)
					printf("第 %d 行,有错误, 缺少 'endfunc'\n",num);
				else
				{
					fp2 = fopen("out.txt","w");
					fprintf(fp2,"第 %d 行,有错误, 缺少 'endfunc'\n",num);
				}
				kk = 1;
			}
		}
	}
	else
	{
		if(y==2)
			printf("第 %d 行,有错误,缺少'function'\n",num);
		else
		{
			fp2 = fopen("out.txt","w");
			fprintf(fp2,"第 %d 行,有错误,缺少'function'\n",num);
		}
		kk = 1;
		syn = 1;
		lrparser();
	}
}

void yucu() // 语句串分析
{
	num++;
	statement();// 调用语句分析函数
	while (syn == 26)    // 一个语句识别结束，继续识别
	{
		num++;
		scaner();
		statement();
	}
}

void statement()
{
	if (syn == 10)//如果是变量名字
	{
		scaner();
		if (syn == 18)//如果是=
		{
			scaner();
			expression();
			//判断是否有分号

		}
		else//为什么不能变量后面跟着;
		{
			if(y==2)
				printf("第 %d 行,有错误,缺少等式\n",num);
			else
			{
				fp2 = fopen("out.txt","w");
				fprintf(fp2,"第 %d 行,有错误,缺少等式\n",num);
			}
			kk = 1;
		}
	}
	else//输入的东西不是以变量名字打头
	{
		if(y==2)
			printf("第 %d 行,有错误,缺少变量\n",num);
		else
		{
			fp2 = fopen("out.txt","w");
			fprintf(fp2,"第 %d 行,有错误,缺少变量\n",num);
		}
		kk = 1;
	}

}

void expression()   // 表达式分析函数
{
	term();
	while (syn == 13 || syn == 14)//判断是+或者-
	{
		scaner();
		term();
	}
}

void term() // 项分析函数
{
	factor();
	while (syn == 15 || syn == 16)//*或者/
	{
		scaner();
		factor();
	}
}

void factor()   // 因子分析函数
{
	if (syn == 10 || syn == 11)//=右边如果是字符串或者数字
	{
		scaner();
	}
	else// 看是否是表达式
	{
		if (syn == 27)//如果是(
		{
			scaner();
			expression();
			if (syn == 28)//如果是)
			{
				scaner();
			}
			else
			{
				if(y==2)
					printf("第 %d 行,有错误,缺少')'\n",num);
				else
				{
					fp2 = fopen("out.txt","w");
					fprintf(fp2,"第 %d 行,有错误,缺少')'\n",num);
				}
				kk = 1;
			}
		}
		else
		{
			if(y==2)//??
				printf("第 %d 行,缺少变量\n",num);
			else
			{
				fp2 = fopen("out.txt","w");
				fprintf(fp2,"第 %d 行,缺少变量\n",num);
			}
		}
	}
}

int main()
{
	p = 0;
	printf("\nplease input the string:\n");
	printf("选择文件输入1,手动输入2\n");
	int x;
	cin>>x;
	cout<<"选择文件输入1，控制台输入2"<<endl;
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
	{
		do
		{
			ch = getchar();
			prog[p++] = ch;
		} while (ch != '#');
	}
	p = 0;
	ch = prog[p++];
	scaner();
	num++;
	lrparser();
	system("pause");
}