#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class BinarySearchTree {
    class TreeNode {
        int value = 0;
        void erase() {
            parent = nullptr;
            leftChild = nullptr;
            rightChild = nullptr;
        }

    public:
        TreeNode* parent = nullptr;
        TreeNode* leftChild = nullptr;
        TreeNode* rightChild = nullptr;

        TreeNode(int v) {
            value = v;
        };

        ~TreeNode() {
            erase();
            value = 0;
        }

        int getValue() {
            return value;
        };

        int& setValue(int i) {
            return value = i;
        };

        void clear() {
            erase();
        }

        friend ostream& operator<<(ostream& os, TreeNode& n);
    };

    TreeNode* clear(TreeNode* n) {
        if(n == nullptr) {
            return nullptr;
        } 
    
        clear(n->leftChild);
        clear(n->rightChild);
        delete n;
        return nullptr;
    };

    

public:
    TreeNode* root = nullptr;

    BinarySearchTree(TreeNode * rt) {
        root = rt;
    };

    BinarySearchTree() {
        root = nullptr;
    }

    ~BinarySearchTree() {
        root = clear(root);
    }

    void inOrderOut(ostream &os,TreeNode* n) {
        if(n == nullptr) {
            return;
        }
        inOrderOut(os, n->leftChild);
        os << n->getValue() << " ";
        inOrderOut(os, n->rightChild);
    }

    void populateTree(vector<int> & arr, int low, int high, TreeNode* current) {
        int mid;
        if(low > high) {
            return;
        }
        if(low == high) {
            mid = low;
        } else {
            mid = (low + high + 1) / 2;
        }
        TreeNode* newNode = new TreeNode(arr[mid]);

        current = populateHelper(current, newNode);

        populateTree(arr, low, mid - 1, current);
        // right
        populateTree(arr, mid + 1, high, current);
    } 

    TreeNode* populateHelper(TreeNode* current, TreeNode* n) {
        if(root == nullptr) {
            current = n;
            root = current;
        } else {
            if(current->getValue() < n->getValue() && current->rightChild == nullptr) {
                current->rightChild = n;
                current->rightChild->parent = current; 
                current = current->rightChild;
            } else if(current->getValue() > n->getValue() && current->leftChild == nullptr) {
                current->leftChild = n;
                current->leftChild->parent = current;
                current = current->leftChild;
            }
        }
        return current;
    }

    TreeNode* find(TreeNode* curr, const int &val) {
        if(curr == nullptr) {
            return nullptr;
        }
        if(curr->getValue() == val)  {
            return curr;
        }

        if(curr->getValue() < val) {
            return find(curr->rightChild, val);
        } else if(curr->getValue() > val) {
            return find(curr->leftChild, val);
        }
        return nullptr;
    }

    bool exists(const int &val) {
        if(find(root, val) == nullptr) {
            return false;
        }
        return true;
    }

    void insert(TreeNode* curr, const int &val) {
        if(curr->getValue() == val) {
            return;
        }
        if(val < curr->getValue()) {
            if(curr->leftChild != nullptr) insert(curr->leftChild, val);
            else {
                curr->leftChild = new TreeNode(val);
                curr->leftChild->parent = curr;
            }
        } else {
            if(curr->rightChild != nullptr) insert(curr->rightChild, val);
            else {
                curr->rightChild = new TreeNode(val);
                curr->rightChild->parent = curr;
            }
        } 
    }

    TreeNode* remove(TreeNode* n) {
        if(root == nullptr || n == nullptr) {
            return nullptr;
        }

        if(n->leftChild == nullptr && n->rightChild == nullptr) {
            if(n->parent == nullptr) {
                root = nullptr;
            } else if(n->parent->leftChild == n) {
                n->parent->leftChild = nullptr;
            } else {
                n->parent->rightChild = nullptr;
            }

            n->clear();
            return n;
        }

        if(n->leftChild == nullptr || n->rightChild == nullptr) {
            TreeNode* child = n->leftChild;
            if(n->leftChild == nullptr) child = n->rightChild;

            child->parent = n->parent;
            if(n->parent == nullptr) {
                root = child;
            } else if(n->parent->leftChild == n) {
                n->parent->leftChild = child;
            } else {
                n->parent->rightChild = child;
            }

            n->clear();
            return n;
        }

        TreeNode* succ = n->rightChild;
        while(succ->leftChild != nullptr) {
            succ = succ->leftChild;
        }
        remove(succ);

        if(n->parent == nullptr) {
            root = succ;
        } else if(n->parent->leftChild == n) {
            n->parent->leftChild = succ;
        } else {
            n->parent->rightChild = succ;
        }

        succ->parent = n->parent;

        succ->leftChild = n->leftChild;
        n->leftChild->parent = succ;
        
        succ->rightChild = n->rightChild;
        if(n->rightChild != nullptr) n->rightChild->parent = succ;
        n->clear();
        return n;
    }

    friend ostream& operator<<(ostream& os, BinarySearchTree& bst);

    friend ostream& operator<<(ostream& os, BinarySearchTree::TreeNode& n);
};

ostream & operator << (ostream &os, BinarySearchTree& bst) {
    bst.inOrderOut(os, bst.root);
    return os;
}

ostream & operator << (ostream &os, BinarySearchTree::TreeNode& n) {
    os << n.getValue();
    return os;
}

int main() {
    vector<int> s = {0,1,2,3,4,5,6};
    BinarySearchTree* tr = new BinarySearchTree();
    cout << "populate tree..." << endl;
    tr->populateTree(s, 0, s.size() - 1, tr->root);
    cout << "current tree" << endl;
    cout << *tr << endl;
    cout << "find and remove 4 value: " << endl;
    tr->remove(tr->find(tr->root, 4));
    cout << "tree with 4 removed: " << endl; 
    cout << *tr << endl;
    cout << "add 7 to the tree: " << endl;
    tr->insert(tr->root, 7);
    cout << "tree with 7 inserted: " << endl;
    cout << *tr << endl;
    delete tr;
} 