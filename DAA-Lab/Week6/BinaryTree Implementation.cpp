#include <iostream>
using namespace std;

struct Node {
    int data;
    Node *left, *right;
    Node(int data){
        this->data = data;
        this->left = NULL;
        this->right = NULL;
    }
};

void inorder(Node *root) {
    if (root == NULL) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}
void preorder(Node *root) {
    if (root == NULL) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}
void postorder(Node *root) {
    if (root == NULL) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}
int height(Node *root){
    if(root==NULL){
        return -1; // change to -1 for empty tree
    }
    else{
        return max(height(root->left),height(root->right))+1;
    }
}

int diameter(Node *root){
    int d ;
    if(root==NULL){
        return 0;
    }
    d = height(root->left)+height(root->right)+1;
    d = max(d,max(diameter(root->left),diameter(root->right)));
    return d;
}

int countNodes(Node *root) {
    if (root == NULL) {
        return 0;
    }
    return 1 + countNodes(root->left) + countNodes(root->right);
}

int main() {
    Node *root = new Node(1);
    root->left = new Node(2);
    root->right = new Node(3);
    root->left->left = new Node(4);
    root->left->right = new Node(5);

    cout << "Inorder traversal: ";
    inorder(root);
    cout << endl;

    cout << "Postorder traversal: ";
    postorder(root);
    cout << endl;
    
    cout << "Preorder traversal: ";
    preorder(root);
    cout << endl;
    
    cout << "Height of tree: " << height(root) << endl;
    cout << "Diameter of tree: " << diameter(root) << endl;
    cout << "Number of nodes in tree: " << countNodes(root) << endl;
    
    return 0;
}

