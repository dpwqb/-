#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<windows.h>
#include<time.h>
//#include<conio.h>
#define explorefile "o:\\explore.txt"
#define mapfile "o:\\map.txt"
void EXPLORE(char c[1024])
{
	char e[4][16][16];
	memset(e,42,sizeof(e));
	e[0][0][0]='^';
	e[1][1][1]='^';
	e[2][1][1]='^';
	e[3][1][1]='^';
	e[3][15][15]='\0';
	//  =
	// { {/*0层探索区域*/
	// 	{ '^', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' }
	// }, {/*1层探索区域*/
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '^', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' }
	// }, {/*2层探索区域*/
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '^', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' }
	// }, {/*3层探索区域*/
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '^', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*' },
	// 	{ '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '*', '\0' }
	// } };
	strcpy(c, e);
}
int IFMT(int a)/*原始信息*/
{
	//
	int i[32] = { 0, 0, 0, 0, 100, 5, 10, 10, 10, 10, 999, 1000, 1, 0, 0, 0, 1 };
	return i[a];
}
void MAP(char c[1024])/*原始地图*/
{
	char m[4][16][16] =
	{ {/*0层地图*/
		{ '0', '0', '0', '0', '!', '0', '0', '%', '0', '0', '0', '0', '%', '0', '0', '0' },
		{ '0', '+', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '$', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '%' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '!', '0', '0', '!', '0', '0' },
		{ '0', '0', '0', '0', '0', '!', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '?', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '$', '0', '0', '?', '0', '0', '0' },
		{ '0', '%', '0', '0', '0', '0', '0', '!', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '?' },
		{ '0', '0', '0', '!', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '$', '0', '0', '!', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '%', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '$', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '!', '0', '0', '0', '0' },
		{ '?', '0', '0', '0', '0', '0', '0', '!', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '%', '0', '0', '^' }
	}, {/*1层地图*/
		{ '&', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '+', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '^' }
	}, {/*2层地图*/
		{ '&', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '+', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '^' }
	}, {/*3层地图*/
		{ '&', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '+', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0' },
		{ '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '0', '\0' }
	} };
	strcpy(c, m);
}
void WASD(char e[4][16][16], int z, int y, int x)/*3*3地图探索范围*/
{
	int fy0, fy15, fx0, fx15;
	fy0 = fy15 = fx0 = fx15 = 1;
	if (y == 0)fy0 = 0;
	else if (y == 15)fy15 = 0;
	if (x == 0)fx0 = 0;
	else if (x == 15)fx15 = 0;
	e[z][y - fy0][x - fx0] = '.';
	e[z][y - fy0][x] = '.';
	e[z][y - fy0][x + fx15] = '.';
	e[z][y][x - fx0] = '.';
	e[z][y][x] = '.';
	e[z][y][x + fx15] = '.';
	e[z][y + fy15][x - fx0] = '.';
	e[z][y + fy15][x] = '.';
	e[z][y + fy15][x + fx15] = '.';
}
//char selectedtext(int f,int x){}
main()
{
	int ifmt[32] = { 0 }, f = 0, bread = 4;
	char explore[4][16][16], map[4][16][16], t;
	EXPLORE(explore);/*更新地图探索数据*/
	MAP(map);/*更新地图数据*/
	for (int i = 0; i < 32; i++)
		ifmt[i] = IFMT(i);/*更新信息*/
	while (1)/*开始游戏*/
	{
		system("cls");/*列出选项*/
		printf("\t%c开始游戏%c\n", t = (f != 0 ? ' ' : '-'), t);
		printf("\t%c查询信息%c\n", t = (f != 1 ? ' ' : '-'), t);
		printf("\t%c游戏帮助%c\n", t = (f != 2 ? ' ' : '-'), t);
		printf("\t%c退出游戏%c\n", t = (f != 3 ? ' ' : '-'), t);
		t = getch();
		if (t <= 0 || t > 127)/*判断是否是方向键*/
		{
			t = getch();
			if (t == 72 && f > 0)
				f--;
			else if (t == 80 && f < 3)
				f++;
		}
		else if (t == 13)switch (f)/*回车触发游戏界面选项*/
		{
		case 0:
			goto start;
		case 1:/*查询信息*/
			for (int i = 0; i < 32; i++)
				if (ifmt[i])
					printf("%3d,%d\n", i, ifmt[i]);
			getch();
			break;
		case 2:/*游戏帮助*/
			printf("wasd移动\n@玩家\n+家\n^下一层\n?居民区\n!精英怪\n%%不知道\n$商店\n");
			getch();
			break;
		case 3:/*退出游戏*/
			return 0;
		}
	}
	start:
	while (1)
	{
		system("cls");
		for (int j = 0; j < 16; j++)
		{
			for (int i = 0; i < 16; i++)
				if (explore[ifmt[2]][j][i] == '*')
					printf("%2c", explore[ifmt[2]][j][i]);/*输出未探索区域*/
				else if (ifmt[1] == j && ifmt[0] == i)
					printf(" @");/*当前位置*/
				else printf("%2c", map[ifmt[2]][j][i]);/*输出当前游戏地图*/
			printf("\n");
		}
		printf("粮食:%d\n", bread);
		t = getch();
		if (t > 0 && t <= 127)/*判断是否是方向键*/
		{
			if (t == 72 || t == 75 || t == 80 || t == 77)t = getch();
			if (t == 27)/*暂停游戏*/
			{

			}
		}
		else if (bread >= ifmt[16])/*携带粮食与饭量比较*/
			switch (getch())
			{
			case 72:/*上行*/
				if (!ifmt[1])printf("无法上行\n");
				else { WASD(explore, ifmt[2], --ifmt[1], ifmt[0]); bread -= ifmt[16]; }
				break;
			case 75:/*左行*/
				if (!ifmt[0])printf("无法左行\n");
				else { WASD(explore, ifmt[2], ifmt[1], --ifmt[0]); bread -= ifmt[16]; }
				break;
			case 80:/*下行*/
				if (ifmt[1] == 15)printf("无法下行\n");
				else { WASD(explore, ifmt[2], ++ifmt[1], ifmt[0]); bread -= ifmt[16]; }
				break;
			case 77:/*右行*/
				if (ifmt[0] == 15)printf("无法右行\n");
				else { WASD(explore, ifmt[2], ifmt[1], ++ifmt[0]); bread -= ifmt[16]; }
				break;
			}
		else
		{
			printf("你被饿死了\n");
			ifmt[0] = ifmt[1] = 1;/*死回家*/
		}
		if (map[ifmt[2]][ifmt[1]][ifmt[0]] != '0')/*判断是否触发副本*/
			switch (map[ifmt[2]][ifmt[1]][ifmt[0]])/*判断触发副本的类型*/
			{
			case '?':
				printf("是否进入居民区（Enter）\n");
				if (getch() == 13);
				break;
			case '!':
				printf("是否进入精英怪的窝（Enter）\n");
				if (getch() == 13);
				break;
			case '%':
				printf("是否进入(Enter)\n");
				if (getch() == 13);
				break;
			case '$':
				printf("是否进入商店（Enter）\n");
				if (getch() == 13);
				break;
			case '+':
				printf("是否回家（Enter）\n");
				if (getch() == 13)
				{
					ifmt[10] += bread;
					bread = 0;
					system("cls");
					printf("输入携带的粮食（0~64）\n粮食剩余:%d\n", ifmt[10]);
					scanf("%d", &bread);
					while (bread <= 0 || bread > 64 || bread > ifmt[10])
					{
						printf("粮食数量错误,重输");
						scanf("%d", &bread);
					}
					ifmt[10] -= bread;
				}
				break;
			case '&':
				printf("已进入上一层\n");
				--ifmt[2];
				ifmt[1] = 1;
				ifmt[0] = 1;
				break;
			case '^':
				printf("已进入下一层\n");
				++ifmt[2];
				ifmt[1] = 1;
				ifmt[0] = 1;
				break;
			case '\0':
				printf("\n游戏通关！");
				getch();
				return 0;
			}
	}
}