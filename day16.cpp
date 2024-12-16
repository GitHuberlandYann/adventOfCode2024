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
int width, height, res;
string grid;
map<array<int, 3>, int> memory;

static void solve( int x, int y, int dir, int score, vector<array<int, 4>>& next )
{
    if (memory.count({x, y, dir}) && memory[{x, y, dir}] < score) return ;
    memory[{x, y, dir}] = score;
    for (; !res || score < res ; ++score) {
        char curr = grid[x + y * width];
        if (curr == 'E') {
            res = score;
            return ;
        } else if (curr == '#') return ;
        dir = (dir + 1) & 3;
        int xright = x + !dir - (dir == 2);
        int yright = y + (dir == 1) - (dir == 3);
        char right = grid[xright + yright * width];
        if (right != '#') next.push_back({xright, yright, dir, score + 1001});
        dir = (dir + 2) & 3;
        int xleft = x + !dir - (dir == 2);
        int yleft = y + (dir == 1) - (dir == 3);
        char left = grid[xleft + yleft * width];
        if (left != '#') next.push_back({xleft, yleft, dir, score + 1001});
        dir = (dir + 1) & 3;
        x += !dir - (dir == 2);
        y += (dir == 1) - (dir == 3);
    }
}

int main( void )
{
    int x = -1, y;
    string line;
    while (getline(cin, line)) {
        if (x == -1 && line.find('S') != string::npos) x = line.find('S'), y = height;
        grid.append(line);
        if (!width) width = line.size();
        ++height;
    }

    vector<array<int, 4>> next{{x, y, 0, 0}}, onext;
    for (bool flip = false; !(flip ? onext : next).empty(); flip = !flip) {
        for (auto [x, y, dir, score] : flip ? onext : next) solve(x, y, dir, score, flip ? next : onext);
        (flip ? onext : next).clear();
    }

    OUT(res << endl);
}