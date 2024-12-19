#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <map>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
vector<string> towels;
map<int, long> memory;

static long solve( string& pattern, int cursor )
{
	if (memory.count(cursor)) return memory[cursor];
    if (!pattern[cursor]) return 1;

	long res = 0;
    for (auto& tow : towels) {
        if (!strncmp(tow.c_str(), &pattern[cursor], tow.size())) {
            res += solve(pattern, cursor + tow.size());
        }
    }
	return memory[cursor] = res;
}

int main( void )
{
	string str;
	for (cin >> str; str.back() == ','; cin >> str) str.pop_back(), towels.push_back(str);
	towels.push_back(str);
	cin.ignore(); cin.ignore();
    long res = 0;
	while (getline(cin, str)) {
		memory.clear();
        res += solve(str, 0);
    }

    OUT(res << endl);
}