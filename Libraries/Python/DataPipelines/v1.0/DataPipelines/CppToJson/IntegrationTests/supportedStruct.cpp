#include <utility>
#include <cstdio>
struct x{
    int a, b;
    x(x &&other): a(std::move(other.a)), b(std::move(other.b)){}
    x(int xa, int xb){
        a=xa;
        b=xb;
    }
};

x go(int y){
    x ret = x(1, 2);
    return ret;
}

int main(){
    return 0;
}