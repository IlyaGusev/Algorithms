#ifndef SORT_H_INCLUDED
#define SORT_H_INCLUDED
    #include <iostream>
    #include <stdlib.h>
    #include <time.h>
    #include <stdint.h>
    #include <cstring>
    #include <math.h>
    #include <fstream>
    #include <algorithm>
    void qsortstan      (int*, int, int);
    void qsortrand      (int*, int, int);
    void qihsort        (int*, int, int);
    void msort          (int*, int, int);
    void msortloop      (int*, int, int);
    void isort          (int*, int, int);
    void hsort          (int*, int, int);
    void hsortloop      (int*, int, int);
    void usort          (int*, int, int);
    void ssort          (int*, int, int);

    void display        (int*, int, int);
    void display_in_file(int*, int, int);

    void swap           (int &, int &);

    int partition       (int*, int, int);
    int rand_partition  (int*, int, int);

    int right           (int);
    int left            (int);
    void heapify        (int*, int, int, int);
    void heapifyloop    (int*, int, int, int);
    void build_max_heap (int*, int, int);
    void build_max_heap_loop (int*, int, int);

    void merge          (int*, int, int, int);
    void mergeloop      (int*, int, int, int, int*, int*);

    template <typename DataType>
    DataType cmp        (DataType * l, DataType * r);
    int cmp_str         (void*, void*);

    bool is_correct     (const char*);
#endif // SORT_H_INCLUDED
