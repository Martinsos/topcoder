#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iostream>

using namespace std;

/**
 * I was trying to think of a smart, dynamic programming solution, but space is just too big and I could not see any way
 * to smartly guide the space search.
 * But, I realized that if we have an inventory of resistors that are with their values nicely covering space from 0 to MAX resistor value,
 * we can quickly build any resistor value just by combining them together in series (summing them up).
 * Then I noticed that by putting resistor in series with itself I get resistor or double the value,
 * while putting it in parallel with itself gives me half its value.
 * Since I start with resistor of 10^9 nanoOhm (all the values I express in nanoOhm), I can create resistor 2 * 10^9 by putting it in series with itself,
 * or I can create 0.5 * 10^9 by putting it in parallel with itself.
 * I can then repeat this process to create smaller and bigger resistors.
 * I repeat this until I have smallest resistor of 2^-40 * 10^9 (which is ~ 0.001 nanoOhm) and biggest resistor of 2^30 * 10^9 (which is ~ 1.07 * 10^18 nanoOhm).
 * Since max value of resistor we need to build is 10^18 nanoOhm and precision we need is 1 nanoOhm, with this we covered the whole space very well with values
 * that have logarithmic distance.
 * This is in total about 70 resistors. I always construct these 70 resistors/products first, and then I start building the final resistor.
 *
 * Now, we can construct the needed resistor by finding the biggest resistor smaller than the final resistor and putting it in series with the
 * biggest resistor that is smaller than the missing amount and we just repeat this process until precision of resistor we have built is good enough.
 * Since distance between our preconstructed resistors is logarithmic with base 2 it means that with each step we are halving the mistake between
 * our current resistor and wanted resistor, which means that a few dozen steps (certainly not more than 70) will be enough to build it.
 * This means we are in total never going to have more than 140 commands, which is way below the limit of 1000, and our time complexity is O(num_commands^2)
 * which is also small.
 */
class ResistorFactory {
public:
    vector <int> construct(long long nanoOhms) {
        vector<int> commands;
        vector<double> values;

        // We divide by 2 and multiply by 2 in order to build an inventory of resistors that we can then quickly
        // use to build resistor of any size.

        // Product 0 is 10^9 ohm.
        values.push_back(1000000000.0);

        // Products 1 to 30, each next is 2 times bigger => last one (#30) is 2^30 * 10^9 which is ~ 1.07 * 10^18.
        for (int i = 0; i < 30; i++) {
            commands.push_back(i);
            commands.push_back(i);
            commands.push_back(0);
            values.push_back(((double) values[values.size() - 1]) * 2);
        }

        // Product 31, which is 10^9 / 2 (product 0 / 2).
        commands.push_back(0);
        commands.push_back(0);
        commands.push_back(1);
        values.push_back(values[0] / 2);

        // Products 32 to 70. each is 2 times smaller => last one (#70) is 10^9 / 2^40, which is way below 0.1.
        for (int i = 31; i < 70; i++) {
            commands.push_back(i);
            commands.push_back(i);
            commands.push_back(1);
            values.push_back(((double) values[values.size() - 1]) / 2);
        }

        // cout << "Values (prepared):" << endl;
        // for (int i = 0; i < values.size(); i++) {
        //     cout << i << ": " << values[i] << endl;
        // }
        // cout << endl;

        // cout << "Start composing" << endl;
        // Now we use our inventory to build the final resistor.
        // I just find the biggest one that is smaller than remaining amount, add it to what I have built so far
        // and then move on.
        double remaining = nanoOhms;
        while (remaining > 0.01) {
            // cout << endl << "Remaining: " << remaining << endl;
            int bestIdx = -1; // Biggest product that is smaller than remaining amount.
            for (int i = 0; i < values.size(); i++) {
                if (values[i] <= remaining && (bestIdx == -1 || remaining - values[i] < remaining - values[bestIdx])) {
                    bestIdx = i;
                }
            }
            // cout << "Best idx:" << bestIdx << ", has value: " << values[bestIdx] << endl;

            // We put resistor we want to add in series with the last resistor/product we created.
            // This works even for the first step we do because last product at that moment is super small so it is like
            // adding with zero.
            commands.push_back(values.size() - 1);
            commands.push_back(bestIdx);
            commands.push_back(0);
            values.push_back(values[values.size() - 1] + values[bestIdx]);
            // cout << "Value added: " << values[values.size() - 1] << endl;

            remaining -= values[bestIdx];
        }

        return commands;
    }
};

int main() {
    ResistorFactory factory;
    const vector<int> commands = factory.construct(1200000000);
    cout << "Commands" << endl;
    for (int i = 0; i < commands.size(); i++) {
        cout << commands[i];
        if (i % 3 == 2) {
            cout << endl;
        } else {
            cout << ", ";
        }
    }
}
