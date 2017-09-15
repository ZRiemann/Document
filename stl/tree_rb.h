#ifndef _Z_CONT_RB_TREE_H_
#define _Z_CONT_RB_TREE_H_
/**
 * @file zit/container/base/tree_rb.h
 * @brief Implement a bed-black tree
  */

#include <zit/base/type.h>
#include <zit/base/atomic.h>
#include <zit/container/base/alloc.h>
#include <zit/thread/spin.h>
ZC_BEGIN

typedef struct zbinary_tree_node_s{
    struct zbinary_tree_node_s *parent;
    struct zbinary_tree_node_s *left;
    struct zbinary_tree_node_s *right;
    int flag; /** 0x01:1-black 0-red; 0x02:0-parent->left 1-parent->right*/
    char data[]; /** key + value structure */
}zbtnode_t;

#define zrbn_is_red(node) (node && !(node->flag & 1))
#define zrbn_is_black(node) (!node || (node->flag & 1))
#define zrbn_chg_color(node) do{node->flag ^= 1;}while(0)
#define zrbn_set_black(node) do{node->flag |= 1;}while(0)
#define zrbn_set_red(node) do{node->flag &= ~1;}while(0)
#define zrbn_key(node) (*(int32_t*)(node)->data)
#define zrbn_great(refer, node) (*(int32_t*)refer->data > *(int32_t*)node->data)
#define zrbn_little(refer, node) (*(int32_t*)refer->data < *(int32_t*)node->data)
#define zrbn_compare(refer, ndoe) (*(int32_t*)refer->data - *(int32_t*)node->data)
#define zrbn_grandpa(node) (node->parent->parent)
//#define zrbn_sibling(ndoe) (node == node->parent->left ? node->parent->right : node->parent->left)
zinline zbtnode_t *zrbn_sibling(zbtnode_t *node){
    return node == node->parent->left ? node->parent->right : node->parent->left;
}

zinline zbtnode_t *zrbn_uncle(zbtnode_t *node){
    zbtnode_t *uncle = NULL;
    if(node && node->parent && node->parent->parent){
        zbtnode_t *parent = node->parent;
        if(parent == parent->parent->left){
            uncle = parent->parent->right;
        }else{
            uncle = parent->parent->left;
        }
    }
    return uncle;
}

typedef struct zbinary_tree_s{
    zbtnode_t *root;
    zalloc_t *alloc;
    zoperate cmp; /** cmp(nod1, NULL, nod2) for extention*/
    zspinlock_t spin; /** thread safe */
    int data_size;
}zbtree_t;

ZAPI zerr_t zrbtree_create(zbtree_t **tree, int32_t node_size, int32_t capacity);
ZAPI zerr_t zrbtree_destroy(zbtree_t *tree);
ZAPI zerr_t zrbtree_foreach(zbtree_t *tree, int order, zoperate do_each, zvalue_t hint);
ZAPI void zrbtree_print(zbtree_t *tree);
ZAPI zerr_t zrbtree_verify(zbtree_t *tree);

/*
 * inline implements
 */
#define ZRB_A 1
#define ZRB_B 2
#define ZRB_IMP ZRB_A
#include <zit/base/trace.h>

zinline zerr_t zrbtree_compare(zbtree_t *tree, zbtnode_t *refer, zbtnode_t *node){
    return tree->cmp ? tree->cmp(refer, NULL, node) : zrbn_compare(refer, node);
}

zinline zerr_t zrbtree_get_node(zbtree_t *tree, zbtnode_t **node){
    return zalloc_pop(tree->alloc, (zvalue_t*)node);
}
zinline zerr_t zrbtree_push_node(zbtree_t *tree, zbtnode_t **node){
    return zalloc_push(tree->alloc, (zvalue_t*)node);
}

zinline zerr_t zrbtree_find(zbtree_t *tree, int32_t key, zbtnode_t **node){
    zbtnode_t *refer = tree->root;
    zerr_t ret = ZEQUAL;
    while(refer){
        ret = zrbn_key(refer) - key;
        if(0 < ret){
            refer = refer->left;
        }else if(0 > ret){
            refer = refer->right;
        }else{
            *node = refer;
            return ZEOK;
        }
    }
    *node = NULL;
    return ZENOT_EXIST;
}

#if (ZRB_IMP == ZRB_A)
static void zrbtree_insert_case1(zbtree_t *tree, zbtnode_t *node);

