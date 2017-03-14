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


class ForwardMancala {
private:
    vector<int> makeMove(const vector<int> &oldState, int slot) {
        int numStones = oldState[slot];
        vector<int> newState(oldState);
        newState[slot] = 0;
        for (int i = 1; i <= numStones; i++) {
            newState[(slot + i) % newState.size()] += 1;
        }
        return newState;
    }

    bool endState(const vector<int> &state) {
        int numNonEmptyHoles = 0;
        for (int i = 0; i < state.size(); i++) {
            if (state[i] > 0) numNonEmptyHoles++;
        }
        return numNonEmptyHoles == 1;
    }

public:
    /**
     * Main idea: pick one hole that is not to be touched, let's call it end hole. I picked first hole for this.
     * Then just pick stones from all the others that are not empty yet, in any order (I went clockwise).
     * With time, stones will be consumed by the end hole - more end more will stay in it, until all of the stones stay there.
     * Super simple.
     */
    vector <int> findMoves(vector <int> state) {
        vector<int> moves;
        int slot = 1;
        while (!endState(state)) {
            if (slot != 0 && state[slot] > 0) {
                state = makeMove(state, slot);
                moves.push_back(slot);
            }
            slot = (slot + 1) % state.size();
        }
        return moves;
    }
};


int main () {
    ForwardMancala task;
    vector<int> start({0, 10, 0, 1});

    vector<int> moves = task.findMoves(start);
    for (int i = 0; i < moves.size(); i++) {
        cout << moves[i] << " ";
    }
    cout << endl;

    return 0;
}
