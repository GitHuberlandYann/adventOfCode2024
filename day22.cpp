#include <iostream>
#include <algorithm>
#include <math.h>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static void genSecret( long& secret )
{
	secret = (secret ^ (secret << 6)) % 16777216;
	secret = (secret ^ int(floor(secret / 32.f))) % 16777216;
	secret = (secret ^ (secret << 11)) % 16777216;
}

int main( void )
{
    long res = 0, secret;
    while (!cin.eof()) {
        cin >> secret; cin.ignore();
		for (int i = 0; i < 2000; ++i) genSecret(secret);
		res += secret;
	}

    OUT(res << endl);
}