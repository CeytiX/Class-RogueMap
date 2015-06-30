CC = g++
FLAGS = -Wall
EXEC = RogueMap

all:
	$(CC) src/main.cpp -o $(EXEC) $(FLAGS)

clean:
	rm $(EXEC)
