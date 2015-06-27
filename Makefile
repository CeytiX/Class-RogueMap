CC = g++
FLAGS = -Wall
EXEC = WaterMapGenerator
EXEC2 = WallMapGenerator

all: water wall

water:
	$(CC) water_map_generator.cpp -o $(EXEC) $(FLAGS)

wall:
	$(CC) wall_map_generator.cpp -o $(EXEC2) $(FLAGS)
