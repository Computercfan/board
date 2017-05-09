#include "vt.h"
#include "board.h"
#include <stdlib.h>
#include <string.h>	//包含strcpy()函数的头文件

int flag_who = 0;	//定义全局变量 用来判断比赛的两人的情况

char user_default[10] = "root"; //设定用户名为root
char passwd_default[15] = "uplooking";	//设定用户密码为uplooking.

#ifdef CROSS
	char state[VBOX+1][HBOX+1] = {0};//交点棋盘数组
#else
	char state[VBOX][HBOX] = {0};//空心棋盘数组
#endif


//用户登录信息
void login(void)
{
	int cnt = 3;//设定用户输入的有效次数为3次
	char user[10];	//定义一个数组用来保存用户输入的用户名
	char passwd[15];//定义一个数组用来保存用户输入的密码

	while(cnt--)
	{
		system("clear");
	
		printf("\t\t********************************\n");
		printf("\t\tWelcome to gobang world!\n");
		printf("\t\tauthor: 汪洋大海中的一只小舟\n");
		printf("\t\t提示：作者很笨，请对他好点...\n\t\t**********我是分隔符************\n");
		
		//printf("\t\tlogin:");
		set_move_xy(17,6); //我认为这个函数可能会影响程序的运行时间，但是我就是想这么写。
		printf("login:");
		scanf("%s", user);
		printf("\t\tpasswd:");
		scanf("%s", passwd);
		
		/*
		 * 此处判断用户还有几次输入的机会以及对输入错误或者次数用完的处理
		 * (废话，肯定是次数用完就没了啊，丢你螺母。。。)
		 */
		if((cnt != 0)&&(strcmp(user, user_default) == 0) && (strcmp(passwd, passwd_default) == 0)) {
			break;
		}else if(cnt != 0){
			printf("you have %d change...\n", cnt);
			sleep(2);
			continue;
		}else {
			printf("no change... exit..\n");
			sleep(2);
			system("clear");
			exit(0);
		}
	}
}


//下棋子的函数
#ifdef CROSS
void fall_chessman(int x, int y, int who)
{
	if (who == BLACK_CHESS) {
		set_bg_fg_colour(BLACK, WHITE);	//设置不同who的对应棋子颜色
	} else if (who == WHITE_CHESS) {
		set_bg_fg_colour(WHITE, BLACK);
	}			

	x = HX+x*3; 
	y = VX+y*2;

	set_move_xy(x, y);
	putchar(' ');

	set_attribute(0);
}
#else
void fall_chessman(int x, int y, int who)
{
	if (who == BLACK_CHESS) {
		set_bg_fg_colour(BLACK, WHITE);
	} else if (who == WHITE_CHESS) {
		set_bg_fg_colour(WHITE, BLACK);
	}			

	x = HX+x*3+1; 
	y = VX+y*2+1;

	set_move_xy(x, y);
	putchar('[');
	putchar(']');

	set_attribute(0);
}
#endif

/*
 * draw_vline2：这个函数用来画竖线
 * @x : 横坐标
 * @y : 纵坐标
 * @ch0：+
 * @ch1：-
 * @len：长度 
 */
void draw_vline2(int x, int y, int ch0, int ch1, int len)
{
	int i;
	set_fg_colour(GREEN);
	for (i = 0; i < len; i++) {
		set_move_xy(x, y+i);
		if (i%2) {
			putchar(ch0);
		} else {
			putchar(ch1);
		}
	}
	set_attribute(0);
}

/*hl: 一行对应的字符占用的总数*/
/*vl: 一列对应的字符占用的总数*/
void draw_board(int x, int y, int hl, int vl)
{
	int i;

	/*画横线*/
	draw_hline(x, y, BD2, hl);
	for (i = 2; i < vl-1; i += 2) {
		draw_hline(x, y+i, BD0, hl);
	}	
	draw_hline(x, y+i, BD2, hl);

	/*画竖线*/	
	draw_vline(x, y+1, BD1, vl-2);
	for (i = 3; i < hl-1; i += 3) {
		draw_vline2(x+i, y+1, BD2, BD1, vl-2);
	}
	draw_vline(x+i, y+1, BD1, vl-2);

	/*两种不同情况下标识列号*/
#ifdef CROSS
	for (i = 0; i <= HBOX; i++) {
		if (i < 10) {
			putchar_xy(x+i*3, y-1, '0'+i);	
		} else {
			putchar_xy(x+i*3, y-1, '0'+i/10);
			putchar_xy(x+i*3+1, y-1, '0'+i%10);
		}
	}	
#else 
	for (i = 0; i < HBOX; i++) {
		if (i < 10) {
			putchar_xy(x+i*3+1, y-1, '0'+i);	
		} else {
			putchar_xy(x+i*3+1, y-1, '0'+i/10);
			putchar_xy(x+i*3+2, y-1, '0'+i%10);
		}
	}	
#endif

#ifdef CROSS
	/*标识行号*/
	for (i = 0; i <= VBOX; i++) {
		if (i < 10) {
			putchar_xy(x-2, y+i*2, '0'+i);	
		} else {
			putchar_xy(x-2, y+i*2, '0'+i/10);
			putchar_xy(x-1, y+i*2, '0'+i%10);
		}
	}	
#else
	/*标识行号*/
	for (i = 0; i < VBOX; i++) {
		if (i < 10) {
			putchar_xy(x-2, y+i*2+1, '0'+i);	
		} else {
			putchar_xy(x-2, y+i*2+1, '0'+i/10);
			putchar_xy(x-1, y+i*2+1, '0'+i%10);
		}
	}	
#endif

	//设置提示信息框
	draw_hline(x+hl,y, BD2, 30);
	set_move_xy(x+hl+10, y);
	printf("\033[%dm %s \033[0m",RED,"imessage");
	draw_hline(x+hl,y+vl-1, BD2, 30);
	draw_vline2(x+hl+30-1, y+1, BD2, BD2, vl-2);
//	set_move_xy(x, y + 2*VBOX + 3);
}

