#ifndef _Z_STL_ALGO_H_
#define _Z_STL_ALGO_H_

namespace z{
    template <class InputIterator, class T>
        InputIterator find(InputIterator first,
                           InputIterator last,
                           const T& value){
        while(first != last && *first != value){
            ++first;
        }
        return first;
    }
}
#endif