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


class MinMaxMax {
public:
    long long findMin(vector <int> a, vector <int> b, vector <int> w, vector <int> v) {
        for (int i = 0; i < v.size(); i++) {
            // Use dijkstra to find minimal distance to all other nodes.
            vector<long long> dist(v.size(), 0);
            vector<bool> processed(v.size(), false);
        }
    }
};
