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


class MagicSubset {
public:
        int findBest(vector <int> values) {
            int sumPos = 0;
            int sumNeg = 0;
            for (int i = 1; i < values.size(); i++) {
                if (values[i] > 0) sumPos += values[i];
                if (values[i] < 0) sumNeg += values[i];
            }
            return max(sumPos,
                       max(-1 * (sumNeg + values[0]),
                           max(-1 * (sumPos + values[0]),
                               -1 * values[0])));
        }
};

int main () {
    return 0;
}
