/**
 * ========================
 * 
 * Filename: water_map_generator.cpp
 * 
 * Author: Ceytix <ceytix@mailoo.org>
 * 
 * Description: This generator creates a map with a variable size.
 *              It creates 4 boats randomly on the map and then it displays the map.
 * 
 * Created: 27/06/15
 * =========================
 **/
 
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

const int SIZE = 10; /** height and width of the map **/

int main()
{
	srand(time(0));
	
	int map[SIZE][SIZE] = {{0}};
	
	/** boat 1 **/
	bool boat1 = false;
	while(!boat1)
	{
		int direction = rand()%2 + 1;
		int x(SIZE+1), y(SIZE+1);
		if(direction == 1)
		{
			do
			{
				x = rand()%SIZE;
				y = rand()%(SIZE-4) + 2;
			} while(map[x][y-2]!=0 || map[x][y-1]!=0 || map[x][y]!=0 || map[x][y+1]!=0 || map[x][y+2]!=0);
			
			map[x][y-2] = 1;
			map[x][y-1] = 1;
			map[x][y] = 1;
			map[x][y+1] = 1;
			map[x][y+2] = 1;
			
			boat1 = true;
		}
		else
		{
			do
			{
				x = rand()%(SIZE-4) + 2;
				y = rand()%SIZE;
			} while(map[x-2][y]!=0 || map[x-1][y]!=0 || map[x][y]!=0 || map[x+1][y]!=0 || map[x+2][y]!=0);
			
			map[x-2][y] = 1;
			map[x-1][y] = 1;
			map[x][y] = 1;
			map[x+1][y] = 1;
			map[x+2][y] = 1;
			
			boat1 = true;
		}
	}
	/** end boat 1 **/
	
	/** boat 2 **/
	bool boat2 = false;
	while(!boat2)
	{
		int direction = rand()%2 + 1;
		int x(SIZE+1), y(SIZE+1);
		if(direction == 1)
		{
			do
			{
				x = rand()%SIZE;
				y = rand()%(SIZE-3) + 2;
			} while(map[x][y-2]!=0 || map[x][y-1]!=0 || map[x][y]!=0 || map[x][y+1]!=0);
			
			map[x][y-2] = 2;
			map[x][y-1] = 2;
			map[x][y] = 2;
			map[x][y+1] = 2;
			
			boat2 = true;
		}
		else
		{
			do
			{
				x = rand()%(SIZE-3) + 2;
				y = rand()%SIZE;
			} while(map[x-2][y]!=0 || map[x-1][y]!=0 || map[x][y]!=0 || map[x+1][y]!=0);
			
			map[x-2][y] = 2;
			map[x-1][y] = 2;
			map[x][y] = 2;
			map[x+1][y] = 2;
			
			boat2 = true;
		}
	}
	/** end boat 2 **/
	
	/** boat 3 **/
	bool boat3 = false;
	while(!boat3)
	{
		int direction = rand()%2 + 1;
		int x(SIZE+1), y(SIZE+1);
		if(direction == 1)
		{
			do
			{
				x = rand()%SIZE;
				y = rand()%(SIZE-2) + 1;
			} while(map[x][y-1]!=0 || map[x][y]!=0 || map[x][y+1]!=0);
			
			map[x][y-1] = 3;
			map[x][y] = 3;
			map[x][y+1] = 3;
			
			boat3 = true;
		}
		else
		{
			do
			{
				x = rand()%(SIZE-2) + 1;
				y = rand()%SIZE;
			} while(map[x-1][y]!=0 || map[x][y]!=0 || map[x+1][y]!=0);
			
			map[x-1][y] = 3;
			map[x][y] = 3;
			map[x+1][y] = 3;
			
			boat3 = true;
		}
	}
	/** end boat 3 **/
	
	/** boat 4 **/
	bool boat4 = false;
	while(!boat4)
	{
		int direction = rand()%2 + 1;
		int x(SIZE+1), y(SIZE+1);
		if(direction == 1)
		{
			do
			{
				x = rand()%SIZE;
				y = rand()%(SIZE-1) + 1;
			} while(map[x][y-1]!=0 || map[x][y]!=0);
			
			map[x][y-1] = 4;
			map[x][y] = 4;
			
			boat4 = true;
		}
		else
		{
			do
			{
				x = rand()%(SIZE-1) + 1;
				y = rand()%SIZE;
			} while(map[x-1][y]!=0 || map[x][y]!=0);
			
			map[x-1][y] = 4;
			map[x][y] = 4;
			
			boat4 = true;
		}
	}
	/** end boat 4 **/
	
	/** display of the map **/
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(map[i][j] == 1)
				cout << "#";
			else if(map[i][j] == 2)
				cout << "@";
			else if(map[i][j] == 3)
				cout << "&";
			else if(map[i][j] == 4)
				cout << "$";
			else
				cout << ".";
		}
		cout << endl;
	}
	
	return 0;
}
