#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
const string clue = "XMAS";
const int len = 4;
int res, w, h;
string grid;


static bool canGo( int x, int y, int dx, int dy )
{
    if (x + dx * (len - 1) < 0 || x + dx * (len - 1) >= w || y + dy * (len - 1) < 0 || y + dy * (len - 1) >= h) return false;
    for (int i = 0; i < len; x += dx, y += dy, ++i) {
        if (grid[x + y * w] != clue[i]) return false;
    }
    return true;
}

static void solve( void )
{
    for (int i = 0; i < h; ++i) {
        for (int j = 0; j < w; ++j) {
            if (canGo(j, i, 1, 0)) ++res;
            if (canGo(j, i, -1, 0)) ++res;
            if (canGo(j, i, 0, 1)) ++res;
            if (canGo(j, i, 0, -1)) ++res;
            if (canGo(j, i, 1, -1)) ++res;
            if (canGo(j, i, 1, 1)) ++res;
            if (canGo(j, i, -1, -1)) ++res;
            if (canGo(j, i, -1, 1)) ++res;
        }
    }
}

int main( void )
{
	string line;
    while (getline(cin, line)) {
		if (!w) w = line.size();
		grid.append(line);
		++h;
	}
	solve();

    OUT(res << endl);
}