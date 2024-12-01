

#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

extern void accelerations(int n_cars, double *input_matrix, int *output_result);

int main() {
    int n_cars = 10000; // Experiment with 10, 100, 1000, etc. 
    int runs = 30; 
    int i, j; 

    double *input_matrix = (double*)malloc(n_cars * 3 * sizeof(double)); 
    int *output_result = (int*)malloc(n_cars * sizeof(int)); 

    if (!input_matrix || !output_result) {
        printf("Memory Allocation Failed.\n"); 
        return 1; 
    }

    // Initialize input_matrix 
    for (i = 0; i < n_cars; i++) {
        input_matrix[i * 3] = 30.0;         // Initial Velocity (Vi in KM/H)
        input_matrix[i * 3 + 1] = 160.7;    // Final Velocity (Vf in KM/H) 
        input_matrix[i * 3 + 2] = 7.8;      // Time (T in seconds) 
    }
    double time = 0.0; 
    printf("Input size (n_cars): %d\n", n_cars);

    LARGE_INTEGER frequency, start, end; 
    QueryPerformanceFrequency(&frequency); 

    // Run acceleration computation to see average execution time 
    for (j = 0; j < runs; j++) {
        QueryPerformanceCounter(&start); 
        accelerations(n_cars, input_matrix, output_result); 
        QueryPerformanceCounter(&end); 

        double run_time = (double)(end.QuadPart - start.QuadPart) / frequency.QuadPart; 
        time += run_time; 

        // Output time for each run 
        printf("Run %d time: %.5f seconds\n", j + 1, run_time); 
    }
    double average = time / runs; 

    // Final average execution time 
    printf("Average execution time: %.5f seconds\n", average);

    // Free allocated memory 
    free(input_matrix); 
    free(output_result); 

    return 0;
}