#include <iostream>
#include <vector>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int width, height, res;
string grid;
vector<int> paths;

static void solve( int x, int y, char t, bool zero )
{
	int cnt = 0;
	if (x && grid[x - 1 + y * width] == t + 1) cnt += paths[x - 1 + y * width];
	if (x < width - 1 && grid[x + 1 + y * width] == t + 1) cnt += paths[x + 1 + y * width];
	if (y && grid[x + (y - 1) * width] == t + 1) cnt += paths[x + (y - 1) * width];
	if (y < height - 1 && grid[x + (y + 1) * width] == t + 1) cnt += paths[x + (y + 1) * width];
	if (zero) res += cnt;
	else paths[x + y * width] = cnt;
}

int main( void )
{
    string line;
    while (getline(cin, line)) {
		if (!width) width = line.size();
		++height;
        grid.append(line);
    }
	paths.resize(width * height, 0);

	for (char target = '9'; target >= '0'; --target) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (grid[j + i * width] == target) {
					if (target == '9') paths[j + i * width] = 1;
					else solve(j, i, target, target == '0');
				}
			}
		}
	}

    OUT(res << endl);
}