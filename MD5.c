#include <stdio.h>
#include <stdint.h>

#define F(b,c,d) (((b) & (c)) | (~(b) & (d)))
#define ROT(x,s) (((x) << (s)) | ((x) >> (32 - (s))))

int main() {
    uint32_t A, B, C, D, M, K1, s;

    printf("Enter A B C D (hex): ");
    scanf("%x %x %x %x", &A, &B, &C, &D);
    printf("Enter M K1 (hex): ");
    scanf("%x %x", &M, &K1);
    printf("Enter shift s (0 = only modular addition): ");
    scanf("%u", &s);

    printf("\nBuffers read:\n");
    printf("A=%08X B=%08X C=%08X D=%08X\n", A, B, C, D);

    uint32_t f_val = (B & C) | (~B & D);   // written out explicitly, no macro
    uint32_t inner = A + f_val + M + K1;

    printf("\nF(B,C,D)        = %08X\n", f_val);
    printf("A+F(B,C,D)+M+K1 = %08X\n",  inner);

    if (s == 0) {
        printf("Result (no rot) = %08X\n", inner);
        printf("(Only modular addition performed)\n");
    } else {
        uint32_t rotated = ROT(inner, s);
        uint32_t newA    = B + rotated;
        printf("After ROT(%u)   = %08X\n", s, rotated);
        printf("New A = B+rot  = %08X\n",  newA);
        printf("(Full MD5 step performed)\n");
    }
    return 0;
}
