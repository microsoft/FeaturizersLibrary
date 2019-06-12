#include <iostream>
#include <stdio.h>
#include <string>

int add(float a, int b){
    return a + b;
}

float mult(int a, float b, bool signal){
    return a * b * (2*signal - 1);
}

std::string toUp(std::string s){
    if(s[0] <= 'a' && s[0]<='z')
        s[0] = s[0] - 'a' + 'A';
    return s;
}

int fat(int curr, int at = 3){
    if(at == 0)return 1;
    return curr * fat(curr - 1, at - 1);
}

int main(){
    std::cout << "Hello World\n";
    return 0;
}
