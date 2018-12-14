#include <vector>

using namespace std;


class ThreePartSplit {
public:
    vector<int> split(int a, int d) {
        const int n = d - a;
        const int m = n / 3;
        vector<int> bc;
        bc.push_back(a + m);
        bc.push_back(a + 2 * m);
        return bc;
    }
};
