#include <stdio.h>
#include <stdlib.h>

// cay AVL node
typedef struct Node {
    int key;
    int height;
    struct Node* left;
    struct Node* right;
} Node;

// chieu cao
int chieu_cao(Node* n) {
    return (n == NULL) ? 0 : n->height;
}

// gia tri lon hon
int lon_hon(int a, int b) {
    return (a > b) ? a : b;
}

// tao node noi
Node* tao_node(int key) {
    Node* node = (Node*)malloc(sizeof(Node));
    node->key = key;
    node->height = 1; // set chieu cao moi la 1
    node->left = NULL;
    node->right = NULL;
    return node;
}

// xoay phai
Node* xoay_phai(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;

    // xoay
    x->right = y;
    y->left = T2;

    y->height = lon_hon(chieu_cao(y->left), chieu_cao(y->right)) + 1;
    x->height = lon_hon(chieu_cao(x->left), chieu_cao(x->right)) + 1;

    return x; 
}

// xoay trai
Node* xoay_trai(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;

    // Txoay
    y->left = x;
    x->right = T2;

    x->height = lon_hon(chieu_cao(x->left), chieu_cao(x->right)) + 1;
    y->height = lon_hon(chieu_cao(y->left), chieu_cao(y->right)) + 1;

    return y; 
}

// can bang
int he_so_can_bang(Node* n) {
    return (n == NULL) ? 0 : chieu_cao(n->left) - chieu_cao(n->right);
}

// chen phan tu
Node* chen(Node* node, int key) {
    if (node == NULL)
        return tao_node(key);

    if (key < node->key)
        node->left = chen(node->left, key);
    else if (key > node->key)
        node->right = chen(node->right, key);
    else
        return node; 

    node->height = 1 + lon_hon(chieu_cao(node->left), chieu_cao(node->right));

    // can bang
    int balance = he_so_can_bang(node);

    // neu khong can bang thi xoay
    // xoay phai don
    if (balance > 1 && key < node->left->key)
        return xoay_phai(node);

    // xoay trai don
    if (balance < -1 && key > node->right->key)
        return xoay_trai(node);

    // tria phai
    if (balance > 1 && key > node->left->key) {
        node->left = xoay_trai(node->left);
        return xoay_phai(node);
    }

    // phai trai
    if (balance < -1 && key < node->right->key) {
        node->right = xoay_phai(node->right);
        return xoay_trai(node);
    }

    return node;
}

// duyet cay thu tu giua
void duyet_cay_inorder(Node* root) {
    if (root != NULL) {
        duyet_cay_inorder(root->left);
        printf("%d ", root->key);
        duyet_cay_inorder(root->right);
    }
}

// thu tu truoc
void duyet_cay_preorder(Node* root) {
    if (root != NULL) {
        printf("%d ", root->key);
        duyet_cay_preorder(root->left);
        duyet_cay_preorder(root->right);
    }
}

// thu tu sau
void duyet_cay_postorder(Node* root) {
    if (root != NULL) {
        duyet_cay_postorder(root->left);
        duyet_cay_postorder(root->right);
        printf("%d ", root->key);
    }
}

int main() {
    Node* root = NULL;
    int arr[] = {10, 20, 30, 40, 50, 25};
    int n = sizeof(arr) / sizeof(arr[0]);

    printf("Quá trình chèn và duyệt cây AVL:\n");
    for (int i = 0; i < n; i++) {
        root = chen(root, arr[i]);
        printf("Sau khi chèn %d: ", arr[i]);
        duyet_cay_inorder(root);
        printf("\n");
    }

    printf("\nDuyệt cây theo thứ tự giữa : ");
    duyet_cay_inorder(root);

    printf("\nDuyệt cây theo thứ tự trước : ");
    duyet_cay_preorder(root);

    printf("\nDuyệt cây theo thứ tự sau : ");
    duyet_cay_postorder(root);

    return 0;
}
