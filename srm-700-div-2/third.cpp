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

class XYZCoder {
public:
        int countWays(int room, int roomSize) {
            const int M = 1000000007;

            vector<int> prev(room * roomSize, 0);
            vector<int> curr(room * roomSize, 0);

            // I count number of combinations of winners in rooms.
            // First I pick the winner with smallest rank, and then always the next one with some bigger rank,
            // such that solution exists. In prev and curr I count number of ways to pick player with rank i as r-th winner.
            curr[0] = 1;  // First room.
            for (int r = 1; r < room; r++) {
                swap(prev, curr);
                curr[r] = prev[r - 1];
                for (int i = r + 1; i <= r * roomSize; i++) {
                    curr[i] = (curr[i - 1] + prev[i - 1]) % M;
                }
            }

            // I count all ways to pick r-th winner and multiply it with number of permutations.
            int result = 0;
            for (int i = room - 1; i <= (room - 1) * roomSize; i++)
                result = (result + curr[i]) % M;
            for (int i = 1; i <= room; i++)
                result = ((long long)result * i) % M;
            return result;
        }
};

int main () {
    XYZCoder prog;
    int room, roomSize;
    cin >> room >> roomSize;
    cout << prog.countWays(room, roomSize);
}
