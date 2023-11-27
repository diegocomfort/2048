# 2048
Just me trying to make [2048](https://play2048.co/) in C

## Installation
1. Install dependancies (most people already have clang and make installed)
    - [ncurses](https://invisible-island.net/ncurses/) (`sudo pacman -S ncurses`) (`sudo apt install ncurses`)
    - [make](https://www.gnu.org/software/make/) (`sudo pacman -S make`) (`sudo apt install make`)
    - [clang](https://clang.llvm.org/) (`sudo pacman -S clang`) (`sudo apt install clang`)
2. Clone this repository
    ```
    git clone https://github.com/diegocomfort/2048
    cd 2048/
    ```
3. Build it\
    Note: you can use `gcc` or whatever compiler you want, but be sure to check it allows `-Weverything` or change it to `-Wall` or whatever warnings you want in `Makefile`
    ```
    make
    ```
4. Have fun!\
    Arrow keys to move; try and reach 2048
    ```
    make run
    ```

## TODO
- Force colors to be the correct ones, not user/terminal defined
- Show Win & Lose screen
- Usage section & page in-game
- Command-line args for --help, etc.?
