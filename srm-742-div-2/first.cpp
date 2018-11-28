#include <vector>

using namespace std;

/**
 * This one is really simple, I just followed their instructions.
 */
class BirthdayCandy {
public:
    int mostCandy(int K, vector <int> candy) {
        int maxCandy = -1;

        for (int i = 0; i < (int) candy.size(); i++) {
            const int numCandy = candy[i] / (K + 1) + candy[i] % (K + 1);
            if (numCandy > maxCandy) {
                maxCandy = numCandy;
            }
        }

        return maxCandy;
    }
};
