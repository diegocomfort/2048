#ifndef GRAPHICS_2048_H
#define GRAPHICS_2048_H

#include <ncurses.h>

#define HEIGHT LINES
#define WIDTH COLS
#define COLOR_DEFAULT -1

typedef struct Box
{
    int height, width, y, x;
}
BOX;

WINDOW *createWindow(int, int, int, int);
int destroyWindow(WINDOW*);

int wmovemodin(WINDOW*, int, int);
#define movemodin(y, x) wmovemodin(stdscr, y, x)

int wmovemod(WINDOW*, int, int);
#define movemod(y, x) wmovemod(stdscr, y, x)

int wprintgrid(WINDOW*, int, int, int, int);
#define printgrid(h, w, y, x) wprintgrid(stdscr, h, w, y, x)

int wbackground(WINDOW*, int);
#define background(colorPairNumber) wbackground(stdscr, colorPairNumber)

#endif
