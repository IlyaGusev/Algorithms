#ifndef UKKONEN_H_INCLUDED
#define UKKONEN_H_INCLUDED
#include <iostream>
#include "../read.hpp"
#include <climits>
#include <utility>
#include <vector>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::pair;
using std::make_pair;
using std::vector;
using std::map;
using std::string;

class Ukkonen{
public:
    Ukkonen(const string& filename);
    void print(int, int);
    int count(const string&);
    vector<int> find(const string&);

private:
    struct Node{
        int parent;
        int begin;
        int end;
        int link;
        map<wchar_t, int> children;
        Node(int p, int b, int e) : parent(p), begin(b), end(e), link(-1), children(){}
        Node() : parent(-1), begin(-1), end(-1), link(-1), children(){}
    };
    vector<Node> nodes;
    string str;
    int inf;

    bool sp_has_edge(pair<int, int>, char);
    pair<int, int> split_edge(pair<int, int>);
    pair<int, int> merge_edge(pair<int, int>, char);
    pair<int, int> build_link(pair<int, int>);
    pair<int, int> go_down(pair<int, int>, char );
    int dfs_count(int);
    vector<int> dfs_find(int);
};
#include "ukkonen.hpp"
#endif // UKKONEN_H_INCLUDED
