#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>

// State matrix size for SHA-3
#define STATE_SIZE 25

// Function to initialize the state matrix
void initialize_state(uint64_t state[STATE_SIZE]) {
    for (int i = 0; i < STATE_SIZE; i++) {
        state[i] = 0;
    }
}

// Function to absorb the message block into the state matrix
void absorb_message(uint64_t state[STATE_SIZE], uint64_t message[16]) {
    for (int i = 0; i < 16; i++) {
        state[i] ^= message[i];
    }
}

// Function to check if all capacity lanes have nonzero bits
int all_capacity_nonzero(uint64_t state[STATE_SIZE]) {
    for (int i = 16; i < STATE_SIZE; i++) {
        if (state[i] == 0) {
            return 0;
        }
    }
    return 1;
}

int main() {
    uint64_t state[STATE_SIZE];
    uint64_t message[16];

    initialize_state(state);

    // Ensure each lane in the message block has at least one nonzero bit
    srand(time(NULL));
    for (int i = 0; i < 16; i++) {
        message[i] = rand() | ((uint64_t)rand() << 32); // Random 64-bit value
        if (message[i] == 0) {
            message[i] = 1; // Ensure at least one nonzero bit
        }
    }

    int rounds = 0;
    while (!all_capacity_nonzero(state)) {
        absorb_message(state, message);
        rounds++;
        
        // Debug: Print the state matrix
        printf("Round %d:\n", rounds);
        for (int i = 0; i < STATE_SIZE; i++) {
            printf("state[%d] = 0x%016llx\n", i, state[i]);
        }
        printf("\n");
    }

    printf("Number of rounds before all capacity lanes are nonzero: %d\n", rounds);

    return 0;
}

