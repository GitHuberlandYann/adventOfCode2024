#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
const string clue = "MAS";
const int len = 3;
int res, w, h;
string grid;


static bool canGo( int x, int y, int dx, int dy )
{
    if (x < 0 || x >= w || y < 0 || y >= h) return false;
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
			int cnt = 0;
            if (canGo(j - 1, i + 1, 1, -1)) ++cnt;
            if (canGo(j - 1, i - 1, 1, 1)) ++cnt;
            if (cnt < 2 && canGo(j + 1, i + 1, -1, -1)) ++cnt;
            if (cnt < 2 && canGo(j + 1, i - 1, -1, 1)) ++cnt;
			if (cnt == 2) ++res;
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