#include <vector>

using namespace std;

class ResistorFactory {
public:
    vector <int> construct(long long nanoOhms) {
        vector<int> commands;
        vector<double> values;

        values.push_back(1000000000.0); // Product 0 is 10^9 ohm.

        for (int i = 0; i <= 28; i++) { // Products 1 to 29, each next is 2 times bigger.
            commands.push_back(i); commands.push_back(i); commands.push_back(0);
            values.push_back(((double) values[values.size() - 1]) * 2);
        }

        // Product 30, which is 10^9 / 2 (product #0 / 2).
        commands.push_back(0); commands.push_back(0); commands.push_back(1);
        values.push_back(values[0] / 2);

        for (int i = 30; i <= 58; i++) { // Products 31 to 59. each is 2 times smaller.
            commands.push_back(i); commands.push_back(i); commands.push_back(1);
            values.push_back(((double) values[values.size() - 1]) / 2);
        }

        // Inventory is built! Now we use our inventory to build the final resistor.
        double remaining = nanoOhms - values[values.size() - 1]; // Difference between what we have and target.
        while (remaining >= 1) {
            int bestIdx = -1; // Biggest resistor that is smaller than remaining amount.
            for (int i = 0; i < (int) values.size(); i++) {
                if (values[i] <= remaining && (bestIdx == -1 || remaining - values[i] < remaining - values[bestIdx])) {
                    bestIdx = i;
                }
            }

            commands.push_back(values.size() - 1); commands.push_back(bestIdx); commands.push_back(0);
            values.push_back(values[values.size() - 1] + values[bestIdx]);

            remaining -= values[bestIdx];
        }

        return commands;
    }
};
