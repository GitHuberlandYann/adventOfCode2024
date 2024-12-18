#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
const int width = 71;
const int bytes = 1024;
string grid(width * width, '.'), ogrid;

static bool solve( int x, int y, int steps, vector<array<int, 2>>& next )
{
	if (ogrid[x + y * width] != '.') return false;
	if (x == width - 1 && y == width - 1) {
		OUT("exit reached in " << steps << " steps" << endl);
		ogrid[x + y * width] = 'X';
		//for (int i = 0; i < width; ++i) LOGND(ogrid.substr(i * width, width));
		return true;
	}
	ogrid[x + y * width] = '0' + steps % 10;
	if (x) next.push_back({x - 1, y});
	if (x < width - 1) next.push_back({x + 1, y});
	if (y) next.push_back({x, y - 1});
	if (y - width - 1) next.push_back({x, y + 1});
	return false;
}

static bool reachableExit( void )
{
	vector<array<int, 2>> next{{0, 0}}, onext;
	int steps = 0;
	ogrid = grid;
	for (bool flip = false; !(flip ? onext : next).empty(); flip = !flip, ++steps) {
		for (auto [x, y] : flip ? onext : next) if (solve(x, y, steps, flip ? next : onext)) return true;
		(flip ? onext : next).clear();
	}
    return false;
}

int main( void )
{
    for (int i = 0, x, y; i < bytes; ++i) {
		cin >> x; cin.ignore(1, ' ');
		cin >> y;
		grid[x + y * width] = '#';
	}
	for (int i = 0; i < width; ++i) LOGND(grid.substr(i * width, width));

	while (!cin.eof()) {
		int x, y;
		cin >> x; cin.ignore(1, ' ');
		cin >> y;
		grid[x + y * width] = '#';
		if (!reachableExit()) {
			OUT(x << ',' << y << endl);
			break ;
		}
	}
}