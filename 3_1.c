#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int comparisons = 0; // Global variable to count comparisons

// Merge function
void merge(int arr[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int L = (int)malloc(n1 * sizeof(int));
    int R = (int)malloc(n2 * sizeof(int));
    
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparisons++;
        if (L[i] <= R[j]) {
            arr[k++] = L[i++];
        } else {
            arr[k++] = R[j++];
        }
    }
    
    while (i < n1)
        arr[k++] = L[i++];
    while (j < n2)
        arr[k++] = R[j++];
    
    free(L);
    free(R);
}

// Merge Sort function
void merge_sort(int arr[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        
        merge(arr, left, mid, right);
    }
}

// Function to read data from a file
int read_data(const char *filename, int **arr) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("Error opening file");
        return -1;
    }
    
    int size = 0;
    int temp = (int)malloc(500 * sizeof(int));
    
    while (fscanf(file, "%d", &temp[size]) != EOF) {
        size++;
    }
    
    fclose(file);
    
    arr = (int)malloc(size * sizeof(int));
    for (int i = 0; i < size; i++) {
        (*arr)[i] = temp[i];
    }
    
    free(temp);
    return size;
}

// Function to write data to a file
void write_data(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }
    
    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }
    
    fclose(file);
}

// Main function with menu
int main() {
    int choice;
    int *data;
    int size;
    char *input_file;
    char *output_file;
    
    while (1) {
        printf("Select an option:\n");
        printf("1. Sort Ascending\n");
        printf("2. Sort Descending\n");
        printf("3. Sort Random\n");
        printf("4. Exit\n");
        printf("Enter option (1-4): ");
        scanf("%d", &choice);
        
        switch (choice) {
            case 1:
                input_file = "inAsce.dat";
                output_file = "outMergeAsce.dat";
                break;
            case 2:
                input_file = "inDesc.dat";
                output_file = "outMergeDesc.dat";
                break;
            case 3:
                input_file = "inRand.dat";
                output_file = "outMergeRand.dat";
                break;
            case 4:
                return 0;
            default:
                printf("Invalid option.\n");
                continue;
        }
        
        // Read data from the file
        size = read_data(input_file, &data);
        if (size == -1) {
            printf("Failed to read data from file.\n");
            continue;
        }
        
        // Measure execution time
        clock_t start_time = clock();
        
        // Sort data
        merge_sort(data, 0, size - 1);
        
        clock_t end_time = clock();
        double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
        
        // Write sorted data to output file
        write_data(output_file, data, size);
        
        // Print results
        printf("Sorted data has been written to %s.\n", output_file);
        printf("Execution Time: %.6f seconds\n", execution_time);
        printf("Number of Comparisons: %d\n", comparisons);
        
        free(data);
        comparisons = 0; // Reset comparisons counter
    }
    
    return 0;
}