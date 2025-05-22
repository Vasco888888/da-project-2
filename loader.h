#ifndef LOADER_H
#define LOADER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <filesystem>
#include <map>
using namespace std;

namespace fs = filesystem;

// Structure representing a pallet.
struct Pallet {
    int id;
    int weight;
    int profit;

    bool operator==(const Pallet& other) const {
        return weight == other.weight && profit == other.profit;
    }
};

// Structure representing an instance (a pair of CSV files for a dataset).
struct Instance {
    int capacity;
    int numPallets;
    vector<Pallet> pallets;
};

// Reads an instance from the given TruckAndPallets and Pallets CSV files.
Instance readInstance(const string& truckPath, const string& palletPath);

// Displays the details of an instance.
void showInstance(const Instance &inst);

// Simulates execution of an algorithm on the given instance.
void executeAlgorithm(const string &datasetID, const Instance &inst);

// Loads all dataset instances from the given folder.
// Returns a map where the key is the dataset identifier and the value is the Instance.
map<string, Instance> loadDatasets(const string &folder);

#endif // LOADER_H
