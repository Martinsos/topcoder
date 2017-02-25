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


class Robofactory {
public:
    int reveal(vector <int> query, vector <string> answer) {
        int unknown = 1;

        for (int i = 1; i < query.size(); i++) {
            if (!correct(query[i], answer[i]))
                return i;
            else {
                if (query[i-1] % 2 == 0)
                    unknown++;
            }
        }

        if (unknown > 1)
            return -1;
        else
            return 0;
    }

    private:
        bool correct(int x, string s) {
            return ((x % 2 == 1) && (s == "Odd")
                    || (x % 2 == 0) && (s == "Even"));
        }
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
