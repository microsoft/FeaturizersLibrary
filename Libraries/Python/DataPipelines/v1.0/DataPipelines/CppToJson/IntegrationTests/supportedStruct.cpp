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

struct x *go(int y){
    x *ret = NULL;
    return ret;
}

int main(){
    return 0;
}