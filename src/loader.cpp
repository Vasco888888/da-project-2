#include "loader.h"
#include "algorithms/bruteforce.h"
#include "algorithms/dynamic.h"
#include "algorithms/greedy.h"
#include "algorithms/hybrid.h"
#include <chrono>
#include <fstream>
#include <iostream>


using namespace std;

/**
 * @brief Prints the details of the selected pallets.
 *
 * This function calculates and displays the total profit, total weight,
 * and the IDs of the selected pallets in a knapsack solution.
 *
 * @param pallets A vector of selected pallets to be printed.
 */
void printSelectedPallets(const std::vector<Pallet> &pallets) {
  int totalWeight = 0;
  int totalProfit = 0;

  for (const auto &p : pallets) {
    totalWeight += p.weight;
    totalProfit += p.profit;
  }

  std::cout << "Total Profit: " << totalProfit << "\n";
  std::cout << "Total Weight: " << totalWeight << "\n";

  std::cout << "Selected pallet IDs: ";
  for (const auto &p : pallets) {
    std::cout << p.id << " ";
  }
  std::cout << "\n";
}

/**
 * @brief Reads a knapsack problem instance from truck and pallet files.
 *
 * @param truckPath Path to the truck file.
 * @param palletPath Path to the pallet file.
 * @return The loaded knapsack problem instance.
 */
Instance readInstance(const string &truckPath, const string &palletPath) {
  Instance instance;
  ifstream truckFile(truckPath);
  ifstream palletFile(palletPath);
  string line;

  // Read the TruckAndPallets file.
  if (truckFile.is_open()) {
    getline(truckFile, line); // Skip header.
    if (getline(truckFile, line)) {
      stringstream ss(line);
      string value;
      getline(ss, value, ',');
      instance.capacity = stoi(value);
      getline(ss, value, ',');
      instance.numPallets = stoi(value);
    }
    truckFile.close();
  } else {
    cerr << "Error opening file: " << truckPath << "\n";
  }

  // Read the Pallets file.
  if (palletFile.is_open()) {
    getline(palletFile, line); // Skip header.
    while (getline(palletFile, line)) {
      stringstream ss(line);
      string value;
      Pallet p;
      getline(ss, value, ',');
      p.id = stoi(value);
      getline(ss, value, ',');
      p.weight = stoi(value);
      getline(ss, value, ',');
      p.profit = stoi(value);
      instance.pallets.push_back(p);
    }
    palletFile.close();
  } else {
    cerr << "Error opening file: " << palletPath << "\n";
  }

  return instance;
}

/**
 * @brief Displays the details of a knapsack problem instance.
 *
 * @param inst The instance to display.
 */
void showInstance(const Instance &inst) {
  cout << "Truck capacity: " << inst.capacity << "\n";
  cout << "Number of pallets (from TruckAndPallets file): " << inst.numPallets
       << "\n";
  cout << "Pallet details:\n";
  for (const auto &p : inst.pallets) {
    cout << "\tPallet " << p.id << ": Weight = " << p.weight
         << ", Profit = " << p.profit << "\n";
  }
}

/**
 * @brief Executes a selected algorithm on a dataset.
 *
 * @param datasetID Identifier of the dataset.
 * @param inst The knapsack problem instance.
 */
void executeAlgorithm(const string &datasetID, const Instance &inst) {
  int algoOption = 0;
  cout << "\nChoose an algorithm:\n";
  cout << "1. Exhaustive Search (Brute Force)\n";
  cout << "2. Dynamic Programming\n";
  cout << "3. Greedy Algorithm\n";
  cout << "4. Hybrid Algorithm\n";
  cout << "Option: ";
  cin >> algoOption;

  switch (algoOption) {
  case 1:
    std::cout << "\nExecuting Exhaustive Search on dataset " << datasetID
              << "...\n";
    {
      auto selected = bruteForceKnapsack(inst);
      printSelectedPallets(selected);
    }
    break;
  case 2:
    cout << "\nExecuting Dynamic Programming on dataset " << datasetID
         << "...\n";
    {
      auto selected = dynamic(inst);
      printSelectedPallets(selected);
    }
    break;
  case 3:
    std::cout << "\nExecuting Greedy Algorithm on dataset " << datasetID
              << "...\n";
    {
      auto selected = greedyKnapsack(inst);
      printSelectedPallets(selected);
    }
    break;
  case 4:
    std::cout << "\nExecuting Hybrid Algorithm on dataset " << datasetID
              << "...\n";
    {
      auto selected = hybridKnapsack(inst);
      printSelectedPallets(selected);
    }
    break;
  default:
    cout << "\nInvalid option. Returning to main menu.\n";
    break;
  }
}

