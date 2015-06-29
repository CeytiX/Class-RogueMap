#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	/*******
	* INIT *
	********/

	int map[40][40] = {{0}};
	srand(time(0));
	
	/*********
	* ROOM 1 *
	*********/

	int xMin, xMax, yMin, yMax, width, height;

	width = rand()%10 + 6;
	height = rand()%10 + 6;

	xMin = rand()%(39-width);
	yMin = rand()%(39-height);

	xMax = xMin + width;
	yMax = yMin + height;

	for(int i=xMin; i<=xMax; i++)
	{
		map[i][yMin]++;
		map[i][yMax]++;
	}

	for(int j=yMin+1; j<yMax; j++)
	{
		map[xMin][j]++;
		map[xMax][j]++;
	}

	/*********
	* ROOM 2 *
	*********/

	int xMin_2, xMax_2, yMin_2, yMax_2, width_2, height_2;

	bool room_2(false);

	while(!room_2)
	{
		width_2 = rand()%10 + 6;
		height_2 = rand()%10 + 6;

		xMin_2 = rand()%(39-width_2);
		yMin_2 = rand()%(39-height_2);

		xMax_2 = xMin_2 + width_2;
		yMax_2 = yMin_2 + height_2;

		bool intersection = true;
		for(int i=(xMin_2-1>=0)?xMin_2-1:xMin_2; i<(xMax_2+1<40?xMax_2+1:xMax_2); i++)
		{
			for(int j=(yMin_2-1>=0)?yMin_2-1:yMin_2; j<(yMax_2+1<40?yMax_2+1:yMax_2); j++)
			{
				if(map[i][j] > 0)
				{
					intersection = false;
				}
			}
		}
		
		bool placed = false;
		if((xMax_2>=xMin+3 && xMax>=xMin_2+3) || (yMax_2>=yMin+3 && yMax>=yMin_2+3))
		{
			placed = true;
		}
		
		room_2 = intersection && placed;
	}
	
	for(int i=xMin_2; i<=xMax_2; i++)
	{
		map[i][yMin_2]++;
		map[i][yMax_2]++;
	}

	for(int j=yMin_2+1; j<yMax_2; j++)
	{
		map[xMin_2][j]++;
		map[xMax_2][j]++;
	}
	
	/******************
	* ROOM.corridor 2 *
	******************/
	
	bool corridor2;
	
	if(xMax_2>=xMin+3 && xMax>=xMin_2+3)
	{
		int y = (yMin > yMax_2)?yMax_2:yMax;
		int y2 = (yMin > yMax_2)?yMin:yMin_2;
		int x = (xMax < xMax_2)?xMax:xMax_2;
		
		for(int i=y; i<=y2; i++)
		{
			map[x][i]++;
			map[x-2][i]++;
			corridor2 = true;
		}
	}
	else
	{
		int x = (xMin > xMax_2)?xMax_2:xMax;
		int x2 = (xMin > xMax_2)?xMin:xMin_2;
		int y = (yMax < yMax_2)?yMax:yMax_2;
		
		for(int i=x; i<=x2; i++)
		{
			map[i][y]++;
			map[i][y-2]++;
			corridor2 = false;
		}
	}
	
	/**************
	* ROOM.door 2 *
	**************/
	
	for(int i=0; i<40; i++)
	{
		for(int j=0; j<40; j++)
		{
			if(map[i][j] == 2)
			{
				if(map[i-2][j] == 2 && map[i-1][j] == 1 && corridor2)
				{
					map[i][j] = map[i-2][j] = 1;
					map[i-1][j] = 3 ;
				}
				else if(map[i+2][j] == 2 && map[i+1][j] == 1 && corridor2)
				{
					map[i][j] = map[i+2][j] = 1;
					map[i+1][j] = 3;
				}
				else if(map[i][j-2] == 2 && map[i][j-1] == 1 && !corridor2)
				{
					map[i][j] = map[i][j-2] = 1;
					map[i][j-1] = 4;
				}
				else if(map[i][j+2] == 2 && map[i][j+1] == 1 && !corridor2)
				{
					map[i][j] = map[i][j+2] = 1;
					map[i][j+1] = 4;
				}
			}
		}
	}
	
	/********
	* PRINT *
	********/
	
	for(int i=0; i<40; i++)
	{
		for(int j=0; j<40; j++)
		{
			if(map[i][j] == 1)
			{
				cout << "# ";
			}
			else if(map[i][j] == 3)
			{
				cout << "| ";
			}
			else if(map[i][j] == 4)
			{
				cout << "_ ";
			}
			else
			{
				cout << ". ";
			}
		}

		cout << endl;
	}
	/******
	* END *
	******/

	return 0;
}
