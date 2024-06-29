#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ALPHABET_SIZE 26

// Function to calculate letter frequencies in the given text
void calculate_frequencies(const char *text, int frequencies[]) {
    int i = 0;
    while (text[i]) {
        if (isalpha(text[i])) {
            char ch = toupper(text[i]);
            frequencies[ch - 'A']++;
        }
        i++;
    }
}

// Function to perform monoalphabetic substitution decryption based on a given key
void decrypt(const char *ciphertext, const char *key, char *plaintext) {
    int i = 0;
    while (ciphertext[i]) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            plaintext[i] = isupper(ch) ? key[ch - 'A'] : tolower(key[ch - 'A']);
        } else {
            plaintext[i] = ciphertext[i];
        }
        i++;
    }
    plaintext[i] = '\0';
}

// Function to perform frequency analysis attack and print top possible plaintexts
void frequency_attack(const char *ciphertext, int top_results) {
    int frequencies[ALPHABET_SIZE] = {0};
    calculate_frequencies(ciphertext, frequencies);

    // Sort frequencies in descending order
    int sorted_indices[ALPHABET_SIZE];
    for (int i = 0; i < ALPHABET_SIZE; i++) {
        sorted_indices[i] = i;
    }
    for (int i = 0; i < ALPHABET_SIZE - 1; i++) {
        for (int j = i + 1; j < ALPHABET_SIZE; j++) {
            if (frequencies[sorted_indices[i]] < frequencies[sorted_indices[j]]) {
                int temp = sorted_indices[i];
                sorted_indices[i] = sorted_indices[j];
                sorted_indices[j] = temp;
            }
        }
    }

    // Decrypt using each permutation and print top results
    char plaintext[strlen(ciphertext) + 1];
    char key[ALPHABET_SIZE + 1];
    key[ALPHABET_SIZE] = '\0';

    for (int k = 0; k < top_results; k++) {
        // Generate key based on sorted frequency order
        for (int i = 0; i < ALPHABET_SIZE; i++) {
            key[sorted_indices[i]] = 'A' + i;
        }

        // Decrypt ciphertext using the current key
        decrypt(ciphertext, key, plaintext);

        // Print the decrypted plaintext with its score (based on frequency order)
        printf("Plaintext (Score %d):\n%s\n\n", k + 1, plaintext);

        // Rotate sorted indices to try the next likely permutation
        int temp = sorted_indices[ALPHABET_SIZE - 1];
        for (int i = ALPHABET_SIZE - 1; i > 0; i--) {
            sorted_indices[i] = sorted_indices[i - 1];
        }
        sorted_indices[0] = temp;
    }
}

int main() {
    char ciphertext[1000];
    int top_results;

    // Input ciphertext
    printf("Enter the ciphertext: ");
    fgets(ciphertext, sizeof(ciphertext), stdin);

    // Remove newline character from fgets
    ciphertext[strcspn(ciphertext, "\n")] = '\0';

    // Input number of top results
    printf("Enter the number of top possible plaintexts to display: ");
    scanf("%d", &top_results);

    // Perform frequency analysis attack and print top possible plaintexts
    frequency_attack(ciphertext, top_results);

    return 0;
}

