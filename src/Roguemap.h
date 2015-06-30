#include <iostream>

const int SIZE = 40; /** between 40 and 60 **/

class Roguemap
{
	public:
		
		Roguemap();
		~Roguemap();
		
		void generate();
		
		void setSeed(int);
		int getSeed();
		
		void setRandom(bool);
		bool getRandom();
		
		void setRoomSize(int, int);
		void setRooms(int);
		
		void setCell(int, int, int);
		int getCell(int, int);
		
	private:
	
		int map[SIZE][SIZE];
		
		int seed;
		bool random;
		
		int min_size;
		int max_size;
		
		int rooms;
};

std::ostream &operator<<(std::ostream&, Roguemap);
