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
                     const int &k,
                     const int &label = -1) {
    if (!root) {
        root = new kDTreeNode(point, nullptr, nullptr, label);
    } else if (point[dimension] < root->data[dimension]) {
        // insert to left tree
        insertRecursion(root->left, point, (dimension + 1) % k, k, label);
    } else {
        // insert to right tree
        insertRecursion(root->right, point, (dimension + 1) % k, k, label);
    }
}

void kDTree::insert(const vector<int> &point, const int &label) {
    if ((int)point.size() != k)
        return;
    insertRecursion(root, point, 0, k);
}

// Merge Sort ascending
// input: list, start, end, dimenstion compare
// output: none
void mergeSort(vector<vector<int>> &listPoints, 
               vector<int> &listLabels,
               int startIdx, 
               int endIdx, 
               const int &dimension) {
    if (endIdx - startIdx < 1) 
        return;

    int len = endIdx - startIdx + 1;
    mergeSort(listPoints, listLabels, startIdx, startIdx + (len / 2) - 1, dimension);
    mergeSort(listPoints, listLabels, startIdx + (len / 2), endIdx, dimension);
    vector<vector<int>> tempListPoints;
    vector<int> tempListLabels;
    int pointer1 = startIdx, pointer2 = startIdx + (len / 2), end1 = pointer2, end2 = endIdx + 1;
    // sort in sub-list
    while (pointer1 < end1 && pointer2 < end2) {
        if (listPoints[pointer1][dimension] < listPoints[pointer2][dimension]) {
            tempListPoints.push_back(listPoints[pointer1]);
            tempListLabels.push_back(listLabels[pointer1]);
            pointer1++;
        } else {
            tempListPoints.push_back(listPoints[pointer2]);
            tempListLabels.push_back(listLabels[pointer2]);
            pointer2++;
        }
    }
    while (pointer1 < end1) {
        tempListPoints.push_back(listPoints[pointer1]);
        tempListLabels.push_back(listLabels[pointer1]);
        pointer1++;
    }
    while (pointer2 < end2) {
        tempListPoints.push_back(listPoints[pointer2]);
        tempListLabels.push_back(listLabels[pointer2]);
        pointer2++;
    }
    // copy to main list
    for (int idx = 0; idx < len; ++idx) {
        listPoints[startIdx + idx] = tempListPoints[idx];
        listLabels[startIdx + idx] = tempListLabels[idx];
    }
}

kDTreeNode* buildKDTree(vector<vector<int>> &pointList, 
                        vector<int> labelList,
                        int dimension, 
                        const int &k) {
    int len = pointList.size(), middle = (len - 1) / 2;
    if (len < 1)
        return nullptr;
    mergeSort(pointList, labelList, 0, len - 1, dimension);
    kDTreeNode *root = new kDTreeNode(pointList[middle], nullptr, nullptr, labelList[middle]);
    // split the list of points
    vector<vector<int>> leftList(pointList.begin(), pointList.begin() + middle);
    vector<vector<int>> rightList(pointList.begin() + middle + 1, pointList.end());
    // split the list of labels
    vector<int> leftLabel(labelList.begin(), labelList.begin() + middle);
    vector<int> rightLabel(labelList.begin() + middle + 1, labelList.end());
    // build left tree and right tree
    root->left = buildKDTree(leftList, leftLabel, (dimension + 1) % k, k);
    root->right = buildKDTree(rightList, rightLabel, (dimension + 1) % k, k);
    return root;
}

