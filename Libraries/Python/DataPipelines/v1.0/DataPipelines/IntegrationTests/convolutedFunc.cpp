#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <vector>

using namespace std;

vector<vector<int>> matrix(int n){
    vector<vector<int>> ret(n);
    for(int i = 0; i < n; i++){
        for(int j = 0; j < n; j++){
            ret[i].push_back(i*4 + j);
        }
    }
    return ret;
}

map<map<int, vector<bool>>, vector<float>> nonsense(int n){
    map<map<int, vector<bool>>, vector<float>> ret;
    map<int, vector<bool>> mpv;
    mpv[32].push_back(0);
    mpv[347].push_back(1);

    ret[mpv].push_back(3.1415926);

    return ret;
}

vector<vector<vector<vector<float>>>> vectorLine(map<bool, int> mp){
    vector<vector<vector<vector<float>>>> ret;
    vector<float> v = {3.4, 7.231321, 5, 0, -10};
    vector<vector<float>> vv = {v, v};
    vector<vector<vector<float>>> vvv = {vv, vv, vv, vv, vv};
    ret.push_back(vvv);
    vvv.clear();
    ret.push_back(vvv);
    return ret;
}


map<int, int> countVector(vector<vector<int>> v){
    map<int, int>ret;
    for(int i = 0; i < v.size(); i++){
        ret[i] = v[i].size();
    }
    return ret;
}

int main(){
    cout << "Hello World"  << endl;
    vector<vector<int>>v;
    v = matrix(4);
    for(int i=0; i<4; i++){
        for(int j=0; j<4; j++){
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
    return 0;
}