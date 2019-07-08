#ifndef HEADER1_H
#define HEADER1_H
#include "header2.hpp"

struct go{
    int a, b;
    go2 x;
    go(go &&other): a(std::move(other.a)), b(std::move(other.b)), x(std::move(other.x)){}
};

struct oth{
    int x;
    oth(oth &&other): x(std::move(other.x)){}
};

int notCounting(std::vector<float> v){
    return v.size();
}

#endif