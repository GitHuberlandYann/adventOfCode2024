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
	long tr = 0, tl = 0, br = 0, bl = 0;
	string skp;
    while (!cin.eof()) {
		robot rob; getline(cin, skp, '=');
		cin >> rob.x; cin.ignore(1, ' ');
		cin >> rob.y; getline(cin, skp, '=');
		cin >> rob.dx; cin.ignore(1, ' ');
		cin >> rob.dy; cin.ignore();
		rob.x = (rob.x + rob.dx * 100) % width;
		rob.y = (rob.y + rob.dy * 100) % height;
		while (rob.x < 0) rob.x += width;
		while (rob.y < 0) rob.y += height;
		if (rob.x == width / 2 || rob.y == height / 2) continue ;
		int quadrant = (rob.x < width / 2 ? 1 : 2) + (rob.y < height / 2 ? 4 : 8);
		switch (quadrant) {
			case 0b0101: ++tl; break ;
			case 0b0110: ++tr; break ;
			case 0b1001: ++bl; break ;
			case 0b1010: ++br; break ;
		}
    }
	LOGND("tr " << tr << " tl " << tl << " br " << br << " bl " << bl);
    OUT(tr * tl * br * bl << endl);
}