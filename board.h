#ifndef BOARD_H_
#define BOARD_H_

//#define CROSS	//此语句控制使用哪种键盘布局

/*
 * HX：棋普的左上角x坐标
 * VX：棋普的左上角y坐标
 */
#define HX 10 
#define VX 3

/*HBOX：棋普一行最多可以下落的棋子的位置总个数*/
/*VBOX: 棋普一列最多可以下落的棋子的位置总个数*/
#define HBOX 35
#define VBOX 15

#define HL (HBOX*2+HBOX+1) //30*2 + (30+1) = 91  
#define VL (VBOX*2+1) //15 + 15+1   = 31; 

/*画棋盘所需要的不同符号*/
#define BD0   '-'
#define BD1   '|'
#define BD2   '+'

/*用1 表示黑棋； 用2表示白棋*/           
enum {BLACK_CHESS = 1, WHITE_CHESS};

/* 棋谱左上角的坐标是(x,y)
 * hl: 一行总共占多少个字符位置
 * vl: 一列总共占多少个字符位置
 * */ 
extern void draw_board(int x, int y, int hl, int vl);
extern void fall_chessman(int x, int y, int who);

/*下面这个函数的x, y 表示棋手下棋的对应的坐标*/
extern int check_if_win(int x, int y);
extern void first_to_go(void);
extern int flag_who;                                                     
extern void login(void);

//根据棋盘，分配不同的数组空间
#ifdef CROSS
	extern char state[VBOX+1][HBOX+1];
#else
	extern char state[VBOX][HBOX];
#endif

#endif
















