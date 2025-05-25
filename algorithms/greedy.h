#ifndef GREEDY_H
#define GREEDY_H

#include "../loader.h"

/**
 * @file greedy.h
 * @brief Header file for the greedy knapsack algorithm.
 */

/**
 * @struct PalletRatio
 * @brief Represents a pallet and its profit-to-weight ratio for the greedy knapsack algorithm.
 */
struct PalletRatio {
    Pallet pallet;  ///< The pallet being considered.
    double ratio;   ///< The profit-to-weight ratio of the pallet.
};

/**
 * @brief Solves the knapsack problem using a greedy approach.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
std::vector<Pallet> greedyKnapsack(const Instance& instance);

#endif // GREEDY_H
