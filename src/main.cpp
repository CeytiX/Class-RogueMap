#include "Roguemap.cpp"

int main()
{
	Roguemap map;

	map.setRoomSize(8,10);
	map.setRooms(14);

	map.generate();
	cout << map;
	cout << map.getSeed() << endl;
	
	return 0;
}
