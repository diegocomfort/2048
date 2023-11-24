#include "include/graphics.h"
#include "include/math.h"

WINDOW *createWindow(const BOX *windowBox)
{
    if (windowBox == NULL)
        return NULL;
    WINDOW *window = newwin(windowBox->height, windowBox->width, windowBox->y, windowBox->x);
    box(window, 0, 0);
    wrefresh(window);
    return window;
}

int destroyWindow(WINDOW *window)
{
    if (window == NULL)
        return 1;
    wborder(window, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(window);
    return delwin(window);
}

void wmovey(WINDOW *window, const BOX *windowBox, int *y, int dy, int dx)
{
    if (window == NULL ||y == NULL || windowBox == NULL ||
        dy >= windowBox->height || dx >= windowBox->width ||
        dy == 0)
        return;
    int x = getcurx(window);
    if (*y + dy >= windowBox->y + windowBox->height)
        wmovex(window, windowBox, &x, dx, 0);
    *y = modRange(*y, windowBox->y, windowBox->height);
    wmove(window, *y, x);
}

void wmovex(WINDOW *window, const BOX *windowBox, int *x, int dx, int dy)
{
    if (window == NULL ||x == NULL || windowBox == NULL ||
        dy >= windowBox->height || dx >= windowBox->width ||
        dx == 0)
        return;
    int y = getcury(window);
    if (*x + dx >= windowBox->x + windowBox->width)
        wmovey(window, windowBox, &y, dy, 0);
    *x = modRange(*x, windowBox->x, windowBox->width);
}

void wmoveyx(WINDOW *window, const BOX *windowBox, int *y, int dy, int *x, int dx)
{
    wmovey(window, windowBox, y, dy, dx);
    wmovex(window, windowBox, x, dx, dy);
}
