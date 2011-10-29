#ifndef AVL_TREE_H
#define AVL_TREE_H

struct avl_tree_node;

struct avl_tree_node* avl_tree_create(void);
void avl_tree_destroy(struct avl_tree_node* root);
void avl_tree_insert(struct avl_tree_node* root, const char* key, int value);
int* avl_tree_find(struct avl_tree_node* root, const char* key);
void avl_tree_for_each(struct avl_tree_node* root, void (*f)(const char* key, int value));
void avl_tree_increase(struct avl_tree_node* root, const char* key);

#endif

