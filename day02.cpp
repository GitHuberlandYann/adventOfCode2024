#include <iostream>
#include <iomanip>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static bool check( vector<int> reports, size_t avoid )
{
    bool increasing;
    if (!avoid) reports[0] = reports[1], avoid = 1, increasing = reports[2] > reports[1];
    else if (avoid == 1) increasing = reports[2] > reports[0];
    else increasing = reports[1] > reports[0];
    for (size_t i = 0; i < reports.size() - 1; ++i) {
        if (i + 1 == avoid) { reports[i + 1] = reports[i]; continue ; }
        if ((reports[i + 1] > reports[i]) != increasing) return false;
        int diff = abs(reports[i + 1] - reports[i]);
        if (!diff || diff > 3) return false;
    }
    return true;
}

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
    for (size_t i = 0; i < reports.size(); ++i) if (check(reports, i)) return true;
    return false;
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