zinline void zrbtree_replace_node(zbtree_t *tree, zbtnode_t *old, zbtnode_t *node){
    if(!old->parent){
        tree->root = node;
    }else{
        if(old == old->parent->left){
            old->parent->left = node;
        }else{
            old->parent->right = node;
        }
    }
    if(node){
        node->parent = old->parent;
    }
}

zinline void zrbtree_left_rotate(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *right = node->right;
    zrbtree_replace_node(tree, node, right);
    node->right = right->left;
    if(right->left){
        right->left->parent = node;
    }
    right->left = node;
    node->parent = right;
}
zinline void zrbtree_right_rotate(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *left = node->left;
    zrbtree_replace_node(tree, node,  left);
    node->left = left->right;
    if(left->right){
        left->right->parent = node;
    }
    left->right = node;
    node->parent = left;
}
zinline void zrbtree_insert_case5(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *grandpa = zrbn_grandpa(node);
    zrbn_set_black(node->parent);
    zrbn_set_red(grandpa);
    if(node == node->parent->left && node->parent == grandpa->left){
        zrbtree_right_rotate(tree, grandpa);
    }else{
        /* assert(node == node->parent->right && node->parent == zrbn_grandpa(node)->right)*/
        zrbtree_left_rotate(tree, grandpa);
    }
}
zinline void zrbtree_insert_case4(zbtree_t *tree, zbtnode_t *node){
    if(node == node->parent->right && node->parent == zrbn_grandpa(node)->left){
        zrbtree_left_rotate(tree, node->parent);
        node = node->left;
    }else if(node == node->parent->left && node->parent == zrbn_grandpa(node)->right){
        zrbtree_right_rotate(tree, node->parent);
        node = node->right;
    }
    zrbtree_insert_case5(tree, node);
}
zinline void zrbtree_insert_case3(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *uncle = zrbn_uncle(node);
    zbtnode_t *grandpa = node->parent->parent;
    if(zrbn_is_red(uncle)){
        zrbn_set_black(node->parent);
        zrbn_set_black(uncle);
        zrbn_set_red(grandpa);
        zrbtree_insert_case1(tree, grandpa);
    }else{
        zrbtree_insert_case4(tree, node);
    }
}

zinline void zrbtree_insert_case2(zbtree_t *tree, zbtnode_t *node){
    if(zrbn_is_red(node->parent)){
        zrbtree_insert_case3(tree, node);
    }
}
zinline void zrbtree_insert_case1(zbtree_t *tree, zbtnode_t *node){
    if(!node->parent){
        zrbn_set_black(node);
    }else{
        zrbtree_insert_case2(tree, node);
    }
}

zinline zerr_t zrbtree_insert(zbtree_t *tree, zbtnode_t *node){
    zerr_t ret;
    zrbn_set_red(node);
    if(!tree->root){
        tree->root = node;
    }else{
        zbtnode_t *refer = tree->root;
        while(refer){
            ret = zrbtree_compare(tree, refer, node);
            if(ZEQUAL == ret){
                return ZEPARAM_INVALID;
            }else if(0 < ret){
                refer->left ? refer = refer->left :
                    (refer->left = node, node->parent = refer, refer = NULL);
            }else{
                refer->right ? refer = refer->right :
                    (refer->right = node, node->parent = refer, refer = NULL);
            }
        }
    }
    zrbtree_insert_case1(tree, node);
    zrbtree_verify(tree);
    return ZEOK;
}

zinline zbtnode_t *zrbtree_maximum(zbtnode_t *node){
    if(node && node->right){
        node = node->right;
    }
    return node;
}

