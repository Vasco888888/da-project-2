#include "hybrid.h"
#include <vector>
#include <algorithm>

using namespace std;

/**
 * @brief Solves the knapsack problem using a hybrid approach combining multiple strategies.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> hybridKnapsack(const Instance& instance) {
    // Step 1: Greedy baseline
    vector<Pallet> greedySet = greedyKnapsack(instance);
    int bestProfit = 0, bestWeight = 0;
    for (const auto& p : greedySet) {
        bestProfit += p.profit;
        bestWeight += p.weight;
    }

    // Step 2: Prepare candidate set
    vector<Pallet> candidates = greedySet;
    int subsetSize = greedySet.size() + max(1, static_cast<int>(instance.pallets.size() * 0.30));

    vector<Pallet> sortedByRatio = instance.pallets;
    sort(sortedByRatio.begin(), sortedByRatio.end(), [](const Pallet& a, const Pallet& b) {
        return double(a.profit) / a.weight > double(b.profit) / b.weight;
    });

    for (const auto& p : sortedByRatio) {
        if (find_if(candidates.begin(), candidates.end(), [&](const Pallet& existing) {
            return existing.id == p.id;
        }) == candidates.end()) {
            candidates.push_back(p);
            if ((int)candidates.size() >= subsetSize)
                break;
        }
    }

    // Step 3: Run limited backtracking
    vector<Pallet> currentSet;
    vector<Pallet> bestSet = greedySet;
    backtrack(candidates, 0, 0, 0, instance.capacity, currentSet, bestSet, bestProfit, bestWeight);

    sort(bestSet.begin(), bestSet.end(), [](const Pallet& a, const Pallet& b) {
        return a.id < b.id;
    });

    return bestSet;
}
