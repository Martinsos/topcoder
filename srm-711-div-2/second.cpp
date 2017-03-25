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


class StringTransform {
public:
        string isPossible(string s, string t) {
            for (int i = t.length() - 1; i >= 0; i--) {
                bool found = false;
                for (int j = 0; j <= i; j++) {
                    if (s[j] == t[i]) {
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    return "Impossible";
                }
            }
            return "Possible";
        }
};
