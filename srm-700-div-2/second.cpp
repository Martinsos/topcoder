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


class XMarksTheSpot {
public:
        int countArea(vector <string> board) {
            int minXO = 50, minYO = 50, maxXO = -1, maxYO = -1;
            vector<pair<int, int> > qMarks;  // (x, y)

            for (int x = 0; x < board.size(); x++) {
                for (int y = 0; y < board[x].length(); y++) {
                    if (board[x][y] == 'O') {
                        minXO = min(minXO, x);
                        minYO = min(minYO, y);
                        maxXO = max(maxXO, x);
                        maxYO = max(maxYO, y);
                    }
                    if (board[x][y] == '?') {
                        qMarks.push_back(make_pair(x, y));
                    }
                }
            }

            int result = 0;
            for (int perm = 0; perm < pow(2, qMarks.size()); perm++) {
                int minX = minXO, minY = minYO, maxX = maxXO, maxY = maxYO;
                for (int i = 0; i < qMarks.size(); i++) {
                    if ((perm >> i) & 1) {
                        int x = qMarks[i].first;
                        int y = qMarks[i].second;
                        minX = min(minX, x);
                        minY = min(minY, y);
                        maxX = max(maxX, x);
                        maxY = max(maxY, y);
                    }
                }
                result += (maxX - minX + 1) * (maxY - minY + 1);
            }

            return result;
        }
};

int main () {

}
