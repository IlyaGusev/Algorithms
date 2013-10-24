#include <fstream>
#include <list>
#include <vector>
#include <iostream>
using namespace std;
struct Action{
    bool is_insert;
    char letter;
    list<string>::iterator str_num;
    string::iterator str_pos;

    Action(bool _i, char _l, list<string>::iterator _n, string::iterator _p) : is_insert(_i), letter(_l),
    str_num(_n), str_pos(_p) {}
};
int main(){
    list<Action> undo_list;
    list<Action> redo_list;
    list<string> text;
    text.push_back(string());
    auto str_num_cursor=text.begin();
    auto str_pos_cursor=text.begin()->begin();
    ifstream fin("in.txt");
    string line;
    while(fin.good()){
        getline(fin, line);
        if (fin.eof()) break;
        size_t i=0;
        while(i<line.size()){
            if ((line[i]>='a' && line[i]<='z') || (line[i]>='A' && line[i]<='Z')){
                str_pos_cursor=str_num_cursor->insert(str_pos_cursor, line[i]);
                auto temp=str_pos_cursor++;
                cout<<"!! "<<*temp<<endl;
                undo_list.push_back(Action(true, line[i], str_num_cursor, temp));
                if (!redo_list.empty())
                    redo_list.clear();
            }
            if (line[i]=='<'){
                if (str_pos_cursor!=str_num_cursor->begin())
                    --str_pos_cursor;
                else
                    if (str_num_cursor!=text.begin()){
                        --str_num_cursor;
                        str_pos_cursor=(str_num_cursor->end());
                    }
            }
            if (line[i]=='>'){
                if (str_pos_cursor!=(str_num_cursor->end()))
                    ++str_pos_cursor;
                else
                    if (str_num_cursor!=--(text.end())){
                        ++str_num_cursor;
                        str_pos_cursor=str_num_cursor->begin();
                    }
            }
            if (line[i]=='^'){
                if (str_num_cursor!=text.begin()){
                    size_t k=0;
                    for (auto it=str_num_cursor->begin(); it!=str_pos_cursor; it++)
                        k++;
                    --str_num_cursor;
                    if (k<str_num_cursor->size())
                        str_pos_cursor=string::iterator(&(str_num_cursor->at(k)));
                    else
                        str_pos_cursor=(str_num_cursor->end());
                }
            }
            if (line[i]=='|'){
                if (str_num_cursor!=--text.end()){
                    size_t k=0;
                    for (auto it=str_num_cursor->begin(); it!=str_pos_cursor; it++)
                        k++;
                    ++str_num_cursor;
                    if (k<str_num_cursor->size())
                        str_pos_cursor=string::iterator(&(str_num_cursor->at(k)));
                    else
                        str_pos_cursor=(str_num_cursor->end());
                }
            }
            if (line[i]=='#'){
                if(str_pos_cursor!=str_num_cursor->begin()){
                    auto temp=--str_pos_cursor;
                    str_pos_cursor++;
                    undo_list.push_back(Action(false, *temp, str_num_cursor, str_pos_cursor));
                    if (!redo_list.empty())
                        redo_list.clear();
                    str_num_cursor->erase(temp);
                }
                else{
                    auto it=str_num_cursor;
                    if (it!=text.begin()){
                        --str_num_cursor;
                        str_pos_cursor=--(str_num_cursor->end());
                        (*str_num_cursor)=(*str_num_cursor)+(*it);
                        text.erase(it);
                        str_pos_cursor++;
                        undo_list.push_back(Action(false, '\n', str_num_cursor, str_pos_cursor));
                            if (!redo_list.empty())
                        redo_list.clear();
                    }
                }
            }
            if (line[i]=='@'){
                if (!undo_list.empty()){
                    Action temp=undo_list.back();
                    undo_list.pop_back();
                    redo_list.push_back(temp);
                    if (temp.is_insert==true){
                        if(temp.letter!='\n'){
                            cout<<*temp.str_pos<<endl;
                            cout<<(temp.str_pos==str_num_cursor->end())<<endl;
                            str_pos_cursor=temp.str_num->erase((temp.str_pos));
                            cout<<(str_pos_cursor==str_num_cursor->end())<<endl;
                        }
                        else{
                            auto it=str_num_cursor;
                            --str_num_cursor;
                            str_pos_cursor=str_num_cursor->end();
                            text.erase(it);
                        }
                    }
                    else{
                        if(temp.letter!='\n')
                            str_pos_cursor=temp.str_num->insert(temp.str_pos, temp.letter);
                        else{
                            int k=0;
                            for (auto it=temp.str_num->begin(); it!=temp.str_pos; it++)
                                k++;
                            string str_temp=temp.str_num->substr(k);
                            str_num_cursor->erase(temp.str_pos, temp.str_num->end());
                            str_num_cursor=text.insert(++temp.str_num, str_temp);
                            str_pos_cursor=str_num_cursor->begin();
                        }
                    }
                }
            }
            if (line[i]=='$'){

            }
            i++;
        }
        size_t k=0;
        for (auto it=str_num_cursor->begin(); it!=str_pos_cursor; it++)
            k++;
        string str_temp=str_num_cursor->substr(k);
        str_num_cursor->erase(str_pos_cursor, str_num_cursor->end());
        str_num_cursor=text.insert(++str_num_cursor, str_temp);
        str_pos_cursor=str_num_cursor->begin();
        undo_list.push_back(Action(true, '\n', str_num_cursor, str_pos_cursor));
    }
    for (auto i : text)
        cout<<i<<" "<<"1"<<endl;
    fin.close();
}
