#include <iostream>
#include <map>

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
	solve(gates[str].left);
	solve(gates[str].right);
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

	// part 1
	long res = 0;
	for (auto& [key, cond] : gates) {
		if (key.front() != 'z') continue ;
		solve(key);
		if (codex[key]) res |= (1L << atoi(&key[1]));
	}
	OUT(res << endl);
}

/*
How to solve part2:

1. understand that we are dealing with a full adder https://en.wikipedia.org/wiki/Adder_(electronics)#Full_adder
2. display schema of full adder:

A --------+----+
          |    XOR --------+
B -----+--#----+     |    |
       |  |          |   XOR ----- S
       |  |          |    |
       |  |          +----#-----+
       |  |               |    AND ----+
Cin ---#--#---------------+-----+      |
       |  |                            OR --- Cout
	   |  +---------------------+      |
       |                       AND ----+
	   +------------------------+

3. ...
4. I resolved it by hand :)
*/