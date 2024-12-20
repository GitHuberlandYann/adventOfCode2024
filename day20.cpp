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
	res += (x > 1 && grid[x - 1 + y * width] == '#' && grid[x - 2 + y * width] != '#' && dists[x - 2 + y * width] + steps < normalDist - 101)
		+ (x < width - 2 && grid[x + 1 + y * width] == '#' && grid[x + 2 + y * width] != '#' && dists[x + 2 + y * width] + steps < normalDist - 101)
		+ (y > 1 && grid[x + (y - 1) * width] == '#' && grid[x + (y - 2) * width] != '#' && dists[x + (y - 2) * width] + steps < normalDist - 101)
		+ (y < height - 2 && grid[x + (y + 1) * width] == '#' && grid[x + (y + 2) * width] != '#' && dists[x + (y + 2) * width] + steps < normalDist - 101);
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