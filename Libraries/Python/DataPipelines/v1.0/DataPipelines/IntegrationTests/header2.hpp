#ifndef HEADER2_H
#define HEADER2_H
#include <vector>

struct go2{
    int a, b;
    go2(struct go2 &&other): a(std::move(other.a)), b(std::move(other.b)){}
};


int AlsoNotCounting(std::vector<int> v){
    return v.size();
}


#endif