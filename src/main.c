#include "include/graphics.h"
#include "include/math.h"
#include "include/game.h"

#include <string.h>
#include <stdlib.h>
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <stdbool.h>
#include <stdio.h>

#define LOGO_HEIGHT 7
#define LOGO_WIDTH 41

#define BOARD_TILE_HEIGHT 3
#define BOARD_TILE_WIDTH  7
#define BOARD_HEIGHT ((BOARD_TILE_HEIGHT + 1) * X + 1)
#define BOARD_WIDTH  ((BOARD_TILE_WIDTH  + 1) * X + 1)

#define MIN_HEIGHT (2 + LOGO_HEIGHT + 1 + BOARD_HEIGHT)
#define MIN_WIDTH  (2 + ((LOGO_WIDTH > BOARD_WIDTH) ? LOGO_WIDTH : BOARD_WIDTH))

int arrowToWASD(int);

int main(void)
{
    int w, h, y, x;
    const char logo[LOGO_HEIGHT][LOGO_WIDTH] = {"  22222      00000        4   4     888  ",
                                                " 2    22   0       0     4    4   8     8",
                                                "      22   0       0    4     4   8     8",
                                                "     22    0       0   44444444     888  ",
                                                "   22      0       0          4   8     8",
                                                " 22        0       0          4   8     8",
                                                "22222222     00000            4     888  "};

    (void) initscr();
    
    if (WIDTH < MIN_WIDTH || HEIGHT < MIN_HEIGHT)
    {
        endwin();
        printf("Please make the screen at least %ix%i characters (WxH)\n"
               "Your screen is currently %ix%i characters\n",
               MIN_WIDTH, MIN_HEIGHT, WIDTH, HEIGHT);
        return 1;
    }

    if (!has_colors())
    {
        endwin();
        printf("Your terminal doesn't support colors :(\n");
        return 2;
    }

    srand(time(NULL));
    Board board = {0};
    addSpace(board); addSpace(board);

    uint64_t score = 0;
    GameState state = PLAYING;

    start_color();
    use_default_colors();
    init_color(COLOR_WHITE, 1000, 1000, 1000);
    init_color(COLOR_BLACK, 0, 0, 0);
    init_pair(1,  COLOR_WHITE,      COLOR_BLACK);  // Default
    init_pair(2,  COLOR_YELLOW,     COLOR_BLACK); // LOGO
    init_pair(3,  COLOR_DEFAULT,    COLOR_BLACK); // Tiles
    init_pair(4,  COLOR_YELLOW,     COLOR_BLACK); //   |
    init_pair(5,  COLOR_RED,        COLOR_BLACK); //   V
    init_pair(6,  COLOR_MAGENTA,    COLOR_BLACK);
    init_pair(7,  COLOR_CYAN,       COLOR_BLACK);
    init_pair(8,  COLOR_BLUE,       COLOR_BLACK);
    init_pair(9,  COLOR_GREEN,      COLOR_BLACK);
    init_pair(10, COLOR_DEFAULT,    COLOR_BLACK);
    init_pair(11, COLOR_DEFAULT,    COLOR_RED);
    init_pair(12, COLOR_DEFAULT,    COLOR_MAGENTA);
    //attron(A_BOLD);

    raw();
    noecho();
    keypad(stdscr, true);
    curs_set(0);
    background(1);
    refresh();

    do
    {
        attron(COLOR_PAIR(2));
        move(y = (HEIGHT - (3 + LOGO_HEIGHT + BOARD_HEIGHT)) / 2, x = (WIDTH - LOGO_WIDTH) / 2);
        for (int i = 0; i < LOGO_HEIGHT; ++i)
        {
            for (int j = 0; j < LOGO_WIDTH; ++j)
                addch(logo[i][j]);
            move (++y, x);
        }
        attroff(COLOR_PAIR(2));

        move(++y, x = (WIDTH - BOARD_WIDTH) / 2);
        attron(COLOR_PAIR(1));
        printgrid(BOARD_TILE_HEIGHT, BOARD_TILE_WIDTH, Y, X);
        attroff(COLOR_PAIR(1));
        
        move(y, x);
        for (int i = 0; i < Y; ++i)
        {
            for (int j = 0; j < X; ++j)
            {
                if (board[i][j] == 0)
                    continue;
                attron(COLOR_PAIR(2 + board[i][j]));
                mvprintw(y + 1 + (1 + BOARD_TILE_HEIGHT) * i + BOARD_TILE_HEIGHT / 2, 
                         x + 1 + (1 + BOARD_TILE_WIDTH) * j + (BOARD_TILE_WIDTH - digits(board[i][j])) / 2,
                         "%lu", 1UL << board[i][j]);
                attroff(COLOR_PAIR(2 + board[i][j]));
                
            }
        }

        int input = getch();

        if (input == 'q')
            break;

        if (moveBoard(board, (Direction) arrowToWASD(input), &score))
            addSpace(board);
    }
    while ((state = stateOf(board)) == PLAYING);  
    
    getch();
    endwin();

    return 0;
}

int arrowToWASD(int arrowCode)
{
    switch (arrowCode)
    {
    case KEY_UP: return 'w';
    case KEY_DOWN: return 's';
    case KEY_LEFT: return 'a';
    case KEY_RIGHT: return 'd';
    default: return 0;
    }
}
