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


class Softmatchd2 {
public:
    int count(string target, string pattern) {
        // Matches - we get them by applying pattern on each position in target, needed substring of target for it to fit is a match.
        // If target is abbaa and pattern is 123, matches would be: abB (position 0), BbA (position 1), BAA (position 2).
        int numMatches = target.size() - pattern.size() + 1;
        vector<string> matches(numMatches);
        for (int i = 0; i < numMatches; i++) {
            string match = "";
            for (int j = 0; j < pattern.size(); j++) {
                match += getMatchingChar(target[i + j], pattern[j]);
            }
            matches[i] = match;
        }

        // Cell i of vector count is a solution for case when target would start from position i.
        // We build it from back to front, through dynamic programming approach.
        vector<int> count(numMatches);
        for (int i = numMatches - 1; i >= 0; i--) {
            int maxOnRight = 0;  // Maximum count on right whose match is compatible with this match.
            for (int j = i + 1; j < numMatches; j++) {  // Do I have to go all the way to the numMatches, or just to i + pattern.size()?
                if (compatible(matches[i], matches[j], j - i)) {
                    maxOnRight = max(maxOnRight, count[j]);
                }
            }
            count[i] = maxOnRight + 1;
        }

        return *max_element(count.begin(), count.end());
    }

    char getMatchingChar(char letter, char number) {
        if (letter == 'a') {
            if (number == '0' || number == '1')
                return 'a';
            else  // number == '2' or '3'
                return 'A';
        } else {  // letter == 'b'
            if (number == '0' || number == '2')
                return 'b';
            else  // number == '1' or '3'
                return 'B';
        }
    }

    bool compatible(string m1, string m2, int m2Offset) {
        if (m2Offset >= m1.length()) return true;
        for (int i = m2Offset; i < m1.length(); i++) {
            if (m1[i] != m2[i - m2Offset]) {
                return false;
            }
        }
        return true;
    }
};

int main () {
    Softmatchd2 sm;
    sm.count("baaaaaaaaabaaaaaaaababbaaabbabbbabbaaababaaaaaaaaa", "31131311");
}
