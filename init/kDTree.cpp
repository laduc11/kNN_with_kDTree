#include "kDTree.hpp"

/* TODO: You can implement methods, functions that support your data structures here.
 * */

// deep copy tree
kDTreeNode* deepCopyTree(kDTreeNode *root) {
    if (!root) 
        return nullptr;
    kDTreeNode *curNode = new kDTreeNode(root->data);
    curNode->left = deepCopyTree(root->left);
    curNode->right = deepCopyTree(root->right);
    return curNode;
}

// max of two numbers
int max(const int &a, const int &b) {
    return (a > b) ? a : b;
}

// assignment operator
const kDTree &kDTree::operator=(const kDTree &other)
{
    clear();        // clear old tree
    // copy a new tree from "other"
    root = deepCopyTree(other.root);
    k = other.k;
    return *this;
}

// copy constructor
kDTree::kDTree(const kDTree &other) {
    root = deepCopyTree(other.root);
    k = other.k;
}

// print inorder
// input: none
// output: inorder traversal and 
//         print node without white space at the end
void printInorder(kDTreeNode *root) {
    if (!root)
        return;
    printInorder(root->left);
    if (root->left && root->right) {
        // have both left child and right child
        cout << " " << *root << " ";
    } else if (root->left) {
        // have left child but do not have right child
        cout << " " << *root;
    } else if (root->right) {
        // have right child but do not have left child
        cout << *root << " ";
    } else {
        // have no child
        cout << *root;
    }
    printInorder(root->right);
}

void kDTree::inorderTraversal() const {
    printInorder(root);
}

// print preorder
// input: none
// output: preorder traversal and 
//         print node without white space at the end
void printPreorder(kDTreeNode *root) {
    if (!root)
        return;
    if (root->left) {
        // have left child
        cout << *root << " ";
    } else {
        // do not have left child
        cout << *root;
    }
    printPreorder(root->left);
    if (root->right) {
        // have right child
        cout << " ";
    }
    printPreorder(root->right);
}


void kDTree::preorderTraversal() const {
    printPreorder(root);
}


// print postorder
// input: none
// output: postorder traversal and 
//         print node without white space at the end
void printPostorder(kDTreeNode *root) {
    if (!root)
        return;
    printPostorder(root->left);
    if (root->left) {
        // have left child
        cout << " ";
    }
    printPostorder(root->right);
    if (root->right) {
        // have right child
        cout << " ";
    }
    cout << *root;
}

void kDTree::postorderTraversal() const {
    printPostorder(root);
}

// get height of tree
// input: none 
// output: height of tree
int heightOfTree(kDTreeNode *root) {
    if (!root)
        return 0;
    return 1 + max(heightOfTree(root->left), heightOfTree(root->right));
}

int kDTree::height() const {
    return heightOfTree(root);
}


// count number of nodes in tree
// input: none
// output: number of nodes
int numberOfNode(kDTreeNode *root) {
    if (!root)
        return 0;
    return 1 + numberOfNode(root->left) + numberOfNode(root->right);
}

int kDTree::nodeCount() const {
    return numberOfNode(root);
}

// count number of leaf nodes in tree
// input: none
// output: number of leafs
int numberOfLeafs(kDTreeNode *root) {
    if (!root)
        return 0;
    if (!root->left && !root->right)
        return 1;
    return numberOfLeafs(root->left) + numberOfLeafs(root->right);
}

int kDTree::leafCount() const {
    return numberOfLeafs(root);
}

// delete the tree
// input: none
// output: empty tree
void deleteTree(kDTreeNode *&root) {
    if (!root)
        return;
    if (!root->left && !root->right) {
        // delete leaf node
        kDTreeNode *delNode = root;
        root = nullptr;
        delete delNode;
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    kDTreeNode *delNode = root;
    root = nullptr;
    delete delNode;
}

void kDTree::clear() {
    deleteTree(root);
}


// insert node to the tree
void insertRecursion(kDTreeNode *&root, 
                     const vector<int> &point, 
                     int dimension, 
                     const int &k) {
    if (!root) {
        root = new kDTreeNode(point);
    } else if (point[dimension] < root->data[dimension]) {
        // insert to left tree
        insertRecursion(root->left, point, (dimension + 1) % k, k);
    } else {
        // insert to right tree
        insertRecursion(root->right, point, (dimension + 1) % k, k);
    }
}

void kDTree::insert(const vector<int> &point) {
    if ((int)point.size() != k)
        return;
    insertRecursion(root, point, 0, k);
}


int main() {
    kDTreeNode *root = nullptr;
    insertRecursion(root, {5, 6}, 0, 2);
    insertRecursion(root, {2, 2}, 0, 2);
    insertRecursion(root, {2, 8}, 0, 2);
    insertRecursion(root, {3, 5}, 0, 2);
    insertRecursion(root, {7, 3}, 0, 2);
    insertRecursion(root, {8, 1}, 0, 2);
    insertRecursion(root, {9, 2}, 0, 2);
    insertRecursion(root, {8, 7}, 0, 2);
    insertRecursion(root, {9, 4}, 0, 2);
    printPreorder(root);
    cout << '\n';
    printInorder(root);
    cout << '\n';
    deleteTree(root);
    return 0;
}