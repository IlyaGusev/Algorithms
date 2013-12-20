#ifndef RMQ_HPP_INCLUDED
#define RMQ_HPP_INCLUDED

template <class T, class Compare>
    void SqrtDecomposition<T, Compare>::preprocess(vector<T>& d) {
        length = ceil(sqrt(d.size()));
        amount = (int)ceil(((double)d.size())/((double)length));
        minimums = vector<T> (amount);

        int counter = 0;
        int current_minimums_index = 0;
        minimums[current_minimums_index] = d[0];
        for (int i=0; i<d.size(); i++){
            if (counter != length){
                if (Compare()((d[i]), minimums[current_minimums_index]))
                    minimums[current_minimums_index] = d[i];
                counter++;
            }
            else{
                counter = 1;
                current_minimums_index++;
                minimums[current_minimums_index] = d[i];
            }
        }
        data = &d;
    }

template <class T, class Compare>
    T SqrtDecomposition<T, Compare>::find(int i, int j) {
        //cout<<"length: "<<length<<endl;
        int r = j/length;
        //cout<<"right: "<<r<<endl;
        int l = (int)ceil(((double)i)/((double)length));
        //cout<<"left: "<<l<<endl;
        T minimum = (*data)[i];
        if (r>=l) {
            for (int p=l; p<r; p++)
                if (Compare()(minimums[p], minimum))
                    minimum = minimums[p];
            for (int p=i; p<l*length; p++)
                if (Compare()((*data)[p], minimum))
                    minimum = (*data)[p];
            for (int p=r*length; p<=j; p++)
                if (Compare()((*data)[p], minimum))
                    minimum = (*data)[p];
        } else {
            for (int p=i; p<=j; p++)
                if (Compare()((*data)[p], minimum))
                    minimum = (*data)[p];
        }
        return minimum;
    }

template <class T, class Compare>
void SqrtDecomposition<T, Compare>::change(int index, T value) {
    (*data)[index] = value;
    int min_index = index/length;
    if (Compare()(value, minimums[min_index]))
        minimums[min_index] = value;
}



#endif // RMQ_HPP_INCLUDED
