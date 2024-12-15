#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int width, height;
string grid;

static void moveRobot( int& x, int& y, char dir )
{
	int dx = (dir == '>') - (dir == '<'), dy = (dir == 'v') - (dir == '^');
	for (int nx = x, ny = y;;) {
		nx += dx, ny += dy;
		char curr = grid[nx + ny * width];
		if (curr == '#') return ;
		if (curr == '.') {
			grid[nx + ny * width] = 'O';
			grid[x + y * width] = '.';
			x += dx, y += dy;
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
		if (x == -1 && line.find('@') != string::npos) x = line.find('@'), y = height;
		if (!width) width = line.size();
		++height;
        grid.append(line);
    }

	string instructions;
	while (getline(cin, line)) instructions.append(line);

	for (auto move : instructions) moveRobot(x, y, move);

	long res = 0;
	for (int i = 1; i < height - 1; ++i) for (int j = 1; j < width - 1; ++j) res += grid[j + i * width] == 'O' ? i * 100 + j : 0;

    OUT(res << endl);
}