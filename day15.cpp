#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int width, height;
string grid;

static void moveRobotVertically( int& x, int& y, int dy )
{
	int left = x, right = x;
	vector<array<int, 2>> boxes;
	for (int ny = y, nleft = width, nright = -1;; nleft = width, nright = -1) {
		ny += dy;
		bool clear = true;
		for (int nx = left; nx <= right; ++nx) {
			char curr = grid[nx + ny * width];
			if (curr == '#') return ;
			if (curr == '[') clear = false, boxes.push_back({nx, ny}), nleft = nx < nleft ? nx : nleft, nright = nx + 1 > nright ? nx + 1 : nright;
			else if (curr == ']') clear = false, boxes.push_back({nx - 1, ny}), nleft = nx - 1 < nleft ? nx - 1 : nleft, nright = nx > nright ? nx : nright;
		}
		left = nleft, right = nright;
		if (clear) {
			for (int i = boxes.size() - 1; i >= 0; --i) {
				auto [bx, by] = boxes[i];
				grid[bx + (by + dy) * width] = '[', grid[bx + 1 + (by + dy) * width] = ']';
				grid[bx + by * width] = '.', grid[bx + 1 + by * width] = '.';
			}
			grid[x + y * width] = '.';
			y += dy;
			grid[x + y * width] = '@';
			return ;
		}
	}
}

static void moveRobot( int& x, int& y, char dir )
{
	int dx = (dir == '>') - (dir == '<'), dy = (dir == 'v') - (dir == '^');
	if (dy) return moveRobotVertically(x, y, dy);
	for (int nx = x;;) {
		nx += dx;
		char curr = grid[nx + y * width];
		if (curr == '#') return ;
		if (curr == '.') {
			for (; nx - dx != x; nx -= dx) grid[nx + y * width] = grid[nx - dx + y * width];
			grid[x + y * width] = '.';
			x += dx;
			grid[x + y * width] = '@';
			return ;
		}
	}
}

int main( void )
{
	int x = -1, y;
    string line;
    for (;;) {
        getline(cin, line);
		if (line.empty()) break ;
		if (x == -1 && line.find('@') != string::npos) x = line.find('@') * 2, y = height;
		if (!width) width = line.size() * 2;
		++height;
		for (auto c : line) switch (c) {
			case 'O': grid += "[]"; break ;
			case '.': grid += ".."; break ;
			case '#': grid += "##"; break ;
			case '@': grid += "@."; break ;
		}
    }

	string instructions;
	while (getline(cin, line)) instructions.append(line);

	for (auto move : instructions) moveRobot(x, y, move);

	long res = 0;
	for (int i = 1; i < height - 1; ++i) for (int j = 1; j < width - 1; ++j) res += grid[j + i * width] == '[' ? i * 100 + j : 0;

    OUT(res << endl);
}