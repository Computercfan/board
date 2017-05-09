/* main.c --> 五子棋的主程序
 * auther： 周汉红
 * date：2017.4.27
 * 虽然ta很笨，也很懒。。。。
 */

#include "vt.h"
#include "board.h"
#include <stdlib.h>	//包含exit()函数的头文件

int main(void)
{
	int user_raw, user_col;	//用户输入的行，列坐标
	int ret;
	int win = 0;

	login();//用户登录界面	

	system("clear");//清屏操作
	hidde_cursor();	//隐藏光标

	draw_board(HX, VX, HL, VL);//画出棋盘
	
	//打印信息
	draw_imessage();	
	
	//此处判断第一个是who 走
	first_to_go();
	
	//打印信息
	draw_imessage();
	
	while (1) {
		printf("Please input raw and colun(eg:3/5):     \b\b\b\b\b");
		show_cursor();	//显示光标
		ret = scanf("%u/%u", &user_raw, &user_col);  //为什么返回的是2
	
	// 为了美观和交互性好，我认为此处应该退出后执行清屏操作。	
		if (ret != 2) {
			fprintf(stderr, "your input is error...\n");
			sleep(3);
			system("clear");
			exit(1);//直接退出整个程序
		}

#ifdef CROSS //当定义了CROSS这个宏时，才会执行此代码段的程序
	     //此代码块属于结合点落棋
		if (user_raw > VBOX || user_col > HBOX) {
			fprintf(stderr, "your input is invalid...");
			sleep(2);//延时2s
			set_move_xy(0, VX + 2*VBOX + 4);//设置提示的起始坐标
			printf("\033[K");	//清空此行的数据
			set_move_xy(HX, VX + 2*VBOX + 3);//设置图示的起始坐标
			continue;
		}
#else 
		//此代码块属于空心块落棋
		if (user_raw > VBOX-1 || user_col > HBOX-1) {
			fprintf(stderr, "your input is invalid...");
			sleep(2);
			set_move_xy(0, VX + 2*VBOX + 4);
			printf("\033[K");
			set_move_xy(HX, VX + 2*VBOX + 3);
			continue;
		}
#endif
		//此代码段检测是否所填区域存在值。
		if (state[user_raw][user_col] != 0) {
			fprintf(stderr, "\there have been fall chess!");
			sleep(2);
			set_move_xy(0, VX + 2*VBOX + 4);
			printf("\033[K");
			set_move_xy(HX, VX + 2*VBOX + 3);
			continue;
		}

		//落子
		if (flag_who == BLACK_CHESS) {
			fall_chessman(user_col , user_raw, BLACK_CHESS);
			state[user_raw][user_col] = BLACK_CHESS;
			flag_who = WHITE_CHESS;
		} else {
			fall_chessman(user_col , user_raw, WHITE_CHESS);
			state[user_raw][user_col] = WHITE_CHESS;
			flag_who = BLACK_CHESS;
		}
		draw_imessage();

		//判断who 可以赢并输出信息
		if ((win = check_if_win(user_raw, user_col)) == BLACK_CHESS) {
			set_move_xy(HX+HL+3, VX+15);
			printf("\033[%d;%dm black gamer is winner!! \033[0m", RED, SGREEN);
			set_move_xy(HX, VX + 2*VBOX + 3);
			printf("\033[K");
			//sleep(5);
			exit(0);
		}else if (win == WHITE_CHESS){
			set_move_xy(HX+HL+3, VX+15);
			printf("\033[%d;%dm white gamer is winner!! \033[0m", BLUE, PURPLE);
			set_move_xy(HX, VX + 2*VBOX + 3);
			printf("\033[K");
			//sleep(5);
			exit(0);
		}else if(win == 0) {
			set_move_xy(HX, VX + 2*VBOX + 3);
			continue;
		}
			
		set_move_xy(HX, VX + 2*VBOX + 3);
	}	
	
	putchar('\n');
	return 0;
}

