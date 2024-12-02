#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static void solve( string str )
{

}

int main( void )
{
    int n;
    cin >> n; cin.ignore();
    for (int i = 0; i < n; ++i) {
        string line;
        getline(cin, line);
        solve(line);
    }

    OUT("answer");
}