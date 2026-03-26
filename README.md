# Sorting Algorithm Time Complexity Analysis

A performance benchmarking suite designed to empirically measure and visualize the Big-O time complexity of various sorting algorithms across different data distributions.

# Overview

This project implements and analyzes the execution efficiency of four fundamental sorting algorithms:
- Bubble Sort
- Insertion Sort
- Selection Sort
- Quicksort (with optimized pivot selection for best-case analysis)

The system measures execution time for **Best**, **Average**, and **Worst** case scenarios across varying input sizes (up to 10,000 elements), providing empirical evidence for theoretical Big-O complexity.

# Key Features

- **Empirical Benchmarking:** Uses C++ `<chrono>` high-resolution clock for precise microsecond-level timing.
- **Automated Data Collection:** Generates and tests algorithms against multiple data distributions:
    - **Best Case:** Already sorted arrays.
    - **Average Case:** Randomly shuffled arrays.
    - **Worst Case:** Reverse-sorted arrays.
- **Statistical Rigor:** Runs multiple iterations per size to calculate mean execution time and standard deviation (visualized as error bars).
- **Data Visualization:** A Python-based plotting engine generates performance curves in both linear and logarithmic scales to highlight growth rates.

## Project Structure

- `project_1.cpp`: The core benchmarking engine implemented in C++.
- `plotData.py`: Data visualization script using Matplotlib and NumPy.
- `graphs/`: Contains generated performance plots.
- `*.csv`: Raw timing data for best, average, and worst cases.

## Getting Started

### Prerequisites

- C++ Compiler (GCC/Clang)
- Python 3.x
- Python Libraries: `numpy`, `matplotlib`

### Running the Benchmark

1. **Compile and run the C++ engine:**
   ```bash
   g++ -O3 project_1.cpp -o benchmark
   ./benchmark
   ```
   This generates `best.csv`, `average.csv`, and `worst.csv`.

2. **Generate Visualizations:**
   ```bash
   python3 plotData.py --data average.csv --case Average --save average_fig
   python3 plotData.py --data best.csv --case Best --save best_fig
   python3 plotData.py --data worst.csv --case Worst --save worst_fig
   ```

## Results & Analysis

The generated graphs (located in the `graphs/` directory) demonstrate the clear distinction between $O(n^2)$ algorithms (Bubble, Insertion, Selection) and $O(n \log n)$ algorithms (Quicksort).

### Example Visualization:
The log-scale plots are particularly useful for observing the power-law relationship between input size and execution time, making the complexity classes easily identifiable.

---
*Developed as part of a Data Structures & Algorithms study.*
