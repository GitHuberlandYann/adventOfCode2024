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
string grid(width * width, '.');

static void solve( int x, int y, int steps, vector<array<int, 2>>& next )
{
	if (grid[x + y * width] != '.') return ;
	if (x == width - 1 && y == width - 1) {
		OUT("exit reached in " << steps << " steps" << endl);
		grid[x + y * width] = 'X';
		for (int i = 0; i < width; ++i) LOGND(grid.substr(i * width, width));
		exit(0);
	}
	grid[x + y * width] = '0' + steps % 10;
	if (x) next.push_back({x - 1, y});
	if (x < width - 1) next.push_back({x + 1, y});
	if (y) next.push_back({x, y - 1});
	if (y - width - 1) next.push_back({x, y + 1});
}

int main( void )
{
    for (int i = 0, x, y; i < bytes; ++i) {
		cin >> x; cin.ignore(1, ' ');
		cin >> y;
		grid[x + y * width] = '#';
	}
	for (int i = 0; i < width; ++i) LOGND(grid.substr(i * width, width));
	int cnt = 0;
	for (auto c : grid) cnt += c == '#';
	LOGND("cnt " << cnt << " # found") << endl;

	vector<array<int, 2>> next{{0, 0}}, onext;
	int steps = 0;
	for (bool flip = false; !(flip ? onext : next).empty(); flip = !flip, ++steps) {
		for (auto [x, y] : flip ? onext : next) solve(x, y, steps, flip ? next : onext);
		(flip ? onext : next).clear();
	}
    OUT("EXIT NOT FOUND" << endl);
}