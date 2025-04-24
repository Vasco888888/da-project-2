#include "dynamic.h"

#include <algorithm>
#include <vector>
using namespace std;

vector<Pallet> dynamic(const Instance& instance) {
    int n = instance.pallets.size();
    int W = instance.capacity;
    int maxPallets = instance.numPallets;

    // 3D DP table to store max profit: dp[i][w][k]
    vector dp(n + 1, vector(W + 1, vector<int>(maxPallets + 1, 0)));
    vector keep(n + 1, vector(W + 1, vector<bool>(maxPallets + 1, false)));

    // Fill DP table
    for (int i = 1; i <= n; ++i) {
        const auto& pallet = instance.pallets[i - 1];
        for (int w = 0; w <= W; ++w) {
            for (int k = 1; k <= maxPallets; ++k) {
                // If pallet fits in current weight
                if (pallet.weight <= w) {
                    int profitWith = dp[i - 1][w - pallet.weight][k - 1] + pallet.profit;
                    int profitWithout = dp[i - 1][w][k];

                    if (profitWith > profitWithout) {
                        dp[i][w][k] = profitWith;
                        keep[i][w][k] = true;
                    } else {
                        dp[i][w][k] = profitWithout;
                    }
                } else {
                    dp[i][w][k] = dp[i - 1][w][k];
                }
            }
        }
    }

    // Backtrack to reconstruct chosen pallets
    vector<Pallet> selected;
    int w = W, k = maxPallets;
    for (int i = n; i > 0; --i) {
        if (keep[i][w][k]) {
            const auto& pallet = instance.pallets[i - 1];
            selected.push_back(pallet);
            w -= pallet.weight;
            --k;
        }
    }

    // Reverse the selected pallets to maintain original order
    std::reverse(selected.begin(), selected.end());

    return selected;
}
