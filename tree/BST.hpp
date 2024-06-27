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

    size_t size;

public:
    BST() : root(nullptr), size(0) {};
    ~BST() { clear(root); }

    BST(const BST& tree) : root(copy(tree.root)), size(tree.size) {};

    BST(BST&& tree) : BST()
    {
        std::swap(root, tree.root);
        std::swap(size, tree.size);
    };

    BST& operator=(const BST& tree)
    {
        if (&tree != this) {
            clear(root);
            root = copy(tree.root);
            size = tree.size;
        }
        return *this;
    }

    BST& operator=(BST&& rhs)
    {
        if (this != &rhs) {
            std::swap(root, rhs.root);
            std::swap(size, rhs.size);
        }
        return *this;
    }

    bool find(const T& key) const { return find(root, key); }
    void insert(const T& key) { insert(root, key); ++size; }
    void remove(const T& key) { remove(root, key); }

    size_t getSize() const { return size; }

    size_t getHeight() const { return (size_t)height(root); }
    bool isBalanced() const { return balanced(root); }
    bool isPerfectlyBalanced() const { return perfectBalanced(root); }

    void printInorder() const { print(root); std::cout << "\n"; }

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
            --size;
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


    bool perfectBalanced(const Node* root) const
    {
        if (!root) return true;
        return labs(weight(root->left) - weight(root->right)) < 2 &&
               perfectBalanced(root->left) && perfectBalanced(root->right);
    }

    long weight(const Node* root) const
    {
        if (!root) return 0;
        return 1 + weight(root->left) + weight(root->right);
    }

    void print(const Node* root) const
    {
        if (root) {
            print(root->left);
            std::cout << root->key << " ";
            print(root->right);
        }
    }
};