#ifndef ANSIC_CODE_H_
#define ANSIC_CODE_H_

#include <stdio.h>

//设置颜色的一个枚举
enum {
	BLACK=30,RED,GREEN,YELLOW,BLUE,PURPLE,SGREEN,WHITE
};

/*vt.c中的所有的函数声明*/
extern void set_attribute(int num);
extern void set_fg_colour(int col);
extern void set_bg_colour(int col);
extern void set_move_xy(int x, int y);
extern void clear_screen(void);
extern void save_cursor_xy(void);
extern void back_cursor_xy(void);
extern void hidde_cursor(void);
extern void show_cursor(void);
extern void putchar_xy(int x, int y, int ch);
extern void set_bg_fg_colour(int bg, int fg);
extern void draw_hline(int x, int y, int ch, int len);
extern void draw_vline(int x, int y, int ch, int len);

#endif