static void zrbtree_erase_case1(zbtree_t *tree, zbtnode_t *node);
static void zrbtree_erase_case6(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *sibling = zrbn_sibling(node);
    if(zrbn_is_black(node->parent)){zrbn_set_black(sibling);}else{zrbn_set_red(sibling);}
    zrbn_set_black(node->parent);
    if(node == node->parent->left){
        // assert(zrbn_is_red(sibling->right))
        zrbn_set_black(sibling->right);
        zrbtree_left_rotate(tree, node->parent);
    }else{
        // assert(zrbn_is_red(sibling->left))
        zrbn_set_black(sibling->left);
        zrbtree_right_rotate(tree, node->parent);
    }
}
static void zrbtree_erase_case5(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *sibling = zrbn_sibling(node);
    if(node == node->parent->left &&
       zrbn_is_black(sibling) &&
       zrbn_is_red(sibling->left) &&
       zrbn_is_black(sibling->right)){
        zrbn_set_red(sibling);
        zrbn_set_black(sibling->left);
        zrbtree_right_rotate(tree, sibling);
    }else if(node == node->parent->right &&
             zrbn_is_black(sibling) &&
             zrbn_is_red(sibling->right) &&
             zrbn_is_black(sibling->left)){
        zrbn_set_red(sibling);
        zrbn_set_black(sibling->right);
        zrbtree_left_rotate(tree, sibling);
    }
    zrbtree_erase_case6(tree, node);
}
static void zrbtree_erase_case4(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *sibling = zrbn_sibling(node);
    if(zrbn_is_red(node->parent) &&
       zrbn_is_black(sibling) &&
       zrbn_is_black(sibling->left) &&
       zrbn_is_black(sibling->right)){
        zrbn_set_red(sibling);
        zrbn_set_black(node->parent);
    }else{
        zrbtree_erase_case5(tree, node);
    }
}

static void zrbtree_erase_case3(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *sibling = zrbn_sibling(node);
    if(zrbn_is_black(node->parent) &&
       zrbn_is_black(sibling) &&
       zrbn_is_black(sibling->left) &&
       zrbn_is_black(sibling->right)){
        zrbn_set_red(sibling);
        zrbtree_erase_case1(tree, node->parent);
    }else{
        /* case 4 */
        zrbtree_erase_case4(tree, node);
    }
}

static void zrbtree_erase_case1(zbtree_t *tree, zbtnode_t *node){
    if(node->parent){
        /* case 2*/
        zbtnode_t *sibling = zrbn_sibling(node);
        if(zrbn_is_red(sibling)){
            zrbn_set_red(node->parent);
            zrbn_set_black(sibling);
            if(node == node->parent->left){
                zrbtree_left_rotate(tree, node->parent);
            }else{
                zrbtree_right_rotate(tree, node->parent);
            }
        }
        zrbtree_erase_case3(tree, node);
    }
}
zinline zerr_t zrbtree_erase(zbtree_t *tree, int32_t key){
    int ret = ZEOK;
    zbtnode_t *child = NULL;
    zbtnode_t *node = NULL;
    if(ZOK != (ret = zrbtree_find(tree, key, &node))){
        return ret;
    }
    if(node->left && node->right){
        zbtnode_t *pred = zrbtree_maximum(node->left);
        memcpy(node->data, pred->data, tree->data_size);
        node = pred;
    }
    // assert(!node->left || !node->right);
    child = node->right ? node->right : node->left;
    if(zrbn_is_black(node)){
        if(zrbn_is_black(child)){zrbn_set_black(node);}else{zrbn_set_red(node);}
        zrbtree_erase_case1(tree, node);
    }
    zrbtree_replace_node(tree, node, child);
    if(!node->parent && child){
        zrbn_set_black(child);
    }
    zrbtree_push_node(tree, &node);
    zrbtree_verify(tree);
    return ret;
}
#else
zinline void zrbtree_right_rotate(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *left = node->left;
    if(!left){
        ZDBG("left is NULL.");
        return;
    }
    node->left = left->right;
    if(node->left){
        left->right->parent = node;
    }
    left->right = node;
    left->parent = node->parent;
    if(left->parent){
        if(node == node->parent->right){
            node->parent->right = left;
        }else{
            node->parent->left = left;
        }
    }else{
        tree->root = left;
        zrbn_set_black(left);
    }
    node->parent = left;
}
zinline void zrbtree_left_rotate(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *right = node->right;
    if(!right){
        ZDBG("right is NULL.");
        return;
    }
    node->right = right->left;
    if(node->right){
        right->left->parent = node;
    }
    right->left = node;
    right->parent = node->parent;
    if(right->parent){
        if(node == node->parent->right){
            node->parent->right = right;
        }else{
            node->parent->left = right;
        }
    }else{
        tree->root = right;
        zrbn_set_black(right);
    }
    node->parent = right;
}

