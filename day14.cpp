#include <iostream>
#include <vector>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
struct robot { int x, y, dx, dy; };

int main( void )
{
	const int width = 101;
	const int height = 103;
	string skp;
	vector<robot> robots;
    while (!cin.eof()) {
		robot rob; getline(cin, skp, '=');
		cin >> rob.x; cin.ignore(1, ' ');
		cin >> rob.y; getline(cin, skp, '=');
		cin >> rob.dx; cin.ignore(1, ' ');
		cin >> rob.dy; cin.ignore();
		robots.push_back(rob);
	}

	// part 2 sucked ass.
	for (int time = 1; time <= 10000; ++time) {
		string grid(width * height, '.');
		for (auto& rob : robots) {
			rob.x += rob.dx;
			rob.y += rob.dy;
			if (rob.x < 0) rob.x += width;
			else if (rob.x >= width) rob.x -= width;
			if (rob.y < 0) rob.y += height;
			else if (rob.y >= height) rob.y -= height;
			grid[rob.x + rob.y * width] = '#';
		}
		LOGND("TIME " << time);
		for (int i = 0; i < height; ++i) LOGND(grid.substr(i * width, width));
    }
}