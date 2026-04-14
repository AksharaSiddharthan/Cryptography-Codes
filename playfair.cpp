#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

char grid[5][5];

void buildGrid(string key) {
    string alpha = "ABCDEFGHIKLMNOPQRSTUVWXYZ";  // I=J merged
    string used = "";
    for (char c : key) {
        c = toupper(c);
        if (c == 'J') c = 'I';
        if (isalpha(c) && used.find(c) == string::npos) used += c;
    }
    for (char c : alpha)
        if (used.find(c) == string::npos) used += c;
    cout << "\nPlayfair Grid:\n";
    for (int i=0;i<5;i++,cout<<"\n")
        for (int j=0;j<5;j++) { grid[i][j]=used[i*5+j]; cout<<grid[i][j]<<" "; }
}

void findPos(char c, int& r, int& col) {
    if(c=='J') c='I';
    for(int i=0;i<5;i++) for(int j=0;j<5;j++) if(grid[i][j]==c){r=i;col=j;return;}
}

string process(string text, bool encrypt) {
    // Prepare text: uppercase, J→I, insert X between doubles, pad if odd
    string t = "";
    for(char c:text) { c=toupper(c); if(c=='J') c='I'; if(isalpha(c)) t+=c; }
    for(int i=0;i<(int)t.size()-1;i+=2)
        if(t[i]==t[i+1]) { t.insert(i+1,1,'X'); }
    if(t.size()%2) t+='Z';

    string result = "";
    int shift = encrypt ? 1 : -1;
    cout << "\nDigraphs: ";
    for(int i=0;i<(int)t.size();i+=2) {
        int r1,c1,r2,c2;
        findPos(t[i],r1,c1); findPos(t[i+1],r2,c2);
        cout << t[i] << t[i+1] << " ";
        char a, b;
        if(r1==r2) {  // Same row → shift columns
            a=grid[r1][(c1+5+shift)%5];
            b=grid[r2][(c2+5+shift)%5];
        } else if(c1==c2) {  // Same column → shift rows
            a=grid[(r1+5+shift)%5][c1];
            b=grid[(r2+5+shift)%5][c2];
        } else {  // Rectangle → swap columns
            a=grid[r1][c2]; b=grid[r2][c1];
        }
        result += a; result += b;
    }
    return result;
}

int main() {
    string key, plaintext;
    int choice;
    cout << "Enter key: "; cin >> key;
    cout << "1=Encrypt  2=Decrypt: "; cin >> choice;
    cout << "Enter text: "; cin >> plaintext;
    buildGrid(key);
    string out = process(plaintext, choice==1);
    cout << "\n" << (choice==1?"Ciphertext":"Plaintext") << ": " << out << "\n";
    return 0;
}

/* Sample I/O:
   Key: MONARCHY  Text: WEAREDISCOVEREDFLEEAONCE  (encrypt)
   Grid:
   M O N A R
   C H Y B D
   I E F G K
   L P Q S T
   U V W X Z
   Digraphs: WE AR ED IS CO VE RE DF LE EA ON CE
   Ciphertext: UGRMKCSXPAGVZM...
*/
