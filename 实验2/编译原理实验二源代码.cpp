#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char prog[80], token[9];
char ch;
int syn, p, m = 0, n, sum, kk = 0;
char * rwtab[6] = { "function", "if", "then", "while", "do", "endfunc" };

void yucu();
void statement();
void expression();
void term();
void factor();

void scaner()
{
	for (n = 0; n < 9; n++)
		token[n] = NULL;
	while (ch == ' ')
		ch = prog[p++];
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
	if (syn == 1)
	{
		scaner();
		yucu();
		if (syn == 6)
		{
			scaner();
			if (syn == 0 && kk == 0)    // 程序分析识别完
				printf("success");
		}
		else
		{
			if (kk != 1) // 没以 endfunc 结束
			{
				printf("error! need 'endfunc'");
				kk = 1;
			}
		}
	}
	else
	{
		printf("error! need 'function'");
		kk = 1;
	}
}

void yucu() // 语句串分析
{
	statement();    // 调用语句分析函数
	while (syn == 26)    // 一个语句识别结束，继续识别
	{
		scaner();
		statement();
	}
}

void statement()
{
	if (syn == 10)
	{
		scaner();
		if (syn == 18)
		{
			scaner();
			expression();
		}
		else
		{
			printf("error! evaluate tag error!");
			kk = 1;
		}
	}
	else
	{
		printf("error! the statement error!");
		kk = 1;
	}
}

void expression()   // 表达式分析函数
{
	term();
	while (syn == 13 || syn == 14)
	{
		scaner();
		term();
	}
}

void term() // 项分析函数
{
	factor();
	while (syn == 15 || syn == 16)
	{
		scaner();
		factor();
	}
}

void factor()   // 因子分析函数
{
	if (syn == 10 || syn == 11)
	{
		scaner();
	}
	else// 看是否是表达式
	{
		if (syn == 27)
		{
			scaner();
			expression();
			if (syn == 28)
			{
				scaner();
			}
			else
			{
				printf("error! need another ')");
				kk = 1;
			}
		}
		else
		{
			printf("error! expression error!");
		}
	}
}

void main()
{
	p = 0;
	printf("\nplease input the string:\n");

	do
	{
		ch = getchar();
		prog[p++] = ch;
	} while (ch != '#');

	p = 0;
	ch = prog[p++];
	scaner();
	lrparser();

	system("pause");
}