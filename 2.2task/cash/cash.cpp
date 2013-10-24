#include <iostream>
#include <list>
#include <map>
using namespace std;
class Cash {
    int size;
    int c_size;
    list<int> id;
    map<int, list<int>::iterator> id_it;
    map<int, list<int>::iterator>::iterator it;
public:
    void get_user(int user_id);
    Cash(int rhs) : size(rhs),c_size(0), id(list<int>()), id_it( map<int, list<int>::iterator>()) {}
};

void Cash::get_user(int user_id){
    it=id_it.find(user_id);
    if (it!=id_it.end()){
        id.erase(it->second);
        id.push_front(user_id);
        it->second=id.begin();
        printf("%d%s", 0, " ");
    }
    else{
        if (c_size==size){
            id_it.erase(id.back());
            id.pop_back();
            c_size--;
        }
        id.push_front(user_id);
        id_it.insert(make_pair(user_id, (id.begin())));
        printf("%d%s", 1, " ");
        c_size++;
    }
}

int main(){
    int n;
    scanf("%d", &n);
    Cash c(n);
    while (1){
        int id;
        scanf("%d", &id);
        if (feof(stdin)) break;
        c.get_user(id);
    }
}
