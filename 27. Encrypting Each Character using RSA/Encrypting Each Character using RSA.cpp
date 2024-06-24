#include <stdio.h>
#include <math.h>

// Function to compute (base^exp) % mod using modular exponentiation
long long mod_exp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to encrypt a single character using RSA
char rsa_encrypt(char plaintext, long long e, long long n) {
    long long m = plaintext - 'A'; // Convert char to integer (0-25)
    long long c = mod_exp(m, e, n);
    return (char)(c + 'A'); // Convert back to char
}

// Function to decrypt a single character using RSA
char rsa_decrypt(char ciphertext, long long d, long long n) {
    long long c = ciphertext - 'A'; // Convert char to integer (0-25)
    long long m = mod_exp(c, d, n);
    return (char)(m + 'A'); // Convert back to char
}

int main() {
    // Example RSA keys (these are not secure and are for demonstration purposes only)
    long long n = 3233; // Modulus
    long long e = 17;   // Public exponent
    long long d = 413;  // Private exponent

    // Example plaintext message
    char plaintext[] = "HELLO";
    int len = sizeof(plaintext) / sizeof(plaintext[0]);

    printf("Plaintext: %s\n", plaintext);

    // Encrypt the message
    char ciphertext[len];
    for (int i = 0; i < len; i++) {
        if (plaintext[i] >= 'A' && plaintext[i] <= 'Z') {
            ciphertext[i] = rsa_encrypt(plaintext[i], e, n);
        } else {
            ciphertext[i] = plaintext[i]; // Non-alphabetic characters remain unchanged
        }
    }

    printf("Ciphertext: %s\n", ciphertext);

    // Decrypt the message
    char decryptedtext[len];
    for (int i = 0; i < len; i++) {
        if (ciphertext[i] >= 'A' && ciphertext[i] <= 'Z') {
            decryptedtext[i] = rsa_decrypt(ciphertext[i], d, n);
        } else {
            decryptedtext[i] = ciphertext[i]; // Non-alphabetic characters remain unchanged
        }
    }

    printf("Decrypted text: %s\n", decryptedtext);

    return 0;
}

