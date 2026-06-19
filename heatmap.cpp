#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <cmath>

using namespace std;
using namespace chrono;

int main()
{
    // === DIMENSION SGHIRA BACH TCON VISUALISATION 7ELWA ===
    const int N = 128;  // 128x128 bch tban mzyan f graph
    const int steps = 300;  // Bch tkon diffusion kamla
    const double alpha = 0.15;
    const double dt = 0.01;
    const double dx = 1.0;

    // === INITIALISATION ===
    vector<vector<double>> grid(N, vector<double>(N, 0));
    vector<vector<double>> newGrid(N, vector<double>(N, 0));

    // Source de chaleur au centre (plus grande bach tban)
    int source_radius = 8;
    for (int i = N/2 - source_radius; i < N/2 + source_radius; i++)
    {
        for (int j = N/2 - source_radius; j < N/2 + source_radius; j++)
        {
            // Source circulaire (gradient)
            double dist = sqrt(pow(i - N/2, 2) + pow(j - N/2, 2));
            if (dist < source_radius)
            {
                grid[i][j] = 100.0 * (1 - dist / source_radius);
            }
        }
    }
    grid[N/2][N/2] = 100.0;  // Point le plus chaud

    cout << "=== SIMULATION DIFFUSION THERMIQUE ===" << endl;
    cout << "Grille: " << N << "x" << N << endl;
    cout << "Steps: " << steps << endl;
    cout << "================================" << endl;

    auto start = high_resolution_clock::now();

    // === SIMULATION ===
    for (int t = 0; t < steps; t++)
    {
        for (int i = 1; i < N - 1; i++)
        {
            for (int j = 1; j < N - 1; j++)
            {
                newGrid[i][j] = grid[i][j] + alpha * dt / (dx*dx) * (
                    grid[i+1][j] + grid[i-1][j] +
                    grid[i][j+1] + grid[i][j-1] -
                    4 * grid[i][j]
                );
            }
        }

        swap(grid, newGrid);
    }

    auto end = high_resolution_clock::now();

    cout << "Temps simulation: " << duration<double>(end - start).count() << " s" << endl;

    // === VÉRIFICATION ===
    double max_val = grid[0][0], min_val = grid[0][0];
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            if (grid[i][j] > max_val) max_val = grid[i][j];
            if (grid[i][j] < min_val) min_val = grid[i][j];
        }
    }
    cout << "Max température: " << max_val << "°C" << endl;
    cout << "Min température: " << min_val << "°C" << endl;
    cout << "Centre: " << grid[N/2][N/2] << "°C" << endl;

    // === SAUVEGARDER CSV ===
    ofstream file("temperature.csv");
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            file << grid[i][j];
            if (j < N - 1) file << ",";
        }
        file << "\n";
    }
    file.close();

    cout << "\n✅ Fichier 'temperature.csv' généré!" << endl;
    cout << "   Dimension: " << N << "x" << N << endl;

    return 0;
}