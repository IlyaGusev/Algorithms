#include <iostream>
#include <map>
#include <set>
#include <cstdlib>
#include <cstdio>
using namespace std;
unsigned int ip_convert(string);
struct comp{
    bool operator()(pair<int, unsigned int> lhs, pair<int, unsigned int> rhs){
        if (lhs.first>rhs.first)
            return true;
        else
            if (lhs.first==rhs.first)
                return (lhs.second<rhs.second);
            else return false;
    }
};
class Radio{
private:
    set<pair<int, unsigned int>, comp> score_id;
    map<string, unsigned int> ip_time;
    map<unsigned int, int> id_score;
public:
    Radio(){
        for (int i=1; i<100000; i++){
            score_id.insert(pair<int, unsigned int>(0, i));
            id_score.insert(pair<unsigned int, int>(i, 0));
        }
    }
    void vote(string ip, unsigned int track_id, int score, unsigned int time);
    void get();
    void exit();
};
void Radio::vote(string ip, unsigned int track_id, int score, unsigned int time){

    map<string, unsigned int>::iterator it=ip_time.find(ip);
    if (it==ip_time.end()){
        ip_time.insert(pair<string, unsigned int> (ip, time));
        map<unsigned int, int>::iterator itt=id_score.find(track_id);
        int temp=0;
        if (itt!=id_score.end()){
            temp=((*itt).second);
            score_id.erase(pair<int, unsigned int>(temp, track_id));
            id_score.erase(itt);
        }
        score_id.insert(pair<int, unsigned int>(temp+score, track_id));
        id_score.insert(pair<unsigned int, int>(track_id, temp+score));
        printf("%d\n",temp+score);
    }
    else
        if ((*it).second+600>time){
            map<unsigned int, int>::iterator itt=id_score.find(track_id);
            if (itt==id_score.end()) cout<<0<<endl;
            else printf("%d\n",(*itt).second);

        }
        else{
            ip_time.erase(it);
            ip_time.insert(pair<string, unsigned int> (ip, time));
            map<unsigned int, int>::iterator itt=id_score.find(track_id);
            int temp=0;
            if (itt!=id_score.end()){
                temp=((*itt).second);
                score_id.erase(pair<int, unsigned int>(temp, track_id));
                id_score.erase(itt);
            }
            score_id.insert(pair<int, unsigned int>(temp+score, track_id));
            id_score.insert(pair<unsigned int, int>(track_id, temp+score));
            printf("%d\n",temp+score);
        }

}
void Radio::get(){
    set<pair<int, unsigned int>, comp>::iterator it=score_id.begin();
    printf("%d %d \n", (*it).second, (*it).first);
    map<unsigned int, int>::iterator itt=id_score.find((*it).second);
    int temp=(*it).second;
    id_score.erase(itt);
    id_score.insert(pair<unsigned int, int>(temp, -1));
    score_id.erase(it);
    score_id.insert(pair<int,unsigned int>(-1, temp));
}
void Radio::exit(){
    printf("OK\n");
}
int main(){
    std::ios_base::sync_with_stdio(1);
    Radio a;
    char str[80];
    char ip[80];
    unsigned int track_id, time;
    int score;
    while(str[0]!='E'){
        scanf("%s", &str);
        if (str[0]=='V'){
            scanf("%s %u %d %u", &ip, &track_id, &score, &time);
            a.vote((string)ip, track_id, score, time);
        }
        if (str[0]=='G'){
            a.get();
        }
    }
    a.exit();
}
