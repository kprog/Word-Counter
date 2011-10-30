#include "avl_tree.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#ifndef max
    #define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif

#ifndef min
    #define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

struct avl_tree_node {
    char* key;
    int value;

    int height;
    struct avl_tree_node* left;
    struct avl_tree_node* right;
};

struct avl_tree_node* avl_tree_create()
{
    struct avl_tree_node* root = malloc(sizeof(struct avl_tree_node));
    if(!root) {
        return NULL;
    }

    root->height = 0;
    root->key = NULL;
    root->value = 0;
    root->left = NULL;
    root->right = NULL;
    return root;
}

void avl_tree_destroy(struct avl_tree_node* root)
{
    assert(root);

    if (root->right != NULL) {
        avl_tree_destroy(root->right);
    }

    if (root->left != NULL) {
        avl_tree_destroy(root->left);
    }

    if(root->key) {
        free(root->key);
    }
    free(root);
}

static struct avl_tree_node* single_rotate_right(struct avl_tree_node* root)
{
    struct avl_tree_node* node;

    node = root->right;
    root->right = node->right;
    node->left = root;

    root->height = max(root->left->height, root->right->height) +1;
    node->height = max(node->left->height, node->right->height) +1;
    return node;
}

static struct avl_tree_node* double_rotate_right(struct avl_tree_node* root)
{
    root->right = single_rotate_right(root->right);
    return single_rotate_right(root);

}

static struct avl_tree_node* single_rotate_left(struct avl_tree_node* root)
{
    struct avl_tree_node* node;

    node = root->left;
    root->left = node->right;
    node->right = root;

    root->height = max(root->left->height, root->right->height) +1;
    node->height = max(node->left->height, node->right->height) +1;
    return node;
}

static struct avl_tree_node* double_rotate_left(struct avl_tree_node* root)
{
    root->left = single_rotate_left(root->left);
    return single_rotate_left(root);
}

void avl_tree_insert(struct avl_tree_node* root, const char* key, int value)
{
    assert(root);

    if (!root->key) {
        assert(root->left == NULL);
        assert(root->right == NULL);

        root->key = malloc(strlen(key) + 1);
        strcpy(root->key, key);
        root->value = value;
        root->height = 0;
        return;
    }

    int comparison = strcmp(key, root->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            root->left = avl_tree_create();
        }
        avl_tree_insert(root->left, key, value);
    } else if (comparison > 0) {
        if (root->right == NULL) {
            root->right = avl_tree_create();
        }
        avl_tree_insert(root->right, key, value);
    } else {
        root->value = value;;
    }
}

int* avl_tree_find(struct avl_tree_node* root, const char* key)
{
    assert(root);

    if (!root->key) {
        assert(root->left == NULL);
        assert(root->right == NULL);

        return NULL;
    }

    int comparison = strcmp(key, root->key);
    if (comparison < 0) {
        if (root->left == NULL) {
            return NULL;
        } else {
            return avl_tree_find(root->left, key);
        }
    } else if (comparison > 0) {
        if (root->right == NULL) {
            return NULL;
        } else {
            return avl_tree_find(root->right, key);
        }
    } else {
        return &root->value;
    }
}


void avl_tree_for_each(struct avl_tree_node* root, void (*function)(const char* key, int value))
{
    assert(root);

    if (root->left) {
        avl_tree_for_each(root->left, function);
    }

    function(root->key, root->value);

    if (root->right) {
        avl_tree_for_each(root->right, function);
    }
}

void avl_tree_increase(struct avl_tree_node* root, const char* key)
{
    assert(root);

    int* newvalue = avl_tree_find(root, key);

    if (!newvalue) {
        avl_tree_insert(root, key, 1);
    } else {
        (*newvalue)++;
    }
}

