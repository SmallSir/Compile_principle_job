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
int flag;
int y;
int num = 0;
FILE* fp1, *fp2;
char * rwtab[6] = { "function", "if", "then", "while", "do", "endfunc" };

void yucu();
void statement();
void expression();
void term();
void factor();

void check()
{
	if ((ch <= '9' && ch >= '1') || ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = prog[++p];
	}
	else
	{
		syn = -1;
		while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
		{
			ch = prog[++p];
		}
		ch = prog[--p];
		return;
	}
	while ((ch <= '9' && ch >= '0') || ch == '.')
	{
		if (ch == '.')
		{
			syn = -1;
			ch = prog[++p];
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
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
	if (ch <= 'z' && ch >= 'a' || token[m - 1] == '-' || token[m - 1] == '+')
	{
		syn = -1;
		ch = prog[++p];
		while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
		{
			ch = prog[++p];
		}
		ch = prog[--p];
		return;
	}
	ch = prog[--p];
}
void DFA()
{

	if (ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = prog[++p];
	}
	if (ch == '0')
	{
		if (prog[p + 1] == '.')
		{
			token[m++] = ch;
			ch = prog[++p];
			token[m++] = ch;
			ch = prog[++p];
		}
		else if (prog[p + 1] == ')')
		{
			token[m++] = ch;
			ch = prog[++p];
		}
		else
		{
			syn = -1;
			ch = prog[++p];
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
			{
				ch = prog[++p];
			}
			ch = prog[--p];
			return;
		}
	}
	while ((ch <= '9' && ch >= '0') || ch == '.')
	{
		if (ch == '.')
		{
			if (flag)
			{
				syn = -1;
				ch = prog[++p];
				while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
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
	if (ch == 'e')
	{
		if (token[m - 1] == '.')
		{
			syn = -1;
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
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
		if (token[m - 1] == '.' || ch <= 'z' && ch >= 'a')
		{
			syn = -1;
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
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
	memset(token, 0, sizeof(token));
	// 跳过空格字符
	ch = prog[++p];
	while (ch == ' ' || ch == '\n' || ch == '\t')
	{
		ch = prog[++p];
	}
	flow = 0;
	// 读到了字母
	//cout<<endl<<ch<<endl;
	if (ch >= 'a' && ch <= 'z')
	{
		m = 0;
		// 把所有字母读到 token 数组中
		while ((ch >= 'a' && ch <= 'z') || (ch >= '0' && ch <= '9') || (ch >= 'A'&&ch <= 'Z'))
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
		m = 0;
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
				token[m++] = ch;
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
			if (ch <= '9' && ch >= '0' && flow != 11 && flow != 10 && syn != 28)
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
			if (ch <= '9' && ch >= '0' && flow != 11 && flow != 10 && syn != 28)
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
void weibu()
{
	if (syn == 6)
	{
		scaner();
		if (syn == 0 && kk == 0)    // 程序分析识别完
		{
			if (y == 2)
				printf("编译成功\n");
			else
			{
				fprintf(fp2, "编译成功\n");
			}
		}
		else {
			if (y == 2)
				printf("编译失败\n");
			else
			{
				fprintf(fp2, "编译失败\n");
			}
		}
	}
	else
	{
		//if (kk != 1)
		//{
		if (y == 2)
			printf("第 %d 行,有错误, 缺少 'endfunc'\n", num);
		else
		{
			fprintf(fp2, "第 %d 行,有错误, 缺少 'endfunc'\n", num);
		}
		kk = 1;
		//}
	}
}
void lrparser()
{
	if (syn == 1)//判断是否有function作为整段程序的开始
	{
		scaner();
		yucu();
		weibu();
	}
	else
	{
		if (y == 2)
			printf("第 %d 行,有错误,缺少'function'\n", num);
		else
		{
			fprintf(fp2, "第 %d 行,有错误,缺少'function'\n", num);
		}
		kk = 1;
		num--;
		yucu();
		weibu();
	}
}

void yucu() // 语句串分析
{
	flag = 0;
	num++;
	statement();// 调用语句分析函数
	while (syn == 26)    // 一个语句识别结束，继续识别
	{
		flag = 0;
		num++;
		scaner();
		if (syn == 6 || syn == 0)
			break;
		statement();
	}
}

void statement()
{
	if (syn == 10)//如果是变量名字
	{
		//flag = 0;
		scaner();
		if (syn == 18)//如果是=
		{
			scaner();
			expression();
			//判断是否有分号
			if (syn != 26)
			{
				if (!flag)
				{
					if (syn == -1)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,错误输出\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,错误输出\n", num);
						}
					}
					else if (syn == 28)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,缺少'('\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,缺少'('\n", num);
						}
					}
					else if (syn == 18)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,出现多余'='\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,出现多余'='\n", num);
						}
					}
					else if (syn == 22)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,出现'!'错误\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,出现'!'错误\n", num);
						}
					}
					else if (syn == 20)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,出现'<'错误\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,出现'<'错误\n", num);
						}
					}
					else if (syn == 23)
					{
						scaner();
						if (y == 2)
							printf("第 %d 行,出现'<'错误\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,出现'<'错误\n", num);
						}
					}
					else
					{
						if (y == 2)
							printf("第 %d 行,有错误,缺少';'或者操作符\n", num);
						else
						{
							fprintf(fp2, "第 %d 行,有错误,缺少';' 或者操作符\n", num);
						}
					}
					kk = 1;
				}

			}
		}
		else
		{
			if (flag == 0)
			{
				flag = 1;
				if (y == 2)
					printf("第 %d 行,缺少等号\n", num);
				else
				{
					fprintf(fp2, "第 %d 行,缺少等号\n", num);
				}
			}
			kk = 1;
		}
	}
	else//输入的东西不是以变量名字打头
	{
		if (flag == 0)
		{
			if (y == 2)
				printf("第 %d 行,有错误,缺少变量\n", num);
			else
			{
				fprintf(fp2, "第 %d 行,有错误,缺少变量\n", num);
			}
			flag = 1;
		}
		kk = 1;
	}
	//scaner();
	while (syn != 26 && syn != 0 && syn != 6)
	{
		scaner();
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
		//flag = 0;
		if (syn == 27)//如果是(
		{
			scaner();
			expression();
			if (syn == 28)//如果是)
			{
				scaner();
			}
			else if (syn == 27)
			{
				if (flag == 0)
				{
					if (y == 2)
						printf("第 %d 行,有错误,出现多余'('\n", num);
					else
					{
						fprintf(fp2, "第 %d 行,有错误,出现多余'（'\n", num);
					}
					flag = 1;
				}
				kk = 1;
			}
			/*else if (syn == 10 || syn == 11)
			{
			if (flag == 0)
			{
			if (y == 2)
			printf("第 %d 行,缺少操作符或者缺少';'\n", num);
			else
			{
			fprintf(fp2, "第 %d 行,缺少操作符或者缺少';' \n", num);
			}
			flag = 1;
			}
			kk = 1;
			}*/
			else
			{
				//flag = 1;
				if (flag == 0)
				{
					if (y == 2)
						printf("第 %d 行,有错误,缺少')'\n", num);
					else
					{
						fprintf(fp2, "第 %d 行,有错误,缺少')'\n", num);
					}
					flag = 1;
				}
				kk = 1;
			}
		}
		else
		{
			if (flag == 0 && syn == -1)
			{
				flag = 1;
				if (y == 2)
					printf("第 %d 行,实数错误\n", num);
				else
				{
					fprintf(fp2, "第 %d 行,实数错误\n", num);
				}
			}
			if (flag == 0)
			{
				flag = 1;
				if (y == 2)
					printf("第 %d 行,缺少操作数\n", num);
				else
				{
					fprintf(fp2, "第 %d 行,缺少操作数\n", num);
				}
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
	cin >> x;
	cout << "选择文件输入1，控制台输入2" << endl;
	cin >> y;
	if (y == 1)
		fp2 = fopen("out.txt", "w");
	if (x == 1)
	{
		fp1 = fopen("in.txt", "r");
		do {
			fscanf(fp1, "%c", &ch);
			prog[p++] = ch;
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
	//ch = prog[p++];
	scaner();
	num++;

	lrparser();
	system("pause");
}