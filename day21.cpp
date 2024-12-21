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
vector<string> sequences;
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

static void genNumericKeypad( string& code, int index, array<int, 2> pos, array<int, 2> target, string seq, bool dir )
{
	if (pos == target) {
		if (!seq.empty()) {
			int changeCnt = 0, prev = 'A';
			for (int idx = seq.size() - 1; idx >= 0 && seq[idx] != 'A'; prev = seq[idx--]) if (seq[idx] != prev) ++changeCnt;
			if (changeCnt > 2) return ;
		}
		seq += 'A';
		if (!code[++index]) {
			sequences.push_back(seq);
			return ;
		}
		return genNumericKeypad(code, index, pos, (dir ? dirKeypadCoords : numKeypadCoords).at(code[index]), seq, dir);
	}
	if (pos == (dir ? dirKeypadCoords : numKeypadCoords).at(' ')) return ;
	if (pos[0] > target[0]) genNumericKeypad(code, index, {pos[0] - 1, pos[1]}, target, seq + '<', dir);
	if (pos[0] < target[0]) genNumericKeypad(code, index, {pos[0] + 1, pos[1]}, target, seq + '>', dir);
	if (pos[1] > target[1]) genNumericKeypad(code, index, {pos[0], pos[1] - 1}, target, seq + '^', dir);
	if (pos[1] < target[1]) genNumericKeypad(code, index, {pos[0], pos[1] + 1}, target, seq + 'v', dir);
}

static int solve( string& code )
{
	genNumericKeypad(code, 0, numKeypadCoords.at('A'), numKeypadCoords.at(code[0]), "", false);
	auto allSequences = sequences;
	sequences.clear();
	for (auto& seq : allSequences) LOGND(seq);
	for (auto& seq : allSequences) genNumericKeypad(seq, 0, dirKeypadCoords.at('A'), dirKeypadCoords.at(seq[0]), "", true);
	allSequences = sequences;
	sequences.clear();
	for (auto& seq : allSequences) LOGND('\t' << seq);
	for (auto& seq : allSequences) genNumericKeypad(seq, 0, dirKeypadCoords.at('A'), dirKeypadCoords.at(seq[0]), "", true);
	allSequences = sequences;
	sequences.clear();
	int res = 2147483647;
	for (auto& seq : allSequences) if (LOGND("\t\t" << seq), seq.size() < res) res = seq.size();
	return res;
}

int main( void )
{
	string code;
	int res = 0;
    while (getline(cin, code)) {
		LOGND("solving " << code);
		res += solve(code) * atoi(code.c_str());
	}

    OUT(res << endl);
}