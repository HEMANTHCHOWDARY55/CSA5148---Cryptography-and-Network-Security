#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(char *ciphertext, int *frequency) {
    for (int i = 0; i < strlen(ciphertext); ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

// Function to decrypt the ciphertext with a given key
void decryptWithKey(char *ciphertext, int key, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = ((ciphertext[i] - 'A' - key + 26) % 26) + 'A';
        } else {
            plaintext[i] = ciphertext[i];
        }
    }
    plaintext[strlen(ciphertext)] = '\0';
}

// Function to compare two frequencies for qsort
int compare(const void *a, const void *b) {
    return (*(int*)b - *(int*)a);
}

int main() {
    // Sample ciphertext (assumed to be in uppercase)
    char ciphertext[] = "WKH TXLFN EURZQ IRA MXPSV RYHU WKH ODCB GRJ";
    int frequency[26] = {0};
    char possiblePlaintexts[26][strlen(ciphertext) + 1];
    int topN;

    // Calculate the frequency of each letter in the ciphertext
    calculateFrequency(ciphertext, frequency);

    // Sort the frequencies in descending order
    int sortedFrequency[26];
    for (int i = 0; i < 26; ++i) {
        sortedFrequency[i] = frequency[i];
    }
    qsort(sortedFrequency, 26, sizeof(int), compare);

    // Get the top N possible plaintexts
    printf("Enter the number of top possible plaintexts you want: ");
    scanf("%d", &topN);

    for (int i = 0; i < topN; ++i) {
        int key = (sortedFrequency[i] - 'E' + 26) % 26;
        decryptWithKey(ciphertext, key, possiblePlaintexts[i]);
        printf("Possible plaintext %d with key %d: %s\n", i + 1, key, possiblePlaintexts[i]);
    }

    return 0;
}

