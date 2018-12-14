#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

vector<int> digits(20);

class MagicNumbersAgain {
public:

    bool isMagicNumber(long long x) {
        int numDigits = 0;

        do {
            digits[numDigits++] = x % 10;
            x /= 10;
        } while (x > 0);


        for (int i = numDigits - 1; i >= 1; i--) {
            if ((i - (numDigits - 1)) % 2 == 0) {
                if (!(digits[i] < digits[i-1])) return false;
            } else {
                if (!(digits[i] > digits[i-1])) return false;
            }
        }

        return true;
    }

    int count(long long A, long long B) {
        long long a = (long long) trunc(sqrt(A));
        if (a * a < A) a += 1;

        int result = 0;
        for (long x = a; x * x <= B; x++) {
            if (isMagicNumber(x*x)) result++;
        }

        return result;
    }
};
