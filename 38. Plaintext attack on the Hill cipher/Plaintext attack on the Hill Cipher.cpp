#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to get the matrix inverse modulo 26
void getMatrixInverse(int keyMatrix[2][2], int inverseMatrix[2][2]) {
    int determinant = (keyMatrix[0][0] * keyMatrix[1][1] - keyMatrix[0][1] * keyMatrix[1][0]) % 26;
    determinant = (determinant + 26) % 26;

    int multiplicativeInverse;
    for (int i = 1; i < 26; ++i) {
        if ((determinant * i) % 26 == 1) {
            multiplicativeInverse = i;
            break;
        }
    }

    inverseMatrix[0][0] = (keyMatrix[1][1] * multiplicativeInverse) % 26;
    inverseMatrix[0][1] = (-keyMatrix[0][1] * multiplicativeInverse) % 26;
    inverseMatrix[1][0] = (-keyMatrix[1][0] * multiplicativeInverse) % 26;
    inverseMatrix[1][1] = (keyMatrix[0][0] * multiplicativeInverse) % 26;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (inverseMatrix[i][j] < 0)
                inverseMatrix[i][j] += 26;
        }
    }
}

// Function to encrypt a pair of characters
void encrypt(char message[2], int keyMatrix[2][2], char ciphertext[2]) {
    int messageVector[2];
    int cipherVector[2];

    for (int i = 0; i < 2; ++i)
        messageVector[i] = message[i] - 'A';

    for (int i = 0; i < 2; ++i) {
        cipherVector[i] = 0;
        for (int j = 0; j < 2; ++j) {
            cipherVector[i] += keyMatrix[i][j] * messageVector[j];
        }
        cipherVector[i] %= 26;
    }

    for (int i = 0; i < 2; ++i)
        ciphertext[i] = cipherVector[i] + 'A';
}

// Function to decrypt a pair of characters
void decrypt(char ciphertext[2], int keyMatrix[2][2], char decryptedtext[2]) {
    int inverseMatrix[2][2];
    getMatrixInverse(keyMatrix, inverseMatrix);

    int cipherVector[2];
    int decryptedVector[2];

    for (int i = 0; i < 2; ++i)
        cipherVector[i] = ciphertext[i] - 'A';

    for (int i = 0; i < 2; ++i) {
        decryptedVector[i] = 0;
        for (int j = 0; j < 2; ++j) {
            decryptedVector[i] += inverseMatrix[i][j] * cipherVector[j];
        }
        decryptedVector[i] %= 26;
    }

    for (int i = 0; i < 2; ++i)
        decryptedtext[i] = decryptedVector[i] + 'A';
}

// Function to perform a known plaintext attack
void knownPlaintextAttack(char plaintext[2], char ciphertext[2], int keyMatrix[2][2]) {
    int p1 = plaintext[0] - 'A';
    int p2 = plaintext[1] - 'A';
    int c1 = ciphertext[0] - 'A';
    int c2 = ciphertext[1] - 'A';

    int determinant = (p1 * p2 - p2 * p1) % 26;
    determinant = (determinant + 26) % 26;

    int multiplicativeInverse;
    for (int i = 1; i < 26; ++i) {
        if ((determinant * i) % 26 == 1) {
            multiplicativeInverse = i;
            break;
        }
    }

    keyMatrix[0][0] = (c1 * multiplicativeInverse) % 26;
    keyMatrix[0][1] = (c2 * multiplicativeInverse) % 26;
    keyMatrix[1][0] = (-c1 * multiplicativeInverse) % 26;
    keyMatrix[1][1] = (p1 * multiplicativeInverse) % 26;

    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            if (keyMatrix[i][j] < 0)
                keyMatrix[i][j] += 26;
        }
    }
}

int main() {
    int keyMatrix[2][2] = {{5, 17}, {8, 3}};
    char plaintext[2] = {'H', 'I'};
    char ciphertext[2];

    // Encrypt the plaintext
    encrypt(plaintext, keyMatrix, ciphertext);
    printf("Ciphertext: %c%c\n", ciphertext[0], ciphertext[1]);

    // Decrypt the ciphertext
    char decryptedtext[2];
    decrypt(ciphertext, keyMatrix, decryptedtext);
    printf("Decrypted text: %c%c\n", decryptedtext[0], decryptedtext[1]);

    // Known plaintext attack
    int recoveredKeyMatrix[2][2];
    knownPlaintextAttack(plaintext, ciphertext, recoveredKeyMatrix);
    printf("Recovered Key Matrix:\n");
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            printf("%d ", recoveredKeyMatrix[i][j]);
        }
        printf("\n");
    }

    return 0;
}

