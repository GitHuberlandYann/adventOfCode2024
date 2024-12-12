#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
struct regio { int area = 0, perimeter = 0; };
int width, height;
string grid;
vector<int> griid;

static void solve( int x, int y, char target, int region )
{
	if (x < 0 || x >= width || y < 0 || y >= height) return ;
	if (grid[x + y * width] != target) return ;
	grid[x + y * width] = '#';
	griid[x + y * width] = region;
	solve(x - 1, y, target, region);
	solve(x + 1, y, target, region);
	solve(x, y - 1, target, region);
	solve(x, y + 1, target, region);
}

int main( void )
{
	string line;
    while (getline(cin, line)) {
		if (!width) width = line.size();
		grid.append(line), ++height;
	}
	LOGND("width " << width << " height " << height);
	griid.resize(width * height, 0);

	int region = 0;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			char c = grid[j + i * width];
			if (c != '#') solve(j, i, c, region++);
		}
	}
	LOGND("nb regions: " << region);

	map<int, regio> regions;
	for (int i = 0; i < height; ++i) {
		for (int j = 0; j < width; ++j) {
			int curr = griid[j + i * width];
			++regions[curr].area;
			if (!j) regions[curr].perimeter += !i || griid[j + (i - 1) * width] != curr;
			if (j == width - 1) regions[curr].perimeter += !i || griid[j + (i - 1) * width] != curr;
			else {
				int neighbour = griid[j + 1 + i * width];
				if (curr != neighbour) {
					regions[curr].perimeter += !i || griid[j + (i - 1) * width] != curr || griid[j + 1 + (i - 1) * width] == curr;
					regions[neighbour].perimeter += !i || griid[j + 1 + (i - 1) * width] != neighbour || griid[j + (i - 1) * width] == neighbour;
				}
			}
			if (!i) regions[curr].perimeter += !j || griid[j - 1 + i * width] != curr;
			if (i == height - 1) regions[curr].perimeter += !j || griid[j - 1 + i * width] != curr;
			else {
				int neighbour = griid[j + (i + 1) * width];
				if (curr != neighbour) {
					regions[curr].perimeter += !j || griid[j - 1 + i * width] != curr || griid[j - 1 + (i + 1) * width] == curr;
					regions[neighbour].perimeter += !j || griid[j - 1 + (i + 1) * width] != neighbour || griid[j - 1 + i * width] == neighbour;
				}
			}
		}
	}

	long res = 0;
	for (auto& [key, reg] : regions) res += reg.area * reg.perimeter;
    OUT(res << endl);
}