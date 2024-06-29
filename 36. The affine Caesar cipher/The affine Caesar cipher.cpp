#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <time.h>

// Function to calculate the modular multiplicative inverse of a modulo m
// Returns -1 if inverse doesn't exist
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1;  // Inverse doesn't exist
}

// Function to encrypt plaintext using the affine Caesar cipher
void encrypt(char plaintext[], int a, int b) {
    int len = strlen(plaintext);
    for (int i = 0; i < len; i++) {
        if (isalpha(plaintext[i])) {
            char ch = toupper(plaintext[i]);
            int p = ch - 'A';
            int C = (a * p + b) % 26;
            plaintext[i] = 'A' + C;
        }
    }
}

// Function to decrypt ciphertext using the affine Caesar cipher
void decrypt(char ciphertext[], int a, int b) {
    int a_inv = mod_inverse(a, 26);
    if (a_inv == -1) {
        printf("Inverse does not exist for given 'a'. Decryption not possible.\n");
        return;
    }

    int len = strlen(ciphertext);
    for (int i = 0; i < len; i++) {
        if (isalpha(ciphertext[i])) {
            char ch = toupper(ciphertext[i]);
            int C = ch - 'A';
            int p = (a_inv * (C - b + 26)) % 26;  // Adding 26 to handle negative modulo
            ciphertext[i] = 'A' + p;
        }
    }
}

int main() {
    char text[1000];
    int a, b;

    // Input plaintext or ciphertext
    printf("Enter plaintext or ciphertext: ");
    fgets(text, sizeof(text), stdin);

    // Remove newline character from fgets
    text[strlen(text) - 1] = '\0';

    // Input values of 'a' and 'b' for encryption
    printf("Enter values of 'a' and 'b' (where 'a' should be coprime with 26): ");
    scanf("%d %d", &a, &b);

    // Encrypt the text
    encrypt(text, a, b);
    printf("Encrypted text: %s\n", text);

    // Decrypt the text
    decrypt(text, a, b);
    printf("Decrypted text: %s\n", text);

    return 0;
}

