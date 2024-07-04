#include <iostream>
#include <algorithm>

template <typename T>
class BST
{
private:
    struct Node
    {
        T key;
        Node* left, * right;

        Node(const T& key, Node* left = nullptr, Node* right = nullptr)
            : key(key)
            , left(left)
            , right(right)
        {}
    } *root;

public:
    BST() : root(nullptr) {};

    BST(const BST& tree) : root(copy(tree.root)) {};

    BST& operator=(const BST& tree)
    {
        if (&tree != this) {
            free(root);
            root = copy(tree.root);
        }
        return *this;
    }

    ~BST() { free(root); }

    bool find(const T& key) const { return find(root, key); }
    void insert(const T& key) { insert(root, key); }
    void remove(const T& key) { remove(root, key); }
private:

    void free(Node* root)
    {
        if (root) {
            free(root->left);
            free(root->right);
            delete root;
        }
    }

    Node* copy(Node* root)
    {
        return root ?
            new Node(root->key, copy(root->left), copy(root->right)) : nullptr;
    }

    bool find(const Node* root, const T& key) const
    {
        if (!root) return false;
        if (root->key == key) return true;
        return key < root->key ? find(root->left, key) : find(root->right, key);
    }

    void insert(Node*& root, const T& key)
    {
        if (!root) {
            root = new Node(key);
        }
        else {
            insert(key < root->key ? root->left : root->right, key);
        }
    }

    void remove(Node*& root, const T& key)
    {
        if (!root) return;

        if (root->key == key) {
            Node* toDel = root;
            if (!root->left) {
                root = root->right;
            }
            else if (!root->right) {
                root = root->left;
            }
            else {
                Node* mR = extractMin(root->right);
                mR->left = root->left;
                mR->right = root->right;
                root = mR;
            }
            delete toDel;
        }
        else {
            remove(key < root->key ? root->left : root->right, key);
        }
    }

    Node* extractMin(Node*& root)
    {
        if (root->left) {
            return extractMin(root->left);
        }

        Node* n = root;
        root = root->right;
        return n;
    }
};