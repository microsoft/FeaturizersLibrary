#include <utility>

struct x{
    int a, b;
    x(struct x &&other): a(std::move(other.a)), b(std::move(other.b)){}
    x(int xa, int xb){
        a=xa;
        b=xb;
    }
};

int go(struct x ya){
    return 2;
}

int main(){
    return 0;
}