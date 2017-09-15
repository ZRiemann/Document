#ifndef _Z_CONT_RB_TREE_H_
#define _Z_CONT_RB_TREE_H_
/**
 * @file zit/container/base/tree_rb.h
 * @brief Implement a bed-black tree
 *
 * - balanced binary search tree (logarithmic time)
 *                   {parent = NULL}(node)
 *                       |(adges)
 *                       |(link to parent)
 *                    {root}(node)          (ancestor)(size=4, height=2,depth=0)
 *                    /    \
 *                   /      \(link to child)
 *                  /        \
 *            {left node}  {right node}      (siblings)(left size=2,height=2,length,depth=1)
 *                /
 *               /
 *           {leaf}                          (descendant)
 *
 *   -# find minimum item: minimum(node){while(node){node = node->left;} return node;}
 *   -# find maximum item: maximum(node){while(node){node = node->right;} return node;}
 *   -# insert item:
 *      insert(node root, node new){
 *         node refer = root;
 *         while(refer){
 *           if(refer > new){refer->left ? refer=refer->left : (refer->left = new, refer = NULL);}
 *           else if(refer < new){refer->right ? refer=refer->right : (refer->rignt = new, refer=NULL);}
 *           else{refer = NULL;}
 *         }
 *      }
 *   -# erase item:
 *      erase(node root, node dest){
 *        find(root, dest, parent, direct);
 *        if(dest->left == NULL && dest->right == NULL){if(parent){parent->direct == NULL}}
 *        else if(dest->left && dest->right){dest->value = minimum(dest->right)->value;
 *                                           minimum->parent->direct_to_min = NULL;}
 *        else{parent->direct = dest->left ? dest->left : dest->right;}
 *      }
 *
 * - VAL-tree(Adelson-Velskii-Landis tree)
 *   definition: ((tree every node) && depth(node->left) - depth(node->right) <= 1)
 *
 *   -# insert item:
 *      insert(node root, node new){
 *        find_rotation(root, new, parent, direct-edge, rotation);
 *        // if outside then single-rotation
 *        // else inside then double-rotation
 *      }
 *
 * - RB-tree
 *   - definition:
 *     -# node = [red|black];
 *     -# root = black;
 *     -# if(node == red){node->child = black;}; new node parent must be black;
 *     -# black node numbers on node* all path to NULL is same; new node must be red;
 *   - A sample RB-tree (see NULL is black node)
 *      (B30)-->(B70)-->(B85)-->(R90)
 *       \         \        \-->(R80)
 *        \         \-->(R60)-->(B65)(leaf is black, due to rotation)
 *         \                \-->(B50)-->(R55)
 *          |                       \-->(R40)
 *          \-->(B15)-->(B20)
 *                  \-->(B10)
 *                          \-->(R05)
 */

#include <zit/base/type.h>
#include <zit/base/atomic.h>
#include <zit/container/base/alloc.h>

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
#define zrbn_key(node) (*(int32_t*)node->data)
#define zrbn_great(refer, node) (*(int32_t*)refer->data > *(int32_t*)node->data)
#define zrbn_little(refer, node) (*(int32_t*)refer->data < *(int32_t*)node->data)

typedef struct zbinary_tree_s{
    zbtnode_t *root;
    zalloc_t *alloc;
}zbtree_t;

ZAPI zerr_t zrbtree_create(zbtree_t **tree, int32_t node_size, int32_t capacity);
ZAPI zerr_t zrbtree_destroy(zbtree_t *tree);
ZAPI zerr_t zrbtree_foreach(zbtree_t *tree, int order, zoperate do_each, zvalue_t hint);
ZAPI void zrbtree_print(zbtree_t *tree);

/*
 * inline implements
 */
#include <zit/base/trace.h>

zinline zerr_t zrbtree_get_node(zbtree_t *tree, zbtnode_t **node){
    return zalloc_pop(tree->alloc, (zvalue_t*)node);
}

/**
 * @brief single rotate for outside insert
 *
 *            (18) parent                 (14)
 *            /  \        right-rotate     /  \
 *    child(14)  (20)   -------------> (12)  (18)
 *         /  \                        /     /  \
 *      (12)  (16)                   *11*  (16) (20)
 *      /
 *   *11*
 *
 *          (18) parent                        (25)
 *          /  \           left-rotate         /  \
 *       (11)  (25) child  ----------->     (18)  (30)
 *             /  \                         /  \     \
 *          (20)  (30)                   (11)  (20)  *27*
 *                   \
 *                   *27*
 */
zinline void single_rotate(zbtnode_t *grandpa, zbtnode_t *parent, zbtnode_t *child){
    if(child == parent->left){
        parent->left = child->right;
        child->right = parent;
    }else{
        parent->right = child->left;
        child->left = parent;
    }
    parent->parent = child;
    child->parent = grandpa;
    if(!grandpa){
        return;
    }
    if(parent == grandpa->left){
        grandpa->left = child;
    }else{
        grandpa->right = child;
    }
}

/**
 * @biref double rotate for inside insert
 *
 *           (18) grandpa                                      (16)
 *           /  \         child-parent left rotate             /  \
 *  parent(14)  (20)      --------------------------->      (14)  (18)
 *        /  \            child-grandpa right rotate        /  \     \
 *     (12)  (16) child                                  (12)  *15*  (20)
 *           /
 *        *15*
 *
 *          (18) grandpa                                          (35)
 *          /  \            child-parent right rotate             /  \
 *       (14)  (30) parent ---------------------------->       (18)  (30)
 *             /  \         child-grandpa left rotate          /     /  \
 *     child(35)  (40)                                      (14)  *38*  (40)
 *             \
 *             *38*
 */
