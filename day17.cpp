#include <iostream>
#include <iomanip>
#include <vector>
#include <array>
#include <algorithm>
#include <bitset>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
enum { A, B, C };
namespace opcode {
	enum { ADV, BXL, BST, JNZ, BXC, OUT, BDV, CDV };
};

static long combo( int operand, array<long, 3>& reg )
{
	if (operand < 4) return operand;
	return reg[operand - 4];
}

static bool validEntry( long regA, int target = 2 )
{
	// Program: 2,4,1,1,7,5,1,5,4,0,0,3,5,5,3,0
	long regB = regA & 7;         // 2 4
	regB ^= 1;                    // 1 1
	long regC = regA >> regB;     // 7 5
	regB ^= 0b101;                // 1 5
	regB ^= regC;                 // 4 0
	regA >>= 3;                   // 0 3
	return (regB & 7) == target;  // 5 5
}

static bool outputsItself( long regA, vector<int>& program, int progSize )
{
	LOGND("outputsItself " << regA);
	array<long, 3> reg{regA, 0, 0};
	vector<int> output;
	bool first = true;
	for (int insPtr = 0; insPtr < progSize; insPtr += 2) {
		int opcode = program[insPtr], operand = program[insPtr + 1];

		switch (opcode) {
			case opcode::ADV: reg[A] /= (1 << combo(operand, reg));                                break ;
			case opcode::BXL: reg[B] ^= operand;                                                   break ;
			case opcode::BST: reg[B] = combo(operand, reg) & 7;                                    break ;
			case opcode::JNZ: if (reg[A]) insPtr = operand - 2;                                    break ;
			case opcode::BXC: reg[B] ^= reg[C];                                                    break ;
			case opcode::OUT: if (output.size() == progSize) return false; output.push_back(combo(operand, reg) & 7);
					if (output.back() != program[output.size() - 1]) return false;                 break ;
			case opcode::BDV: reg[B] = reg[A] / (1 << combo(operand, reg));                        break ;
			case opcode::CDV: reg[C] = reg[A] / (1 << combo(operand, reg));                        break ;
		}
	}
	return output.size() == progSize;
}

int main( void )
{
	string skp;
	vector<int> program;

	for (int i = 0; i < 3; ++i) getline(cin, skp);
	getline(cin, skp, ':');
	while (!cin.eof()) {
		int value;
		cin >> value;
		program.push_back(value);
		cin.ignore(1, ' ');
	}

	/*
	// how I solved part 2:
	// 1. generate all combinaisons of 10 bits to get given target
	// 2. construct res backwards from program (see comment below)
	for (int target = 0; target < 8; ++target) {
		LOGND(endl << "target " << target);
		for (int i = 0; i < (1 << 10); ++i) if (validEntry(i, target)) LOGND("validEntry " << bitset<10>(i));
	}
	*/
	int progSize = program.size();
	OUT(outputsItself(0b100101011010011000111001011011010110111010111101L, program, progSize) << endl);
	return 0;
}

/*
Program: 2,4,1,1,7,5,1,5,4,0,0,3,5,5,3,0
2 4 -> regB = regA & 7
1 1 -> regB ^= 0b1
7 5 -> regC = regA >> regB
1 5 -> regB ^= 0b101
4 0 -> regB ^= regC
0 3 -> regA >>= 3
5 5 -> output(regB & 7) -> result must be 2 (== first ins of program)
--> on each loop, regA is bitshifted by 3 and stays > 0
regA >= (1 << (15 * 3)) AND regA < (1 << (16 * 3))
0b1.000.000.000.000.000.000.000.000.000.000.000.000.000.000 <= regA < 0b1.000.000.000.000.000.000.000.000.000.000.000.000.000.000.000

          0   3   5   5   3   0   0   4   5   1   5   7   1   1   4   2  
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.010.000.abort
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.010.001.abort
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.010.010.abort
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.010.101.abort
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.010.111.101 <- winner
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.011.
res = 0b100.101.011.010.011.000.111.001.011.011.010.110.111.110.
res = 0b100.101.011.010.011.000.111.001.101.
res = 0b100.101.011.010.011.101.000.
res = 0b100.101.011.010.011.101.111.
*/