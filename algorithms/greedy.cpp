#include "greedy.h"
#include <algorithm>

using namespace std;

/**
 * @brief Solves the knapsack problem using a greedy approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> greedyKnapsack(const Instance& instance) {
    vector<PalletRatio> palletRatios;

    for (const auto& p : instance.pallets) {
        double r = 1.0 * p.profit / p.weight;
        palletRatios.push_back({p, r});
    }

    stable_sort(palletRatios.begin(), palletRatios.end(),
         [](const PalletRatio& a, const PalletRatio& b) {
             return a.ratio > b.ratio;
         });

    vector<Pallet> selected;
    int remainingCapacity = instance.capacity;

    for (const auto& pr : palletRatios) {
        if (pr.pallet.weight <= remainingCapacity) {
            selected.push_back(pr.pallet);
            remainingCapacity -= pr.pallet.weight;
        }
    }

    return selected;
}
