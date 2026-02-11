#ifndef LOADER_H
#define LOADER_H

#include <vector>
#include <string>
#include <filesystem>
#include <map>

using namespace std;

namespace fs = filesystem;

/**
 * @file loader.h
 * @brief Header file for loading datasets and managing knapsack problem instances.
 */

/**
 * @struct Pallet
 * @brief Represents a pallet with an ID, weight, and profit.
 */
struct Pallet {
    int id;       ///< Unique identifier for the pallet.
    int weight;   ///< Weight of the pallet.
    int profit;   ///< Profit associated with the pallet.
};

/**
 * @struct Instance
 * @brief Represents a knapsack problem instance with pallets and capacity.
 */
struct Instance {
    int capacity;               ///< Maximum capacity of the truck.
    int numPallets;             ///< Number of pallets in the instance.
    vector<Pallet> pallets;     ///< List of pallets.
};

/**
 * @brief Prints the details of the selected pallets.
 *
 * This function calculates and displays the total profit, total weight,
 * and the IDs of the selected pallets in a knapsack solution.
 *
 * @param pallets A vector of selected pallets to be printed.
 */
void printSelectedPallets(const vector<Pallet>& pallets);

/**
 * @brief Reads a knapsack problem instance from truck and pallet files.
 *
 * @param truckPath Path to the truck file.
 * @param palletPath Path to the pallet file.
 * @return The loaded knapsack problem instance.
 */
Instance readInstance(const string& truckPath, const string& palletPath);

/**
 * @brief Displays the details of a knapsack problem instance.
 *
 * @param inst The instance to display.
 */
void showInstance(const Instance &inst);

/**
 * @brief Executes a selected algorithm on a dataset.
 *
 * @param datasetID Identifier of the dataset.
 * @param inst The knapsack problem instance.
 */
void executeAlgorithm(const string &datasetID, const Instance &inst);

/**
 * @brief Loads all datasets from a specified folder.
 *
 * @param folder Path to the folder containing dataset files.
 * @return A map of dataset identifiers to their corresponding instances.
 */
map<string, Instance> loadDatasets(const string &folder);

/**
 * @brief Evaluates all algorithms on a specific dataset and exports results.
 *
 * @param id Identifier of the dataset.
 * @param inst The knapsack problem instance.
 */
void evaluateAlgorithmsOnDataset(const string& id, const Instance& inst);

/**
 * @brief Times the execution of a knapsack algorithm.
 *
 * @param name Name of the algorithm.
 * @param inst The knapsack problem instance.
 * @param algorithm Pointer to the algorithm function.
 * @param repeat Number of repetitions for timing.
 * @param outProfit Output parameter for the profit of the last run.
 * @return Average execution time in microseconds.
 */
long long timeAlgorithm(const string& name,
                        const Instance& inst,
                        vector<Pallet> (*algorithm)(const Instance&),
                        int repeat,
                        int& outProfit = *(new int));

#endif // LOADER_H
