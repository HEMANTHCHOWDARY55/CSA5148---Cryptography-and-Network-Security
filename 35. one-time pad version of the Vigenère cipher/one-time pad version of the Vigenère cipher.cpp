#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// Function to encrypt plaintext using a one-time pad Vigenère cipher
void encrypt(char plaintext[], int key[], int key_length) {
    int len = strlen(plaintext);
    int i, j = 0;

    for (i = 0; i < len; i++) {
        char ch = plaintext[i];

        // Determine if the character is a letter
        if (isalpha(ch)) {
            int shift = key[j % key_length];  // Get the current key shift
            int base = isupper(ch) ? 'A' : 'a';  // Determine the base ('A' or 'a')

            // Encrypt the character using Vigenère cipher shift
            ch = base + (ch - base + shift) % 26;
            plaintext[i] = ch;

            j++;  // Move to the next key element
        }
    }
}

int main() {
    char plaintext[1000];
    int key[1000];
    int key_length, i;

    // Seed the random number generator based on current time
    srand(time(NULL));

    // Input plaintext
    printf("Enter plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    // Remove newline character from fgets
    plaintext[strcspn(plaintext, "\n")] = 0;

    // Generate random key stream
    printf("Enter the length of the key: ");
    scanf("%d", &key_length);

    printf("Generating random key stream...\n");
    for (i = 0; i < key_length; i++) {
        key[i] = rand() % 26;  // Generate a random number between 0 and 25
        printf("%d ", key[i]);
    }
    printf("\n");

    // Encrypt the plaintext using the generated key
    encrypt(plaintext, key, key_length);

    // Output the encrypted text
    printf("\nEncrypted text: %s\n", plaintext);

    return 0;
}

