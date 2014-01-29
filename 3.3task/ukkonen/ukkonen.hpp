#ifndef UKKONEN_HPP_INCLUDED
#define UKKONEN_HPP_INCLUDED

Ukkonen::Ukkonen(const string& filename) : nodes(3), str(), inf(){
    str = my::read(filename);
    str+='$';
    inf = str.size()-1;

    nodes[0] = Node(-1, -1, -1);
    for (int i=0; i<UCHAR_MAX+1; i++)
        nodes[0].children[(char)i] = 1;

    nodes[1] = Node(-1, -1, -1);
    nodes[1].link = 0;
    nodes[1].children[str[0]] = 2;

    nodes[2] = Node(1, 0, inf);

    pair<int, int> sp = make_pair(1, 0);

    for (int k=1; k<(int)str.size(); k++){
        char c = str[k];
        while (!sp_has_edge(sp, c)){
            if (sp.second != 0)
                sp = split_edge(sp);
            nodes.push_back(Node(sp.first, k, inf));
            nodes[sp.first].children[c] = nodes.size()-1;

            sp = build_link(sp);
            if (nodes[sp.first].children.size()==1 && sp_has_edge(sp, c))
                sp = merge_edge(sp, c);
        }
        sp = go_down(sp, c);
    }
}

bool Ukkonen::sp_has_edge(pair<int, int> sp, char c){
    if (sp.second!=0){
        if (c==str[nodes[sp.first].begin+sp.second])
            return true;
    }
    if (sp.second==0){
        if (nodes[sp.first].children[c]!=0)
            return true;
        else
            nodes[sp.first].children.erase(c);
    }
    return false;
}

pair<int, int> Ukkonen::split_edge(pair<int, int> sp){
    int current = sp.first;
    int parent = nodes[current].parent;
    nodes.push_back(Node(parent, nodes[current].begin, nodes[current].begin+sp.second-1));
    nodes[parent].children[str[nodes[current].begin]] = nodes.size()-1;
    nodes[nodes.size()-1].children[str[nodes[current].begin+sp.second]] = current;
    nodes[current].parent = nodes.size()-1;
    nodes[current].begin = nodes[current].begin+sp.second;
    return make_pair(nodes.size()-1, 0);
}

pair<int, int> Ukkonen::merge_edge(pair<int, int> sp, char c){
    int current = sp.first;
    int parent = nodes[current].parent;
    int child = nodes[current].children[c];
    int diff = nodes[current].end-nodes[current].begin+1;
    nodes[parent].children[str[nodes[current].begin]] = child;
    nodes[child].parent = parent;
    nodes[child].begin = nodes[current].begin;
    return (make_pair(child, sp.second+diff));
}

pair<int, int> Ukkonen::build_link(pair<int, int> sp){
    int cur_shift = nodes[sp.first].begin;
    char c = str[cur_shift];
    if (sp.first == 1)
        return make_pair(0, 0);
    int u = nodes[sp.first].parent;
    u = nodes[u].link;
    if (sp.second==0)
        sp.second = nodes[sp.first].end-nodes[sp.first].begin+1;
    while (sp.second!=0){
        int s = nodes[nodes[u].children[c]].end-nodes[nodes[u].children[c]].begin+1;
        if (sp.second == s){
            nodes[sp.first].link = nodes[u].children[c];
            return make_pair(nodes[u].children[c], 0);
        }
        else if (sp.second < s){
            auto v = split_edge(make_pair(nodes[u].children[c], sp.second));
            nodes[sp.first].link = v.first;
            return v;
        }
        else{
            sp.second -= s;
            u = nodes[u].children[c];
            cur_shift+=s;
            c = str[cur_shift];
        }
    }
    return make_pair(0, 0);
}
pair<int, int> Ukkonen::go_down(pair<int, int> sp, char c){
    if (sp.second!=0){
        if (sp.second!=nodes[sp.first].end-nodes[sp.first].begin)
            return make_pair(sp.first, sp.second+1);
        else
            return make_pair(sp.first, 0);
    }
    if (sp.second==0){
        int child = nodes[sp.first].children[c];
        if (nodes[child].end-nodes[child].begin==0)
            return make_pair(child, 0);
        else
            return make_pair(child, 1);
    }
    return make_pair(0, 0);
}

void Ukkonen::print(int current = 1, int h = 0){
    for (int i=0; i<h; i++)
        cout<<"  ";
    cout<<current<<": ";
    for (int i=nodes[current].begin; i<=nodes[current].end; i++)
        if (str[i]!=L'\n')
            cout<<str[i];
        else
            cout<<"~";
    cout<<endl;
    for (auto& i: nodes[current].children)
        if (i.second!=0)
            print(i.second, h+1);
}

int Ukkonen::count(const string& needle){
    int current = 1;
    int i = 0;
    int l = needle.length();
    while(i<l){
        if (nodes[current].children[needle[i]] == 0)
            return 0;
        current = nodes[current].children[needle[i]];
        i+=(nodes[current].end-nodes[current].begin+1);
    }
    return dfs_count(current);
}

int Ukkonen::dfs_count(int current){
    if (nodes[current].end == inf)
        return 1;
    int sum = 0;
    for (auto& i: nodes[current].children){
        if (i.second!=0){
            sum+=dfs_count(i.second);
        }
    }
    return sum;
}

vector<int> Ukkonen::find(const string& needle){
    int current = 1;
    int i = 0;
    int l = needle.length();
    while(i<l){
        current = nodes[current].children[needle[i]];
        i+=(nodes[current].end-nodes[current].begin+1);
    }
    return dfs_find(current);
}

vector<int> Ukkonen::dfs_find(int current){
    if (nodes[current].end == inf)
        return vector<int>(1, nodes[current].begin);
    vector<int> answer;
    for (auto& i: nodes[current].children){
        if (i.second!=0){
            vector<int> temp = dfs_find(i.second);
            for (auto i: temp){
                answer.push_back(i);
            }
        }
    }
    return answer;
}

#endif // UKKONEN_HPP_INCLUDED
