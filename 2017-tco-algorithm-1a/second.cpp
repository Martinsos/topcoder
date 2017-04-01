#include <vector>
#include <list>
#include <map>
#include <set>
#include <queue>
#include <deque>
#include <stack>
#include <bitset>
#include <algorithm>
#include <functional>
#include <numeric>
#include <utility>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cstdio>
#include <cmath>
#include <cstdlib>
#include <ctime>

using namespace std;


class CheeseSlicing {
public:
    int memo[101][101][101];

    int area(int A, int B, int C, int S) {
        int dim[3];
        dim[0] = min(A, min(B, C));
        dim[2] = max(A, max(B, C));
        dim[1] = A + B + C - dim[0] - dim[2];

        if (dim[0] < S) return 0;
        if (memo[dim[0]][dim[1]][dim[2]] != -1)
            return memo[dim[0]][dim[1]][dim[2]];

        int sol = dim[1] * dim[2];
        if (dim[0] > S) {
            sol = max(sol, area(dim[0] - S, dim[1], dim[2], S) + area(S, dim[1], dim[2], S));
        }
        if (dim[1] > S) {
            sol = max(sol, area(dim[0], dim[1] - S, dim[2], S) + area(dim[0], S, dim[2], S));
        }
        if (dim[2] > S) {
            sol = max(sol, area(dim[0], dim[1], dim[2] - S, S) + area(dim[0], dim[1], S, S));
        }

        memo[dim[0]][dim[1]][dim[2]] = sol;
        return sol;
    }

    int totalArea(int A, int B, int C, int S) {
        for (int i = 0; i < 101; i++)
            for (int j = 0; j < 101; j++)
                for (int k = 0; k < 101; k++)
                    memo[i][j][k] = -1;
        return area(A, B, C, S);
    }
};
