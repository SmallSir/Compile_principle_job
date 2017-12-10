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
#pragma warning(disable:4996)
using namespace std;
typedef long long LL;


struct quad
{
	char result[12];
	char ag1[12];
	char op[12];
	char ag2[12];
}qua[30];
char * expression(void);
char prog[200], token[200];
char ch;
int flag;
int cnt;
int num;
int syn, p, m, n, sum = 0;
int kk = 0, k = 0;
int x, y;
FILE* fp1, *fp2;
char * rwtab[6] = { "function", "if", "then", "while", "do", "endfunc" };

void check()
{
	if ((ch <= '9' && ch >= '1') || ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = prog[p++];
	}
	else
	{
		syn = -1;
		while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
		{
			ch = prog[p++];
		}
		ch = prog[p--];
		return;
	}
	while ((ch <= '9' && ch >= '0') || ch == '.')
	{
		if (ch == '.')
		{
			syn = -1;
			ch = prog[p++];
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
			{
				ch = prog[p++];
			}
			ch = prog[p--];
			return;
		}
		else
		{
			token[m++] = ch;
			ch = prog[p++];
		}
	}
	if (ch <= 'z' && ch >= 'a' || token[m - 1] == '-' || token[m - 1] == '+')
	{
		syn = -1;
		ch = prog[p++];
		while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
		{
			ch = prog[p++];
		}
		ch = prog[p--];
		return;
	}
	ch = prog[p--];
}
void DFA()
{

	if (ch == '+' || ch == '-')
	{
		token[m++] = ch;
		ch = prog[p++];
	}
	if (ch == '0')
	{
		if (prog[p + 1] == '.')
		{
			token[m++] = ch;
			ch = prog[p++];
			token[m++] = ch;
			ch = prog[p++];
		}
		else
		{
			syn = -1;
			ch = prog[p++];
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
			{
				ch = prog[p++];
			}
			ch = prog[p--];
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
				ch = prog[p++];
				while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
				{
					ch = prog[p++];
				}
				ch = prog[p--];
				return;
			}
			else
				flag = 1;
		}
		//cout<<endl<<"----"<<ch<<endl;
		token[m++] = ch;
		ch = prog[p++];
		//cout<<endl<<"----"<<token<<endl;
	}
	if (ch == 'e')
	{
		if (token[m - 1] == '.')
		{
			syn = -1;
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
			{
				ch = prog[p++];
			}
			ch = prog[p--];
			return;
		}
		token[m++] = ch;
		ch = prog[p++];
		check();
	}
	else
	{
		if (token[m - 1] == '.' || ch <= 'z' && ch >= 'a')
		{
			syn = -1;
			while ((ch <= '9 '&& ch >= '0') || (ch <= 'z' && ch >= 'a') || ch == '.')
			{
				ch = prog[p++];
			}
			ch = prog[p--];
			return;
		}
		else
		{
			ch = prog[p--];
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
	ch = prog[p++];
	while (ch == ' ' || ch == '\n' || ch == '\t')
	{
		ch = prog[p++];
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
			ch = prog[p++];
		}

		ch = prog[p--];
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
		sum = 0;
		/*while (ch >= '0'&&ch <= '9')
		  {
		  sum = sum * 10 + ch - '0';
		  ch = prog[p++];
		  }*/
		//p--;
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
					syn = 21;
					token[m++] = ch;
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
			case '+':
				flow = syn;
				syn = 13;
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
				flag = 0;
				if (ch <= '9' && ch >= '0' && flow != 11 && flow != 10 && flow != 28)
				{
					syn = 11;
					DFA();
				}
				else
					ch = prog[p--];
				break;
			case '-':
				flow = syn;
				syn = 14;
				m = 0;
				token[m++] = ch;
				ch = prog[p++];
				flag = 0;
				if (ch <= '9' && ch >= '0' && flow != 11 && flow != 10 && flow != 28)
				{
					syn = 11;
					DFA();
				}
				else
					ch = prog[p--];
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
void emit(char * result, char * ag1, char * op, char * ag2)
{
	strcpy(qua[cnt].result, result);
	strcpy(qua[cnt].ag1, ag1);
	strcpy(qua[cnt].op, op);
	strcpy(qua[cnt].ag2, ag2);
	cnt++;
	return;
}
char * newtemp()
{
	char *p;
	char m[8];
	p = (char *)malloc(8);
	k++;
	itoa(k, m, 10);
	strcpy(p + 1, m);
	p[0] = 't';
	return (p);
}
char * factor(void)
{
	char * fplace;
	fplace = (char*)malloc(12);
	strcpy(fplace, "");
	if (syn == 10)
	{
		strcpy(fplace, token);
		scaner();
	}
	else if (syn == 11)
	{
		strcpy(fplace, token);
		//itoa(sum, fplace, 10);
		scaner();
	}
	else if (syn == 27)
	{
		scaner();
		fplace = expression();
		if (syn == 28)
			scaner();
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
		else
		{
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
		if (flag == 0)
		{
			flag = 1;
			if (y == 2)
				printf("第 %d 行,缺少操作数\n", num);
			else
			{
				fprintf(fp2, "第 %d 行,缺少操作数\n", num);
			}
			kk = 1;
		}

	}
	return(fplace);
}
char * term(void)
{
	char *tp, *ep2, *eplace, *tt;
	tp = (char *)malloc(12);
	ep2 = (char *)malloc(12);
	eplace = (char *)malloc(12);
	tt = (char *)malloc(12);
	strcpy(eplace, factor());
	while (syn == 15 || syn == 16)
	{
		if (syn == 15)
		{
			tt[0] = '*';
			tt[1] = '\0';
		}
		else if (syn == 16)
		{
			tt[0] = '/';
			tt[1] = '\0';
		}
		scaner();
		strcpy(ep2, factor());
		strcpy(tp, newtemp());
		emit(tp, eplace, tt, ep2);
		strcpy(eplace, tp);
	}
	return(eplace);
}
char * expression(void)
{
	char *tp, *ep2, *eplace, *tt;
	tp = (char *)malloc(12);
	ep2 = (char *)malloc(12);
	eplace = (char *)malloc(12);
	tt = (char *)malloc(12);
	strcpy(eplace, term());
	while (syn == 13 || syn == 14)
	{
		if (syn == 13)
		{
			tt[0] = '+';
			tt[1] = '\0';
		}
		else if (syn == 14)
		{
			tt[0] = '-';
			tt[1] = '\0';
		}
		scaner();
		strcpy(ep2, term());
		strcpy(tp, newtemp());
		emit(tp, eplace, tt, ep2);
		strcpy(eplace, tp);
	}
	return (eplace);
}
int statement()
{
	char tt[8], eplace[8];
	int schain = 0;
	if (syn == 10)
	{
		strcpy(tt, token);
		scaner();
		if (syn == 18)
		{
			scaner();
			strcpy(eplace, expression());
			emit(tt, eplace, " ", " ");
			schain = 0;
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

	return (schain);
}
int yucu()
{
	flag = 0;
	num++;
	int schain = 0;
	schain = statement();
	while (syn == 26)
	{
		flag = 0;
		num++;
		scaner();
		if (syn == 6 || syn == 0)
			break;
		schain = statement();


	}
	return (schain);
}
int lrparser()
{
	int schain = 0;
	kk = 0;
	if (syn == 1)
	{
		num++;
		scaner();
		schain = yucu();
		if (syn == 6)
		{
			scaner();
			if (syn == 0 && kk == 0)
			{
				if (y == 2)
					printf("\n语法,语义分析成功");
				else
					fprintf(fp2, "\n语法,语义分析成功");
			}
		}
		else
		{
			if (kk != 1)
			{
				if (y == 2)
					printf("\n缺endfunc\n");
				else
					fprintf(fp2, "\n缺endfunc\n");
				kk = 1;
			}
		}
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
		syn = -1;
	}
	return (schain);
}
int main()
{
	int i;
	p = 0;
	printf("选择文件输入1,手动输入2\n");
	int x;
	cin >> x;
	cout << "选择文件输入1，控制台输入2" << endl;
	cin >> y;
	printf("请输入语句\n");
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
	int uu=0;
	if (y == 2)
		printf("种别码      单词符号\n");
	else
		fprintf(fp2, "种别码      单词符号\n");
	do
	{
		scaner();
		switch (syn)
		{
			case 11:
				if (y == 2)
					printf("%-3d     %s\n", syn, token);
				else
					fprintf(fp2, "%-3d     %s\n", syn, token);
				break;
			case -1:
				uu = 1;
				if (y == 2)
					printf("error     %s\n", token);
				else
					fprintf(fp2, "error     %s\n", token);
				getchar();
			default:
				if (y == 2)
					printf("%-3d   %s\n", syn, token);
				else
					fprintf(fp2, "%-3d   %s\n", syn, token);
		}
	} while (syn != 0);
	if(uu == 0)
	{
		if (y == 2)
			printf("词法分析成功，按任意键进行语法，语义分析");
		else
			fprintf(fp2, "词法分析成功，按任意键进行语法，语义分析");
	}
	else
	{
		if (y == 2)
			printf("词法分析失败，程序终止! \n");
		else
			fprintf(fp2, "词法分析失败，程序终止! \n");
		return 0;
	}
	getchar();
	p = 0;
	scaner();
	lrparser();
	if (kk != 0)
	{
		if (y == 2)
			printf("语法分析失败，程序终止!");
		else
			fprintf(fp2, "语法分析失败，程序终止!");
		getchar();
		return 0;
	}
	if (y == 2)
		printf("\n三地址指令如下:\n");
	else
		fprintf(fp2, "\n三地址指令如下:\n");
	for (i = 0; i<cnt; i++)
	{
		if (y == 2)
		{
			printf("%s=", qua[i].result);
			printf("%s", qua[i].ag1);
			printf("%s", qua[i].op);
			printf("%s\n", qua[i].ag2);
		}
		else
		{
			fprintf(fp2, "%s=", qua[i].result);
			fprintf(fp2, "%s", qua[i].ag1);
			fprintf(fp2, "%s", qua[i].op);
			fprintf(fp2, "%s\n", qua[i].ag2);
		}
	}
	getchar();
	return 0;
}