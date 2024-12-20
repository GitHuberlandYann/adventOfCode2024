#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int width, height, res;
int startX, startY, normalDist;
string grid;
vector<int> dists;

static void genMapping( int x, int y, int steps )
{
	if (grid[x + y * width] == '#') return ;
	if (dists[x + y * width] != -1) return ;
	if (grid[x + y * width] == 'S') startX = x, startY = y, normalDist = steps;
	dists[x + y * width] = steps;
	genMapping(x - 1, y, steps + 1);
	genMapping(x + 1, y, steps + 1);
	genMapping(x, y - 1, steps + 1);
	genMapping(x, y + 1, steps + 1);
}

static void genShortCuts( int x, int y, int steps )
{
	if (grid[x + y * width] == '#') return ;
	grid[x + y * width] = '#';
	int minValue = normalDist;
	for (int dx = -20; dx < 21; ++dx) {
		if (x + dx < 1 || x + dx >= width - 1) continue ;
		for (int dy = -20; dy < 21; ++dy) {
			if (y + dy < 1 || y + dy >= height - 1) continue ;
			if (abs(dx) + abs(dy) > 20) continue ;
			if (grid[x + dx + (y + dy) * width] == '#') continue ;
			if (dists[x + dx + (y + dy) * width] + steps + abs(dx) + abs(dy) <= normalDist - 100) ++res;
			//if (dists[x + dx + (y + dy) * width] < minValue) minValue = dists[x + dx + (y + dy) * width];
		}
	}
	//if (minValue + steps < normalDist - 51) ++res;
	//res += (x > 1 && grid[x - 1 + y * width] == '#' && grid[x - 2 + y * width] != '#' && dists[x - 2 + y * width] + steps < normalDist - 101)
	//	+ (x < width - 2 && grid[x + 1 + y * width] == '#' && grid[x + 2 + y * width] != '#' && dists[x + 2 + y * width] + steps < normalDist - 101)
	//	+ (y > 1 && grid[x + (y - 1) * width] == '#' && grid[x + (y - 2) * width] != '#' && dists[x + (y - 2) * width] + steps < normalDist - 101)
	//	+ (y < height - 2 && grid[x + (y + 1) * width] == '#' && grid[x + (y + 2) * width] != '#' && dists[x + (y + 2) * width] + steps < normalDist - 101);
	genShortCuts(x - 1, y, steps + 1);
	genShortCuts(x + 1, y, steps + 1);
	genShortCuts(x, y - 1, steps + 1);
	genShortCuts(x, y + 1, steps + 1);
}

int main( void )
{
	int x = -1, y;
	string line;
    while (getline(cin, line)) {
		grid.append(line);
		if (x == -1 && (x = line.find('E')) != string::npos) y = height;
		if (!width) width = line.size();
		++height;
	}

	dists.resize(width * height, -1);
	genMapping(x, y, 0);
	LOGND("normal dist from " << startX << ' ' << startY << " to " << x << ' ' << y << ": " << normalDist);
	genShortCuts(startX, startY, 0);

    OUT(res << endl);
}