#ifndef HYBRID_H
#define HYBRID_H

#include <vector>
#include "bruteforce.h"

std::vector<Pallet> hybridKnapsack(const Instance& instance);

void backtrack(
    const std::vector<Pallet>& pallets,
    int index,
    int currentWeight,
    int currentProfit,
    int capacity,
    std::vector<Pallet>& currentSet,
    std::vector<Pallet>& bestSet,
    int& bestProfit,
    int& bestWeight
);

#endif
