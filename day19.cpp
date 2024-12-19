#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
vector<string> towels;
string memory;

static bool solve( string& pattern, int cursor )
{
	if (memory[cursor] == '1') return false;
    if (!pattern[cursor]) return true;

	memory[cursor] = '1';
    for (auto& tow : towels) {
        if (!strncmp(tow.c_str(), &pattern[cursor], tow.size())) {
            if (solve(pattern, cursor + tow.size())) return true;
        }
    }
    return false;
}

int main( void )
{
	string str;
	for (cin >> str; str.back() == ','; cin >> str) str.pop_back(), towels.push_back(str);
	towels.push_back(str);
	cin.ignore(); cin.ignore();
    int res = 0;
	while (getline(cin, str)) {
		memory = string(str.size(), '0');
        if (solve(str, 0)) ++res;
    }

    OUT(res << endl);
}