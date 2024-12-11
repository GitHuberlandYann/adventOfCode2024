#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static long solve( long long n, int loop )
{
	if (!loop) return 1;
	if (!n) return solve(1, loop - 1);
	auto str = to_string(n);
	if (str.size() & 1) return solve(n * 2024, loop - 1);
	return solve(atoi(str.substr(0, str.size() / 2).c_str()), loop - 1)
		+ solve(atoi(str.substr(str.size() / 2).c_str()), loop - 1);
}

int main( void )
{
	long res = 0;
    while (!cin.eof()) {
		int stone;
		cin >> stone;
		cin.ignore(1, ' ');
		res += solve(stone, 25);
	}

    OUT(res << endl);
}