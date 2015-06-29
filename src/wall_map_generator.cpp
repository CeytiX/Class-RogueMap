#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	/*******
	* INIT *
	********/
	const int SIZE = 50;
	const int MIN_ROOM = 6; /** walls included **/
	const int MAX_ROOM = 15; /** walls included **/
	
	int map[SIZE][SIZE] = {{0}};
	srand(time(0));
	
	/*********
	* ROOM 1 *
	*********/

	int xMin_1, xMax_1, yMin_1, yMax_1, width_1, height_1;

	width_1 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;
	height_1 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;

	xMin_1 = rand()%(SIZE-width_1-1);
	yMin_1 = rand()%(SIZE-height_1-1);

	xMax_1 = xMin_1 + width_1;
	yMax_1 = yMin_1 + height_1;

	for(int i=xMin_1; i<=xMax_1; i++)
	{
		map[i][yMin_1]++;
		map[i][yMax_1]++;
	}

	for(int j=yMin_1+1; j<yMax_1; j++)
	{
		map[xMin_1][j]++;
		map[xMax_1][j]++;
	}
	
	/*********
	* ROOM 2 *
	*********/

	int xMin_2, xMax_2, yMin_2, yMax_2, width_2, height_2;

	bool room_2(false);
	bool corridor_2(true);
	bool orientation_2;

	while(!room_2)
	{
		width_2 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;
		height_2 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;

		xMin_2 = rand()%(SIZE-width_2-1);
		yMin_2 = rand()%(SIZE-height_2-1);

		xMax_2 = xMin_2 + width_2;
		yMax_2 = yMin_2 + height_2;

		bool intersection = true;
		
		for(int i=(xMin_2-2>=0)?xMin_2-2:xMin_2; i<=(xMax_2+2<SIZE?xMax_2+2:xMax_2); i++)
		{
			for(int j=(yMin_2-2>=0)?yMin_2-2:yMin_2; j<=(yMax_2+2<SIZE?yMax_2+2:yMax_2); j++)
			{
				if(map[i][j] > 0)
				{
					intersection = false;
				}
			}
		}
		
		bool placed = false;
		
		if((xMax_2>=xMin_1+3 && xMax_1>=xMin_2+3) || (yMax_2>=yMin_1+3 && yMax_1>=yMin_2+3))
		{
			placed = true;
		}
		
		/******************
		* ROOM.corridor 2 *
		******************/
	
		if(xMax_2>=xMin_1+3 && xMax_1>=xMin_2+3)
		{
			int y = (yMin_1 > yMax_2)?yMax_2:yMax_1;
			int y2 = (yMin_1 > yMax_2)?yMin_1:yMin_2;
			int x = (xMax_1 < xMax_2)?xMax_1:xMax_2;
		
			for(int i=y+1; i<y2; i++)
			{
				if(map[x][i]>0 || map[x-2][i]>0)
				{
					corridor_2 = false;
					orientation_2 = true;
				}
			}
		}
		else
		{
			int x = (xMin_1 > xMax_2)?xMax_2:xMax_1;
			int x2 = (xMin_1 > xMax_2)?xMin_1:xMin_2;
			int y = (yMax_1 < yMax_2)?yMax_1:yMax_2;
		
			for(int i=x+1; i<x2; i++)
			{
				if(map[i][y]>0 || map[i][y-2]>0)
				{
					corridor_2 = false;
					orientation_2 = false;
				}
			}
		}
		
		room_2 = intersection && placed && corridor_2;
	}
	
	/**************
	* ROOM.place 2 *
	**************/
	
	/** place the walls **/
	
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
	
	/** place the corridor **/
	
	if(xMax_2>=xMin_1+3 && xMax_1>=xMin_2+3)
	{
		int y = (yMin_1 > yMax_2)?yMax_2:yMax_1;
		int y2 = (yMin_1 > yMax_2)?yMin_1:yMin_2;
		int x = (xMax_1 < xMax_2)?xMax_1:xMax_2;

		for(int i=y; i<=y2; i++)
		{
			map[x][i]++;
			map[x-2][i]++;
		}
	}
	else
	{
		int x = (xMin_1 > xMax_2)?xMax_2:xMax_1;
		int x2 = (xMin_1 > xMax_2)?xMin_1:xMin_2;
		int y = (yMax_1 < yMax_2)?yMax_1:yMax_2;

		for(int i=x; i<=x2; i++)
		{
			map[i][y]++;
			map[i][y-2]++;
		}
	}
	
	/** place the doors **/
	
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(map[i][j] == 2)
			{
				if(map[i-2][j] == 2 && map[i-1][j] == 1 && orientation_2)
				{
					map[i][j] = map[i-2][j] = 1;
					map[i-1][j] = 3;
				}
				else if(map[i+2][j] == 2 && map[i+1][j] == 1 && orientation_2)
				{
					map[i][j] = map[i+2][j] = 1;
					map[i+1][j] = 3;
				}
				else if(map[i][j-2] == 2 && map[i][j-1] == 1 && !orientation_2)
				{
					map[i][j] = map[i][j-2] = 1;
					map[i][j-1] = 4;
				}
				else if(map[i][j+2] == 2 && map[i][j+1] == 1 && !orientation_2)
				{
					map[i][j] = map[i][j+2] = 1;
					map[i][j+1] = 4;
				}
			}
		}
	}
	
	/*********
	* ROOM 3 *
	*********/

	int xMin_3, xMax_3, yMin_3, yMax_3, width_3, height_3;

	bool room_3(false);
	bool corridor_3(true);
	bool orientation_3;

	while(!room_3)
	{
		width_3 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;;
		height_3 = rand()%(MAX_ROOM-MIN_ROOM+1) + MIN_ROOM;;

		xMin_3 = rand()%(SIZE-width_3-1);
		yMin_3 = rand()%(SIZE-height_3-1);

		xMax_3 = xMin_3 + width_3;
		yMax_3 = yMin_3 + height_3;

		bool intersection = true;
		
		for(int i=(xMin_3-2>=0)?xMin_3-2:xMin_3; i<=(xMax_3+2<SIZE?xMax_3+2:xMax_3); i++)
		{
			for(int j=(yMin_3-2>=0)?yMin_3-2:yMin_3; j<=(yMax_3+2<SIZE?yMax_3+2:yMax_3); j++)
			{
				if(map[i][j] > 0)
				{
					intersection = false;
				}
			}
		}
		
		bool placed = false;
		
		if((xMax_3>=xMin_2+3 && xMax_2>=xMin_3+3) || (yMax_3>=yMin_2+3 && yMax_2>=yMin_3+3))
		{
			placed = true;
		}
		
		/******************
		* ROOM.corridor 3 *
		******************/
	
		if(xMax_3>=xMin_2+3 && xMax_2>=xMin_3+3)
		{
			int y = (yMin_2 > yMax_3)?yMax_3:yMax_2;
			int y2 = (yMin_2 > yMax_3)?yMin_2:yMin_3;
			int x = (xMax_2 < xMax_3)?xMax_2:xMax_3;
		
			for(int i=y+1; i<y2; i++)
			{
				if(map[x][i]>0 || map[x-2][i]>0)
				{
					corridor_3 = false;
					orientation_3 = true;
				}
			}
		}
		else
		{
			int x = (xMin_2 > xMax_3)?xMax_3:xMax_2;
			int x2 = (xMin_2 > xMax_3)?xMin_2:xMin_3;
			int y = (yMax_2 < yMax_3)?yMax_2:yMax_3;
		
			for(int i=x+1; i<x2; i++)
			{
				if(map[i][y]>0 || map[i][y-2]>0)
				{
					corridor_3 = false;
					orientation_3 = false;
				}
			}
		}
		
		room_3 = intersection && placed && corridor_3;
	}
	
	/**************
	* ROOM.place 3 *
	**************/
	
	/** place the walls **/
	
	for(int i=xMin_3; i<=xMax_3; i++) 
	{
		map[i][yMin_3]++;
		map[i][yMax_3]++;
	}

	for(int j=yMin_3+1; j<yMax_3; j++)
	{
		map[xMin_3][j]++;
		map[xMax_3][j]++;
	}
	
	/** place the corridor **/
	
	if(xMax_3>=xMin_2+3 && xMax_2>=xMin_3+3)
	{
		int y = (yMin_2 > yMax_3)?yMax_3:yMax_2;
		int y2 = (yMin_2 > yMax_3)?yMin_2:yMin_3;
		int x = (xMax_2 < xMax_3)?xMax_2:xMax_3;

		for(int i=y; i<=y2; i++)
		{
			map[x][i]++;
			map[x-2][i]++;
		}
	}
	else
	{
		int x = (xMin_2 > xMax_3)?xMax_3:xMax_2;
		int x2 = (xMin_2 > xMax_3)?xMin_2:xMin_3;
		int y = (yMax_2 < yMax_3)?yMax_2:yMax_3;

		for(int i=x; i<=x2; i++)
		{
			map[i][y]++;
			map[i][y-2]++;
		}
	}
	
	/** place the doors **/
	
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
		{
			if(map[i][j] == 2)
			{
				if(map[i-2][j] == 2 && map[i-1][j] == 1 && orientation_3)
				{
					map[i][j] = map[i-2][j] = 1;
					map[i-1][j] = 3;
				}
				else if(map[i+2][j] == 2 && map[i+1][j] == 1 && orientation_3)
				{
					map[i][j] = map[i+2][j] = 1;
					map[i+1][j] = 3;
				}
				else if(map[i][j-2] == 2 && map[i][j-1] == 1 && !orientation_3)
				{
					map[i][j] = map[i][j-2] = 1;
					map[i][j-1] = 4;
				}
				else if(map[i][j+2] == 2 && map[i][j+1] == 1 && !orientation_3)
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
	
	for(int i=0; i<SIZE; i++)
	{
		for(int j=0; j<SIZE; j++)
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
