#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
map<int, set<int>> order;

static bool validUpdate( vector<int>& update )
{
	for (int i = update.size() - 1; i > 0; --i) {
		auto& ord = order[update[i]];
		for (int j = i - 1; j >= 0; --j) {
			if (ord.count(update[j])) return false;
		}
	}
	return true;
}

static void restoreUpdate( vector<int>& update )
{
	for (bool fixed = false; !fixed;) {
		fixed = true;
		for (int i = update.size() - 1; i > 0; --i) {
			auto& ord = order[update[i]];
			for (int j = i - 1; j >= 0; --j) {
				if (ord.count(update[j])) {
					swap(update[i], update[j]);
					fixed = false;
					break ;
				}
			}
		}
	}
}

int main( void )
{
	string line;
    while (getline(cin, line)) {
		if (line.empty()) break ;
		int key = atoi(line.c_str());
		order[key].insert(atoi(&line[3]));
    }
	int res = 0;
	while (getline(cin, line)) {
		vector<int> update;
		for (int i = 0; i < line.size(); i += 3) update.push_back(atoi(&line[i]));
		// part1: if (!validUpdate(update)) continue ;
		if (validUpdate(update)) continue ;
		restoreUpdate(update);
		res += update[update.size() / 2];
	}

    OUT(res << endl);
}