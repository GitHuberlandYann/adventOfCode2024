#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int w, h;
string grid;
map<char, vector<array<int, 2>>> antennas;

int main( void )
{
    string line;
    while (getline(cin, line)) {
		if (!w) w = line.size();
		grid.append(line);
		++h;
	}

	for (int i = 0; i < h; ++i) for (int j = 0; j < w; ++j)
		if (grid[j + i * w] != '.') antennas[grid[j + i * w]].push_back({j, i});
	
	set<array<int, 2>> antinodes;
	for (auto& [key, vec] : antennas) {
		int len = vec.size();
		for (int i = 0; i < len; ++i) {
			auto& a = vec[i];
			antinodes.insert(a);
			for (int j = i + 1; j < len; ++j) {
				auto& b = vec[j];
				array<int, 2> diff{b[0] - a[0], b[1] - a[1]};
				for (array<int, 2> aprime{a[0] - diff[0], a[1] - diff[1]}; aprime[0] >= 0 && aprime[0] < w && aprime[1] >= 0 && aprime[1] < h; aprime[0] -= diff[0], aprime[1] -= diff[1]) antinodes.insert(aprime);
				for (array<int, 2> bprime{a[0] + diff[0], a[1] + diff[1]}; bprime[0] >= 0 && bprime[0] < w && bprime[1] >= 0 && bprime[1] < h; bprime[0] += diff[0], bprime[1] += diff[1]) antinodes.insert(bprime);
			}
		}
	}
    OUT(antinodes.size() << endl);
}