// Build Tree from a list of points
// input: list of points
// output: new k-D tree
void kDTree::buildTree(const vector<vector<int>> &pointList, vector<int> labelList) {
    if ((int)pointList[0].size() != k)
        return;

    // default list of labels with -1
    if (labelList[0] == -1)
        labelList = vector<int>(pointList.size(), -1);
    vector<vector<int>> newList(pointList);
    if (root)
        clear();
    root = buildKDTree(newList, labelList, 0, k);
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

// Find nearest neighbour
double calDistance(const vector<int> &a, const vector<int> &b) {
    long long sum = 0, size = a.size();
    for (int idx = 0; idx < size; ++idx) {
        sum += (a[idx] - b[idx]) * (a[idx] - b[idx]);
    }
    return sqrt(sum);
}

kDTreeNode* findNearest(const vector<int> &target,
                        kDTreeNode *root, 
                        int dimension, 
                        const int &k) {
    if (!root)
        return nullptr;
    
    if (target[dimension] < root->data[dimension]){
        if (root->left) {
            // find the nearest in left tree
            kDTreeNode *nearest = findNearest(target, root->left, (dimension + 1) % k, k);
            double distanceFromBest = calDistance(nearest->data, target);
            double distanceFromRoot = calDistance(nearest->data, target);
            if (distanceFromRoot < distanceFromBest)
                return root;
            
            if ((double)(root->data[dimension] - target[dimension]) < distanceFromBest) {
                if (root->right) {
                    kDTreeNode *otherNearest = findNearest(target, root->right, (dimension + 1) % k, k);
                    if (calDistance(otherNearest->data, target) < distanceFromBest)
                        return otherNearest;
                }
            }
            return nearest;
        }
    } else if (root->right) {
        // special case
        if (target[dimension] == root->data[dimension] && is_equal(target, root->data))
            return root;
        // find the nearest in right tree
        kDTreeNode *nearest = findNearest(target, root->right, (dimension + 1) % k, k);
            double distanceFromBest = calDistance(nearest->data, target);
            double distanceFromRoot = calDistance(nearest->data, target);
            if (distanceFromRoot < distanceFromBest)
                return root;
            
            if ((double)(root->data[dimension] - target[dimension]) < distanceFromBest) {
                if (root->left) {
                    kDTreeNode *otherNearest = findNearest(target, root->left, (dimension + 1) % k, k);
                    if (calDistance(otherNearest->data, target) < distanceFromBest)
                        return otherNearest;
                }
            }
            return nearest;
    }
    return root;
}

// find the nearest neighbour
// input: taget
// output: all the nearest
void kDTree::nearestNeighbour(const vector<int> &target, kDTreeNode *&best) {
    if (!root)
        return;
    best = findNearest(target, root, 0, k);
}

// find k nearest neighbours
struct nodeInMaxHeap {
    kDTreeNode* data;
    double distance;
    int ID;
    nodeInMaxHeap(kDTreeNode *point, 
                  const double &distance, 
                  const int &ID) : data(point), 
                                   distance(distance), 
                                   ID(ID) {}
};

struct maxHeap{
    vector<nodeInMaxHeap> listPoints;
    int k, count;

    maxHeap(const int k) : k(k), count(0), listPoints(vector<nodeInMaxHeap>()) {}
    void reheapDown(int position) {
        int leftChild = 2 * position + 1, rightChild = leftChild + 1;
        if (rightChild < k && 
            listPoints[rightChild].distance > listPoints[leftChild].distance &&  
            listPoints[rightChild].distance > listPoints[position].distance) {
            // reheap down on right child
            std::swap(listPoints[position], listPoints[rightChild]);
            reheapDown(rightChild);
        } else if (leftChild < k && 
                   listPoints[leftChild].distance > listPoints[position].distance) {
            // reheap down on left child
            std::swap(listPoints[position], listPoints[leftChild]);
            reheapDown(leftChild);
        } else {
            if (rightChild < k) {
                if (listPoints[leftChild].distance == listPoints[rightChild].distance &&
                    listPoints[leftChild].distance == listPoints[position].distance) {
                    // left child == right child == position
                    // => check ID
                    if (listPoints[leftChild].ID > listPoints[rightChild].ID &&
                        listPoints[leftChild].ID > listPoints[position].ID) {
                        std::swap(listPoints[position], listPoints[leftChild]);
                        reheapDown(leftChild);
                    } else if (listPoints[rightChild].ID > listPoints[leftChild].ID &&
                               listPoints[rightChild].ID > listPoints[position].ID) {
                        std::swap(listPoints[position], listPoints[rightChild]);
                        reheapDown(rightChild);
                    }
                } else if (listPoints[leftChild].distance == listPoints[position].distance) {
                    // left child == position
                    if (listPoints[leftChild].ID > listPoints[position].ID) {
                        std::swap(listPoints[position], listPoints[leftChild]);
                        reheapDown(leftChild);
                    }
                } else if (listPoints[rightChild].distance == listPoints[position].distance) {
                    // right child == position
                    if (listPoints[rightChild].ID > listPoints[position].ID) {
                        std::swap(listPoints[position], listPoints[rightChild]);
                        reheapDown(rightChild);
                    }
                }
            } else if (leftChild < k) {
                if (listPoints[leftChild].distance == listPoints[position].distance) {
                    if (listPoints[leftChild].ID > listPoints[position].ID) {
                        std::swap(listPoints[position], listPoints[leftChild]);
                        reheapDown(leftChild);
                    }
                } 
            }
        }
    }
    void buildHeap() {
        for (int position = (k - 1) / 2; position > -1; --position) {
            reheapDown(position);
        }
    }
    void push(const nodeInMaxHeap &node) {
        listPoints.push_back(node);
        count++;
        if ((int)listPoints.size() == k) {
            buildHeap();
        } else if ((int)listPoints.size() > k) {
            if (listPoints[listPoints.size() - 1].distance <  listPoints[0].distance) {
                std::swap(listPoints[listPoints.size() - 1], listPoints[0]);
                reheapDown(0);
            }
            listPoints.pop_back();
        }
    }
    void heapSort() {
        int numberOfElement = listPoints.size();
        for (int idx = numberOfElement - 1; idx > 0; --idx) {
            std::swap(listPoints[0], listPoints[idx]);
            this->k--;
            reheapDown(0);
        }
        this->k = numberOfElement;
    }
};

kDTreeNode* findKNearest(const vector<int> &target,
                  kDTreeNode *root,
                  maxHeap &storage,
                  int dimension,
                  const int &k) {
    if (!root)
        return nullptr;

    double distanceFromRoot = calDistance(root->data, target);

    if (target[dimension] < root->data[dimension]) {
        // move to left tree
        if (root->left) {
            // find the nearest in left tree
            kDTreeNode *nearest = findKNearest(target, root->left, storage, (dimension + 1) % k, k);
            double distanceFromBest = calDistance(nearest->data, target);
            // double distanceFromRoot = calDistance(root->data, target);
            if (distanceFromRoot < distanceFromBest) {
                nearest = root;
                distanceFromBest = distanceFromRoot;
            }
            if ((double)(root->data[dimension] - target[dimension]) < distanceFromBest) {
                if (root->right) {
                    // find on an opposite side
                    kDTreeNode *otherNearest = findKNearest(target, root->right, storage, (dimension + 1) % k, k);
                    if (calDistance(otherNearest->data, target) < distanceFromBest) {
                        storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
                        return otherNearest;
                    }
                        
                }
            }
            storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
            return nearest;
        }
    } else {
        if (root->right) {
            // special case
            if (target[dimension] == root->data[dimension] && is_equal(target, root->data)) {
                storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
                return root;
            }
            // find the nearest in right tree
            kDTreeNode *nearest = findKNearest(target, root->right, storage, (dimension + 1) % k, k);
            double distanceFromBest = calDistance(nearest->data, target);
            // double distanceFromRoot = calDistance(root->data, target);
            if (distanceFromRoot < distanceFromBest) {
                nearest = root;
                distanceFromBest = distanceFromRoot;
            }
            if ((double)(root->data[dimension] - target[dimension]) < distanceFromBest) {
                if (root->left) {
                    // find on an opposite side
                    kDTreeNode *otherNearest = findKNearest(target, root->left, storage, (dimension + 1) % k, k);
                    if (calDistance(otherNearest->data, target) < distanceFromBest) {
                        storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
                        return otherNearest;
                    }
                }
            }
            storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
            return nearest;
        }
    }
    storage.push(nodeInMaxHeap(root, distanceFromRoot, storage.count));
    return root;
}

void kDTree::kNearestNeighbour(const vector<int> &target, int k, vector<kDTreeNode *> &bestList) {
    maxHeap storage(k);
    findKNearest(target, root, storage, 0, this->k);
    int size = storage.listPoints.size();
    if (!bestList.empty()) bestList.clear();
    storage.heapSort();
    for (int idx = 0; idx < size; ++idx) {
        bestList.push_back(storage.listPoints[idx].data);
    }
}

// kNN class
// default constructor
kNN::kNN(int k) : k(k), trainData(kDTree()) {}

// destructor
kNN::~kNN() {}

// load the train dataset
void kNN::fit(Dataset &X_train, Dataset &y_train) {
    int dimensionData = X_train.columnName.size(), numberOfSamples = X_train.data.size();
    trainData = kDTree(dimensionData);
    // convert list to vector
    vector<vector<int>> data(numberOfSamples, vector<int>());   // convert data
    vector<int> labels(numberOfSamples, -1);
    int index = 0;
    for (auto line : X_train.data) {
        data[index++] = vector<int>(line.begin(), line.end());
    }
    index = 0;
    for (auto line : y_train.data) {
        labels[index++] = line.front();
    }
    // build k-D tree for train dataset
    trainData.buildTree(data, labels);
}

// predict the labels base on kNN algorithm
Dataset kNN::predict(Dataset &X_test) {
    Dataset y_pred;
    y_pred.columnName = vector<string>(1, "label");
    for (auto testPoint : X_test.data) {
        vector<kDTreeNode *> bestPoints;
        trainData.kNearestNeighbour(vector<int>(testPoint.begin(), testPoint.end()), k, bestPoints);
        int label[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (int idx = 0; idx < (int)bestPoints.size(); ++idx) {
            label[bestPoints[idx]->label]++;
        }
        // find label for test point
        int labelPredict = 0, maxCount = label[0];
        for (int idx = 1; idx < 10; ++idx) {
            if (label[idx] > maxCount) {
                maxCount = label[idx];
                labelPredict = idx;
            }
        }
        y_pred.data.push_back(list<int>(1, labelPredict));
    }
    return y_pred;
}

// calculate accuracy of result predicted
double kNN::score(const Dataset &y_test, const Dataset &y_pred) {
    double correct = 0.0;
    int size = y_test.data.size();
    list<list<int>> correctLabels = y_test.data, predictLabels = y_pred.data;
    list<list<int>>::iterator curCorrectLabel = correctLabels.begin(), 
                              curPredictLabel = predictLabels.begin(),
                              endCorrectLabel = correctLabels.end();
    for (; curCorrectLabel != endCorrectLabel; ++curCorrectLabel, ++curPredictLabel) {
        if ((*curPredictLabel).front() == (*curCorrectLabel).front())
            correct += 1.0;
    }
    return (double)correct / size;
}

