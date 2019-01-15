#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class PairProduct {
public:
    vector <int> findPair(int n, int a0, int step, long long p) {
        if (step == 0) {
            if (a0 * (long long) a0 == p)
                return {0, 0};
            else
                return {};
        }

        for (int i = 0; i < n; i++) {
            const long long x = a0 + (long long) i * step;
            if (x == 0) {
                if (p == 0)
                    return {i, i};
                else
                    continue;
            }

            if (p % x != 0) continue;

            const long long y = p / (long long) x;
            if ((y - (long long) a0) % step != 0) continue;
            const long long j = (y - (long long) a0) / step;
            if (j >= n || j < 0) continue;
            return {i, (int) j};
        }
        return {};
    }
};
