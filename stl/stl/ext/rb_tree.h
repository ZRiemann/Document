#ifndef _Z_RB_TREE_H_
#define _Z_RB_TREE_H_

namespace z{
    typedef bool __rb_tree_color_type;
    const __rb_tree_color_type __rb_tree_red = false; // 0 红色
    const __rb_tree_color_type __rb_tree_black = true; // 1 黑色

    struct __rb_tree_node_base{
        typedef __rb_tree_color_type color_type;
        typedef __rb_tree_node_base *base_ptr;

        color_type color; // 节点颜色
        base_ptr parent;
        base_ptr left;
        base_ptr right;
        // void *user;
        static base_ptr minimum(base_ptr x){
            while(x->left) x=x->left;
            return x;
        }
        static base_ptr maxmum(base_ptr x){
            while(x->right) x=x->right;
            return x;
        }
    };

    template <class Value>
        struct __rb_tree_node : public __rb_tree_node_base{
        typedef __rb_tree_node<Value> *link_type;
        Value value_field;  // 节点值
    };

    struct __rb_tree_base_iterator{
        __rb_tree_node_base *node;
        void increment(){
            if(node->right){
                node = node->right;
                while(node->left){
                    node = node->left;
                }
            }else{
                base_ptr y = node->parent;
                while(node == y->right){
                    node = y;
                    y = y->parent;
                }
                if(node->right != y){
                    node = y;
                }
            }
        }
        void decrement(){
            if(node->color == __rb_tree_red && node->parent->parent == node){
                node = node->right;
            }else if(node->left){
                base_ptr y = node->left;
                while(y->right){
                    y = y->right;
                    node = y;
                }
            }else{
                base_ptr y = node->parent;
                while(node == y->left){
                    node = y;
                    y = y->parent;
                }
                node = y;
            }
        }
    };

    template <class Value, class Ref, class Ptr>
        struct __rb_tree_iterator{
            typedef Value value_type;
            typedef Ref reference;
            typedef Ptr pointer;
            typedef __rb_tree_iterator<Value, Value&, Value*> iterator;
            typedef __rb_tree_iterator<Value, const Value&, const Value*> const_iterator;
            typedef __rb_tree_iterator<Value, Ref, Ptr> self;
            typedef __rb_tree_node<Value> *link_type;

            __rb_tree_iterator(){}
            __rb_tree_iterator(link_type x){node = x;}
            __rb_tree_iterator(const iterator &it){node = it.node;}

            reference operator*()const{return link_type(node)->value_field;}
            pointer operator->()const{return &(operator*());}
            self& operator++(){increment(); return *this;}
            self operator++(int){
                self tmp = *this;
                increment();
                return tmp;
            }
            operator--(){decrement(); return *this;}
            operator--(int){
                self tmp = *this;
                decrement();
                return tmp;
            }
        };

    template <class Key, class Value, class KeyOfValue, class Compare, class Alloc = alloc>
        class rb_tree{
    protected:
    typedef void *void_pointer;
    typedef __rb_tree_node_base *base_ptr;
    typedef __rb_tree_node<Value> rb_tree_node;
    typedef simple_alloc<rb_tree_node, Alloc> rb_tree_node_allocator;
    typedef __rb_tree_color_type color_type;

    size_type node_count;
    link_type header;
    Compare key_compare;

    link_type &root()const{return (link_type&)header->parent;}
    link_type &leftmost()const{return (link_type&)header->left;}
    link_type &rightmost()const{return (link_type&)header->right;}
    public:
    
    };
}


#endif
