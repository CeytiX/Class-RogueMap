#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include "Roguemap.h"

using namespace std;

/**************
* constructor *
**************/

Roguemap::Roguemap()
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			map[i][j] = 0;
		}
	}
	
	seed = 1;
	random = true;

	min_size = 6; /** insde: 5 **/
	max_size = 15; /** inside: 14 **/
	
	rooms = 3;
}

/*************
* destructor *
*************/

Roguemap::~Roguemap()
{
	/** void **/
}

/******************
* void generate() *
******************/

void Roguemap::generate()
{
	if(random) seed = time(0);
	srand(seed);
	
	/*********
	* ROOM 1 *
	*********/

	int xMin[rooms];
	int xMax[rooms];
	int yMin[rooms];
	int yMax[rooms];
	int width[rooms];
	int height[rooms];

	width[0] = rand()%(max_size-min_size+1) + min_size;
	height[0] = rand()%(min_size-min_size+1) + min_size;

	xMin[0] = rand()%(SIZE-width[0]-1);
	yMin[0] = rand()%(SIZE-height[0]-1);

	xMax[0] = xMin[0] + width[0];
	yMax[0] = yMin[0] + height[0];

	for(int i=xMin[0]; i<=xMax[0]; i++) /** place the walls of room 0 **/
	{
		map[i][yMin[0]]++;
		map[i][yMax[0]]++;
	}

	for(int j=yMin[0]+1; j<yMax[0]; j++) /** place the walls of room 0 **/
	{
		map[xMin[0]][j]++;
		map[xMax[0]][j]++;
	}
	
	for(int i=xMin[0]+1; i<xMax[0]; i++) /** place the ground of room 0 **/
		{
			for(int j=yMin[0]+1; j<yMax[0]; j++)
			{
				map[i][j] = 5;
			}
		}
	
	/***************
	* OTHERS ROOMS *
	***************/
	
	bool room[rooms];
	bool corridor[rooms];
	bool orientation[rooms];
	
	for(int i=0; i<rooms; i++)
	{
		room[i] = false;
		corridor[i] = true;
		orientation[i] = true;
	}
	 
	for(int k=1; k<rooms; k++)
	{
		int beginRoom;
		
		while(!room[k])
		{
			corridor[k] = true;
			
			beginRoom = rand()%k + 1;
			
			width[k] = rand()%(max_size-min_size+1) + min_size;
			height[k] = rand()%(max_size-min_size+1) + min_size;

			xMin[k] = rand()%(SIZE-width[k]-1);
			yMin[k] = rand()%(SIZE-height[k]-1);

			xMax[k] = xMin[k] + width[k];
			yMax[k] = yMin[k] + height[k];

			bool intersection = true;
		
			for(int i=(xMin[k]-2>=0)?xMin[k]-2:xMin[k]; i<=(xMax[k]+2<SIZE?xMax[k]+2:xMax[k]); i++)
			{
				for(int j=(yMin[k]-2>=0)?yMin[k]-2:yMin[k]; j<=(yMax[k]+2<SIZE?yMax[k]+2:yMax[k]); j++)
				{
					if(map[i][j] > 0)
					{
						intersection = false;
					}
				}
			}
		
			bool placed = false;
		
			if((xMax[k]>=xMin[k-beginRoom]+3 && xMax[k-beginRoom]>=xMin[k]+3) || (yMax[k]>=yMin[k-beginRoom]+3 && yMax[k-beginRoom]>=yMin[k]+3))
			{
				placed = true;
			}
			
			/****************
			* ROOM.corridor *
			****************/
	
			if(xMax[k]>=xMin[k-beginRoom]+3 && xMax[k-beginRoom]>=xMin[k]+3)
			{
				int y = (yMin[k-beginRoom] > yMax[k])?yMax[k]:yMax[k-beginRoom];
				int y2 = (yMin[k-beginRoom] > yMax[k])?yMin[k-beginRoom]:yMin[k];
				int x = (xMax[k-beginRoom] < xMax[k])?xMax[k-beginRoom]:xMax[k];
		
				for(int i=y+1; i<y2; i++)
				{
					if(map[x][i]>0 || map[x-2][i]>0)
					{
						corridor[k] = false;
					}
				}
			}
			else
			{
				int x = (xMin[k-beginRoom] > xMax[k])?xMax[k]:xMax[k-beginRoom];
				int x2 = (xMin[k-beginRoom] > xMax[k])?xMin[k-beginRoom]:xMin[k];
				int y = (yMax[k-beginRoom] < yMax[k])?yMax[k-beginRoom]:yMax[k];
		
				for(int i=x+1; i<x2; i++)
				{
					if(map[i][y]>0 || map[i][y-2]>0)
					{
						corridor[k] = false;
					}
				}
			}
			
			room[k] = intersection && placed && corridor[k];
		}
	
		/*************
		* ROOM.place *
		*************/
	
		/** place the walls **/
	
		for(int i=xMin[k]; i<=xMax[k]; i++) 
		{
			map[i][yMin[k]]++;
			map[i][yMax[k]]++;
		}

		for(int j=yMin[k]+1; j<yMax[k]; j++)
		{
			map[xMin[k]][j]++;
			map[xMax[k]][j]++;
		}
		
		for(int i=xMin[k]+1; i<xMax[k]; i++)
		{
			for(int j=yMin[k]+1; j<yMax[k]; j++)
			{
				map[i][j] = 5;
			}
		}
	
		/** place the corridor **/
	
		if(xMax[k]>=xMin[k-beginRoom]+3 && xMax[k-beginRoom]>=xMin[k]+3)
		{
			int y = (yMin[k-beginRoom] > yMax[k])?yMax[k]:yMax[k-beginRoom];
			int y2 = (yMin[k-beginRoom] > yMax[k])?yMin[k-beginRoom]:yMin[k];
			int x = (xMax[k-beginRoom] < xMax[k])?xMax[k-beginRoom]:xMax[k];

			for(int i=y; i<=y2; i++) /** place the walls of the corridor **/
			{
				map[x][i]++;
				map[x-2][i]++;
				orientation[k] = true;
			}
			
			for(int i=y+1; i<y2; i++) /** place the ground of the corridor **/
			{
				map[x-1][i] = 5;
			}
		}
		else
		{
			int x = (xMin[k-beginRoom] > xMax[k])?xMax[k]:xMax[k-beginRoom];
			int x2 = (xMin[k-beginRoom] > xMax[k])?xMin[k-beginRoom]:xMin[k];
			int y = (yMax[k-beginRoom] < yMax[k])?yMax[k-beginRoom]:yMax[k];

			for(int i=x; i<=x2; i++) /** place the walls of the corridor **/
			{
				map[i][y]++;
				map[i][y-2]++;
				orientation[k] = false;
			}
			
			for(int i=x+1; i<x2; i++) /** place the ground of the corridor **/
			{
				map[i][y-1] = 5;
			}
		}
		
		/** place the doors **/
	
		for(int i=0; i<SIZE; i++)
		{
			for(int j=0; j<SIZE; j++)
			{
				if(map[i][j] == 2)
				{
					if(map[i-2][j] == 2 && map[i-1][j] == 1 && orientation[k])
					{
						map[i][j] = map[i-2][j] = 1;
						map[i-1][j] = 3;
					}
					else if(map[i+2][j] == 2 && map[i+1][j] == 1 && orientation[k])
					{
						map[i][j] = map[i+2][j] = 1;
						map[i+1][j] = 3;
					}
					else if(map[i][j-2] == 2 && map[i][j-1] == 1 && !orientation[k])
					{
						map[i][j] = map[i][j-2] = 1;
						map[i][j-1] = 4;
					}
					else if(map[i][j+2] == 2 && map[i][j+1] == 1 && !orientation[k])
					{
						map[i][j] = map[i][j+2] = 1;
						map[i][j+1] = 4;
					}
				}
			}
		}
	}
}

