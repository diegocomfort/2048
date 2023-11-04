CC = gcc
FLAGS = -Wall -Wextra
DIST = dist

all: $(DIST)/main

$(DIST)/main: $(DIST)/main.o $(DIST)/2048.o 2048.h
	gcc -o $@ $^

# .c to .o
$(DIST)/%.o: %.c
	gcc -c $< -o $@

run: $(DIST)/main
	./$(DIST)/main

clean:
	rm -f dist/*

reset: clean all run