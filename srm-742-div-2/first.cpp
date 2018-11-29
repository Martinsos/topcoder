#include <vector>

using namespace std;

/**
 * For each candy bag we do whole number division with (K + 1) to learn
 * how many rounds of giving candies Elisa did.
 * Then, we take the rest of the candies and sum it up with number of rounds
 * and that is the total number of candies Elisa got from that bag of candies.
 * We return that number for the bag that has it he biggest.
 */
class BirthdayCandy {
public:
    int mostCandy(int K, vector <int> candy) {
        int maxCandy = -1;
        for (int i = 0; i < (int) candy.size(); i++) {
            const int numCandy = candy[i] / (K + 1) + candy[i] % (K + 1);
            if (numCandy > maxCandy) maxCandy = numCandy;
        }
        return maxCandy;
    }
};
