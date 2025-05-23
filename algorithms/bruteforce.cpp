#include "bruteforce.h"
#include <vector>

using namespace std;

void backtrack(
    const vector<Pallet>& pallets,
    int index,
    int currentWeight,
    int currentProfit,
    int capacity,
    vector<Pallet>& currentSet,
    vector<Pallet>& bestSet,
    int& bestProfit,
    int& bestWeight
) {
    if (index == pallets.size()) {
        if (currentProfit > bestProfit ||
            (currentProfit == bestProfit && currentSet.size() < bestSet.size()) ||
            (currentProfit == bestProfit && currentSet.size() == bestSet.size() && currentWeight < bestWeight)) {

            bestProfit = currentProfit;
            bestWeight = currentWeight;
            bestSet = currentSet;
            }
        return;
    }

    // Include current pallet
    const Pallet& p = pallets[index];
    if (currentWeight + p.weight <= capacity) {
        currentSet.push_back(p);
        backtrack(pallets, index + 1, currentWeight + p.weight, currentProfit + p.profit,
                  capacity,currentSet, bestSet, bestProfit, bestWeight);
        currentSet.pop_back();
    }

    // Exclude current pallet
    backtrack(pallets, index + 1, currentWeight, currentProfit,
              capacity, currentSet, bestSet, bestProfit, bestWeight);
}

vector<Pallet> bruteForceKnapsack(const Instance& instance) {
    vector<Pallet> bestSet;
    vector<Pallet> currentSet;
    int bestProfit = 0;
    int bestWeight = INT_MAX;

    backtrack(instance.pallets, 0, 0, 0, instance.capacity, currentSet, bestSet, bestProfit, bestWeight);

    return bestSet;
}
