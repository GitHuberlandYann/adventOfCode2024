#include <iostream>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
map<pair<long long, int>, long> memory;

static int cntDigits( long long n )
{
	for (long long pow = 1, cmp = 10; ; cmp *= 10, ++pow) if (n < cmp) return pow;
}

static long solve( long long n, int loop )
{
	if (memory.count({n, loop})) return memory[{n, loop}];
	if (!loop) return 1;
	if (!n) return memory[{n, loop}] = solve(1, loop - 1);

	int digits = cntDigits(n);
	if (digits & 1) return memory[{n, loop}] = solve(n * 2024, loop - 1);
	digits >>= 1;
	long long pow = 1;
	for (int i = 0; i < digits; ++i) pow *= 10;
	long long a = n / pow, b = n - a * pow;
	return memory[{n, loop}] = solve(a, loop - 1) + solve(b, loop - 1);
}

int main( void )
{
	long res = 0;
    while (!cin.eof()) {
		int stone;
		cin >> stone;
		cin.ignore(1, ' ');
		res += solve(stone, 75);
	}

    OUT(res << endl);
}