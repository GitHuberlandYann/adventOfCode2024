#include <iostream>
#include <vector>
#include <map>
#include <math.h>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static void genSecret( long& secret )
{
	secret = (secret ^ (secret << 6)) % 16777216;
	secret = (secret ^ (secret >> 5)) % 16777216;
	secret = (secret ^ (secret << 11)) % 16777216;
}

int main( void )
{
    long res = 0, secret, index = 0;
	map<array<int, 4>, array<int, 2000>> codex;
    while (!cin.eof()) {
        cin >> secret; cin.ignore();
		vector<int> digits{int(secret % 10)};
		for (int i = 0; i < 2000; ++i) genSecret(secret), digits.push_back(secret % 10);
		for (int i = 4; i < 2001; ++i) {
			array<int, 4> key{digits[i - 3] - digits[i - 4], digits[i - 2] - digits[i - 3], digits[i - 1] - digits[i - 2], digits[i] - digits[i - 1]};
			int curr = digits[i];
			if (!codex[key][index]) codex[key][index] = curr;
		}
		++index;
	}

	for (auto& [key, vec] : codex) {
		long sum = 0;
		for (int i = 0; i < index; ++i) sum += vec[i];
		res = sum > res ? sum : res;
	}

    OUT(res << endl);
}