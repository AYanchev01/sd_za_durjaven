#include <iostream>

template <typename T>
class BinaryTree
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
    BinaryTree() : root(nullptr) {};

    BinaryTree(const BinaryTree& tree) : root(copy(tree.root)) {};

    BinaryTree& operator=(const BinaryTree& tree)
    {
        if (&tree != this) {
            free(root);
            root = copy(tree.root);
        }
        return *this;
    }

    ~BinaryTree() { free(root); }

    void insert(const T& key) { insert(root, key); }
    bool find(const T& key) const { return find(root, key); }
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
        return root ? new Node(root->key, copy(root->left), copy(root->right)) : nullptr;
    }

    void insert(Node*& root, const T& key)
    {
        if (!root) {
            root = new Node(key);
        }
        else {
            // In a binary tree, we can insert the key to either left or right
            // Here we use a simple heuristic to insert to left if left is empty, otherwise to right
            if (!root->left) {
                insert(root->left, key);
            }
            else {
                insert(root->right, key);
            }
        }
    }

    bool find(const Node* root, const T& key) const
    {
        if (!root) return false;
        if (root->key == key) return true;
        // Search both subtrees in a general binary tree
        return find(root->left, key) || find(root->right, key);
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
                // Find the minimum node in the right subtree
                Node* minNode = extractMin(root->right);
                minNode->left = root->left;
                minNode->right = root->right;
                root = minNode;
            }
            delete toDel;
        }
        else {
            // Recursively search for the node to remove in both subtrees
            remove(root->left, key);
            remove(root->right, key);
        }
    }

    Node* extractMin(Node*& root)
    {
        if (root->left) {
            return extractMin(root->left);
        }

        Node* minNode = root;
        root = root->right;
        return minNode;
    }
};
