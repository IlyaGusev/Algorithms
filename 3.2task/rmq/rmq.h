#ifndef RMQ_H_INCLUDED
#define RMQ_H_INCLUDED

#include <algorithm>
#include <utility>
#include <vector>
#include <string>
#include <cmath>
#include "../../3.1task/speedtest/speedtest.h"
#include "../treap/treap.h"

using std::cout;
using std::cin;
using std::endl;
using std::less;
using std::vector;
using std::string;
using std::pair;
using std::make_pair;
using std::logic_error;
using std::min;
using std::max;
using std::swap;

template <class T, class Compare = less<T>>
class SqrtDecomposition{
    public:
        void preprocess(vector<T>&);
        T find(int, int);
        void change(int, T);
    private:
        int amount;
        int length;
        vector<T> minimums;

        vector<T>* data;
};

template <class T, class Compare = less<T>>
class SegmentTree{
    public:
        void preprocess(vector<T>&);
        T find(int, int);
        void change(int, T);
    private:
        vector<T> minimums;

        vector<T>* data;

        T find_recursive(int, int, int, int, int);
        void build(int, int, int);
};

template <class T, class Compare = less<T>>
class FKB{
    public:
        void preprocess(vector<T>&);
        T find(int, int);
        void print_preprocess();
    private:
        vector<int> height;
        vector<int> first;
        vector<int> order;
        vector<vector<int>> table;
        vector<int> pows;
        vector<int> hashes;
        vector<vector<vector<int>>> precalcs;
        int block_size;
        int amount;

        vector<T>* data;

        void precalc_block(int, int);
        void rmq_to_srmq();
        int dfs(shared_ptr<typename Treap<int, T>::Node>, int, int);
        void build_sparse_table();
        void calc_hashes();
};

template <class T, class Compare = less<T>, class Algo = SqrtDecomposition<T, Compare> >
class RMQ{
    public:
        RMQ(vector<T>& _data) : data(_data), algo() { algo.preprocess(_data); }
        RMQ() : data(), algo() {}
        RMQ(const RMQ& c) : data(c.data), algo(c.algo) { algo.preprocess(data); }
        T find(int id1, int id2){ return algo.find(id1, id2); }
        void change(int index, T value){ algo.change(index, value); }
        void print_preprocess(){ algo.print_preprocess(); }
    private:
        vector<T> data;
        Algo algo;
};

#include "sqr.hpp"
#include "fkb.hpp"
#include "str.hpp"

#endif // RMQ_H_INCLUDED
