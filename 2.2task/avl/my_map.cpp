#include "my_map.h"
int main(){
    my::map<int, int> a;
    a.insert(std::make_pair(30,6));
    a.insert(std::make_pair(20,7));
    a.insert(std::make_pair(1,9));
    a.insert(std::make_pair(2,10));
    a.insert(std::make_pair(100,100));
    a.insert(std::make_pair(100,0));
    a.insert(std::make_pair(6,100));
    a.insert(std::make_pair(7,100));
    a.insert(std::make_pair(8,100));
    a.insert(std::make_pair(9,100));
    a.erase(20);
    a.erase(200);
    a.erase(a.begin());
    a.erase(a.find(100));
    for (auto it=a.begin(); it!=a.end(); it++){
        cout<<it->first<<" ";
    }
    cout<<endl;
}
