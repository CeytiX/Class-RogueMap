CC = g++
FLAGS = -Wall
EXEC = WaterMapGenerator
EXEC2 = WallMapGenerator

all: water

water:
	$(CC) src/water_map_generator.cpp -o $(EXEC) $(FLAGS)

wall:
	$(CC) src/wall_map_generator.cpp -o $(EXEC2) $(FLAGS)
