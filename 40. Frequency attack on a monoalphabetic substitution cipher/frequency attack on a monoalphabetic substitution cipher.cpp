#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALPHABET_SIZE 26

// English letter frequencies in descending order (E, T, A, O, I, N, S, H, R, D, L, U, C, M, F, Y, W, G, P, B, V, K, J, X, Q, Z)
const char englishFreqOrder[ALPHABET_SIZE] = "ETAOINSHRDLCUMWFGYPBVKJXQZ";

// Function to calculate the frequency of each letter in the ciphertext
void calculateFrequency(const char *ciphertext, int *frequency) {
    for (int i = 0; i < strlen(ciphertext); ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            frequency[ciphertext[i] - 'A']++;
        }
    }
}

// Function to decrypt the ciphertext with a given mapping
void decryptWithMapping(const char *ciphertext, const char *mapping, char *plaintext) {
    for (int i = 0; i < strlen(ciphertext); ++i) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            plaintext[i] = mapping[ciphertext[i] - 'A'];
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
    int frequency[ALPHABET_SIZE] = {0};
    char possiblePlaintexts[ALPHABET_SIZE][strlen(ciphertext) + 1];
    int sortedIndices[ALPHABET_SIZE];
    int topN;

    // Calculate the frequency of each letter in the ciphertext
    calculateFrequency(ciphertext, frequency);

    // Sort the frequencies in descending order and keep track of original indices
    for (int i = 0; i < ALPHABET_SIZE; ++i) {
        sortedIndices[i] = i;
    }
    qsort(sortedIndices, ALPHABET_SIZE, sizeof(int), compare);

    // Get the top N possible plaintexts
    printf("Enter the number of top possible plaintexts you want: ");
    scanf("%d", &topN);

    for (int k = 0; k < topN; ++k) {
        // Generate the mapping based on the sorted frequencies
        char mapping[ALPHABET_SIZE];
        for (int i = 0; i < ALPHABET_SIZE; ++i) {
            mapping[sortedIndices[i]] = englishFreqOrder[(i + k) % ALPHABET_SIZE];
        }

        // Decrypt the ciphertext with the current mapping
        decryptWithMapping(ciphertext, mapping, possiblePlaintexts[k]);
        printf("Possible plaintext %d: %s\n", k + 1, possiblePlaintexts[k]);
    }

    return 0;
}

