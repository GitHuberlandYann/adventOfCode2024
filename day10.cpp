#include <iostream>
#include <vector>
#include <set>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int width, height, res;
string grid;
vector<set<int>> paths;

static void solve( int x, int y, char t, bool zero )
{
	auto& sets = paths[x + y * width];
	if (x && grid[x - 1 + y * width] == t + 1) sets.insert(paths[x - 1 + y * width].begin(), paths[x - 1 + y * width].end());
	if (x < width - 1 && grid[x + 1 + y * width] == t + 1) sets.insert(paths[x + 1 + y * width].begin(), paths[x + 1 + y * width].end());
	if (y && grid[x + (y - 1) * width] == t + 1) sets.insert(paths[x + (y - 1) * width].begin(), paths[x + (y - 1) * width].end());
	if (y < height - 1 && grid[x + (y + 1) * width] == t + 1) sets.insert(paths[x + (y + 1) * width].begin(), paths[x + (y + 1) * width].end());
	if (zero) res += sets.size();
}

int main( void )
{
    string line;
    while (getline(cin, line)) {
		if (!width) width = line.size();
		++height;
        grid.append(line);
    }
	paths.resize(width * height);

	for (char target = '9'; target >= '0'; --target) {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				if (grid[j + i * width] == target) {
					if (target == '9') paths[j + i * width].insert(j + i * width);
					else solve(j, i, target, target == '0');
				}
			}
		}
	}

    OUT(res << endl);
}