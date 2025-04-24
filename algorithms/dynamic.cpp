#include "dynamic.h"
#include <vector>
#include <algorithm>
using namespace std;

vector<Pallet> dynamic(const Instance& instance) {
    int n = instance.pallets.size();
    int W = instance.capacity;
    int maxPallets = instance.numPallets;

    // Only keep two layers of DP for current and previous
    vector dp(2, vector(W + 1, vector<int>(maxPallets + 1, 0)));
    vector keep(n + 1, vector(W + 1, vector<bool>(maxPallets + 1, false)));

    for (int i = 1; i <= n; ++i) {
        const auto& pallet = instance.pallets[i - 1];
        int cur = i % 2;
        int prev = 1 - cur;

        for (int w = 0; w <= W; ++w) {
            for (int k = 1; k <= maxPallets; ++k) {
                if (pallet.weight <= w) {
                    int withPallet = dp[prev][w - pallet.weight][k - 1] + pallet.profit;
                    int withoutPallet = dp[prev][w][k];

                    if (withPallet > withoutPallet) {
                        dp[cur][w][k] = withPallet;
                        keep[i][w][k] = true;
                    } else {
                        dp[cur][w][k] = withoutPallet;
                    }
                } else {
                    dp[cur][w][k] = dp[prev][w][k];
                }
            }
        }
    }

    // Backtrack to reconstruct solution
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
    reverse(selected.begin(), selected.end());

    return selected;
}
