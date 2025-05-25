#ifndef BRUTEFORCE_H
#define BRUTEFORCE_H

#include "../loader.h"

/**
 * @file bruteforce.h
 * @brief Header file for the brute-force knapsack algorithm.
 */

/**
 * @brief Performs a backtracking algorithm to solve the knapsack problem.
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
);

/**
 * @brief Solves the knapsack problem using a brute-force approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> bruteForceKnapsack(const Instance& instance);

#endif // BRUTEFORCE_H
