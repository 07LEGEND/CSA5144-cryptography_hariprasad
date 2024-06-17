#include <stdio.h>
#include <stdlib.h>
#include <math.h>
long long int powerMod(long long int base, long long int exp, long long int mod) {
    long long int result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1) {
            result = (result * base) % mod;
        }
        exp = exp >> 1; 
        base = (base * base) % mod;
    }
   return result;
}
int main() {
    long long int p, g, a, b;
    long long int A, B;
    long long int secretA, secretB;
    printf("Enter a prime number (p): ");
    scanf("%lld", &p);
    printf("Enter a primitive root modulo p (g): ");
    scanf("%lld", &g);
    printf("Enter Alice's private key (a): ");
    scanf("%lld", &a);
    printf("Enter Bob's private key (b): ");
    scanf("%lld", &b);
    A = powerMod(g, a, p);
    B = powerMod(g, b, p);
    secretA = powerMod(B, a, p); 
    secretB = powerMod(A, b, p); 
    printf("Prime (p): %lld\n", p);
    printf("Primitive Root (g): %lld\n", g);
    printf("Alice's Private Key (a): %lld\n", a);
    printf("Bob's Private Key (b): %lld\n", b);
    printf("Alice's Public Key (A): %lld\n", A);
    printf("Bob's Public Key (B): %lld\n", B);
    printf("Shared Secret computed by Alice: %lld\n", secretA);
    printf("Shared Secret computed by Bob: %lld\n", secretB);
  return 0;
}

