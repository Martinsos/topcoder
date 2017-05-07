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
#include <string>

using namespace std;

map<string, int> mem;

class RemovingParenthesis {
public:
    bool isValid(string s) {
        int numOpen = 0;
        for (int i = 0; i < s.size(); i++) {
            if (s[i] == '(') numOpen++;
            if (s[i] == ')') numOpen--;
            if (numOpen < 0) return false;
        }
        return numOpen == 0;
    }

    int countWays(string s) {
        if (s.length() == 0) return 1;
        if (mem.find(s) != mem.end()) {
            return mem[s];
        }

        int result = 0;
        for (int i = 1; i < s.length(); i++) {
            string newS = s.substr(1, i - 1) + s.substr(i + 1);
            if (isValid(newS)) {
                result += countWays(newS);
            }
        }

        mem[s] = result;
        return result;
    }
};


//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
