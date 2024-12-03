#include <iostream>
#include <vector>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;
int res;

static void handleMul( size_t index, string& str )
{
	int a = 0, b = 0;
	for (index += 4; isdigit(str[index]); ++index) a = a * 10 + str[index] - '0';
	if (str[index] != ',' || !a || a > 999) return ;
	for (++index; isdigit(str[index]); ++index) b = b * 10 + str[index] - '0';
	if (str[index] != ')' || !b || b > 999) return ;
	res += a * b;
}

static void solve( string& str )
{
	vector<size_t> dos, donts;
	for (auto search = str.find("do("); search != string::npos; search = str.find("do(", search + 3)) dos.push_back(search);
	for (auto search = str.find("don't("); search != string::npos; search = str.find("don't(", search + 6)) donts.push_back(search);
	for (auto search = str.find("mul("); search != string::npos; search = str.find("mul(", search + 4)) {
		size_t lastDont = string::npos, lastDo = string::npos;
		for (auto Do : dos) if (Do < search) lastDo = Do; else break ;
		for (auto dont : donts) if (dont < search) lastDont = dont; else break ;
		if (lastDont == string::npos || (lastDo != string::npos && lastDo > lastDont)) handleMul(search, str);
	}
}

int main( void )
{
	string line, str;
    while (getline(cin, line)) str.append(line);
	solve(str);

    OUT(res << endl);
}