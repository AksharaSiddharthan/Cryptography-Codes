// SHA-512 Padding: find padding bits & no. of blocks
#include <iostream>
using namespace std;

int main() {
    long long L;
    cout << "Enter original message length (bytes): ";
    cin >> L;

    long long msg_bits = L * 8;

    // After appending '1' bit, we need: (msg_bits+1 + zero_bits + 128) % 1024 == 0
    // So: zero_bits = (896 - (msg_bits+1) % 1024 + 1024) % 1024
    long long used = (msg_bits + 1) % 1024;
    long long zero_bits = (896 - used + 1024) % 1024;

    // Total padding = 1 (the '1' bit) + zero_bits + 128 (length field)
    long long total_padding = 1 + zero_bits + 128;
    long long total_bits = msg_bits + total_padding;
    long long blocks = total_bits / 1024;

    cout << "\n--- SHA-512 Padding ---\n";
    cout << "Message bits     : " << msg_bits << "\n";
    cout << "Padding bits     : " << total_padding << "\n";
    cout << "  (1 + " << zero_bits << " zeros + 128 length bits)\n";
    cout << "Total bits       : " << total_bits << "\n";
    cout << "Number of blocks : " << blocks << "\n";
    return 0;
}
