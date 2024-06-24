#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

int main() {
    // Public parameters (example values)
    long long q = 23; // A prime number
    long long a = 5;  // A primitive root modulo q

    // Secret numbers chosen by Alice and Bob
    srand(time(NULL)); // Seed the random number generator
    long long x_Alice = rand() % (q - 1) + 1; // Alice's secret
    long long x_Bob = rand() % (q - 1) + 1;   // Bob's secret

    // Compute public values to be exchanged
    long long y_Alice = mod_exp(a, x_Alice, q); // Alice sends this to Bob
    long long y_Bob = mod_exp(a, x_Bob, q);     // Bob sends this to Alice

    // Compute shared secret keys
    long long k_Alice = mod_exp(y_Bob, x_Alice, q); // Alice's computed key
    long long k_Bob = mod_exp(y_Alice, x_Bob, q);   // Bob's computed key

    // Display results
    printf("Public parameters: q = %lld, a = %lld\n", q, a);
    printf("Alice's secret number: x_Alice = %lld\n", x_Alice);
    printf("Bob's secret number: x_Bob = %lld\n", x_Bob);
    printf("Alice's public value: y_Alice = %lld\n", y_Alice);
    printf("Bob's public value: y_Bob = %lld\n", y_Bob);
    printf("Shared secret key computed by Alice: k_Alice = %lld\n", k_Alice);
    printf("Shared secret key computed by Bob: k_Bob = %lld\n", k_Bob);

    return 0;
}

