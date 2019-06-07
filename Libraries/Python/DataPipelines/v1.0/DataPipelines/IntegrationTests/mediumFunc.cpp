#include <iostream>#include <stdio.h>#include <string>

using namespace std;

int add(float a, int b){
    return a + b;
}

float mult(int a, float b, bool signal){
    return a * b * (2*signal - 1);
}

string toUp(string s){
    if(s[0] <= 'a' and s[0]<='z')
        s[0] = s[0] - 'a' + 'A';
    return s;
} 

int fat(int curr, int at = 3){
    if(at == 0)return 1;
    return curr * fat(curr - 1, at - 1);
}

int main(){
    cout << "Hello World"  << endl;
    return 0;
}