#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
enum { A, B, C };
enum { ADV, BXL, BST, JNZ, BXC, opOUT, BDV, CDV };

static int combo( int operand, array<int, 3>& reg )
{
	if (operand < 4) return operand;
	return reg[operand - 4];
}

int main( void )
{
	string skp;
	array<int, 3> reg;
	vector<int> program;

	for (auto& r : reg) {
		getline(cin, skp, ':');
		cin >> r;
	}
	getline(cin, skp, ':');
	while (!cin.eof()) {
		int value;
		cin >> value;
		program.push_back(value);
		cin.ignore(1, ' ');
	}

	bool first = true;
	int progSize = program.size();
	for (int insPtr = 0; insPtr < progSize; insPtr += 2) {
		int opcode = program[insPtr], operand = program[insPtr + 1];
		CUT(LOGND("opcode " << opcode << " operand " << operand));
		CUT(LOGND("A: " << reg[A] << " B: " << reg[B] << " C: " << reg[C]));

		switch (opcode) {
			case ADV: reg[A] /= (1 << combo(operand, reg)); break ;
			case BXL: reg[B] ^= operand; break ;
			case BST: reg[B] = combo(operand, reg) & 7; break ;
			case JNZ: if (reg[A]) insPtr = operand - 2; break ;
			case BXC: reg[B] ^= reg[C]; break ;
			case opOUT: OUT((first ? "" : ",") << (combo(operand, reg) & 7)); first = false; break ;
			case BDV: reg[B] = reg[A] / (1 << combo(operand, reg)); break ;
			case CDV: reg[C] = reg[A] / (1 << combo(operand, reg)); break ;
		}
	}
	OUT(endl);
}