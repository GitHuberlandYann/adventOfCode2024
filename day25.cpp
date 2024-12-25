#include <iostream>
#include <vector>
#include <array>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
const int width = 5, height = 7;

static array<int, width> parse( string& str, char key )
{
	array<int, width> res;
	for (int x = 0; x < width; ++x) {
		for (int y = 1; y < height; ++y) if (str[x + y * width] != key) {
			res[x] = y;
			break ;
		}
	}
	return res;
}

int main( void )
{
	vector<array<int, width>> locks, keys;
    while (!cin.eof()) {
        string key, line;
		for (int i = 0; i < height; ++i)
        	getline(cin, line), key.append(line);
		key.front() == '.' ? keys.push_back(parse(key, '.')) : locks.push_back(parse(key, '#'));
		cin.ignore();
    }

	long res = 0;
	for (auto& l : locks) {
		for (auto& k : keys) {
			bool fit = true;
			for (int i = 0; i < width; ++i) {
				if (k[i] < l[i]) {
					fit = false;
					break ;
				}
			}
			res += fit;
		}
	}
    OUT(res << endl);
}