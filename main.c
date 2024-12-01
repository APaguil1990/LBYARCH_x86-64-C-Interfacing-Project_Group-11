

#include <stdio.h> 
#include <stdlib.h> 
#include <windows.h> 

extern void accelerations(int n_cars, double *input_matrix, int *output_result);

int main() {
    // Hardcoded sample case 
    int test_cars = 3; 
    double *test_matrix = (double*)malloc(test_cars * 3 * sizeof(double)); 
    int *test_result = (int*)malloc(test_cars * sizeof(int)); 
    int x;

    if (!test_matrix || !test_result) {
        printf("Memory allocation failed for test case.\n"); 
        return 1;
    } 

    // Initialize hardcoded sample matrix 
    test_matrix[0] = 0.0;    test_matrix[1] = 62.5;   test_matrix[2] = 10.1;
    test_matrix[3] = 60.0;   test_matrix[4] = 122.3;  test_matrix[5] = 5.5;
    test_matrix[6] = 30.0;   test_matrix[7] = 160.7;  test_matrix[8] = 7.8; 

    printf("Testing with hardcoded sample matrix:\n"); 
    printf("Input Matrix:\n"); 
    for (x = 0; x < test_cars; x++) {
        printf("%f, %f, %f\n", test_matrix[x *3], test_matrix[x * 3 + 1], test_matrix[x * 3 + 2]); 
    }

    LARGE_INTEGER test_frequency, test_start, test_end; 
    QueryPerformanceFrequency(&test_frequency); 
    QueryPerformanceCounter(&test_start); 

    accelerations(test_cars, test_matrix, test_result); 

    QueryPerformanceCounter(&test_end);

    printf("Returned from accelerations\n"); 
    printf("Results:\n"); 
    for (x = 0; x < test_cars; x++) {
        printf("%d\n", test_result[x]);
    }

    double test_execution_time = (double)(test_end.QuadPart - test_start.QuadPart) / test_frequency.QuadPart;
    printf("Execution time of test: %.6f seconds\n\n", test_execution_time);

    free(test_matrix);
    free(test_result);

    // Large input test
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