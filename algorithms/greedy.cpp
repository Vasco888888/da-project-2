#include "greedy.h"
#include <algorithm>

using namespace std;

struct PalletRatio {
    Pallet pallet;
    double ratio;
};

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
    int remainingPallets = instance.numPallets;

    for (const auto& pr : palletRatios) {
        if (pr.pallet.weight <= remainingCapacity && remainingPallets > 0) {
            selected.push_back(pr.pallet);
            remainingCapacity -= pr.pallet.weight;
            -- remainingPallets;
        }
    }

    return selected;
}
