#include "2048.h"

#include <stdio.h>

int main(void)
{
    srand(time(NULL));
    
    Board board = {0};
    addPoint(board);
    addPoint(board);
    // {
    //     {0, 1, 0, 0},
    //     {0, 1, 0, 0},
    //     {1, 1, 1, 1},
    //     {0, 1, 0, 0}
    // };

    uint64_t score = 0;

    while (!gameIsOver(board))
    {
        (void) system("clear");
        printf("Score: %lu\n", score);
        printBoard(board);

        // https://stackoverflow.com/a/11432632
        int c = getchar();
        if (c == 'q' || c == 'x')
            return 1;
        if (c != '\033')
            continue;
        getchar();
        if (!moveBoard(board, (Direction) getchar(), &score))
            continue;
        addPoint(board);
    }

    return 0;
}