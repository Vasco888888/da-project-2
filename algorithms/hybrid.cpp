#include "hybrid.h"
#include "greedy.h"
#include "bruteforce.h"  // for backtrack function
#include <vector>
#include <algorithm>

using namespace std;

vector<Pallet> hybridKnapsack(const Instance& instance, int extraMargin = 20) {
    // Step 1: Get greedy solution and initial profit
    vector<Pallet> greedySet = greedyKnapsack(instance);

    int bestProfit = 0;
    for (const auto& p : greedySet) {
        bestProfit += p.profit;
    }

    // Step 2: Build candidate set starting with greedy pallets
    vector<Pallet> candidates = greedySet;

    int subsetSize = greedySet.size() + extraMargin;


    // Sort all pallets by profit/weight ratio descending
    vector<Pallet> sortedByRatio = instance.pallets;
    sort(sortedByRatio.begin(), sortedByRatio.end(), [](const Pallet& a, const Pallet& b) {
        return double(a.profit) / a.weight > double(b.profit) / b.weight;
    });

    // Add pallets to candidates until reaching subsetSize, skipping duplicates
    for (const auto& p : sortedByRatio) {
        if (find_if(candidates.begin(), candidates.end(),
                    [&](const Pallet& existing) {
                        return existing.id == p.id;  // safer than full object comparison
                    }) == candidates.end()) {
            candidates.push_back(p);
            if ((int)candidates.size() >= subsetSize)
                break;
                    }
    }

    // Step 3: Use backtracking on reduced candidate set to try improving best solution
    vector<Pallet> currentSet;
    vector<Pallet> bestSet = greedySet;

    backtrack(candidates, 0, 0, 0, instance.capacity, instance.numPallets,
              currentSet, bestSet, bestProfit);

    return bestSet;
}
