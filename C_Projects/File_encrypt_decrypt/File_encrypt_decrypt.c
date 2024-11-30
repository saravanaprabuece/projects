#include <stdio.h>
#include <stdlib.h>

void encryptDecrypt(FILE *inputFile, FILE *outputFile, char key) {
    char ch;

    // Read each byte from the input file
    while ((ch = fgetc(inputFile)) != EOF) {
        // XOR operation for encryption/decryption
        ch ^= key;
        fputc(ch, outputFile);
    }
}

int main() {
    char inputFileName[100], outputFileName[100];
    char key;
    FILE *inputFile, *outputFile;

    // Ask the user for the file to encrypt/decrypt
    printf("Enter the name of the file to encrypt/decrypt: ");
    scanf("%s", inputFileName);
    printf("Enter the name for the output file: ");
    scanf("%s", outputFileName);

    // Open the input file in read mode
    inputFile = fopen(inputFileName, "rb");
    if (inputFile == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Open the output file in write mode
    outputFile = fopen(outputFileName, "wb");
    if (outputFile == NULL) {
        printf("Error opening output file.\n");
        fclose(inputFile);
        return 1;
    }

    // Ask the user for a key for encryption/decryption
    printf("Enter a single character key for encryption/decryption: ");
    getchar();  // Consume newline left by previous scanf
    key = getchar();  // Read a single character

    // Perform encryption or decryption
    encryptDecrypt(inputFile, outputFile, key);

    // Close the files
    fclose(inputFile);
    fclose(outputFile);

    printf("File processed successfully.\n");
    getch();

    return 0;
}
