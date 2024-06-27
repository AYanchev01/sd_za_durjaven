#include <iostream>
#include <vector>
#include <stdexcept>
using namespace std;

template <typename T>
class Tree
{
private:
    struct Node
    {
        T data;
        vector<Node*> children;

        Node(const T& data) : data(data) {}
    };

    Node* root;

public:
    Tree(const T& rootData);
    Tree(const Tree<T>& other);
    Tree<T>& operator=(const Tree<T>& other);
    ~Tree();

private:
    void copyFrom(Node*& thisNode, Node* otherNode);
    void free(Node* node);

public:
    void addChild(Node* parent, const T& childData);
    void addChildToNode(const T& parentData, const T& childData);
    Node* find(Node* node, const T& data) const;
    void print(Node* node) const;
    void printTree() const;
    Node* getRoot() const;
};

template <typename T>
Tree<T>::Tree(const T& rootData)
{
    root = new Node(rootData);
}

template <typename T>
Tree<T>::Tree(const Tree<T>& other)
{
    copyFrom(this->root, other.root);
}

template <typename T>
Tree<T>& Tree<T>::operator=(const Tree<T>& other)
{
    if (this != &other)
    {
        free(root);
        copyFrom(this->root, other.root);
    }
    return *this;
}

template <typename T>
Tree<T>::~Tree()
{
    free(root);
}

template <typename T>
void Tree<T>::copyFrom(Node*& thisNode, Node* otherNode)
{
    if (otherNode == nullptr)
        return;

    thisNode = new Node(otherNode->data);
    for (Node* child : otherNode->children)
    {
        Node* newChild = nullptr;
        copyFrom(newChild, child);
        thisNode->children.push_back(newChild);
    }
}

template <typename T>
void Tree<T>::free(Node* node)
{
    if (node == nullptr)
        return;

    for (Node* child : node->children)
    {
        free(child);
    }
    delete node;
}

template <typename T>
void Tree<T>::addChild(Node* parent, const T& childData)
{
    if (parent != nullptr)
    {
        Node* childNode = new Node(childData);
        parent->children.push_back(childNode);
    }
}

template <typename T>
void Tree<T>::addChildToNode(const T& parentData, const T& childData)
{
    Node* parentNode = find(root, parentData);
    if (parentNode != nullptr)
    {
        addChild(parentNode, childData);
    }
    else
    {
        throw std::invalid_argument("Parent node not found");
    }
}

template <typename T>
typename Tree<T>::Node* Tree<T>::find(Node* node, const T& data) const
{
    if (node == nullptr) return nullptr;
    if (node->data == data) return node;

    for (Node* child : node->children)
    {
        Node* found = find(child, data);
        if (found != nullptr) return found;
    }

    return nullptr;
}

template <typename T>
void Tree<T>::print(Node* node) const
{
    if (node == nullptr) return;
    cout << node->data << " ";
    for (Node* child : node->children)
    {
        print(child);
    }
}

template <typename T>
void Tree<T>::printTree() const
{
    print(root);
    cout << endl;
}

template <typename T>
typename Tree<T>::Node* Tree<T>::getRoot() const
{
    return root;
}

// Example usage
int main()
{
    Tree<int> tree(1); // Create a tree with root value 1
    tree.addChild(tree.getRoot(), 2); // Add child with value 2 to the root
    tree.addChild(tree.getRoot(), 3); // Add child with value 3 to the root

    tree.addChildToNode(2, 4); // Add child with value 4 to the node with value 2
    tree.addChildToNode(2, 5); // Add child with value 5 to the node with value 2

    tree.printTree(); // Should print: 1 2 4 5 3

    return 0;
}