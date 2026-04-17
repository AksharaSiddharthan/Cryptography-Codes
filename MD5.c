#include <iostream>
#include <cstdint>
using namespace std;

uint32_t F(uint32_t b, uint32_t c, uint32_t d) {
    return (b & c) | (~b & d);
}

uint32_t leftRotate(uint32_t x, int n) {
    return (x << n) | (x >> (32 - n));
}

int main() {
    uint32_t A, B, C, D, K1, M0;
    int s = 7;

    cout << "Enter buffers A B C D (hex, e.g. 67452301 EFCDAB89 98BADCFE 10325476): ";
    cin >> hex >> A >> B >> C >> D;   // ← hex modifier added

    cout << "Enter K1 (hex, e.g. d76aa478): ";
    cin >> hex >> K1;                 // ← hex modifier added

    cout << "Enter message word M0 (hex, e.g. 00000000): ";
    cin >> hex >> M0;                 // ← hex modifier added

    uint32_t newA = B + leftRotate(A + F(B, C, D) + M0 + K1, s);

    printf("\nF(B,C,D)        = 0x%08X\n", F(B, C, D));
    printf("Inner sum       = 0x%08X\n", A + F(B, C, D) + M0 + K1);
    printf("After rotate(7) = 0x%08X\n", leftRotate(A + F(B, C, D) + M0 + K1, s));
    printf("new_A           = 0x%08X\n", newA);

    return 0;
}
