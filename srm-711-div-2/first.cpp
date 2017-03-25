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


class SquareMaking {
public:
        int getMinimalPrice(int a, int b, int c, int d) {
            int solution = 4000000;
            for (int i = 1; i <= 1000000; i++) {
                solution = min(solution, abs(i - a) + abs(i - b) + abs(i - c) + abs(i - d));
            }
            return solution;
        }
};
