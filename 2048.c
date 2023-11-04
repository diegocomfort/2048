#include "2048.h"
#include <stdio.h>

bool addSpace(Board board)
{
    if (stateOf(board) != PLAYING)
        return false;

    int x, y;
    do
    {
        x = rand() % 4;
        y = rand() % 4;
    }
    while (board[y][x]);

    // 1 or 2
    board[y][x] = 1; 
    if (rand() % 100 < 25) ++board[y][x];
    
    return true;
}

GameState stateOf(const Board board)
{
    GameState state = LOST;
    for (int y = 0; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == (uint8_t) 11)                    // Reached 2048
                return WON;
            if ((board[y][x] == 0) ||                           // Blank space
                (y > 0 && board[y][x] == board[y - 1][x]) ||    // Move up
                (y < 3 && board[y][x] == board[y + 1][x]) ||    // Move down
                (x > 0 && board[y][x] == board[y][x - 1]) ||    // Move left
                (x < 3 && board[y][x] == board[y][x + 1]))      // Move right
                state = PLAYING;
        }
    }
    return state;
}

void printBoard(Board board)
{
    int paddSize = 8;
    for (int y = 0; y < 4; ++y)
    {
        printf("%.*s\n|", paddSize * 4 + 5, "---------------------------------------");
        for (int x = 0; x < 4; ++x)
        {
            if (board[y][x] == 0)
                printf("%.*s|", paddSize, "                  "); // prints `padSize` spaces
            else
                printf("%-*lu|", paddSize,  1UL << board[y][x]); // pow(2, board[y][x])
        }
        printf("\n");
    }
    printf("%.*s\n", paddSize * 4 + 5, "---------------------------------------");
}

bool moveLeft(Board board, uint64_t *score);
bool moveRight(Board board, uint64_t *score);
bool moveUp(Board board, uint64_t *score);
bool moveDown(Board board, uint64_t *score);

bool moveBoard(Board board, Direction d, uint64_t *score)
{
    switch (d)
    {
    case LEFT:
        return moveLeft(board, score);
    case RIGHT:
        return moveRight(board, score);
    case UP:
        return moveUp(board, score);
    case DOWN:
        return moveDown(board, score);
    default:
        return false;
    }
}

bool moveLeft(Board board, uint64_t *score)
{
    bool moveHasBeenMade = false;
    Board joinedBoxes = {0};    // Prevents a box being merged twice

    for (int y = 0; y < 4; ++y)
    {
        for (int x = 1; x < 4; ++x)
        {
            // Ignore blank blocks
            if (board[y][x] == 0)
                continue;

            // Go through blank space
            int newX = x; // new x value
            while (newX > 0 && board[y][newX - 1] == 0) --newX;
            if (newX == x) goto join; // prevents setting the current block to zero without moving it
            board[y][newX] = board[y][x];
            board[y][x] = 0;
            moveHasBeenMade = true;

            join: // Join two equal blocks
            if (newX == 0 || board[y][newX - 1] != board[y][newX] || joinedBoxes[y][newX - 1])
                continue;
            *score += 1UL << ++board[y][newX - 1];  // Add the merged tile to the score
            board[y][newX] = 0;
            joinedBoxes[y][newX - 1] = (uint8_t) true;
            moveHasBeenMade = true;
        }
    }
    return moveHasBeenMade;
}

bool moveRight(Board board, uint64_t *score)
{
    bool moveHasBeenMade = false;
    Board joinedBoxes = {0};

    for (int y = 0; y < 4; ++y)
    {
        for (int x = 2; x >= 0; --x)
        {
            // Ignore blank blocks
            if (board[y][x] == 0)
                continue;

            // Go through blank space
            int newX = x; // new x value
            while (newX < 3 && board[y][newX + 1] == 0) ++newX;
            if (newX == x) goto join; // prevents setting the current block to zero without moving it
            board[y][newX] = board[y][x];
            board[y][x] = 0;
            moveHasBeenMade = true;

            join: // Join two equal blocks
            if (newX == 3 || board[y][newX + 1] != board[y][newX] || joinedBoxes[y][newX + 1])
                continue;
            *score += 1UL << ++board[y][newX + 1];    // this will hold the logarithmic value (eg. 1 -> 2, 3 -> 8)
            board[y][newX] = 0;
            joinedBoxes[y][newX + 1] = (uint8_t) true;
            moveHasBeenMade = true;
        }
    }
    return moveHasBeenMade;
}

bool moveUp(Board board, uint64_t *score)
{
    bool moveHasBeenMade = false;
    Board joinedBoxes = {0};

    for (int y = 1; y < 4; ++y)
    {
        for (int x = 0; x < 4; ++x)
        {
            // Ignore blank blocks
            if (board[y][x] == 0)
                continue;

            // Go through blank space
            int newY = y;
            while (newY > 0 && board[newY - 1][x] == 0) --newY;
            if (y == newY) goto join;
            board[newY][x] = board[y][x];
            board[y][x] = 0;
            moveHasBeenMade = true;

            join: // Join two equal blocks
            if (newY == 0 || board[newY - 1][x] != board[newY][x] || joinedBoxes[newY - 1][x])
                continue;
            *score += 1UL << ++board[newY - 1][x];
            board[newY][x] = 0;
            joinedBoxes[newY - 1][x] = (uint8_t) true;
            moveHasBeenMade = true;
        }
    }
    
    return moveHasBeenMade;
}

bool moveDown(Board board, uint64_t *score)
{
    bool moveHasBeenMade = false;
    Board joinedBoxes = {0};

    for (int y = 2; y >= 0; --y)
    {
        for (int x = 0; x < 4; ++x)
        {
            // Ignore blank blocks
            if (board[y][x] == 0)
                continue;

            // Go through blank space
            int newY = y;
            while (newY < 3 && board[newY + 1][x] == 0) ++newY;
            if (y == newY) goto join;
            board[newY][x] = board[y][x];
            board[y][x] = 0;
            moveHasBeenMade = true;

            join: // Join two equal blocks
            if (newY == 3 || board[newY + 1][x] != board[newY][x] || joinedBoxes[newY + 1][x])
                continue;
            *score += 1UL << ++board[newY + 1][x];
            board[newY][x] = 0;
            joinedBoxes[newY + 1][x] = (uint8_t) true;
            moveHasBeenMade = true;
        }
    }
    
    return moveHasBeenMade;
}