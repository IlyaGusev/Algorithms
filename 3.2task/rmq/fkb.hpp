#ifndef FKB_HPP_INCLUDED
#define FKB_HPP_INCLUDED

#define H(x) height[order[x]]
#define PRECALC(l, i, j) precalcs[hashes[l]][i][j]

template <class T, class Compare>
    void FKB<T, Compare>::preprocess(vector<T>& d) {
        data = &d;
        rmq_to_srmq();
        block_size = (int)(ceil(0.5*log2(order.size())));
        amount = (int)ceil(((double)order.size())/((double)block_size));
        build_sparse_table();
        pows = vector<int>(amount);
        for (int i=0; i<amount; i++)
            pows[i] = (int)log2(i);
        calc_hashes();
        //print_preprocess();
    }

template <class T, class Compare>
    void FKB<T, Compare>::rmq_to_srmq() {
        Treap<int, T> treap;
        treap.build((*data));
        height = vector<int>((*data).size(), 0);
        first = vector<int>((*data).size(), -1);
        order = vector<int>(3*(*data).size());
        int n = dfs(treap.root(), 0, 0);
        order.resize(n);
    }

template <class T, class Compare>
    int FKB<T, Compare>::dfs(shared_ptr<typename Treap<int, T>::Node> node, int index, int h){
        order[index] = node->key();
        first[node->key()] = index;
        height[node->key()] = h;
        index++;
        h++;
        if (node->left()!=nullptr){
            index = dfs(node->left(), index, h);
            order[index] = node->key();
            index++;
        }
        if (node->right()!=nullptr){
            index = dfs(node->right(), index, h);
            order[index] = node->key();
            index++;
        }
        return index;
    }

template <class T, class Compare>
    void FKB<T, Compare>::build_sparse_table(){
        ///Find minimums in blocks
        vector<int> minimums = vector<int>(amount);
        int counter = 0;
        int current_minimum = H(0);
        int current_minimums_index = 0;
        minimums[0] = 0;
        for (int i=0; i<order.size(); i++){
            if (counter != block_size){
                if (H(i) < current_minimum){
                    minimums[current_minimums_index] = i;
                    current_minimum = H(i);
                }
                counter++;
            }
            else{
                counter = 1;
                current_minimum = H(i);
                current_minimums_index++;
                minimums[current_minimums_index] = i;
            }
        }

        ///Build sparse table on it
        table = vector<vector<int>>(minimums.size(), vector<int>((int)log2(amount)+2, -1));
        for (int i=0; i<amount; i++)
            table[i][0] = minimums[i];

        for (int i=1; i<(int)log2(amount)+2; i++){
            for (int j=0; j<amount; j++){
                if (j+(int)pow(2, i-1)<amount){
                    if(H(table[j][i-1]) < H(table[j+(int)pow(2, i-1)][i-1]))
                        table[j][i] = table[j][i-1];
                    else
                        table[j][i] = table[j+(int)pow(2, i-1)][i-1];
                }
                else
                    table[j][i] = table[j][i-1];
            }
        }
    }

template <class T, class Compare>
    void FKB<T, Compare>::calc_hashes(){
        hashes = vector<int>(amount, 0);
        precalcs = vector<vector<vector<int>>>((int)pow(2, block_size-1), vector<vector<int>>(block_size, vector<int>(block_size, -1)));
        int counter = 0;
        int index = 0;
        for (int i=0; i<order.size(); i++){
            if (counter != block_size){
                if (H(i)>H(i-1))
                    hashes[index]=(hashes[index]<<1)+1;
                else
                    hashes[index]=(hashes[index]<<1);
                counter++;
            }
            else{
                precalc_block(index, block_size);
                counter = 1;
                index++;
            }
        }
        if (counter != 1)
            precalc_block(index, counter);
    }


template <class T, class Compare>
    void FKB<T, Compare>::precalc_block(int index, int border) {
        if (PRECALC(index, 0, 0) == -1){
            for (int k=0; k<border; k++)
                    PRECALC(index, k, k) = k;
            for (int k=0; k<border; k++)
                for (int j=k+1; j<border; j++)
                    if (H(j+index*block_size)< H(PRECALC(index, k, j-1)+index*block_size))
                        PRECALC(index, k,j) = j;
                    else
                        PRECALC(index, k, j) = PRECALC(index, k, j-1);
        }
    }


template <class T, class Compare>
    T FKB<T, Compare>::find(int __i, int __j) {
        if (__i<=__j){
            int i = first[__i];
            int j = first[__j];
            if (i>j)
                swap(i,j);

            int b = block_size;
            int r = j/b;
            int l = (int)ceil(((double)i+1)/((double)b))-1;
            int minimum = i;
            if (r > l+1) {
                int sz = pows[r-l-1];
                if (H(table[l+1][sz])<H(table[r-1-pow(2, sz)+1][sz]))
                    minimum = table[l+1][sz];
                else
                    minimum = table[r-1-pow(2, sz)+1][sz];
                if (H(PRECALC(l, i-l*b, b-1) + l*b) < H(minimum))
                    minimum = PRECALC(l, i-l*b, b-1)+l*b;
                if (H(PRECALC(r, 0, j-r*b)+r*b) < H(minimum))
                    minimum = PRECALC(r, 0, j-r*b)+r*b;
            }
            if (r == l+1){
                if (H(PRECALC(l, i-l*b, b-1)+l*b) < H(minimum))
                    minimum = PRECALC(l, i-l*b, b-1)+l*b;
                if (H(PRECALC(r, 0, j-r*b)+r*b) < H(minimum))
                    minimum = PRECALC(r, 0, j-r*b)+r*b;
            }
            if (r == l){
                if (H(PRECALC(l, i-l*b, j-l*b)+l*b) < H(minimum))
                    minimum = PRECALC(l, i-l*b, j-l*b)+l*b;
            }

            return (*data)[order[minimum]];
        }
        return (*data)[__i];
    }

template <class T, class Compare>
    void FKB<T, Compare>::print_preprocess() {
        Treap<int, T> treap;
        treap.build((*data));
        treap.print();

        cout<<"Order: "<<order<<endl;
        cout<<"Height: "<<height<<endl;

        cout<<"Order's heights: ";
        for (int i=0; i<order.size(); i++)
            cout<<height[order[i]]<<" ";
        cout<<endl;

        cout<<"Table:"<<endl;
        for (int i=0; i<table.size(); i++){
            cout<<table[i]<<endl;
        }

        cout<<"Hashes: "<<hashes<<endl;

        for (int i=0; i<precalcs.size(); i++){
            cout<<"Hash: "<<i<<" "<<"Table:"<<endl;
            for (int j=0; j<precalcs[i].size(); j++){
                for (int k=0; k<precalcs[i][j].size(); k++)
                    cout<<precalcs[i][j][k]<<" ";
                cout<<endl;
            }
        }
        cout<<endl;
    }

#endif // FKB_HPP_INCLUDED
