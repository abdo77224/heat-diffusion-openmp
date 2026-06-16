#include <iostream>
#include <vector>
#include <chrono>

using namespace std;
using namespace chrono;

int main()
{
    const int N = 1000;
    const int steps = 200;

    // grid principal
    vector<vector<double>> grid(N, vector<double>(N, 0));
    vector<vector<double>> newGrid(N, vector<double>(N, 0));

    // source de chaleur
    grid[N/2][N/2] = 100.0;

    double alpha = 0.1;

    auto start = high_resolution_clock::now();

    for (int t = 0; t < steps; t++)
    {
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

        // swap (faster than copy)
        swap(grid, newGrid);
    }

    auto end = high_resolution_clock::now();

    cout << "Serial version completed" << endl;
    cout << "Time = " 
         << duration<double>(end - start).count() 
         << " seconds" << endl;

    return 0;
}