#ifndef PREFIX_HPP_INCLUDED
#define PREFIX_HPP_INCLUDED

#include <iostream>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;
vector<int> prefix_func(const string&);
vector<int> prefix_func(const string& str) {
    int length = str.length();
    vector<int> answer(length);
    answer[0] = 0;
    int k = 0;
    for(int i=1; i<length; i++){
        while (k>0 && str[k]!=str[i])
            k = answer[k-1];
        if (str[k] == str[i])
            k++;
        answer[i] = k;
    }
    return answer;
}

#endif // PREFIX_HPP_INCLUDED
