#include "bruteforce.h"
#include <vector>

using namespace std;

/**
 * @brief Recursive backtracking function to explore all possible combinations of pallets.
 *
 * @param pallets The list of pallets to consider.
 * @param index The current index in the list of pallets.
 * @param currentWeight The current total weight of the selected pallets.
 * @param currentProfit The current total profit of the selected pallets.
 * @param capacity The maximum weight capacity of the knapsack.
 * @param currentSet The current set of selected pallets.
 * @param bestSet The best set of pallets found so far.
 * @param bestProfit The best profit found so far.
 * @param bestWeight The weight of the best set found so far.
 */
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

/**
 * @brief Solves the knapsack problem using a brute-force approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> bruteForceKnapsack(const Instance& instance) {
    vector<Pallet> bestSet;
    vector<Pallet> currentSet;
    int bestProfit = 0;
    int bestWeight = INT_MAX;

    backtrack(instance.pallets, 0, 0, 0, instance.capacity, currentSet, bestSet, bestProfit, bestWeight);

    return bestSet;
}
