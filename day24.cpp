#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
struct gate { string left, op, right; };
map<string, int> codex;
map<string, gate> gates;

static void solve( const string& str )
{
	if (codex.count(str)) return ;
	if (!codex.count(gates[str].left)) solve(gates[str].left);
	if (!codex.count(gates[str].right)) solve(gates[str].right);
	switch (gates[str].op.front()) {
		case 'A': codex[str] = codex[gates[str].left] & codex[gates[str].right]; break ;
		case 'O': codex[str] = codex[gates[str].left] | codex[gates[str].right]; break ;
		case 'X': codex[str] = codex[gates[str].left] ^ codex[gates[str].right]; break ;
	}
}

int main( void )
{
	string line;
    while (getline(cin, line)) {
		if (line.empty()) break ;
		codex[line.substr(0, 3)] = line[5] == '1';
    }
	while (!cin.eof()) {
		gate ngate;
		cin >> ngate.left >> ngate.op >> ngate.right >> line >> line;
		gates[line] = ngate;
	}

	for (auto& [key, cond] : gates) solve(key);

	long res = 0;
	for (auto& [key, boo] : codex) if (key.front() == 'z' && boo) res |= (1L << atoi(&key[1])); 
    OUT(res << endl);
}