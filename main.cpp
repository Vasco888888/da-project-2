#include <iostream>
#include "loader.h"
using namespace std;

int main() {
    // Change this folder path if needed.
    string folder = "datasets-extra";

    // Check if the folder exists.
    if (!filesystem::exists(folder)) {
        cerr << "Error: Directory '" << folder << "' not found.\n";
        return 1;
    }

    // Load all datasets from the specified folder.
    map<string, Instance> instances = loadDatasets(folder);

    int option = 0;
    do {
        cout << "\n====== Pallet Packing Optimization Menu ======\n";
        cout << "1. List available datasets\n";
        cout << "2. View dataset details\n";
        cout << "3. Execute algorithm on a dataset\n";
        cout << "4. Exit\n";
        cout << "Option: ";
        cin >> option;

        switch (option) {
            case 1: {
                cout << "\nAvailable datasets:\n";
                for (const auto& [key, instance] : instances) {
                    cout << "\tDataset " << key << "\n";
                }
                break;
            }
            case 2: {
                string ds;
                cout << "Enter the dataset identifier (e.g., 01): ";
                cin >> ds;
                if (instances.find(ds) != instances.end()) {
                    cout << "\n=== Details of Dataset " << ds << " ===\n";
                    showInstance(instances[ds]);
                } else {
                    cout << "Dataset not found.\n";
                }
                break;
            }
            case 3: {
                string ds;
                cout << "Enter the dataset identifier (e.g., 01): ";
                cin >> ds;
                if (instances.find(ds) != instances.end()) {
                    executeAlgorithm(ds, instances[ds]);
                } else {
                    cout << "Dataset not found.\n";
                }
                break;
            }
            case 4: {
                cout << "Exiting...\n";
                break;
            }
            default: {
                cout << "Invalid option! Please try again.\n";
                break;
            }
        }
    } while (option != 4);

    return 0;
}
