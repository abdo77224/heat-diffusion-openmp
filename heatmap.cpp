#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <omp.h>

using namespace std;
using namespace chrono;

int main()
{
    const int N = 1024;
    const int steps = 200;
    const double alpha = 0.1;

    vector<vector<double>> grid(N, vector<double>(N, 0));
    vector<vector<double>> newGrid(N, vector<double>(N, 0));

    grid[N/2][N/2] = 100.0;

    omp_set_num_threads(8);

    auto start = high_resolution_clock::now();

    for (int t = 0; t < steps; t++)
    {
        #pragma omp parallel for collapse(2)
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                newGrid[i][j] =
                    grid[i][j] +
                    alpha * (
                        grid[i+1][j] +
                        grid[i-1][j] +
                        grid[i][j+1] +
                        grid[i][j-1] -
                        4 * grid[i][j]
                    );
            }
        }

        swap(grid, newGrid);
    }

    auto end = high_resolution_clock::now();

    cout << "Simulation completed" << endl;
    cout << "Time = "
         << duration<double>(end - start).count()
         << " seconds" << endl;

    // Save temperature field to CSV
    ofstream file("temperature.csv");

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << grid[i][j];

            if (j < N - 1)
                file << ",";
        }

        file << "\n";
    }

    file.close();

    cout << "Temperature saved to temperature.csv" << endl;

    return 0;
}