zinline void zrbtree_rebalance_erase(zbtree_t *tree, zbtnode_t *node, zbtnode_t *parent){
    zbtnode_t *sibling = NULL;
    zbtnode_t *root = tree->root;//->left; // ++
    while((!node || zrbn_is_black(node)) && (node != root)){
        if(parent->left == node){
            sibling = parent->right;
            if(zrbn_is_red(sibling)){
                zrbn_set_black(sibling);
                zrbn_set_red(parent);
                zrbtree_left_rotate(tree, parent);
                sibling = parent->right;
            }

            if(!sibling){
                zprint("\nsibling is NULL.\n");
                break;
            }

            if((!sibling->left || zrbn_is_black(sibling->left)) &&
               (!sibling->right || zrbn_is_black(sibling->right))){
                zrbn_set_red(sibling);
                node = parent;
                parent = node->parent;
            }else{
                if(!sibling->right ||  zrbn_is_black(sibling->right)){
                    if(sibling->left){
                        zrbn_set_black(sibling->left);
                    }
                    zrbn_set_red(sibling);
                    zrbtree_right_rotate(tree, sibling);
                    sibling = parent->right;
                }
                if(zrbn_is_black(parent)){ zrbn_set_black(sibling); }else{ zrbn_set_red(sibling);}
                zrbn_set_black(parent);
                if(sibling->right){
                    zrbn_set_black(sibling->right);
                }
                zrbtree_left_rotate(tree, parent);
                node = root;
            }
        }else{
            sibling = parent->left;
            if(zrbn_is_red(sibling)){
                zrbn_set_black(sibling);
                zrbn_set_red(parent);
                zrbtree_right_rotate(tree, parent);
                sibling = parent->left;
            }
            if(!sibling){
                zprint("\nsibling is NULL.\n");
                break;
            }
            if((!sibling->left || zrbn_is_black(sibling->left)) &&
               (!sibling->right || zrbn_is_black(sibling->right))){
                zrbn_set_red(sibling);
                node = parent;
                parent = node->parent;
            }else{
                if(!sibling->left || zrbn_is_black(sibling->left)){
                    if(sibling->right){
                        zrbn_set_black(sibling->right);
                    }
                    zrbn_set_red(sibling);
                    zrbtree_left_rotate(tree, sibling);
                    sibling = parent->left;
                }
                if(zrbn_is_black(parent)){zrbn_set_black(sibling);}else{zrbn_set_red(sibling);}
                zrbn_set_black(parent);
                if(sibling->left){
                    zrbn_set_black(sibling->left);
                }
                zrbtree_right_rotate(tree, parent);
                node = root;
                break;
            }
        }
    }

    if(node){
        zrbn_set_black(node);
    }
}


