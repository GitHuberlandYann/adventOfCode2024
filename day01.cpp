#include <iostream>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

int main( void )
{
    map<int, int> left, right;
    while (cin) {
        int l, r;
        cin >> l >> r; cin.ignore();
        ++left[l];
        ++right[r];
    }
    int res = 0;
    for (auto [key, cnt] : left) res += cnt * key * right[key];
    OUT(res << endl);
    return 0;
    
    /*/ part 1
    vector<int> left, right;
    while (cin) {
        int l, r;
        cin >> l >> r; cin.ignore();
        left.push_back(l);
        right.push_back(r);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int res = 0;
    for (size_t i = 0; i < left.size(); ++i) res += abs(left[i] - right[i]);
    OUT(res << endl);*/
}