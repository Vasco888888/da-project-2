#include "dynamic.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Solves the knapsack problem using a dynamic programming approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> dynamic(const Instance& instance) {
    int n = instance.pallets.size();
    int W = instance.capacity;

    vector<vector<State>> dp(n + 1, vector<State>(W + 1));

    for (int i = 1; i <= n; ++i) {
        const auto& p = instance.pallets[i - 1];
        for (int w = 0; w <= W; ++w) {
            // Not taking current pallet
            dp[i][w] = dp[i - 1][w];

            // Try including the current pallet
            if (w >= p.weight) {
                const auto& prev = dp[i - 1][w - p.weight];
                int newProfit = prev.profit + p.profit;
                int newPallets = prev.pallets + 1;
                int newWeight = prev.totalWeight + p.weight;

                const auto& curr = dp[i][w];

                if (newProfit > curr.profit ||
                    (newProfit == curr.profit && newPallets < curr.pallets) ||
                    (newProfit == curr.profit && newPallets == curr.pallets && newWeight < curr.totalWeight)) {
                    dp[i][w] = { newProfit, newPallets, newWeight };
                }
            }
        }
    }

    // Find the best result
    State bestState;
    int bestW = 0;
    for (int w = 0; w <= W; ++w) {
        const auto& s = dp[n][w];
        if (s.profit > bestState.profit ||
            (s.profit == bestState.profit && s.pallets < bestState.pallets) ||
            (s.profit == bestState.profit && s.pallets == bestState.pallets && s.totalWeight < bestState.totalWeight)) {
            bestState = s;
            bestW = w;
        }
    }

    // Backtrack to reconstruct the selected pallets
    vector<Pallet> selected;
    int w = bestW;
    for (int i = n; i > 0; --i) {
        if (dp[i][w].profit != dp[i - 1][w].profit ||
            dp[i][w].pallets != dp[i - 1][w].pallets) {
            const auto& p = instance.pallets[i - 1];
            selected.push_back(p);
            w -= p.weight;
        }
    }

    reverse(selected.begin(), selected.end());
    return selected;
}
