#include <utility>

struct go{
    int a;
    bool b;
    go(){

    }
    go(struct go &&other): a(std::move(other.a)), b(std::move(other.b)){}
};

struct go2{
    int a;
    float b;
    go2(){

    }
    go2(struct go2 &&other): a(std::move(other.a)), b(std::move(other.b)){}
};

struct oth: public go, go2{
    int x;
    oth(){
        go();
    }
    oth(struct oth &&other)=default;
};


oth goooo(int a, float b){
    oth x;
    x.x = 3;
    return x;
}