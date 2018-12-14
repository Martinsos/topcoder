#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;


class ModularQuadrant {
public:

    long long sum(int r1, int r2, int c1, int c2) {
        return calcRect(r2, c2) - calcRect(r1 - 1, c2) - calcRect(r2, c1 - 1) + calcRect(r1 - 1, c1 - 1);
    }

    // If we have sequence like this x--x--x--x--x--... of length n, how many times does x appear?
    long long numAppear(long long n) {
        if (n <= 0) return 0;
        return n / 3 + (n % 3 ? 1 : 0);
    }

    // Sum of n consecutive numbers, starting with 'start' and step of 'step'.
    long long sumNum(long long start, long long step, long long n) {
        if (n <= 0) return 0;
        return start * n + step * (n - 1) * n / 2;
    }

    // Calculates sum for rectangle from (0, 0) to (r, c).
    long long calcRect(const long long r, const long long c) {
        if (r > c) return calcRect(c, r);
        if (r < 0 || c < 0) return 0;

        // Calc rectangle part.
        const long long w = c - r; // width of rectangle part.
        const long long h = r + 1;
        const long long x = h % 3;

        const long long sumRectPart = h * (x * numAppear(w) +
                                           (x + 1) % 3 * numAppear(w - 1) +
                                           (x + 2) % 3 * numAppear(w - 2));


        // Calc triangle part.
        const long long a = r + 1;
        const long long sumTrngPart = 0 + 1 * sumNum(2, 3, numAppear(a - 1)) + 2 * sumNum(3, 3, numAppear(a - 2));
        const long long trngDiag = numAppear(a - 1) + 2 * numAppear(a - 2); // Diagonal.

        return sumRectPart + sumTrngPart * 2 - trngDiag;
    }
};
