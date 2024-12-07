#include <iostream>
#include <vector>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static bool valid( long total, long curr, int index, int len, vector<long>& factors )
{
	if (curr > total) return false;
	if (index == len) return curr == total;
	return valid(total, curr * factors[index], index + 1, len, factors)
		|| valid(total, curr + factors[index], index + 1, len, factors)
		|| valid(total, stol(to_string(curr) + to_string(factors[index])), index + 1, len, factors);
}

int main( void )
{
	long res = 0;
    while (!cin.eof()) {
        string line;
		long total, value;
		cin >> total;
		cin.ignore(1, ' ');
		vector<long> factors;
		while (!cin.eof() && cin.peek() != '\n') cin >> value, factors.push_back(value);
        if (valid(total, factors.front(), 1, factors.size(), factors)) res += total;
    }

    OUT(res << endl);
}