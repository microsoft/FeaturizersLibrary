#include <vector>

using namespace std;

class Point{
    public:
        int x, y;
        Point() {}
        Point(int a, int b){
            x=a;
            y=b;
        }
};

Point operator + (const Point& a, const Point& b) {
  Point ret;
  ret.x = a.x + b.x;
  ret.y = a.y + b.y;
  return ret;
}

int sum(Point a){
    return a.x + a.y;
}

vector<int> go(int n){
    vector<int> ret;
    for(int i = 0 ; i < n; i++){
        ret.push_back(i);
    }
    return ret;
}

int main(){
    return 0;
}