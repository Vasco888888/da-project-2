# Knapsack Solver Project

## Overview
This project implements several algorithms to solve the **Knapsack problem** — a classic optimization challenge. It includes:

- **Brute Force (Exhaustive Search)**
- **Dynamic Programming**
- **Greedy Algorithm**
- **Hybrid Algorithm** (combines greedy with limited backtracking)

The program loads datasets describing pallets and truck capacities, runs selected algorithms, measures performance, and exports evaluation results.

---

## Features

- Load multiple datasets from CSV files.
- Support for different algorithm strategies.
- Performance measurement (average time and profit).
- Export evaluation results in CSV format.
- Command-line interface to select and run algorithms interactively.
- Modular design for easy extension and testing.

---

## Project Structure

/algorithms  
├─ bruteForce.h / bruteForce.cpp  
├─ dynamic.h / dynamic.cpp  
├─ greedy.h / greedy.cpp  
├─ hybrid.h / hybrid.cpp  
/loader.h  
/loader.cpp  
/main.cpp  
/evaluation_single.csv (output file)  
README.md

---

## Dataset Format

- **TruckAndPallets_XX.csv**  
  Contains truck capacity and number of pallets.

- **Pallets_XX.csv**  
  Contains pallets data: id, weight, profit.

Files must be placed in the same folder for the program to load datasets successfully.

---

## Algorithms Summary

- **Brute Force**: Exhaustively tries all pallet combinations. Accurate but slow for large datasets.
- **Dynamic Programming**: Uses tabulation for efficient exact solution.
- **Greedy**: Picks pallets by highest profit-to-weight ratio, fast but approximate.
- **Hybrid**: Starts with greedy, extends candidate set, and applies limited backtracking for improvement.

---

## Notes

- Pallets in output are sorted by ID (except for greedy).
- Timing measurements are averaged over multiple runs (default 20).
- The hybrid algorithm balances solution quality and runtime.