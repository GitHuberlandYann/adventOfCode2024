#include <iostream>
#include <set>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

int main( void )
{
	map<string, set<string>> cos;
    while (!cin.eof()) {
        string a, b;
		getline(cin, a, '-');
		getline(cin, b);
		cos[a].insert(b);
		cos[b].insert(a);
    }

	set<set<string>> trios;
	for (auto& [key, connect] : cos)
		for (auto& left : connect) for (auto& right : connect)
			if (cos[right].count(left)) trios.insert({key, left, right});
	LOGND("nbr trios: " << trios.size());

	long res = 0;
	for (auto& trio : trios) for (auto& s : trio) if (s.front() == 't') {
		++res;
		break ;
	}

    OUT(res << endl);
}