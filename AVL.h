#ifndef AVL_H
#define AVL_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// structure for treenode
struct Node {
    Node* left;
    Node* right;
    int height;
    string ufId;
    string name;

    Node(string name, string ufId) : name(name), ufId(ufId), left(nullptr), right(nullptr), height(1) {}
};

// class of AVL tree
class AVL {

    //private functions not accessible to public
private:
    Node* root;

    Node* insertHelper(Node* node, const string& name, const string& ufId);
    Node* removeHelper(Node* node, const string& ufId);
    Node* searchHelper(Node* node, const string& ufId);
    void searchByNameHelper(Node* node, const string& name, bool& found);
    void printInorderHelper(Node* node, bool& first);
    void printPreorderHelper(Node* node, bool& first);
    void printPostorderHelper(Node* node, bool& first);
    int calculateHeight(Node* node);
    void inorderTraversal(Node* node, vector<Node*>& nodes);
    void destroyTree(Node* node);

    Node* rotateLeft(Node* node);
    Node* rotateRight(Node* node);
    Node* rotateLeftRight(Node* node);
    Node* rotateRightLeft(Node* node);

public:
    //destructor
    AVL() : root(nullptr) {}
    ~AVL() { destroyTree(root); }

    //height of node
    int height(Node* node) {
        return node ? node->height : 0;
    }

    //gets balance factor of node
    int getBalance(Node* node) {
        return node ? height(node->left) - height(node->right) : 0;
    }

    //public insert function uses helper function (private)
    void insert(string name, string ufId) {
        if (ufId.length() != 8) {
            cout << "unsuccessful" << endl;
            return;
        }
        root = insertHelper(root, name, ufId);
    }

    // public removal function uses private removehelper function
    void remove(const string& ufId) {
        root = removeHelper(root, ufId);
    }

    //searches using ID
    void search(const string& ufId) {
        Node* result = searchHelper(root, ufId);
        if (result) {
            cout << result->name << endl;
        } else {
            cout << "unsuccessful" << endl;
        }
    }
    //searches using name
    void searchByName(const string& name) {
        bool found = false;
        searchByNameHelper(root, name, found);
        if (!found) {
            cout << "unsuccessful" << endl;
        }
    }
    // printing functions with different traversal techniques
    void printInorder() {
        bool first = true;
        printInorderHelper(root, first);
        cout << endl;
    }

    void printPreorder() {
        bool first = true;
        printPreorderHelper(root, first);
        cout << endl;
    }

    void printPostorder() {
        bool first = true;
        printPostorderHelper(root, first);
        cout << endl;
    }

    void printLevelCount() {
        cout << calculateHeight(root) << endl;
    }

    // removes using inOrder traversal for the Nth element
    void removeInorder(int n) {
        vector<Node*> nodes;
        inorderTraversal(root, nodes);

        if (n < 0 || n >= nodes.size()) {
            cout << "unsuccessful" << endl;
            return;
        }

        string ufId = nodes[n]->ufId;
        remove(ufId); // Call the existing remove function
    }

    // for testing purposes
    bool isEmpty() {
        return root == nullptr;
    }

    Node* getRoot() { return root; }

    int size() {
        vector<Node*> nodes;
        inorderTraversal(root, nodes);
        return nodes.size();
    }
};
    // private helper function to searchName
void AVL::searchByNameHelper(Node* node, const string& name, bool& found) {
    if (node == nullptr) {
        return;
    }

    if (node->name == name) {
        cout << node->ufId << endl;
        found = true;
    }

    searchByNameHelper(node->left, name, found);
    searchByNameHelper(node->right, name, found);
}

    // private helper function for search by Id function
Node* AVL::searchHelper(Node* node, const string& ufId) {
    if (node == nullptr || node->ufId == ufId) {
        return node;
    }

    if (ufId < node->ufId) {
        return searchHelper(node->left, ufId);
    } else {
        return searchHelper(node->right, ufId);
    }
}
    // private helper printing functions using different traversal techniques
void AVL::printInorderHelper(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    printInorderHelper(node->left, first);

    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;

    printInorderHelper(node->right, first);
}

void AVL::printPreorderHelper(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;

    printPreorderHelper(node->left, first);
    printPreorderHelper(node->right, first);
}

void AVL::printPostorderHelper(Node* node, bool& first) {
    if (node == nullptr) {
        return;
    }

    printPostorderHelper(node->left, first);
    printPostorderHelper(node->right, first);

    if (!first) {
        cout << ", ";
    }
    cout << node->name;
    first = false;
}

int AVL::calculateHeight(Node* node) {
    if (node == nullptr) {
        return 0;
    }
    return max(calculateHeight(node->left), calculateHeight(node->right)) + 1;
}
    // inorder traversal function used when using the removeInorder N function
void AVL::inorderTraversal(Node* node, vector<Node*>& nodes) {
    if (node == nullptr) {
        return;
    }
    inorderTraversal(node->left, nodes);
    nodes.push_back(node);
    inorderTraversal(node->right, nodes);
}
// destructor
void AVL::destroyTree(Node* node) {
    if (node == nullptr) return;
    destroyTree(node->left);
    destroyTree(node->right);
    delete node;
}

// rotation function defs
Node* AVL::rotateLeft(Node* node) {
    Node* temp = node->right;
    node->right = temp->left;
    temp->left = node;
    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));
    return temp;
}

Node* AVL::rotateRight(Node* node) {
    Node* temp = node->left;
    node->left = temp->right;
    temp->right = node;
    node->height = 1 + max(height(node->left), height(node->right));
    temp->height = 1 + max(height(temp->left), height(temp->right));
    return temp;
}

Node* AVL::rotateLeftRight(Node* node) {
    node->left = rotateLeft(node->left);
    return rotateRight(node);
}

Node* AVL::rotateRightLeft(Node* node) {
    node->right = rotateRight(node->right);
    return rotateLeft(node);
}

Node* AVL::insertHelper(Node* node, const string& name, const string& ufId) {
    if (node == nullptr) { // base case
        cout << "successful" << endl;
        return new Node(name, ufId);
    }

    if (ufId < node->ufId) {
        node->left = insertHelper(node->left, name, ufId);
    } else if (ufId > node->ufId) {
        node->right = insertHelper(node->right, name, ufId);
    } else {
        cout << "unsuccessful" << endl;
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int bal = getBalance(node);

    // balancing of the tree after insertion
    if (bal > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (bal > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bal < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (bal < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

Node* AVL::removeHelper(Node* node, const string& ufId) {
    if (node == nullptr) { // base case
        cout << "unsuccessful" << endl;
        return nullptr;
    }

    if (ufId < node->ufId) {
        node->left = removeHelper(node->left, ufId);
    } else if (ufId > node->ufId) {
        node->right = removeHelper(node->right, ufId);
    } else {
        if (!node->left && !node->right) {
            delete node;
            cout << "successful" << endl;
            return nullptr;
        } else if (!node->left) {
            Node* temp = node->right;
            delete node;
            cout << "successful" << endl;
            return temp;
        } else if (!node->right) {
            Node* temp = node->left;
            delete node;
            cout << "successful" << endl;
            return temp;
        } else {
            Node* temp = node->right;
            while (temp->left != nullptr) {
                temp = temp->left;
            }
            node->ufId = temp->ufId;
            node->name = temp->name;
            node->right = removeHelper(node->right, temp->ufId);
        }
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int bal = getBalance(node);

    //balancing of the tree after removal
    if (bal > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }

    if (bal > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }

    if (bal < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }

    if (bal < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }

    return node;
}

#endif // AVL_H