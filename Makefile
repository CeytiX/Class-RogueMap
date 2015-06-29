CC = g++
FLAGS = -Wall
EXEC = WaterMapGenerator
EXEC2 = RogueMap

all: water wall

water:
	$(CC) src/water_map_generator.cpp -o $(EXEC) $(FLAGS)

wall:
	$(CC) src/main.cpp -o $(EXEC2) $(FLAGS)

clean:
	rm $(EXEC) $(EXEC2)
