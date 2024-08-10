#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Function prototypes
void quick_sort(int arr[], int low, int high, int *comparison_count);
int partition(int arr[], int low, int high, int *comparison_count);
void read_file(const char *filename, int **arr, int *size);
void write_file(const char *filename, int arr[], int size);
void display_file_contents(const char *filename);

int main() {
    int choice;
    int *data = NULL;
    int size = 0;
    int comparison_count;
    clock_t start, end;
    double execution_time;

    while (1) {
        printf("\nMAIN MENU (QUICK SORT)\n");
        printf("1. Ascending Data\n");
        printf("2. Descending Data\n");
        printf("3. Random Data\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: // Ascending Data
                read_file("inAsce.dat", &data, &size);
                break;
            case 2: // Descending Data
                read_file("inDesc.dat", &data, &size);
                break;
            case 3: // Random Data
                read_file("inRand.dat", &data, &size);
                break;
            case 4: // Exit
                free(data);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                continue;
        }

        // Measure execution time
        comparison_count = 0;
        start = clock();
        quick_sort(data, 0, size - 1, &comparison_count);
        end = clock();
        execution_time = ((double) (end - start)) / CLOCKS_PER_SEC;

        // Write sorted data to output file
        write_file("outQuickSort.dat", data, size);

        // Display results
        display_file_contents("outQuickSort.dat");
        printf("Number of comparisons: %d\n", comparison_count);
        printf("Execution time: %.6f seconds\n", execution_time);

        free(data); // Free memory allocated for data
    }
}

// Quick Sort function
void quick_sort(int arr[], int low, int high, int *comparison_count) {
    if (low < high) {
        int pivot_index = partition(arr, low, high, comparison_count);
        quick_sort(arr, low, pivot_index - 1, comparison_count);
        quick_sort(arr, pivot_index + 1, high, comparison_count);
    }
}

// Partition function
int partition(int arr[], int low, int high, int *comparison_count) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        (*comparison_count)++;
        if (arr[j] < pivot) {
            i++;
            // Swap arr[i] and arr[j]
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }
    // Swap arr[i + 1] and arr[high]
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    return i + 1;
}

// Read data from file
void read_file(const char *filename, int **arr, int *size) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    // Determine the number of elements
    int capacity = 10;
    *arr = malloc(capacity * sizeof(int));
    *size = 0;
    while (fscanf(file, "%d", &(*arr)[*size]) == 1) {
        (*size)++;
        if (*size >= capacity) {
            capacity *= 2;
            *arr = realloc(*arr, capacity * sizeof(int));
        }
    }

    fclose(file);
}

// Write data to file
void write_file(const char *filename, int arr[], int size) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < size; i++) {
        fprintf(file, "%d ", arr[i]);
    }

    fclose(file);
}

// Display contents of the file
void display_file_contents(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Error opening file %s\n", filename);
        exit(1);
    }

    printf("Contents of %s: ", filename);
    int value;
    while (fscanf(file, "%d", &value) == 1) {
        printf("%d ", value);
    }
    printf("\n");

    fclose(file);
}
