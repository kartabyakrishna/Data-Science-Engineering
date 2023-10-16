#include <iostream>
#include <cstdlib>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;
    int height;
};

int getHeight(Node* node) {
    if (node == NULL) {
        return -1;
    }
    return node->height;
}

int getBalanceFactor(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

Node* rightRotate(Node* node) {
    Node* newRoot = node->left;
    node->left = newRoot->right;
    newRoot->right = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    return newRoot;
}

Node* leftRotate(Node* node) { 
    Node* newRoot = node->right;
    node->right = newRoot->left;
    newRoot->left = node;
    node->height = max(getHeight(node->left), getHeight(node->right)) + 1;
    newRoot->height = max(getHeight(newRoot->left), getHeight(newRoot->right)) + 1;
    return newRoot;
}

Node* insert(Node* root, int value) {
    if (root == NULL) {
        root = new Node();
        root->data = value;
        root->left = NULL;
        root->right = NULL;
        root->height = 0;
        return root;
    }
    if (value < root->data) {
        root->left = insert(root->left, value);
    }
    else if (value > root->data) {
        root->right = insert(root->right, value);
    }
    else {
        return root;
    }
    root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
    int balanceFactor = getBalanceFactor(root);
    if (balanceFactor > 1 && value < root->left->data) {
        return rightRotate(root);
    }
    if (balanceFactor < -1 && value > root->right->data) {
        return leftRotate(root);
    }
    if (balanceFactor > 1 && value > root->left->data) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balanceFactor < -1 && value < root->right->data) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inOrderTraversal(Node* root) {
    if (root == NULL) {
        return;
    }
    inOrderTraversal(root->left);
    cout << root->data << " ";
    inOrderTraversal(root->right);
}

int main() {
    Node* root = NULL;
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cout << "Enter element " << i+1 << ": ";
        cin >> x;
        root = insert(root, x);
    }
    cout << "Before inserting 6: ";
    inOrderTraversal(root);
    cout << endl;
    root = insert(root, 6);
    cout << "After inserting 6: ";
    inOrderTraversal(root);
    cout << endl;
    return 0;
}

