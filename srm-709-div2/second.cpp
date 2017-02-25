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


class Permatchd2 {
public:
        int fix(vector <string> edges) {
            int numOdd = 0;
            int numEven = 0;
            int n = edges.size();

            vector<bool> used(n, false);

            for (int i = 0; i < n; i++) {
                if (used[i]) continue;
                int numEdges = 0;

                deque<int> flood;
                flood.push_back(i);
                used[i] = true;

                while (flood.size() > 0) {
                    // Pop next node
                    int node = flood[0];
                    flood.pop_front();

                    for (int j = 0; j < n; j++) {
                        if (edges[node][j] == 'Y') {
                            numEdges++;
                            if (!used[j]) {
                                flood.push_back(j);
                                used[j] = true;
                            }
                        }
                    }
                }

                numEdges = numEdges / 2;
                if (numEdges % 2 == 0)
                    numEven++;
                else
                    numOdd++;
            }

            printf("%d %d\n", numOdd, numEven);

            if (numOdd == 1 && numEven == 0) {
                int numEdges = 0;
                for (int i = 0; i < n; i++)
                    for (int j = 0; j < n; j++)
                        if (edges[i][j] == 'Y')
                            numEdges++;

                numEdges = numEdges / 2;
                if (numEdges < n * (n-1) / 2)
                    return 1;
                else
                    return -1;
            } else {
                return numOdd;
            }

        }
};


int main() {
    Permatchd2 prog;
    vector<string> input;
    input.push_back("NYY");
    input.push_back("YNN");
    input.push_back("YNN");
    printf("result: %d\n", prog.fix(input));
}