zinline void zrbtree_rebalance_insert(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *parent = NULL;
    zbtnode_t *grandpa = NULL;
    zbtnode_t *uncle = NULL;
    zbtnode_t *tmp = NULL;

    while((parent = node->parent) && (zrbn_is_red(parent))){
        grandpa = parent->parent;
        if(!grandpa){
            break;
        }

        if(parent == grandpa->left){
            uncle = grandpa->right;
            if(uncle && zrbn_is_red(uncle)){
                zrbn_set_black(uncle);
                zrbn_set_black(parent);
                zrbn_set_red(grandpa);
                node = grandpa;
            }else{
                if(parent->right == node){
                    zrbtree_left_rotate(tree, parent);
                    tmp= node;
                    node = parent;
                    parent = tmp;
                }
                zrbn_set_black(parent);
                zrbn_set_red(grandpa);
                zrbtree_right_rotate(tree, grandpa);
            }
        }else{
            uncle = grandpa->left;
            if(uncle && zrbn_is_red(uncle)){
                zrbn_set_black(uncle);
                zrbn_set_black(parent);
                zrbn_set_red(grandpa);
                node = grandpa;
            }else{
                if(parent->left == node){
                    zrbtree_right_rotate(tree, parent);
                    tmp = node;
                    node = parent;
                    parent = tmp;
                }
                zrbn_set_black(parent);
                zrbn_set_red(grandpa);
                zrbtree_left_rotate(tree, grandpa);
            }
        }
    }
    zrbn_set_black(tree->root);
}
zinline zbtnode_t *zrbtree_search_auxiliary(zbtree_t *tree, int32_t key, zbtnode_t **parent){
    zbtnode_t *node = tree->root;
    int ret = 0;
    *parent = NULL;
    while(node){
        *parent = node;
        ret = zrbn_key(node) - key;
        if(0 < ret){
            node = node->left;
        }else if(0 > ret){
            node = node->right;
        }else{
            return node;
        }
    }
    return NULL;
}
zinline zerr_t zrbtree_insert(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *parent = NULL;
    if(zrbtree_search_auxiliary(tree, zrbn_key(node), &parent)){
        return ZEPARAM_INVALID;
    }
    zrbn_set_red(node);
    node->parent = parent;
    if(parent){
        if(zrbn_key(parent) > zrbn_key(node)){
            parent->left = node;
        }else{
            parent->right = node;
        }
    }else{
        tree->root = node;
        zrbn_set_black(node);
    }
    zrbtree_rebalance_insert(tree, node);
    return ZEOK;
}
zinline zbtnode_t *zrbtree_successor(zbtree_t *tree, zbtnode_t *node, zbtnode_t **parent_){
    zbtnode_t *child, *parent, *old;
    int color;
    old = node;
    /*get right subtree minimum node */
    node = node->right;
    while(node->left){
        node  = node->left;
    }

    /* buffer node infomation */
    child = node->right;
    parent = node->parent;
    color = zrbn_is_black(node);

    if(child){
        child->parent = parent;
    }

    if(parent){
        if(parent->left == node){
            parent->left = child;
        }else{
            /*
             * condition old == parent && child == NULL --> old->right=NULL
             */
            parent->right = child;
        }
    }else{
        tree->root = child;
        zrbn_set_black(tree->root);
    }
    if(node->parent == old){
        parent = node;
    }

    node->parent = old->parent;
    if(zrbn_is_black(node)){zrbn_set_black(old);}else{zrbn_set_red(old);}
    node->right = old->right;
    node->left = old->left;

    if(old->parent){
        if(old->parent->left == old){
            old->parent->left = node;
        }else{
            old->parent->right = node;
        }
    }else{
        tree->root = node;
        zrbn_set_black(node);
    }

    if(old->left){
        old->left->parent = node;
    }else{
        zprint("\nold->left is NULL\n");
    }
    if(old->right){
        old->right->parent = node;
    }else{
        zprint("\n(ln:289) cause old->right is NULL\n");
    }
    if(color){
        zrbn_set_black(node);
    }else{
        zrbn_set_red(node);
    }
    *parent_ = parent;
    return child;
}

zinline zerr_t zrbtree_erase(zbtree_t *tree, int32_t key){
    zbtnode_t *child, *parent, *old, *node;
    char color = 0;
    child = NULL;
    if(!(node = zrbtree_search_auxiliary(tree, key, &parent))){
        return ZENOT_EXIST;
    }
    old = node;
    if(node->left && node->right){
        child = zrbtree_successor(tree, node, &parent);
    }else{
        if(!node->left){
            child = node->right;
        }else if(!node->right){
            child = node->left;
        }//else{child = NULL}
        parent = node->parent;
        color = zrbn_is_black(node);

        if(child){
            child->parent = parent;
        }
        if(parent){
            if(parent->left == node){
                parent->left = child;
            }else{
                parent->right = child;
            }
        }else{
            tree->root = child;
            if(child){
                zrbn_set_black(child);
            }
        }
    }
    zalloc_push(tree->alloc, (zvalue_t*)&old);
    if(color){
        zrbtree_rebalance_erase(tree, child, parent);
    }
    return ZEOK;
}

#endif

zinline zerr_t zrbtree_locked_insert(zbtree_t *tree, zbtnode_t *node){
    zerr_t ret = ZEOK;
    zspin_lock(&tree->spin);
    ret = zrbtree_insert(tree, node);
    zspin_unlock(&tree->spin);
    return ret;
}

zinline zerr_t zrbtree_locked_erase(zbtree_t *tree, int32_t key){
    zerr_t ret = ZEOK;
    zspin_lock(&tree->spin);
    ret = zrbtree_erase(tree, key);
    zspin_unlock(&tree->spin);
    return ret;
}

zinline zerr_t zrbtree_locked_find(zbtree_t *tree, int32_t key, zbtnode_t **node){
    zerr_t ret = ZEOK;
    zspin_lock(&tree->spin);
    ret = zrbtree_find(tree, key, node);
    zspin_unlock(&tree->spin);
    return ret;
}

ZC_END

#endif
