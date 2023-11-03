#include "2048.h"

#include <stdio.h>

int main(void)
{
    srand(time(NULL));
    
    Board board = {0};
    addSpace(board);
    addSpace(board);

    uint64_t score = 0;

    while (!gameIsOver(board))
    {
        (void) system("clear");
        printf("Score: %lu\n", score);
        printBoard(board);

        int c = getchar();
        if (c == 'q' || c == 'x')
            return 0;

        if (c == 'h')
        {
            printf("Usage:\n"
                   "WASD to move\n"
                   "\'x\' or \'q\' to exit");
            continue;
        }

        if (c == 'a' || c == 's' || c == 'd' || c == 'w')
        {
            if (moveBoard(board, (Direction) c, &score))
                addSpace(board);
        }
    }

    (void) system("clear");
    printf("Score: %lu\n", score);
    printBoard(board);
    printf("Game Over!");

    return 0;
}