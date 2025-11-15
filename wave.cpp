#include <iostream>
#include <vector>
#include <cmath>
#include <fstream>   
#include <iomanip>   
#include <sstream>   
#include <sys/stat.h> 
#include <omp.h>     

const int GRID_SIZE = 500;
const int TOTAL_TIME_STEPS = 10000;
const int OUTPUT_EVERY_N_STEPS = 5; 


typedef std::vector<std::vector<double>> Grid;

/**
 * @brief Saves the current grid state to a file.
 * @param grid The grid to save.
 * @param time_step The current time step, used for the filename.
 */
void saveGridToFile(const Grid& grid, int time_step) {
    std::stringstream ss;
    // Format the filename: "wave_output/wave_00000.dat"
    ss << "wave_output/wave_" << std::setw(5) << std::setfill('0') << time_step << ".dat";
    
    std::ofstream outfile(ss.str());
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            outfile << grid[i][j] << " ";
        }
        outfile << "\n";
    }
    outfile.close();
}


int main() {
    mkdir("wave_output", 0777);

    // --- Allocate the three grids ---
    Grid psi_new(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
    Grid psi(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));
    Grid psi_old(GRID_SIZE, std::vector<double>(GRID_SIZE, 0.0));

    // --- Set up the wave speed constant ---
    // (c*dt/dx)^2. This "Courant number" (c*dt/dx) must be < 0.707
    // for 2D, so (c*dt/dx)^2 must be < 0.5. We use 0.4.
    const double tau_sq = 0.4;

    // --- Initialize a "pluck" in the pond ---
    int center = GRID_SIZE / 2;
    for (int i = 0; i < GRID_SIZE; ++i) {
        for (int j = 0; j < GRID_SIZE; ++j) {
            double dist = std::sqrt(std::pow(i - center, 2) + std::pow(j - center, 2));
            if (dist < 20.0) {
                // A smooth "Gaussian" bump
                double val = 100.0 * std::exp(-dist * dist / 50.0);
                psi[i][j] = val;
                psi_old[i][j] = val;
            }
        }
    }

    std::cout << "Starting 2D wave simulation..." << std::endl;
    double start_time = omp_get_wtime();

    // --- Main Time Loop ---
    // This loop is for time, not convergence.
    for (int t = 0; t < TOTAL_TIME_STEPS; ++t) {

        // --- Parallel Calculation ---
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < GRID_SIZE - 1; ++i) { 
            for (int j = 1; j < GRID_SIZE - 1; ++j) {
                
                // --- 2D WAVE EQUATION UPDATE RULE ---
                psi_new[i][j] = (2.0 * psi[i][j]) - psi_old[i][j] +
                                tau_sq * (psi[i-1][j] + // North
                                          psi[i+1][j] + // South
                                          psi[i][j-1] + // West
                                          psi[i][j+1] - // East
                                          (4.0 * psi[i][j]));
                
                // Add a small damping factor to prevent instability
                //psi_new[i][j] *= 0.999;
            }
        }
        
        psi_old.swap(psi);
        psi.swap(psi_new);
        
        if (t % OUTPUT_EVERY_N_STEPS == 0) {
            saveGridToFile(psi, t);
        }
    }

    double end_time = omp_get_wtime();
    std::cout << "Simulation finished." << std::endl;
    std::cout << "Total time taken: " << (end_time - start_time) << " seconds." << std::endl;
    std::cout << "Output files saved in 'wave_output/' directory." << std::endl;

    return 0;
}