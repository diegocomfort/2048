#include "2048.h"

#include <stdio.h>

int main(void)
{
    srand(time(NULL));
    
    Board board = {0};
    addSpace(board);
    addSpace(board);

    uint64_t score = 0;

    GameState state = PLAYING;

    while ((state = stateOf(board)) == PLAYING)
    {
        (void) system("clear");
        printBoard(board);

        char input = getchar();
        if (input == 'q' || input == 'x')
            return 0;

        if (input == 'h')
        {
            (void) system("clear");
            printf("Usage:\n"
                   "WASD to move\n"
                   "\'x\' or \'q\' to exit\n"
                   "Press <ENTER> to continue");
            getchar(); getchar();
            continue;
        }

        if (input == 'a' || input == 's' || input == 'd' || input == 'w')
        {
            if (moveBoard(board, (Direction) input, &score))
                addSpace(board);
        }
    }

    (void) system("clear");
    printf("Score: %lu\n", score);
    printBoard(board);
    if (state == LOST)
        printf("Game Over!\n");
    else
        printf("You Won!\n");

    return 0;
}