//判断第一次谁走的函数
void first_to_go(void)
{	
	int first = 0;
	while(1)
	{
		set_move_xy(HX, VX + 2*VBOX + 3);	//设置需要第一步先走的提示信息的起始位置
		
		printf("Please input who first to go(1:black,2:white):    \b\b\b\b");
		show_cursor();	//显示光标
		scanf("%d",&first);

		//对用户输入的数字的不同处理结果
		//此处有个bug，当输入first为字符时，出现错误提示一直循环
		if((first != 1) && (first != 2)) {
			fprintf(stderr,"your input error...again>>>>>");
			sleep(2);
			set_move_xy(0, VX + 2*VBOX + 4);
			printf("\033[K");
			set_move_xy(HX, VX + 2*VBOX + 3);
			continue;
		}else if(first == 1) {
			flag_who = BLACK_CHESS;
			set_move_xy(0, VX + 2*VBOX + 3);
			printf("\033[K");
			set_move_xy(HX, VX + 2*VBOX + 3);
			break;
		}else if(first == 2) {
			flag_who = WHITE_CHESS;
			set_move_xy(0, VX + 2*VBOX + 3);
			printf("\033[K");
			set_move_xy(HX, VX + 2*VBOX + 3);
			break;
		}
	}
}


/*
 * check_if_win:判断谁的棋子达到了一条直线上五个棋子。
 * 这个函数的代码太多了吧！！这么写好影响形象的。。
 * */
int check_if_win(int x, int y)
{
	int win = 0;
	win = state[x][y];
	int  i, j, k, l, m;	
	// i表示用来循环次数
	// j：横
	// k：竖
	// l：右斜
	// m：左斜
	
	j = k = l = m = 1;
	
	//横向成立
	for(i = 1;i<5;i++){
		if(win == state[x+i][y])
			j++;
		else
			break;
	}
	for(i = 1;i<5;i++){
		if(win == state[x-i][y])
			j++;
		else
			break;
	}
	if(j >= 5)
		return win;

	//纵向成立
	for(i = 1;i<5;i++){
		if(win == state[x][y+i])
			k++;
		else
			break;
	}
	for(i = 1;i<5;i++){
		if(win == state[x][y-i])
		k++;
		else
			break;	
	}
	if(k >= 5)
		return win;


	//右斜成立
	for(i = 1;i<5;i++){
		if(win == state[x+i][y+i])
			l++;
		else
			break;
	}
	for(i = 1;i<5;i++){
		if(win == state[x-i][y-i])
			l++;
		else
			break;	
	}
	if(l >= 5)
		return win;

	//左斜成立
	for(i = 1;i<5;i++){
		if(win == state[x-i][y+i])
			m++;
		else
			break;
	}
	for(i = 1;i<5;i++){
		if(win == state[x+i][y-i])
			m++;
		else
			break;	
	}
	if(m >= 5)
		return win;

	return 0;
}

//打印who to go 的信息
void draw_imessage(void)
{
	char name[15];
	if(flag_who == 0) {	//当flag_who为0时,打印一段线
		strcpy(name,"___________");
	}else if(flag_who == 1){	
		strcpy(name,"BLACK_CHESS");
	}else if(flag_who == 2) {
		strcpy(name,"WHITE_CHESS");
	}
	set_move_xy(HX+HL+3, VX+9);
	printf("\033[%dmnow \" %s  \"to go \033[0m", YELLOW, name);
	
	set_move_xy(HX, VX + 2*VBOX + 3);
}
