
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


class RangeEncoding {
public:
        int minRanges(vector <int> arr) {
            int last = -2;
            int result = 0;
            for (int i = 0; i < arr.size(); i++) {
                if (arr[i] != last + 1) {
                    result += 1;
                }
                last = arr[i];
            }
            return result;
        }
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
