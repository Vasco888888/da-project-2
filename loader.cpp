#include "loader.h"
#include "algorithms/bruteforce.h"
#include "algorithms/greedy.h"
#include "algorithms/dynamic.h"
#include "algorithms/linear.h"
using namespace std;

void printSelectedPallets(const std::vector<Pallet>& pallets) {
    int totalWeight = 0;
    int totalProfit = 0;

    for (const auto& p : pallets) {
        totalWeight += p.weight;
        totalProfit += p.profit;
    }

    std::cout << "Total Profit: " << totalProfit << "\n";
    std::cout << "Total Weight: " << totalWeight << "\n";

    std::cout << "Selected pallet IDs: ";
    for (const auto& p : pallets) {
        std::cout << p.id << " ";
    }
    std::cout << "\n";
}


Instance readInstance(const string& truckPath, const string& palletPath) {
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

void showInstance(const Instance &inst) {
    cout << "Truck capacity: " << inst.capacity << "\n";
    cout << "Number of pallets (from TruckAndPallets file): " << inst.numPallets << "\n";
    cout << "Pallet details:\n";
    for (const auto &p : inst.pallets) {
        cout << "\tPallet " << p.id << ": Weight = " << p.weight
                  << ", Profit = " << p.profit << "\n";
    }
}

void executeAlgorithm(const string &datasetID, const Instance &inst) {
    int algoOption = 0;
    cout << "\nChoose an algorithm:\n";
    cout << "1. Exhaustive Search (Brute Force)\n";
    cout << "2. Dynamic Programming\n";
    cout << "3. Greedy Algorithm\n";
    cout << "4. Integer Linear Programming (ILP)\n";
    cout << "Option: ";
    cin >> algoOption;

    switch (algoOption) {
        case 1:
            std::cout << "\nExecuting Exhaustive Search on dataset " << datasetID << "...\n";
        {
            auto selected = bruteForceKnapsack(inst);
            printSelectedPallets(selected);
        }
        break;
        case 2:
            cout << "\nExecuting Dynamic Programming on dataset " << datasetID << "...\n";
        {
            auto selected = dynamic(inst);
            printSelectedPallets(selected);
        }
        break;
        case 3:
            std::cout << "\nExecuting Greedy Algorithm on dataset " << datasetID << "...\n";
        {
            auto selected = greedyKnapsack(inst);
            printSelectedPallets(selected);
        }
        break;
        case 4:
            cout << "\nExecuting ILP on dataset " << datasetID << "...\n";
            // TODO: Implement the ILP algorithm.
            break;
        default:
            cout << "\nInvalid option. Returning to main menu.\n";
            break;
    }
}

map<string, Instance> loadDatasets(const string &folder) {
    map<string, string> trucks;
    map<string, string> pallets;
    // Iterate over the given folder.
    for (const auto& entry : fs::directory_iterator(folder)) {
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
    for (const auto& [key, truckPath] : trucks) {
        if (pallets.count(key)) {
            string palletPath = pallets[key];
            Instance instance = readInstance(truckPath, palletPath);
            instances[key] = instance;
        }
    }
    return instances;
}


