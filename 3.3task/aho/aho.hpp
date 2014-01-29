#ifndef AHO_HPP_INCLUDED
#define AHO_HPP_INCLUDED

Aho::Aho() : patterns(), nodes(1){
    nodes[0] = Node();
    nodes[0].link = 0;
}

void Aho::add_string(const string& str){
    patterns.push_back(str);
    int current=0;
    for (int i=0; i<(int)str.length(); i++){
        char c = str[i];
        if (!nodes[current].children[c]){
            nodes.push_back(Node(current, c));
            nodes[current].children[c]=nodes.size()-1;
        }
        current = nodes[current].children[c];
    }
    nodes[current].is_terminal = true;
    nodes[current].pattern = patterns.size()-1;
}

int Aho::go(int current, char c){
    if (!nodes[current].moves[c]){
        if (nodes[current].children.find(c)!=nodes[current].children.end())
            nodes[current].moves[c] = nodes[current].children[c];
        else{
            if (current==0)
                nodes[current].moves[c] = 0;
            else
                nodes[current].moves[c]=go(build_link(current), c);
        }
    }
    return nodes[current].moves[c];
}

int Aho::build_link(int current){
    if (nodes[current].link == -1){
        if (current==0 || nodes[current].parent==0)
            nodes[current].link = 0;
        else
            nodes[current].link = go(build_link(nodes[current].parent), nodes[current].parent_char);
    }
    return nodes[current].link;
}

int Aho::build_terminal_link(int current){
    if (nodes[current].terminal_link == -1){
        int link = build_link(current);
        if (link==0)
            nodes[current].terminal_link = 0;
        else{
            if (nodes[link].is_terminal)
                nodes[current].terminal_link = link;
            else
                nodes[current].terminal_link = build_terminal_link(link);
        }

    }
    return nodes[current].terminal_link;
}

map<string, vector<int>> Aho::find_all_patterns(const string& haystack){
    map<string, vector<int>> answers;
    int current = 0;
    int hlen = haystack.length();
    for (int i=0; i<hlen; i++){
        current = go(current, haystack[i]);
        int temp = current;
        while(temp!=0){
            if (nodes[temp].is_terminal)
                answers[patterns[nodes[temp].pattern]].push_back(i-patterns[nodes[temp].pattern].length());
            temp = build_terminal_link(temp);
        }
    }
    return answers;
}

#endif // AHO_HPP_INCLUDED
