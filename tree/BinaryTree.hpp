#include <iostream>
#include <algorithm>
#include <stdexcept>

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

    size_t size;

public:
    BinaryTree() : root(nullptr), size(0) {};
    ~BinaryTree() { clear(root); }

    BinaryTree(const BinaryTree& tree) : root(copy(tree.root)), size(tree.size) {};

    BinaryTree(BinaryTree&& tree) : BinaryTree()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    BinaryTree& operator=(const BinaryTree& tree)
    {
        if (&tree != this) {
            clear(root);
            root = copy(tree.root);
            size = tree.size;
        }
        return *this;
    }

    BinaryTree& operator=(BinaryTree&& rhs)
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    void insert(const T& key, const std::string& path = "");
    bool find(const T& key) const { return find(root, key); }
    void remove(const T& key) { remove(root, key); }
    size_t getSize() const { return size; }

    size_t getHeight() const { return (size_t)height(root); }
    bool isBalanced() const { return balanced(root); }

    void printInorder() const { printInorder(root); std::cout << "\n"; }
    void printPreorder() const { printPreorder(root); std::cout << "\n"; }
    void printPostorder() const { printPostorder(root); std::cout << "\n"; }

private:
    void clear(Node* root)
    {
        if (root) {
            clear(root->left);
            clear(root->right);
            delete root;
        }
    }

    Node* copy(Node* root)
    {
        return root ?
            new Node(root->key, copy(root->left), copy(root->right)) :
            root;
    }

    bool find(const Node* root, const T& key) const
    {
        if (!root) return false;
        if (root->key == key) return true;
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
                Node* mR = extractMin(root->right);
                mR->left = root->left;
                mR->right = root->right;
                root = mR;
            }
            --size;
            delete toDel;
        }
        else {
            remove(root->left, key);
            remove(root->right, key);
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

    int height(const Node* root) const
    {
        if (!root) return 0;
        return 1 + std::max(height(root->left), height(root->right));
    }

    bool balanced(const Node* root) const
    {
        if (!root) return true;
        return abs(height(root->left) - height(root->right)) < 2 &&
               balanced(root->left) && balanced(root->right);
    }

    void printInorder(const Node* root) const
    {
        if (root) {
            printInorder(root->left);
            std::cout << root->key << " ";
            printInorder(root->right);
        }
    }

    void printPreorder(const Node* root) const
    {
        if (root) {
            std::cout << root->key << " ";
            printPreorder(root->left);
            printPreorder(root->right);
        }
    }

    void printPostorder(const Node* root) const
    {
        if (root) {
            printPostorder(root->left);
            printPostorder(root->right);
            std::cout << root->key << " ";
        }
    }
    
    void insert(Node*& root, const T& key, const std::string& path)
    {
        if (!root) {
            root = new Node(key);
            ++size;
            return;
        }

        if (path.empty()) {
            throw std::invalid_argument("Path cannot be empty for non-root insertion");
        }

        Node* current = root;
        for (size_t i = 0; i < path.length() - 1; ++i) {
            if (path[i] == 'L') {
                if (!current->left) {
                    current->left = new Node(T());
                }
                current = current->left;
            }
            else if (path[i] == 'R') {
                if (!current->right) {
                    current->right = new Node(T());
                }
                current = current->right;
            }
            else {
                throw std::invalid_argument("Path can only contain 'L' or 'R'");
            }
        }

        if (path.back() == 'L') {
            if (current->left) {
                throw std::invalid_argument("Node already exists at the given path");
            }
            current->left = new Node(key);
        }
        else if (path.back() == 'R') {
            if (current->right) {
                throw std::invalid_argument("Node already exists at the given path");
            }
            current->right = new Node(key);
        }
        else {
            throw std::invalid_argument("Path can only contain 'L' or 'R'");
        }

        ++size;
    }
};
