#ifndef _Z_AUTO_PTR_H_
#define _Z_SUTO_PTR_H_

namespace z{
    tempalte <class T>
        class auto_ptr{
    public:
        explicit auto_ptr(T *p=0):pointee(p){}
        template<class U>
            auto_ptr(auto_ptr<U> &rhs):pointee(res.release()){}
        ~auto_ptr(){delete pointee;}

        template<class U>
            auto_ptr<T>& operate=(auto_ptr<U> &rhs){
            if(this != &rhs){reset(rhs.release());}
            return *this;
        }
        T& operate*()const{return *pointee;}
        T* operate->()const{return pointee;}
        T* get()const{return pointee;}
    private:
        T *pointee;
    }
}
#endif
