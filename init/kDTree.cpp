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

// Merge Sort ascending
// input: list, start, end, dimenstion compare
// output: none
void mergeSort(vector<vector<int>> &listPoints, 
               int startIdx, 
               int endIdx, 
               const int &dimension) {
    if (endIdx - startIdx < 1) 
        return;

    int len = endIdx - startIdx + 1;
    mergeSort(listPoints, startIdx, startIdx + (len / 2) - 1, dimension);
    mergeSort(listPoints, startIdx + (len / 2), endIdx, dimension);
    vector<vector<int>> tempVector;
    int pointer1 = startIdx, pointer2 = startIdx + (len / 2), end1 = pointer2, end2 = endIdx + 1;
    // sort in sub-list
    while (pointer1 < end1 && pointer2 < end2) {
        if (listPoints[pointer1][dimension] < listPoints[pointer2][dimension]) {
            tempVector.push_back(listPoints[pointer1]);
            pointer1++;
        } else {
            tempVector.push_back(listPoints[pointer2]);
            pointer2++;
        }
    }
    while (pointer1 < end1) {
        tempVector.push_back(listPoints[pointer1]);
        pointer1++;
    }
    while (pointer2 < end2) {
        tempVector.push_back(listPoints[pointer2]);
        pointer2++;
    }
    // copy to main list
    for (int idx = 0; idx < len; ++idx) {
        listPoints[startIdx + idx] = tempVector[idx];
    }
}

kDTreeNode* buildKDTree(vector<vector<int>> &pointList, 
                        int dimension, 
                        const int &k) {
    int len = pointList.size(), middle = (len - 1) / 2;
    if (len < 1)
        return nullptr;
    mergeSort(pointList, 0, len - 1, dimension);
    kDTreeNode *root = new kDTreeNode(pointList[middle]);
    vector<vector<int>> leftList(pointList.begin(), pointList.begin() + middle);
    vector<vector<int>> rightList(pointList.begin() + middle + 1, pointList.end());
    root->left = buildKDTree(leftList, (dimension + 1) % k, k);
    root->right = buildKDTree(rightList, (dimension + 1) % k, k);
    return root;
}

// Build Tree from a list of points
// input: list of points
// output: new k-D tree
void kDTree::buildTree(const vector<vector<int>> &pointList) {
    if ((int)pointList[0].size() != k)
        return;

    vector<vector<int>> newList(pointList);
    root = buildKDTree(newList, 0, k);
}

// compare data
bool is_equal(const vector<int> &a, const vector<int> &b) {
    if (a.size() != b.size())
        return false;
    for (int i = 0; i < (int)a.size(); ++i)
        if (a[i] != b[i])
            return false;
    return true;
}

// find a node have smallest value in alpha dimension
// input: root of tree, dimension to find
// output: smallest data
vector<int> findSmallest(kDTreeNode *root, const int &alpha) {
    vector<kDTreeNode *> queueNode;
    queueNode.push_back(root);
    vector<int> smallest = root->data;
    while (!queueNode.empty()) {
        kDTreeNode *top = queueNode[0];
        if (top->data[alpha] < smallest[alpha])
            smallest = top->data;

        queueNode.erase(queueNode.begin());
        if (top->left)
            queueNode.push_back(top->left);
        if (top->right)
            queueNode.push_back(top->right);
    }
    return smallest;
}

// Remove a node in tree
void removeNode(const vector<int> &point, kDTreeNode *&root, int dimension, const int &k) {
    if (!root)
        return;
    if (point[dimension] < root->data[dimension]) {
        removeNode(point, root->left, (dimension + 1) % k, k);
    } else if (point[dimension] > root->data[dimension]) {
        removeNode(point, root->right, (dimension + 1) % k, k);
    } else {
        if (is_equal(point, root->data)) {
            // remove node
            if (root->right) {
                // have right tree
                vector<int> smallestRightNode = findSmallest(root->right, dimension);
                root->data = smallestRightNode;
                removeNode(smallestRightNode, root->right, (dimension + 1) % k, k);
            } else if (root->left) {
                // do not have right tree but have left tree
                vector<int> smallestLeftNode = findSmallest(root->left, dimension);
                root->data = smallestLeftNode;
                removeNode(smallestLeftNode, root->left, (dimension + 1) % k, k);
            } else {
                // deletion node is leaf node
                kDTreeNode *delNode = root;
                root = nullptr;
                delete delNode;
                return;
            }

        } else {
            removeNode(point, root->right, (dimension + 1) % k, k);
        }
    }
}

void kDTree::remove(const vector<int> &point) {
    if ((int)point.size() != k)
        return;
    removeNode(point, root, 0, k);
}

// Search in k-D tree
bool searchNode(const vector<int> &point, kDTreeNode *root, int dimension, const int &k) {
    if (!root)
        return false;
    
    if (point[dimension] < root->data[dimension])
        return searchNode(point, root->left, (dimension + 1) % k, k);
    else if (point[dimension] > root->data[dimension])
        return searchNode(point, root->right, (dimension + 1) % k, k);

    if (is_equal(point, root->data))
        return true;
    return searchNode(point, root->right, (dimension + 1) % k, k);
}

bool kDTree::search(const vector<int> &point) {
    return searchNode(point, root, 0, k);
}




// test functions
// int main() {
//     kDTreeNode *root = nullptr;
//     // insertRecursion(root, {5, 6}, 0, 2);
//     // insertRecursion(root, {2, 2}, 0, 2);
//     // insertRecursion(root, {2, 8}, 0, 2);
//     // insertRecursion(root, {3, 5}, 0, 2);
//     // insertRecursion(root, {7, 3}, 0, 2);
//     // insertRecursion(root, {8, 1}, 0, 2);
//     // insertRecursion(root, {9, 2}, 0, 2);
//     // insertRecursion(root, {8, 7}, 0, 2);
//     // insertRecursion(root, {9, 4}, 0, 2);
//     // printPreorder(root);
//     // cout << '\n';
//     // printInorder(root);
//     // cout << '\n';
//     // deleteTree(root);

//     // vector<vector<int>> listPoints = {{5, 6}, {2, 2}, {7, 3}, {2, 8}, {8, 7}, {8, 1}, {9, 4}, {3, 5}};
//     // root = buildKDTree(listPoints, 0, 2);
//     // printPreorder(root);
//     // cout << '\n';
//     // printInorder(root);
//     // cout << '\n';
//     // deleteTree(root);
    
//     return 0;
// }