zinline void double_rotate(zbtnode_t *ggrandpa, zbtnode_t *grandpa, zbtnode_t *parent, zbtnode_t *child){
    if(child == parent->left){
        parent->left = child->right;
        grandpa->right = child->left;

        child->left = grandpa;
        child->right = parent;
    }else{
        parent->right = child->left;
        grandpa->left = child->right;

        child->left = parent;
        child->right = grandpa;
    }
    parent->parent = child;
    grandpa->parent = child;
    child->parent = ggrandpa;
    if(!ggrandpa){
        child->parent = NULL;
        return;
    }
    if(grandpa == ggrandpa->left){
        ggrandpa->left = child;
    }else{
        ggrandpa->right = child;
    }
}

zinline int zrbtree_sibling_color(zbtnode_t *parent, zbtnode_t *child){
    int isblack;
    if(child == parent->left){
        isblack = parent->right ? zrbn_is_black(parent->right) : 1;
    }else{
        isblack = parent->left ? zrbn_is_black(parent->left) : 1;
    }
    return isblack;
}

/**
 * @beief check is outside insert
 * @return 0 inside
 * @return 1 outside
 */
#define zrbtree_is_outside(grandpa, parent, child) (grandpa->left == parent ? (parent->left == child ? 1 : 0) \
                                                    : (parent->right == child ? 1 : 0))

zinline void zrbtree_rebalance(zbtree_t *tree, zbtnode_t *node){
    int is_outside  = 0;
    int is_sibling_black = 0;
    zbtnode_t *child; //= node->parent;
    zbtnode_t *parent; // = child->parent;
    zbtnode_t *grandpa; // = parent->parent;
    zbtnode_t *ggrandpa; // = grandpa->parent;
    child = node;
    parent = child->parent;
    grandpa = parent->parent;
    if(!grandpa){
        return;
    }

    ggrandpa = grandpa->parent;
    if(!ggrandpa && grandpa->left && grandpa->right){
        return;
    }
    ZDBG("\nBefore rebalance:");
    zrbtree_print(tree);

    is_outside = zrbtree_is_outside(grandpa, parent, child);
    is_sibling_black = zrbtree_sibling_color(grandpa, parent);

    if(is_sibling_black && is_outside){
        /* 3.1
         * 3.1.1 ParentSibling is black or NULL
         * 3.1.2 outside insert
         */
        single_rotate(ggrandpa, grandpa, parent);
        zrbn_chg_color(parent);
        zrbn_chg_color(grandpa);
        if(!ggrandpa){
            tree->root = parent;
            zrbn_set_black(parent);
        }
        ZDBG("\nAfter rebalance:");
        zrbtree_print(tree);
        return;
    }
    if(is_sibling_black && !is_outside){
        /* 3.2
         * 3.2.1 ParentSibling is black or NULL
         * 3.2.2 inside insert
         */
        double_rotate(ggrandpa, grandpa, parent, child);
        zrbn_chg_color(child);
        zrbn_chg_color(grandpa);
        ZDBG("\nAfter rebalance:");
        zrbtree_print(tree);
        return;
    }
    if(!is_sibling_black && is_outside){
        /* 3.3 top-down procedure
         * 3.3.1 ParentSibling is red
         * 3.3.2 outside insert
         */
        if(ggrandpa && zrbn_is_red(ggrandpa)){
            /* top-down procedure not work*/
            ZERRCX(ZENOT_SUPPORT);
            return;
        }
        single_rotate(ggrandpa, grandpa, parent);
        zrbn_chg_color(child);
        ZDBG("\nAfter rebalance:");
        zrbtree_print(tree);
        return;
    }
    if(!is_sibling_black && !is_outside){
        /* error insert work */
        ZERRCX(ZENOT_SUPPORT);
    }
}

zinline zerr_t zrbtree_insert(zbtree_t *tree, zbtnode_t *node){
    zbtnode_t *refer = tree->root;
    /* 1. Insert node must be red */
    zrbn_set_red(node);
    node->left = node->right = node->parent = NULL;
    /* 2. Normal binary tree insert */
    if(!refer){
        tree->root = node;
        zrbn_set_black(node);
        return ZEOK;
    }
    /* 3.3 top-down procedure*/
    while(refer){
        if(zrbn_is_red(refer->left) && zrbn_is_red(refer->right)){
            if(refer != tree->root){
                zrbn_set_red(refer);
            }
            zrbn_set_black(refer->left);
            zrbn_set_black(refer->right);
            /* rebalance if refer parent is red */
            if(zrbn_is_red(refer->parent)){
                zrbtree_rebalance(tree, refer);
            }
        }
        if(zrbn_great(refer, node)){
            refer->left ? refer = refer->left : (refer->left = node, node->parent = refer, refer = NULL);
        }else if(zrbn_little(refer, node)){
            refer->right ? refer = refer->right : (refer->right = node, node->parent = refer, refer = NULL);
        }else{
            return ZEPARAM_INVALID;
        }
    }
    /* 3. rebalance tree */
    zrbtree_rebalance(tree, node);
    return ZEOK;
}

zinline zerr_t zrbtree_erase(zbtree_t *tree, int32_t key){
    return ZEOK;
}

zinline zerr_t zrbtree_find(zbtree_t *tree, int32_t key, zbtnode_t **node){
    return ZEOK;
}

ZC_END

#endif
