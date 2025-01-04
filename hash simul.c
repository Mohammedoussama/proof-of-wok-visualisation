#include <stdio.h>
#include <string.h>

unsigned int simple_hash(const char *str) {
    unsigned int hash = 0;
    while (*str) {
        hash = (hash << 5) + *str++;
    }
    return hash;
}

void proof_of_work(const char *data, unsigned int difficulty) {
    unsigned int nonce = 0;
    unsigned int target = 1 << (32 - difficulty);
    unsigned int hash = 0;

    printf("Starting Proof of Work...\n");
    printf("Difficulty target: Leading %d bits must be zero in hash\n\n", difficulty);

    while (1) {

        char message[256];
        snprintf(message, sizeof(message), "%s:%u", data, nonce);


        hash = simple_hash(message);


        printf("Trying nonce: %u -> Hash: %08x\n", nonce, hash);


        if (hash < target) {
            printf("\nSuccess! Found valid nonce: %u\n", nonce);
            printf("Final hash: %08x\n", hash);
            break;
        }

        nonce++;
    }
}

int main() {
    const char *data = "Hello, Blockchain!";
    unsigned int difficulty = 4;

    proof_of_work(data, difficulty);
    return 0;
}
