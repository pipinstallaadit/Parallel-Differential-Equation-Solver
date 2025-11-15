#include <iostream>
#include <vector>
#include <cmath>
#include <fstream> 
#include <omp.h>   

const int GRID_SIZE = 100;
const int MAX_ITERATIONS = 10000;
const double CONVERGENCE_THRESHOLD = 1e-5;

// Define a 3D grid type
typedef std::vector<std::vector<std::vector<double>>> Grid3D;

int main() {
    // Allocate two 3D grids
    Grid3D grid(GRID_SIZE, std::vector<std::vector<double>>(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0)));
    Grid3D grid_new(GRID_SIZE, std::vector<std::vector<double>>(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0)));

    // --- Set Boundary Conditions ---
    // Set the "West" face (i=0) to 100.0 degrees
    for (int j = 0; j < GRID_SIZE; ++j) {
        for (int k = 0; k < GRID_SIZE; ++k) {
            grid[0][j][k] = 100.0;
            grid_new[0][j][k] = 100.0;
        }
    }
    
    std::cout << "Starting 3D Jacobi iteration on " << GRID_SIZE << "x" 
              << GRID_SIZE << "x" << GRID_SIZE << " grid..." << std::endl;
    
    double max_change = 0.0;
    int iterations = 0;
    double start_time = omp_get_wtime();

    for (iterations = 0; iterations < MAX_ITERATIONS; ++iterations) {
        max_change = 0.0;

        // --- Parallel Calculation (3D) ---
        #pragma omp parallel for collapse(3) reduction(max:max_change)
        for (int i = 1; i < GRID_SIZE - 1; ++i) { // X-axis
            for (int j = 1; j < GRID_SIZE - 1; ++j) { // Y-axis
                for (int k = 1; k < GRID_SIZE - 1; ++k) { // Z-axis
                    
                    grid_new[i][j][k] = (1.0/6.0) * (grid[i-1][j][k] + // West
                                                    grid[i+1][j][k] + // East
                                                    grid[i][j-1][k] + // South
                                                    grid[i][j+1][k] + // North
                                                    grid[i][j][k-1] + // Down
                                                    grid[i][j][k+1]); // Up
                    
                    double change = std::fabs(grid_new[i][j][k] - grid[i][j][k]);
                    if (change > max_change) {
                        max_change = change;
                    }
                }
            }
        }

        grid.swap(grid_new);

        if (max_change < CONVERGENCE_THRESHOLD) {
            std::cout << "Converged after " << iterations << " iterations." << std::endl;
            break;
        }
    }

    double end_time = omp_get_wtime();
    std::cout << "---" << std::endl;
    std::cout << "Final max change: " << max_change << std::endl;
    std::cout << "Total time taken: " << (end_time - start_time) << " seconds." << std::endl;

    // --- NEW: Save 3 different 2D slices ---
    
    int mid_i = GRID_SIZE / 2;
    int mid_j = GRID_SIZE / 2;
    int mid_k = GRID_SIZE / 2;

    // 1. Save YZ slice (at a fixed X = mid_i)
    std::cout << "Writing YZ slice to slice_YZ.dat..." << std::endl;
    std::ofstream out_yz("slice_YZ.dat");
    for (int j = 0; j < GRID_SIZE; ++j) {
        for (int k = 0; k < GRID_SIZE; ++k) {
            out_yz << grid[mid_i][j][k] << " ";
        }
        out_yz << "\n";
    }
    out_yz.close();

    // 2. Save XZ slice (at a fixed Y = mid_j)
    std::cout << "Writing XZ slice to slice_XZ.dat..." << std::endl;
    std::ofstream out_xz("slice_XZ.dat");
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int k = 0; k < GRID_SIZE; ++k) {
            out_xz << grid[i][mid_j][k] << " ";
        }
        out_xz << "\n";
    }
    out_xz.close();

    // 3. Save XY slice (at a fixed Z = mid_k)
    std::cout << "Writing XY slice to slice_XY.dat..." << std::endl;
    std::ofstream out_xy("slice_XY.dat");
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            out_xy << grid[i][j][mid_k] << " ";
        }
        out_xy << "\n";
    }
    out_xy.close();
    
    std::cout << "All slices written." << std::endl;

    return 0;
}