/**
 * @brief Loads all datasets from a specified folder.
 *
 * @param folder Path to the folder containing dataset files.
 * @return A map of dataset identifiers to their corresponding instances.
 */
map<string, Instance> loadDatasets(const string &folder) {
  map<string, string> trucks;
  map<string, string> pallets;
  // Iterate over the given folder.
  for (const auto &entry : fs::directory_iterator(folder)) {
    string filename = entry.path().filename().string();
    // Check for the file prefix using rfind (compatible with C++17).
    if (filename.rfind("TruckAndPallets_", 0) == 0) {
      // Assumes the filename pattern "TruckAndPallets_XX.csv"
      string key = filename.substr(string("TruckAndPallets_").size(), 2);
      trucks[key] = entry.path().string();
    } else if (filename.rfind("Pallets_", 0) == 0) {
      string key = filename.substr(string("Pallets_").size(), 2);
      pallets[key] = entry.path().string();
    }
  }
  map<string, Instance> instances;
  // Combine truck and pallet files based on matching keys.
  for (const auto &[key, truckPath] : trucks) {
    if (pallets.count(key)) {
      string palletPath = pallets[key];
      Instance instance = readInstance(truckPath, palletPath);
      instances[key] = instance;
    }
  }
  return instances;
}

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
long long timeAlgorithm(const string &name, const Instance &inst,
                        vector<Pallet> (*algorithm)(const Instance &),
                        int repeat, int &outProfit) {
  outProfit = 0;
  long long totalTime = 0;

  for (int i = 0; i < repeat; ++i) {
    auto start = chrono::high_resolution_clock::now();
    auto result = algorithm(inst);
    auto end = chrono::high_resolution_clock::now();

    int profit = 0;
    for (const auto &p : result)
      profit += p.profit;
    outProfit = profit; // save last profit (assuming deterministic)

    totalTime += duration_cast<chrono::microseconds>(end - start).count();
  }
  cout << name << " average time over " << repeat
       << " runs: " << (totalTime / repeat) << " us, Profit: " << outProfit
       << "\n";
  return totalTime / repeat;
}

/**
 * @brief Evaluates all algorithms on a specific dataset and exports results.
 *
 * @param id Identifier of the dataset.
 * @param inst The knapsack problem instance.
 */
void evaluateAlgorithmsOnDataset(const string &id, const Instance &inst) {
  ofstream out("data/evaluation_single.csv");
  out << "Algorithm,AvgTime(us),Profit\n";

  int profitGreedy, profitBrute, profitDyn, profitHybrid;

  long long timeGreedy =
      timeAlgorithm("Greedy", inst, greedyKnapsack, 20, profitGreedy);
  long long timeBrute =
      timeAlgorithm("BruteForce", inst, bruteForceKnapsack, 20, profitBrute);
  long long timeDyn = timeAlgorithm("Dynamic", inst, dynamic, 20, profitDyn);
  long long timeHybrid =
      timeAlgorithm("Hybrid", inst, hybridKnapsack, 20, profitHybrid);

  out << "Greedy," << timeGreedy << "," << profitGreedy << "\n";
  out << "BruteForce," << timeBrute << "," << profitBrute << "\n";
  out << "Dynamic," << timeDyn << "," << profitDyn << "\n";
  out << "Hybrid," << timeHybrid << "," << profitHybrid << "\n";

  out.close();

  cout << "\nEvaluation complete for dataset " << id << ".\n";
  cout << "Results saved to 'data/evaluation_single.csv'.\n";
}
