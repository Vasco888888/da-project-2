#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "../loader.h"

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
);

// Returns the list of selected pallets using brute-force.
std::vector<Pallet> bruteForceKnapsack(const Instance& instance);

#endif // BRUTEFORCE_H
