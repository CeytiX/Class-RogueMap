#include "Roguemap.cpp"

int main()
{
	Roguemap map;

	map.generate();

	cout << map;
	cout << map.getSeed() << endl;
	
	return 0;
}
