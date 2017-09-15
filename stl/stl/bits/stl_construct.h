#ifndef _Z_STL_CONSTRUCT_H_
#define _Z_STL_CONSTRUCT_H_

#include <new>

namespace z{
    template <class T1, class T2>
        inline void construct(T1 *p, const T2 &value){
        new(p) T1(value);
    }

    template <class T>
        inline void destroy(T *pointer){
        pointer->~T();
    }

    template <class ForwardIterator, class T>
        inline void __destroy(ForwardIterator first, ForwardIterator last, T*){
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;
        __destroy_aux(first, last, trivial_destructor());
    }

    template <class ForwardIterator>
        inline void destroy(ForwardIterator first, ForwardIterator last){
        __destroy(first, last, value_type(first));
    }
#if 1 // non-trivial destructor 效率考虑 需要调用析构函数的析构， __false_type 进行析构
    template <class ForwardIterator>
        inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type){
        for(; first < last; ++first){
            destroy(&*first);
        }
    }
#else // trivial destructor 不需要调用析构函数的析构
    template <class ForwardIterator>
        inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type){}
#endif
}
#endif