#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}
int modInverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1)
            return x;
    }
    return -1;
}
long long modExp(long long base, long long exp, long long mod) {
    long long result = 1;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        exp = exp >> 1;
        base = (base * base) % mod;
    }
    return result;
}

int main() {
    int p, q, e;
    printf("Enter two distinct prime numbers (p and q): ");
    scanf("%d %d", &p, &q);
    int n = p * q;
    int phi = (p - 1) * (q - 1);
    printf("Enter an integer e (1 < e < %d and gcd(e, %d) = 1): ", phi, phi);
    scanf("%d", &e);
    int d = modInverse(e, phi);
    printf("Public Key: (%d, %d)\n", e, n);
    printf("Private Key: (%d, %d)\n", d, n);
    int plaintext;
    printf("Enter plaintext (an integer): ");
    scanf("%d", &plaintext);

    long long ciphertext = modExp(plaintext, e, n);
    printf("Ciphertext: %lld\n", ciphertext);
    long long decrypted = modExp(ciphertext, d, n);
    printf("Decrypted Text: %lld\n", decrypted);

    return 0;
}

