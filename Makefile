CC = clang
FLAGS = -Weverything -ggdb3 
LINK = -lncurses
DIST = dist
SRC = src
INCL = src/include

all: $(DIST)/main

$(DIST)/main: $(DIST)/main.o $(DIST)/game.o $(DIST)/graphics.o $(DIST)/math.o
	$(CC) -o $@ $^ $(FLAGS) $(LINK)

$(DIST)/main.o: $(SRC)/main.c

# .c to .o
$(DIST)/%.o: $(SRC)/%.c
	$(CC) -o $@ -c $< $(FLAGS)

run: $(DIST)/main
	./$(DIST)/main

clean:
	rm -f dist/*

reset: clean all