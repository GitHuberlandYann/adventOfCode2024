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

	long biggestGroupCnt = 0, groupCnt = 0;
	string biggestGroupKey, currentKey;
	for (auto& trio : trios) {
		auto& key = *trio.begin();
		if (key == currentKey) ++groupCnt;
		else {
			if (groupCnt > biggestGroupCnt) biggestGroupCnt = groupCnt, biggestGroupKey = currentKey;
			currentKey = key, groupCnt = 0;
		}
	}
	LOGND("biggestGroupCnt: " << biggestGroupCnt << " with key " << biggestGroupKey);

	set<string> res{biggestGroupKey};
	for (auto& trio : trios) if (*trio.begin() == biggestGroupKey) {
		res.insert(trio.begin(), trio.end());
	}

    for (auto& s : res) OUT(s << ',');
	OUT(endl);
}