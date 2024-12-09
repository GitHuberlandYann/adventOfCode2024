#include <iostream>
#include <array>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static int parse( string& str, array<int, 100000>& storage )
{
	int id = 0, i = 0, mode = 0;
	storage.fill(-1);

	for (auto c : str) {
		if (!mode) for (int j = 0; j < c - '0'; ++j) storage[i++] = id;
		else i += c - '0';
		mode = !mode;
		if (!mode) ++id;
	}
	return i;
}

static int getLast( array<int, 100000>& storage, int& end )
{
	for (--end; storage[end] == -1; --end);
	return storage[end];
}

static long solve( array<int, 100000>& storage, int end )
{
	long res = 0;

	for (int start = 0; start < end; ++start) {
		int curr = storage[start];
		if (curr == -1) curr = getLast(storage, end);
		res += start * curr;
	}
	return res;
}

int main( void )
{
    string line;
    getline(cin, line);
	array<int, 100000> storage;
    int end = parse(line, storage);
    OUT(solve(storage, end) << endl);
}