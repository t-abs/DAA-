#include <stdio.h>

int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

int main() {
    const char *inputFileName = "input.txt";
    const char *outputFileName = "output.txt";

    FILE *inputFile = fopen(inputFileName, "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }

    FILE *outputFile = fopen(outputFileName, "w");
    if (outputFile == NULL) {
        perror("Error opening output file");
        fclose(inputFile);
        return 1;
    }

    int num1, num2;

    while (fscanf(inputFile, "%d %d", &num1, &num2) == 2) {
        int result = gcd(num1, num2);

        fprintf(outputFile, "GCD of %d and %d is %d\n", num1, num2, result);
    }

    fclose(inputFile);
    fclose(outputFile);

    printf("Processing complete. Results are written to %s\n", outputFileName);

    return 0;
}
