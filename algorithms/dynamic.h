#ifndef DYNAMIC_H
#define DYNAMIC_H

#include "../loader.h"

/**
 * @file dynamic.h
 * @brief Header file for the dynamic programming knapsack algorithm.
 */

/**
 * @struct State
 * @brief Represents the state of the dynamic programming table for the knapsack problem.
 */
struct State {
    int profit = 0;       ///< Total profit for the current state.
    int pallets = 0;      ///< Number of pallets used in the current state.
    int totalWeight = 0;  ///< Total weight of the pallets in the current state.
};

/**
 * @brief Solves the knapsack problem using a dynamic programming approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> dynamic(const Instance& instance);

#endif //DYNAMIC_H
