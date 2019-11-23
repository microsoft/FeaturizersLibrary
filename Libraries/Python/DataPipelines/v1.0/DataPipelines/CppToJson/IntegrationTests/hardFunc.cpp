#include <iostream>
#include <map>
#include <vector>




using namespace std;

int add(int a){
    return 2;
}

int n;
vector<int>x;

int main(){
    cout << "Hello World"  << endl;
    return 0;
}

vector<int> bubbleSort(vector<int> v){
    for(int i = 0; i < v.size(); i++){
        for(int j = i + 1; j < v.size() ; j++){
            if(v[i] > v[j])
                swap(v[i], v[j]);
        }
    }
    return v;
}

int sizeOfMap(map<int, bool> mp){
    return mp.size();
}
vector<int> keys(map<int, int> mp){
    vector<int> ret;
    for(auto it : mp){
        ret.push_back(it.first);
    }
    return ret;
}

map<float, int> goCount(vector<float> v, bool signal){
    map<float, int> ret;
    for(int i = 0; i < v.size(); i++){
        ret[i] = v[i] * (2*signal - 1);
    }
    return ret;
}


