#include "dynamic.h"
#include <vector>
#include <algorithm>
using namespace std;

struct State {
    int profit = 0;
    int pallets = 0; // number of pallets used
};

vector<Pallet> dynamic(const Instance& instance) {
    int n = instance.pallets.size();
    int W = instance.capacity;

    vector<State> dp(W + 1);
    vector<int> prev(W + 1, -1);   // to track previous weight
    vector<int> choice(W + 1, -1); // to track chosen item index

    for (int i = 0; i < n; ++i) {
        const auto& p = instance.pallets[i];
        for (int w = W; w >= p.weight; --w) {
            int newProfit = dp[w - p.weight].profit + p.profit;
            int newPallets = dp[w - p.weight].pallets + 1;

            const auto& cur = dp[w];

            // Update if better profit, or same profit with fewer pallets
            if (newProfit > cur.profit || (newProfit == cur.profit && newPallets < cur.pallets)) {
                dp[w].profit = newProfit;
                dp[w].pallets = newPallets;
                prev[w] = w - p.weight;
                choice[w] = i;
            }
        }
    }

    // Find best profit and minimum pallets at best profit
    int bestWeight = 0;
    for (int w = 1; w <= W; ++w) {
        if (dp[w].profit > dp[bestWeight].profit ||
            (dp[w].profit == dp[bestWeight].profit && dp[w].pallets < dp[bestWeight].pallets)) {
            bestWeight = w;
            }
    }

    // Reconstruct solution
    vector<Pallet> selected;
    int w = bestWeight;
    while (choice[w] != -1) {
        selected.push_back(instance.pallets[choice[w]]);
        w = prev[w];
    }
    reverse(selected.begin(), selected.end());

    return selected;
}
