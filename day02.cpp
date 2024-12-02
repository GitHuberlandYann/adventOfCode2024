#include <iostream>
#include <iomanip>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static bool solve( string str )
{
    istringstream in(str);
    vector<int> reports;
    while (in) {
        int nbr;
        in >> nbr;
        reports.push_back(nbr);
    }
    reports.pop_back();
    if (reports.empty()) return false;
    bool increasing = reports[1] > reports[0];
    for (size_t i = 0; i < reports.size() - 1; ++i) {
        if ((reports[i + 1] > reports[i]) != increasing) return false;
        int diff = abs(reports[i + 1] - reports[i]);
        if (!diff || diff > 3) return false;
    }
    return true;
}

int main( void )
{
    int res = 0;
    while (cin) {
        string line;
        getline(cin, line);
        res += solve(line);
    }

    OUT(res);
}