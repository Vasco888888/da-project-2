#include <vector>
#include "bruteforce.h"

using namespace std;

void backtrack(
    const vector<Pallet>& pallets,
    int index,
    int currentWeight,
    int currentProfit,
    int capacity,
    int maxPallets,
    vector<Pallet>& currentSet,
    vector<Pallet>& bestSet,
    int& bestProfit
) {
    if (currentSet.size() > maxPallets) {
        return; // Exceeded the maximum number of pallets
    }

    if (index == pallets.size()) {
        if (currentProfit > bestProfit || (currentProfit == bestProfit && currentSet.size() < bestSet.size())) {
            bestProfit = currentProfit;
            bestSet = currentSet;
        }
        return;
    }

    // Option 1: incluir este pallet
    const Pallet& p = pallets[index];
    if (currentWeight + p.weight <= capacity) {
        currentSet.push_back(p);
        backtrack(pallets, index + 1, currentWeight + p.weight, currentProfit + p.profit,
                  capacity, maxPallets, currentSet, bestSet, bestProfit);
        currentSet.pop_back(); // backtrack
    }

    // Option 2: ignorar este pallet
    backtrack(pallets, index + 1, currentWeight, currentProfit, capacity, maxPallets, currentSet, bestSet, bestProfit);
}

vector<Pallet> bruteForceKnapsack(const Instance& instance) {
    vector<Pallet> bestSet;
    vector<Pallet> currentSet;
    int bestProfit = 0;

    backtrack(instance.pallets, 0, 0, 0, instance.capacity, instance.numPallets, currentSet, bestSet, bestProfit);

    return bestSet;
}
