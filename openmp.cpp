#include <iostream>
#include <vector>
#include <chrono>
#include <omp.h>

using namespace std;
using namespace chrono;

int main()
{
    int sizes[] = {256, 512, 1024};
    const int steps = 200;
    double alpha = 0.1;

    omp_set_num_threads(8);

    cout << "Threads used = " << omp_get_max_threads() << endl;
    cout << "============================" << endl;

    for (int s = 0; s < 3; s++)
    {
        int N = sizes[s];

        vector<vector<double>> grid(N, vector<double>(N, 0));
        vector<vector<double>> newGrid(N, vector<double>(N, 0));

        grid[N/2][N/2] = 100.0;

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

        cout << "Grid Size: " << N << "x" << N << endl;
        cout << "OpenMP Time = "
             << duration<double>(end - start).count()
             << " seconds" << endl;

        cout << "------------------------" << endl;
    }

    return 0;
}