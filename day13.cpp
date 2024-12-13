#include <iostream>
#include <algorithm>

#define OUT(x) cout << x
#define LOG(x) cerr << x
#define LOGND(x) cerr << x << endl
#define CUT(x)

using namespace std;

static array<long, 2> readInput( char sep )
{
    long x, y;
    string ign;
    getline(cin, ign, sep);
    cin >> x;
    getline(cin, ign, sep);
    cin >> y;
    cin.ignore();
    cin.ignore();
    return {x, y};
}

int main( void )
{
    long res = 0;
    while (!cin.eof()) {
        auto buttonA = readInput('+');
        auto buttonB = readInput('+');
        auto target = readInput('=');
        target[0] += 10000000000000;
        target[1] += 10000000000000;
        if ((target[0] * buttonA[1] - target[1] * buttonA[0]) % (buttonB[0] * buttonA[1] - buttonB[1] * buttonA[0])) continue ;
        long cntB = (target[0] * buttonA[1] - target[1] * buttonA[0]) / (buttonB[0] * buttonA[1] - buttonB[1] * buttonA[0]);
        if ((target[1] - cntB * buttonB[1]) % buttonA[1]) continue ;
        long cntA = (target[1] - cntB * buttonB[1]) / buttonA[1];
        //if (cntA > 100 || cntB > 100) continue ;
        res += cntA * 3 + cntB;
        /*
        cntA * buttonA[0] + cntB * buttonB[0] = target[0];
        cntA * buttonA[1] + cntB * buttonB[1] = target[1];
        <=> cntA = (target[1] - cntB * buttonB[1]) / buttonA[1];
        <=> (target[1] - cntB * buttonB[1]) / buttonA[1] * buttonA[0] + cntB * buttonB[0] = target[0];
        <=> cntB * buttonB[0] - cntB * buttonB[1] * buttonA[0] / buttonA[1] = target[0] - target[1] * buttonA[0] / buttonA[1];
        <=> cntB * buttonB[0] * buttonA[1] - cntB * buttonB[1] * buttonA[0] = target[0] * buttonA[1] - target[1] * buttonA[0];
        <=> cntB = (target[0] * buttonA[1] - target[1] * buttonA[0]) / (buttonB[0] * buttonA[1] - buttonB[1] * buttonA[0]);
        */
    }

    OUT(res << endl);
}