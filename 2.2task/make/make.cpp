#include <fstream>
#include <map>
#include <string>
#include <vector>
#include "../graph/graph.h"
using namespace std;

int main(){
    ifstream fin("makefile");
    string line, cur_name;
    map<string, vector<string>> files;
    Graph<bool, string> graph;
    vector<string> targets;
    while(fin.good()){
        getline(fin, line);
        if (fin.eof()) break;
        if (line=="") continue;
        if (line[0]=='\t'){
            line.erase(line.begin());
            for (size_t i=0; i<targets.size(); i++)
                files[targets[i]].push_back(line);
        }
        else{
            size_t i=0;
            cur_name="";
            targets.clear();
            while (line[i]!=':'){
                while(line[i]!=' ' && line[i]!=':'){
                    cur_name=cur_name+line[i];
                    i++;
                }
                if (cur_name!=""){
                    targets.push_back(cur_name);
                    if (!graph.isNodeExists(cur_name))
                        graph.addNode(cur_name);
                    if (files.find(cur_name)==files.end())
                        files.insert(make_pair(cur_name, vector<string>()));
                }
                cur_name="";
                if (line[i]!=':')i++;
            }
            i++;
            cur_name="";
            while(i<line.size()){
                while(line[i]!=' ' && i<line.size()){
                    cur_name=cur_name+line[i];
                    i++;
                }
                if (cur_name!=""){
                if (!graph.isNodeExists(cur_name))
                    graph.addNode(cur_name);
                for (size_t j=0; j<targets.size(); j++)
                   graph.addEdgeOnValue(cur_name, targets[j], 1);
                if (files.find(cur_name)==files.end())
                    files.insert(make_pair(cur_name, vector<string>()));
                }
                cur_name="";
                i++;
            }
        }
    }
    fin.close();
    pair<bool, list<Node<string>>> answer=graph.TSort();
    //for (auto i: answer.second)
      //  cout<<i.value<< " ";
    //cout<<endl;
    if (!answer.first){
        auto its=answer.second.end();
        do{
            its--;
            auto it=files.find(its->value);
            if (it!=files.end()){
                if (!it->second.empty())
                    for(auto j : it->second)
                        //cout<<j<<endl;
                        system (j.c_str());
            }
        }while(its!=answer.second.begin());
    }
    else cout<<"Terminated. Cycled."<<endl;
}
