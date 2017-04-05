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


class Xylophone {
public:
        int countKeys(vector <int> keys) {
            vector<bool> notesHit(7, false);
            int result = 0;
            for (int i = 0; i < keys.size(); i++) {
                if (!notesHit[keys[i] % 7]) result++;
                notesHit[keys[i] % 7] = true;
            }
            return result;
        }
};


<%:testing-code%>
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
