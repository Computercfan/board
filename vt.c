#include "vt.h"


void set_attribute(int num)
{
	printf("\033[%dm", num);
}

/*col: 30~37*/
void set_fg_colour(int col)
{
	printf("\033[%dm", col);
}

/*col: 40~47*/
void set_bg_colour(int col)
{
	printf("\033[%dm", col);
}

/*设置光标位置*/
void set_move_xy(int x, int y)
{
	printf("\033[%d;%dH", y, x);
}

/*清屏*/
void clear_screen(void)
{
	printf("\033[2J");
}

/*保存光标位置*/
void save_cursor_xy(void)
{
	printf("\033[s");
}

/*恢复光标位置*/
void back_cursor_xy(void)
{
	printf("\033[u");
}

/*隐藏光标*/
void hidde_cursor(void)
{
	printf("\033[?25l");
}

/*显示光标*/
void show_cursor(void)
{
	printf("\033[?25h");
}

void putchar_xy(int x, int y, int ch)
{
	save_cursor_xy();
	set_move_xy(x, y);
	set_fg_colour(GREEN);
	putchar(ch);
	set_attribute(0);
	back_cursor_xy();
}

void set_bg_fg_colour(int bg, int fg)
{
	printf("\033[%d;%dm", bg+10, fg);
}

void draw_hline(int x, int y, int ch, int len)
{
	save_cursor_xy();
	set_move_xy(x, y);

	set_fg_colour(GREEN);
	while(len--) {
		putchar(ch);
	}
	set_attribute(0);
	back_cursor_xy();
}

void draw_vline(int x, int y, int ch, int len)
{
	int i;
	set_fg_colour(GREEN);
	save_cursor_xy();
	for (i = 0; i < len; i++) {
		set_move_xy(x, y+i);
		putchar(ch);
	}
	set_attribute(0);
	back_cursor_xy();
}
