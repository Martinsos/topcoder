#include <vector>
#include <cstdlib>

using namespace std;

class SixteenQueens {
public:
    vector <int> addQueens(vector <int> row, vector <int> col, int add) {
        vector<int> result;
        for (int i = 0; i < add; i++) { // For each queen that we want to add.
            bool done = false;
            for (int r = 0; r < 50 && !done; r++) { // Let's try every field on the board. Every row.
                for (int c = 0; c < 50 && !done; c++) { // And every column.
                    bool fieldOk = true; // Is field ok to put queen on it?
                    // Check if any of previous queens is compromising the field.
                    for (int j = 0; j < (int) row.size() && fieldOk; j++) {
                        if (r == row[j] || c == col[j] || (abs(r - row[j]) == abs(c - col[j]))) {
                            fieldOk = false; break;
                        }
                    }
                    if (fieldOk) { // If field is ok to go, put queen on it.
                        row.push_back(r); col.push_back(c); // Add to queens on board.
                        result.push_back(r); result.push_back(c); // Add to results.
                        done = true;
                    }
                }
            }
        }

        return result;
    }
};
