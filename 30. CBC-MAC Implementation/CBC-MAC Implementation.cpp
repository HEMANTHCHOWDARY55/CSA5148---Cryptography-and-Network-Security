#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Define block size (for simplicity, we use 8 bytes or 64 bits)
#define BLOCK_SIZE 8

// A simple XOR-based block cipher for demonstration
void simple_block_cipher(uint8_t *block, uint8_t *key) {
    for (int i = 0; i < BLOCK_SIZE; i++) {
        block[i] ^= key[i];
    }
}

// Function to compute CBC-MAC for a single block message
void compute_cbc_mac(uint8_t *mac, uint8_t *key, uint8_t *message) {
    memcpy(mac, message, BLOCK_SIZE); // Copy message to MAC
    simple_block_cipher(mac, key);    // Encrypt using the block cipher
}

int main() {
    uint8_t key[BLOCK_SIZE] = {0x1A, 0x2B, 0x3C, 0x4D, 0x5E, 0x6F, 0x7A, 0x8B}; // Example key
    uint8_t message[BLOCK_SIZE] = {0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80}; // Example message
    uint8_t mac[BLOCK_SIZE]; // To store the MAC

    // Compute CBC-MAC for the one-block message
    compute_cbc_mac(mac, key, message);

    // Print the CBC-MAC for the one-block message
    printf("CBC-MAC for one-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac[i]);
    }
    printf("\n");

    // Compute the message X ? T
    uint8_t x_xor_t[BLOCK_SIZE];
    for (int i = 0; i < BLOCK_SIZE; i++) {
        x_xor_t[i] = message[i] ^ mac[i];
    }

    // Compute CBC-MAC for the two-block message X || (X ? T)
    uint8_t mac_two_block[BLOCK_SIZE];
    uint8_t temp[BLOCK_SIZE];

    // First block (X)
    memcpy(temp, message, BLOCK_SIZE);
    simple_block_cipher(temp, key);

    // Second block (X ? T)
    for (int i = 0; i < BLOCK_SIZE; i++) {
        temp[i] ^= x_xor_t[i];
    }
    simple_block_cipher(temp, key);

    memcpy(mac_two_block, temp, BLOCK_SIZE);

    // Print the CBC-MAC for the two-block message
    printf("CBC-MAC for two-block message: ");
    for (int i = 0; i < BLOCK_SIZE; i++) {
        printf("%02X ", mac_two_block[i]);
    }
    printf("\n");

    return 0;
}

