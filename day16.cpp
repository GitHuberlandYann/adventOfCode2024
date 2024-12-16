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
vector<string> paths;
map<array<int, 3>, int> memory;

static void backtrack( int x, int y, int dir, int score, string grid )
{
    if (memory.count({x, y, dir}) && memory[{x, y, dir}] < score) return ;
    memory[{x, y, dir}] = score;
    for (; !res || score <= res ; ++score) {
        char curr = grid[x + y * width];
        if (curr == 'E') {
            if (res == score) paths.push_back(grid);
            else paths = {grid};
            res = score;
            break ;
        } else if (curr == '#') break ;
        grid[x + y * width] = 'O';
        dir = (dir + 1) & 3;
        int xright = x + !dir - (dir == 2);
        int yright = y + (dir == 1) - (dir == 3);
        char right = grid[xright + yright * width];
        if (right != '#') backtrack(xright, yright, dir, score + 1001, grid);
        dir = (dir + 2) & 3;
        int xleft = x + !dir - (dir == 2);
        int yleft = y + (dir == 1) - (dir == 3);
        char left = grid[xleft + yleft * width];
        if (left != '#') backtrack(xleft, yleft, dir, score + 1001, grid);
        dir = (dir + 1) & 3;
        x += !dir - (dir == 2);
        y += (dir == 1) - (dir == 3);
    }
}

int main( void )
{
    int x = -1, y;
    string grid, line;
    while (getline(cin, line)) {
        if (x == -1 && line.find('S') != string::npos) x = line.find('S'), y = height;
        grid.append(line);
        if (!width) width = line.size();
        ++height;
    }

    backtrack(x, y, 0, 0, grid);
    //OUT(res << endl); // part 1

    for (auto g : paths) for (int i = 0; i < height; ++i) for (int j = 0; j < width; ++j)
        if (g[j + i * width] == 'O') grid[j + i * width] = 'O';

    res = 1;
    for (auto c : grid) res += c == 'O';
    OUT(res << endl);
}