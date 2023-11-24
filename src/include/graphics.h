#ifndef GRAPHICS_2048_H
#define GRAPHICS_2048_H

#include <ncurses.h>

#define HEIGHT LINES
#define WIDTH COLS

#define MIN_HEIGHT 60
#define MIN_WIDTH  80

typedef struct Box
{
    int height, width, y, x;
}
BOX;

WINDOW *createWindow(const BOX*);
int destroyWindow(WINDOW*);

void wmovey(WINDOW*, const BOX*, int *, int, int);
void wmovex(WINDOW*, const BOX*, int*, int, int);
void wmoveyx(WINDOW*, const BOX*, int*, int, int*, int);

#endif
