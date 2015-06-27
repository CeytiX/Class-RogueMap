#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

int main()
{
	int map[40][40] = {0};
	srand(time(0));

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

	for(int j=yMin; j<=yMax; j++)
	{
		map[xMin][j]++;
		map[xMax][j]++;
	}

	for(int i=0; i<40; i++)
	{
		for(int j=0; j<40; j++)
		{
			if(map[i][j] == 1)
			{
				cout << "# ";
			}
			else if(map[i][j] == 2)
			{
				cout << "@ ";
			}
			else if(map[i][j] == 0)
			{
				cout << ". ";
			}
		}

		cout << endl;
	}

	return 0;
}
