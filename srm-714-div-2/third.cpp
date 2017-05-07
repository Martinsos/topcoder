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


class Saleswoman {
public:
    int minMoves(vector <int> pos, vector <int> delta) {
        int supply = 0;

        int positive = 0;
        while (positive < delta.size() && delta[positive] < 0) {
            positive++;
        }

        int nextPositive = positive + 1;
        while (nextPositive < delta.size() && delta[nextPositive] < 0) nextPositive++;

        int demand = 0;
        int stop = 0;
        for (int stop = 0; stop < positive; stop++) {
            if (delta[stop] < 0) {
                demand += delta[stop];
            }
            if (demand > supply + delta[positive]) {
                break;
            }
        }

        int previous = stop - 1;
        while (previous >= 0 && delta[previous] >= 0) previous--;

        if (previous >= 0 && nextPositive < delta.size()) {
            bool go = false;
            if ((positive - previous) * 2 + (nextPositive - stop) * 2 < (nextPositive - previous) * 2) {
                supply += delta[positive];
                for (int i = 0; i <= previous; i++) {
                    if (delta[i] < 0) {
                        demand += delta[stop];
                    }
                    if (demand > supply + delta[positive]) {
                        break;
                    }
                }
            }
        }

        // Didn't get enough time to finish, but I think greedy approach works. Travelwoman should go from left to right, and each time she encounters a supplier,
        // she asks herself: should I go back at this moment, all the way to the first buyer that is not satisfied yet and sell to him and all the others after him
        // while she has enough goods or should I just continue on? It is easy to calculate what is better to do, we just calc diff between going back now for
        // some portion and then later for some other or doing the whole trip later from the next supplier. We just continue making this decisions and that is it!
        // I think this could work well.
    }
};


<%:testing-code%>
   //Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
