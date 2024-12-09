#include <iostream>
#include <vector>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

struct space { int size, type; };

static void parse( string& str, vector<space>& storage )
{
	int id = 0, mode = 0;

	for (auto c : str) {
		if (!mode) storage.push_back({c - '0', id});
		else storage.push_back({c - '0', -1});
		mode = !mode;
		if (!mode) ++id;
	}
}

static void moveMem( vector<space>& storage )
{
	for (int index = storage.size() - 1; index >= 0; --index) {
		auto [cnt, id] = storage[index];
		if (id == -1) continue ;
		for (int search = 0; search < index; ++search) {
			auto [ocnt, oid] = storage[search];
			if (oid == -1 && ocnt >= cnt) {
				storage[index].type = -1;
				if (cnt == ocnt) storage[search].type = id;
				else {
					int diff = ocnt - cnt;
					storage[search] = {cnt, id};
					storage.insert(storage.begin() + search + 1, space{diff, -1});
					++index;
				}
				break ;
			}
		}
	}
}

static long solve( vector<space>& storage )
{
	int i = 0;
	long res = 0;

	for (auto [cnt, type] : storage) {
		if (type == -1) i += cnt;
		else for (int j = 0; j < cnt; ++j) res += i++ * type;
	}
	return res;
}

int main( void )
{
    string line;
    getline(cin, line);
	vector<space> storage;
    parse(line, storage);
	moveMem(storage);
    OUT(solve(storage) << endl);
}