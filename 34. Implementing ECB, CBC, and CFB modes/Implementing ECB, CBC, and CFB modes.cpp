#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/des.h>

// Function to add padding to the plaintext
int add_padding(uint8_t *input, uint8_t *output, int length) {
    int pad_len = 8 - (length % 8);
    memcpy(output, input, length);
    output[length] = 0x80; // Add the 1 bit
    for (int i = 1; i < pad_len; i++) {
        output[length + i] = 0x00; // Add the 0 bits
    }
    return length + pad_len;
}

// Function to print hex values
void print_hex(const char *label, const uint8_t *data, int length) {
    printf("%s", label);
    for (int i = 0; i < length; i++) {
        printf("%02x", data[i]);
    }
    printf("\n");
}

// ECB mode encryption
void des_ecb_encrypt(const uint8_t *plaintext, int length, const DES_cblock *key, uint8_t *ciphertext) {
    DES_key_schedule schedule;
    DES_set_key(key, &schedule);

    for (int i = 0; i < length; i += 8) {
        DES_ecb_encrypt((DES_cblock *)(plaintext + i), (DES_cblock *)(ciphertext + i), &schedule, DES_ENCRYPT);
    }
}

// CBC mode encryption
void des_cbc_encrypt(const uint8_t *plaintext, int length, const DES_cblock *key, const DES_cblock *iv, uint8_t *ciphertext) {
    DES_key_schedule schedule;
    DES_set_key(key, &schedule);

    DES_ncbc_encrypt(plaintext, ciphertext, length, &schedule, (DES_cblock *)iv, DES_ENCRYPT);
}

// CFB mode encryption
void des_cfb_encrypt(const uint8_t *plaintext, int length, const DES_cblock *key, const DES_cblock *iv, uint8_t *ciphertext) {
    DES_key_schedule schedule;
    DES_set_key(key, &schedule);

    int num = 0;
    DES_cfb64_encrypt(plaintext, ciphertext, length, &schedule, (DES_cblock *)iv, &num, DES_ENCRYPT);
}

int main() {
    uint8_t plaintext[] = "This is a secret message.";
    uint8_t padded_plaintext[64];
    uint8_t ciphertext[64];
    uint8_t decryptedtext[64];

    // Key and IV
    DES_cblock key = "12345678";
    DES_cblock iv = "12345678";

    int length = strlen((char *)plaintext);
    int padded_length = add_padding(plaintext, padded_plaintext, length);

    printf("Plaintext: %s\n", plaintext);

    // ECB mode
    des_ecb_encrypt(padded_plaintext, padded_length, &key, ciphertext);
    print_hex("ECB Ciphertext: ", ciphertext, padded_length);

    // CBC mode
    memset(ciphertext, 0, sizeof(ciphertext));
    des_cbc_encrypt(padded_plaintext, padded_length, &key, &iv, ciphertext);
    print_hex("CBC Ciphertext: ", ciphertext, padded_length);

    // CFB mode
    memset(ciphertext, 0, sizeof(ciphertext));
    des_cfb_encrypt(padded_plaintext, padded_length, &key, &iv, ciphertext);
    print_hex("CFB Ciphertext: ", ciphertext, padded_length);

    return 0;
}

