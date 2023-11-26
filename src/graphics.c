#include "include/graphics.h"
#include "include/math.h"

#include <ncurses.h>

WINDOW *createWindow(int height, int width, int y, int x)
{
    WINDOW *window = newwin(height, width, y, x);
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

int wmovemodin(WINDOW *window, int y, int x)
{
    int height, width, yOrigin, xOrigin;
    getbegyx(window, yOrigin, xOrigin);
    getmaxyx(window, height, width);

    y = modRange(y, yOrigin + 1, height);
    x = modRange(x, xOrigin + 1, width);

    return wmove(window, y, x);
}

int wmovemod(WINDOW *window, int y, int x)
{
    int height, width, yOrigin, xOrigin;
    getbegyx(window, yOrigin, xOrigin);
    getmaxyx(window, height, width);

    y = modRange(y, yOrigin, height);
    x = modRange(x, xOrigin, width);

    return wmove(window, y, x);
}

int wprintgrid(WINDOW *window, 
                int heightOfInnerSquare, 
                int widthOfInnerSquare, 
                int verticalBoxes, 
                int horizontalBoexs)
{
    const int   h = heightOfInnerSquare, 
                w = widthOfInnerSquare,
                y = verticalBoxes,
                x = horizontalBoexs,
                totalY = 1 + (h + 1) * y,
                totalX = 1 + (w + 1) * x;
    int initialY, initialX;
    getyx(window, initialY, initialX);
    
    if ((x < 1) || (y < 1) || (w < 1) || (h < 1) || (initialX + totalX >= WIDTH) || (initialX + totalY >= HEIGHT))
        return -1;

    for (int i = 0; i < totalY; ++i) 
    {
        waddch(window, (i == 0) ? ACS_ULCORNER
                                : (i == totalY - 1) ? ACS_LLCORNER
                                                    : (i % (h + 1) == 0) ? ACS_LTEE
                                                                  : ACS_VLINE);
        for (int j = 0; j < x; ++j)
        {
            for (int k = 0; k < w; ++k)
                waddch(window, (i % (h + 1) == 0) ? ACS_HLINE 
                                                  : ' ');
            if (j != x - 1)
                waddch(window, (i == 0) ? ACS_TTEE 
                                        : (i == totalY - 1) ? ACS_BTEE 
                                                            : (i % (h + 1) == 0) ? ACS_PLUS 
                                                                                 : ACS_VLINE);
        }
        waddch(window, (i == 0) ? ACS_URCORNER
                                : (i == totalY - 1) ? ACS_LRCORNER
                                                    : (i % (h + 1) == 0) ? ACS_RTEE
                                                                  : ACS_VLINE);
        wmove(window, ++initialY, initialX);
    }

    return 0;
}

int wbackground(WINDOW* window, int colorPairNumber)
{
    int h, w, y, x;
    getbegyx(window, y, x);
    getmaxyx(window, h, w);

    wattron(window, COLOR_PAIR(colorPairNumber));
    for (int i = 0; i < h; ++i)
    {
        for (int j = 0; j < w; ++j)
        {
            waddch(window, ' ');
        }
    }
    wattroff(window, COLOR_PAIR(colorPairNumber));
}
