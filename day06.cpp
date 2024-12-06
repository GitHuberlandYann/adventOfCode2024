#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int w, h;
string grid;

static void solve( int x, int y, int dir )
{
	grid[x + y * w] = 'X';
	for (int loop = 0; loop < 4; ++loop) {
		x += !dir - (dir == 2);
		y += (dir == 1) - (dir == 3);
		if (x < 0 || x >= w || y < 0 || y >= h) return ;
		if (grid[x + y * w] != '#') return solve(x, y, dir);
		x -= !dir - (dir == 2);
		y -= (dir == 1) - (dir == 3);
		dir = (dir + 1) & 3;
	}
}

int main( void )
{
	string line;
	int x = -1, y, dir;
    while (getline(cin, line)) {
		++h;
		if (!w) w = line.size();
		if (x == -1) {
			for (int j = 0; j < w; ++j) {
				if ((dir = string(">v<^").find(line[j])) != string::npos) {
					x = j, y = h - 1;
					break ;
				}
			}
		}
		grid.append(line);
    }
	solve(x, y, dir);
	int res = 0;
	for (auto c : grid) res += c == 'X';
    OUT(res << endl);
}