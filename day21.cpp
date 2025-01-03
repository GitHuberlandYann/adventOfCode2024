#include <iostream>
#include <vector>
#include <array>
#include <map>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int shortestSeq;
string nextSequence;
const map<char, array<int, 2>> numKeypadCoords{
	{'7', {0, 0}}, {'8', {1, 0}}, {'9', {2, 0}},
	{'4', {0, 1}}, {'5', {1, 1}}, {'6', {2, 1}},
	{'1', {0, 2}}, {'2', {1, 2}}, {'3', {2, 2}},
	{' ', {0, 3}}, {'0', {1, 3}}, {'A', {2, 3}}
};
const map<char, array<int, 2>> dirKeypadCoords{
	{' ', {0, 0}}, {'^', {1, 0}}, {'A', {2, 0}},
	{'<', {0, 1}}, {'v', {1, 1}}, {'>', {2, 1}}
};
const map<char, const map<char, string>> shortestMoves{
	{'A', { {'A', "A"}, {'^', "<A"}, {'<', "v<<A"}, {'v', "<vA"}, {'>', "vA"} }},
	{'^', { {'A', ">A"}, {'^', "A"}, {'<', "v<A"}, {'v', "vA"}, {'>', "v>A"} }},
	{'<', { {'A', ">>^A"}, {'^', ">^A"}, {'<', "A"}, {'v', ">A"}, {'>', ">>A"} }},
	{'v', { {'A', "^>A"}, {'^', "^A"}, {'<', "<A"}, {'v', "A"}, {'>', ">A"} }},
	{'>', { {'A', "^A"}, {'^', "<^A"}, {'<', "<<A"}, {'v', "<A"}, {'>', "A"} }},
};

static bool genNumericKeypad( string& code, int index, array<int, 2> pos, array<int, 2> target, string seq, bool dir )
{
	if (pos == target) {
		if (!seq.empty()) {
			int changeCnt = 0, prev = 'A';
			for (int idx = seq.size() - 1; idx >= 0 && seq[idx] != 'A'; prev = seq[idx--]) if (seq[idx] != prev) ++changeCnt;
			if (changeCnt > 2) return false;
		}
		seq += 'A';
		if (!code[++index]) {
			shortestSeq = seq.size();
			nextSequence = seq;
			return true;
		}
		return genNumericKeypad(code, index, pos, (dir ? dirKeypadCoords : numKeypadCoords).at(code[index]), seq, dir);
	}
	if (pos == (dir ? dirKeypadCoords : numKeypadCoords).at(' ')) return false;
	if (pos[0] > target[0] && genNumericKeypad(code, index, {pos[0] - 1, pos[1]}, target, seq + '<', dir)) return true;
	if (pos[1] > target[1] && genNumericKeypad(code, index, {pos[0], pos[1] - 1}, target, seq + '^', dir)) return true;
	if (pos[1] < target[1] && genNumericKeypad(code, index, {pos[0], pos[1] + 1}, target, seq + 'v', dir)) return true;
	if (pos[0] < target[0] && genNumericKeypad(code, index, {pos[0] + 1, pos[1]}, target, seq + '>', dir)) return true;
	return false;
}

map<int, map<char, map<char, pair<long, char>>>> memory;
static long genKeypad( int i, char start, char end )
{
	if (i == 25) return 1;
	if (memory[i][start].count(end)) { return memory[i][start][end].first; }
	long res = 0;
	char curr = 'A';
	for (auto val : shortestMoves.at(start).at(end)) res += genKeypad(i + 1, curr, val), curr = val;
	memory[i][start][end] = {res, curr};
	return res;
}

static long solve( string& code )
{
	nextSequence.clear();
	genNumericKeypad(code, 0, numKeypadCoords.at('A'), numKeypadCoords.at(code[0]), "", false);

	char curr = 'A';
	long res = 0;
	string seq = nextSequence;
	nextSequence.clear();
	for (auto val : seq) res += genKeypad(0, curr, val), curr = val;
	LOGND(code << " -> " << res << " -> " << nextSequence);
	return res;
}

int main( void )
{
	string code;
	long res = 0;
    while (getline(cin, code)) {
		OUT("solving " << code << endl);
		res += solve(code) * atoi(code.c_str());
	}

    OUT(res << endl);
}