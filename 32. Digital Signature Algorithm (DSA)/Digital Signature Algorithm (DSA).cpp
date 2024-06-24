#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <openssl/dsa.h>
#include <openssl/sha.h>
#include <openssl/rand.h>

void handleErrors() {
    ERR_print_errors_fp(stderr);
    abort();
}

void printBN(const char *msg, const BIGNUM *a) {
    char *number_str = BN_bn2dec(a);
    printf("%s %s\n", msg, number_str);
    OPENSSL_free(number_str);
}

int main() {
    // Message to be signed
    const char *message = "Hello, this is a test message.";
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // Generate SHA-256 hash of the message
    SHA256((unsigned char *)message, strlen(message), hash);

    // Print the hash
    printf("Message hash: ");
    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++) {
        printf("%02x", hash[i]);
    }
    printf("\n");

    // Generate DSA parameters
    DSA *dsa = DSA_new();
    if (DSA_generate_parameters_ex(dsa, 1024, NULL, 0, NULL, NULL, NULL) == 0) {
        handleErrors();
    }

    // Generate DSA key pair
    if (DSA_generate_key(dsa) == 0) {
        handleErrors();
    }

    // Print public and private keys
    printBN("Private key:", dsa->priv_key);
    printBN("Public key:", dsa->pub_key);

    // Sign the message hash
    DSA_SIG *sig1 = DSA_do_sign(hash, SHA256_DIGEST_LENGTH, dsa);
    if (sig1 == NULL) {
        handleErrors();
    }

    // Print the first signature
    printBN("Signature 1 (r):", sig1->r);
    printBN("Signature 1 (s):", sig1->s);

    // Sign the same message hash again
    DSA_SIG *sig2 = DSA_do_sign(hash, SHA256_DIGEST_LENGTH, dsa);
    if (sig2 == NULL) {
        handleErrors();
    }

    // Print the second signature
    printBN("Signature 2 (r):", sig2->r);
    printBN("Signature 2 (s):", sig2->s);

    // Verify the first signature
    int verify1 = DSA_do_verify(hash, SHA256_DIGEST_LENGTH, sig1, dsa);
    if (verify1 == 1) {
        printf("Signature 1 is valid.\n");
    } else {
        printf("Signature 1 is invalid.\n");
    }

    // Verify the second signature
    int verify2 = DSA_do_verify(hash, SHA256_DIGEST_LENGTH, sig2, dsa);
    if (verify2 == 1) {
        printf("Signature 2 is valid.\n");
    } else {
        printf("Signature 2 is invalid.\n");
    }

    // Clean up
    DSA_SIG_free(sig1);
    DSA_SIG_free(sig2);
    DSA_free(dsa);

    return 0;
}

