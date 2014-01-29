#ifndef AHO_H_INCLUDED
#define AHO_H_INCLUDED
#include "../read.hpp"
#include <iostream>
#include <vector>
#include <map>

using std::cout;
using std::cin;
using std::endl;
using std::ifstream;
using std::vector;
using std::map;
using std::string;

class Aho{
public:
    Aho();
    void add_string(const string&);
    map<string, vector<int>> find_all_patterns(const string&);
private:
    struct Node{
        map<char, int> children;
        map<char, int> moves;
        int parent;
        char parent_char;
        int link;
        int terminal_link;
        bool is_terminal;
        int pattern;
        Node() : children(), parent(-1), parent_char((char)0), link(-1), terminal_link(-1), is_terminal(0), pattern(-1){}
        Node(int p, char pc) : children(), parent(p), parent_char(pc), link(-1), terminal_link(-1), is_terminal(0), pattern(-1){}
        Node(int p, char pc, bool it, int pat) : children(), parent(p), parent_char(pc), link(-1), terminal_link(-1), is_terminal(it), pattern(pat){}
    };
    vector<string> patterns;
    vector<Node> nodes;

    int go(int, char);
    int build_link(int);
    int build_terminal_link(int);
};
#include "aho.hpp"

#endif // AHO_H_INCLUDED
