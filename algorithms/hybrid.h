#ifndef HYBRID_H
#define HYBRID_H

#include <vector>
#include "bruteforce.h"

/**
 * @file hybrid.h
 * @brief Header file for the hybrid knapsack algorithm.
 */

/**
 * @brief Solves the knapsack problem using a hybrid approach combining multiple strategies.
 *
 * @param instance The knapsack problem instance containing pallets and capacity.
 * @return A vector of selected pallets that maximize profit while respecting constraints.
 */
vector<Pallet> hybridKnapsack(const Instance& instance);

#endif