/********************
* void setSeed(int) *
********************/

void Roguemap::setSeed(int value)
{
	seed = abs(value);
}

/****************
* int getSeed() *
****************/

int Roguemap::getSeed()
{
	return seed;
}

/***********************
* void setRandom(bool) *
***********************/

void Roguemap::setRandom(bool value)
{
	random = value;
}

/*******************
* bool getRandom() *
*******************/

bool Roguemap::getRandom()
{
	return random;
}

/****************************
* void setRoomSize(int, int) *
****************************/

void Roguemap::setRoomSize(int min, int max)
{
	min_size = ((min<max)?min:max)-1;
	max_size = ((min<max)?max:min)-1;
}

/*********************
* void setRooms(int) *
*********************/

void Roguemap::setRooms(int number)
{
	int max;
	
	if(SIZE>=40 && SIZE<45)
	{
		max = 4;
	}
	else if(SIZE>=45 && SIZE<50)
	{
		max = 5;
	}
	else if(SIZE>=50 && SIZE<55)
	{
		max = 7;
	}
	else if(SIZE>=55 && SIZE<60)
	{
		max = 9;
	}
	else if(SIZE==60)
	{
		max = 10;
	}
	
	if(number<=max)
	{
		rooms = number;
	}
	else
	{
		rooms = max;
	}
}

/******************************
* void setCell(int, int, int) *
******************************/

void Roguemap::setCell(int x, int y, int value)
{
	if(x>=0 && x<SIZE && y>=0 && y<SIZE && value>=0 && value<=5 && value!=2)
	{
		map[x][y] = value;
	}
}

/************************
* int getCell(int, int) *
************************/

int Roguemap::getCell(int x, int y)
{
	if(x>=0 && x<SIZE && y>=0 && y<SIZE)
	{
		return map[x][y];
	}
	else return -1;
}

/******************************************
* ostream &operator<<(ostream&, Roguemap) *
******************************************/
ostream &operator<<(ostream &stream, Roguemap roguemap)
{
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			switch(roguemap.getCell(j, i))
			{
				case 0:
					stream << ". ";
					break;
					
				case 1:
					stream << "# ";
					break;
				
				/** there isn't case 2 **/
					
				case 3:
					stream << "_ ";
					break;
					
				case 4:
					stream << "| ";
					break;
					
				case 5:
					stream << "\" ";
					break;
					
				default:
					stream << ". ";
					break;
			}
		}
		
		stream << endl;
	}
	
	return stream;
}

