#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define the block size
#define BLOCK_SIZE_64 8
#define BLOCK_SIZE_128 16

// XOR operation for bytes
void xor_bytes(uint8_t *out, const uint8_t *in, const uint8_t *xor_val, size_t len) {
    for (size_t i = 0; i < len; i++) {
        out[i] = in[i] ^ xor_val[i];
    }
}

// Left shift operation
void left_shift(uint8_t *out, const uint8_t *in, size_t len) {
    for (size_t i = 0; i < len - 1; i++) {
        out[i] = (in[i] << 1) | (in[i + 1] >> 7);
    }
    out[len - 1] = in[len - 1] << 1;
}

// Subkey generation
void generate_subkeys(uint8_t *K1, uint8_t *K2, const uint8_t *L, size_t block_size, uint8_t R_b) {
    uint8_t tmp[BLOCK_SIZE_128] = {0}; // Temporary buffer for intermediate results

    // Step 1: Calculate K1
    left_shift(tmp, L, block_size);
    if (L[0] & 0x80) {
        tmp[block_size - 1] ^= R_b;
    }
    memcpy(K1, tmp, block_size);

    // Step 2: Calculate K2
    left_shift(tmp, K1, block_size);
    if (K1[0] & 0x80) {
        tmp[block_size - 1] ^= R_b;
    }
    memcpy(K2, tmp, block_size);
}

// Simple block cipher encryption function (AES-like, but simplified)
void simple_block_cipher(uint8_t *out, const uint8_t *in, const uint8_t *key, size_t len) {
    // For simplicity, we just copy the input to output. In a real scenario, you'd use AES or another block cipher.
    memcpy(out, in, len);
}

int main() {
    uint8_t L[BLOCK_SIZE_128] = {0}; // L is the output of the block cipher encryption of the zero block
    uint8_t K1[BLOCK_SIZE_128] = {0}; // First subkey
    uint8_t K2[BLOCK_SIZE_128] = {0}; // Second subkey
    uint8_t key[BLOCK_SIZE_128] = {0x00}; // Example key (all zeros for simplicity)

    // Zero block
    uint8_t zero_block[BLOCK_SIZE_128] = {0};

    // Encrypt the zero block
    simple_block_cipher(L, zero_block, key, BLOCK_SIZE_128);

    // For 64-bit block size
    printf("64-bit block size:\n");
    generate_subkeys(K1, K2, L, BLOCK_SIZE_64, 0x1B);
    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE_64; i++) printf("%02X ", K1[i]);
    printf("\nK2: ");
    for (int i = 0; i < BLOCK_SIZE_64; i++) printf("%02X ", K2[i]);
    printf("\n");

    // For 128-bit block size
    printf("\n128-bit block size:\n");
    generate_subkeys(K1, K2, L, BLOCK_SIZE_128, 0x87);
    printf("K1: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) printf("%02X ", K1[i]);
    printf("\nK2: ");
    for (int i = 0; i < BLOCK_SIZE_128; i++) printf("%02X ", K2[i]);
    printf("\n");

    return 0;
}

