#ifndef GAME_2048_H
#define GAME_2048_H

#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

typedef enum 
{
    LEFT = 'a',
    RIGHT = 'd',
    UP = 'w',
    DOWN = 's',
}
Direction;

typedef enum
{
    PLAYING,
    LOST,
    WON,
}
GameState;

#define Y 4
#define X 4
// Holds the logarithmic values of the board
typedef uint8_t Board[Y][X];

bool addSpace(Board board);

GameState stateOf(const Board board);

void printBoard(Board board);

bool moveBoard(Board board, Direction d, uint64_t *score);

#endif