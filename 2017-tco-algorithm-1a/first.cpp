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


class PingPongQueue {
public:
        vector <int> whoPlaysNext(vector <int> skills, int N, int K) {
            queue<int> players;
            for (int i = 0; i < skills.size(); i++) {
                players.push(skills[i]);
            }

            int first = -1, second = -1;
            int winner, loser;
            int previousWinner = -1;
            int numberConsecutiveWins = 0;
            for (int i = 0; i < K; i++) {
                if (first == -1) {
                    first = players.front();
                    players.pop();
                }
                if (second == -1) {
                    second = players.front();
                    players.pop();
                }

                winner = max(first, second);
                loser = min(first, second);

                if (winner == previousWinner) {
                    numberConsecutiveWins++;
                } else {
                    previousWinner = winner;
                    numberConsecutiveWins = 1;
                }

                first = -1; second = -1;
                players.push(loser);
                if (numberConsecutiveWins == N) {
                    players.push(winner);
                } else {
                    first = winner;
                }
            }

            vector<int> result;
            result.push_back(loser);
            result.push_back(winner);
            return result;
        }
};
//Powered by KawigiEdit 2.1.4 (beta) modified by pivanof!
