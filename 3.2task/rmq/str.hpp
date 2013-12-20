#ifndef STR_HPP_INCLUDED
#define STR_HPP_INCLUDED

template <class T, class Compare>
    void SegmentTree<T, Compare>::build(int index, int left, int right) {
        if (left == right)
            minimums[index] = (*data)[left];
        else {
            int middle = (left+right)/2;
            build(index*2, left, middle);
            build(index*2+1, middle+1, right);
            if (Compare()(minimums[index*2], minimums[index*2+1]))
                minimums[index] = minimums[index*2];
            else
                minimums[index] = minimums[index*2+1];
        }
    }

template <class T, class Compare>
    void SegmentTree<T, Compare>::preprocess(vector<T>& d) {
        data = &d;
        minimums.resize(4*d.size());
        build(1, 0, d.size()-1);
    }

template <class T, class Compare>
    T SegmentTree<T, Compare>::find_recursive(int index, int left, int right, int i, int j) {
        if  (i == left && j == right) return minimums[index];

        int middle = (left+right)/2;
        T l,r;
        bool bad_l = false, bad_r = false;

        if (i<=min(j,middle)) l=find_recursive(index*2, left, middle, i, min(j,middle)); else bad_l = true;
        if (max(i,middle+1)<=j) r=find_recursive(index*2+1, middle+1, right, max(i,middle+1), j); else bad_r = true;

        if (bad_l && bad_r)
            return minimums[index];
        if (bad_l)
            return r;
        if (bad_r)
            return l;
        if (Compare()(l, r)) return l; else return r;
    }

template <class T, class Compare>
    T SegmentTree<T, Compare>::find(int i, int j) {
        return find_recursive(1, 0, data->size()-1, i, j);
    }

template <class T, class Compare>
    void SegmentTree<T, Compare>::change(int index, T value) {
        int left = 0, right = (*data).size(), tree_index = 1;
        while (left!=right){
            int middle = (left+right)/2;
            if (Compare()(value, minimums[tree_index]))
                minimums[tree_index] = value;
            if (index>middle){
                left = middle+1;
                tree_index=2*tree_index+1;
            }
            else{
                right = middle;
                tree_index*=2;
            }
        }
        (*data)[index] = value;
        minimums[tree_index] = value;
    }

#endif // STR_HPP_INCLUDED
