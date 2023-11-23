CC = clang
FLAGS = -Weverything -ggdb3
DIST = dist
SRC = src
INCL = src/include

all: $(DIST)/main

$(DIST)/main: $(DIST)/main.o $(DIST)/game.o $(INCL)/game.h
	gcc -o $@ $^

# .c to .o
$(DIST)/%.o: $(SRC)/%.c
	gcc -c $< -o $@

run: $(DIST)/main
	./$(DIST)/main

clean:
	rm -f dist/*

reset: clean all