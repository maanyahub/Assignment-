#include <stdio.h>
#include <stdlib.h>

// Red-Black Tree node
struct RBNode {
    int data;
    char color; // 'R' for Red, 'B' for Black
    struct RBNode *left, *right, *parent;
    int size; // Size of subtree rooted with this node
};

struct RBNode *root = NULL;

// Create a new Red-Black Tree node
struct RBNode* newNode(int data) {
    struct RBNode *node = (struct RBNode *)malloc(sizeof(struct RBNode));
    node->data = data;
    node->color = 'R';
    node->left = node->right = node->parent = NULL;
    node->size = 1;
    return node;
}

// Left rotate subtree rooted with x
void leftRotate(struct RBNode **root, struct RBNode *x) {
    struct RBNode *y = x->right;
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->left)
        x->parent->left = y;
    else
        x->parent->right = y;
    y->left = x;
    x->parent = y;
    
    y->size = x->size;
    x->size = (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0) + 1;
}

// Right rotate subtree rooted with x
void rightRotate(struct RBNode **root, struct RBNode *x) {
    struct RBNode *y = x->left;
    x->left = y->right;
    if (y->right != NULL)
        y->right->parent = x;
    y->parent = x->parent;
    if (x->parent == NULL)
        *root = y;
    else if (x == x->parent->right)
        x->parent->right = y;
    else
        x->parent->left = y;
    y->right = x;
    x->parent = y;
    
    y->size = x->size;
    x->size = (x->left ? x->left->size : 0) + (x->right ? x->right->size : 0) + 1;
}

// Fix the Red-Black Tree after insertion
void fixInsertion(struct RBNode **root, struct RBNode *z) {
    struct RBNode *parent = NULL;
    struct RBNode *grandparent = NULL;

    while ((z != *root) && (z->color != 'B') && (z->parent->color == 'R')) {
        parent = z->parent;
        grandparent = z->parent->parent;

        if (parent == grandparent->left) {
            struct RBNode *uncle = grandparent->right;
            if (uncle && uncle->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                z = grandparent;
            } else {
                if (z == parent->right) {
                    leftRotate(root, parent);
                    z = parent;
                    parent = z->parent;
                }
                rightRotate(root, grandparent);
                char temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                z = parent;
            }
        } else {
            struct RBNode *uncle = grandparent->left;
            if (uncle && uncle->color == 'R') {
                grandparent->color = 'R';
                parent->color = 'B';
                uncle->color = 'B';
                z = grandparent;
            } else {
                if (z == parent->left) {
                    rightRotate(root, parent);
                    z = parent;
                    parent = z->parent;
                }
                leftRotate(root, grandparent);
                char temp = parent->color;
                parent->color = grandparent->color;
                grandparent->color = temp;
                z = parent;
            }
        }
    }
    (*root)->color = 'B';
}

// Insert a new node into the Red-Black Tree
void insert(struct RBNode **root, int data) {
    struct RBNode *z = newNode(data);
    struct RBNode *y = NULL;
    struct RBNode *x = *root;

    while (x != NULL) {
        y = x;
        x->size++;
        if (z->data < x->data)
            x = x->left;
        else
            x = x->right;
    }

    z->parent = y;
    if (y == NULL)
        *root = z;
    else if (z->data < y->data)
        y->left = z;
    else
        y->right = z;

    fixInsertion(root, z);
}

// Find the k-th smallest element in the Red-Black Tree
int kthSmallest(struct RBNode *root, int k) {
    int leftSize = root->left ? root->left->size : 0;
    
    if (k == leftSize + 1)
        return root->data;
    else if (k <= leftSize)
        return kthSmallest(root->left, k);
    else
        return kthSmallest(root->right, k - leftSize - 1);
}

// Function to get the k-th largest (use k-th smallest with inverted k)
int kthLargest(struct RBNode *root, int k, int totalSize) {
    return kthSmallest(root, totalSize - k + 1);
}

// Driver program to test the functions
int main() {
    int arr[] = {20, 8, 22, 4, 12, 10, 14};
    int n = sizeof(arr) / sizeof(arr[0]);

    for (int i = 0; i < n; i++)
        insert(&root, arr[i]);

    int k = 3; // 3rd smallest element
    printf("%d-th smallest element is %d\n", k, kthSmallest(root, k));

    printf("%d-th largest element is %d\n", k, kthLargest(root, k, n));

    return 0;
}
