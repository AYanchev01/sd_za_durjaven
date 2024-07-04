#include <iostream>
#include <vector>
#include <algorithm>

template <typename T>
class Tree {
private:
    T data;
    std::vector<Tree<T>*> children;

public:
    Tree(const T& data) : data(data)
    {}

    ~Tree() {
        for (Tree<T>* subtree : children) {
            delete subtree;
        }
    }

    void addSubtree(Tree<T>* tree) {
        children.push_back(tree);
    }

    const T& root() const {
        return data;
    }

    T& root() {
        return data;
    }

    std::vector<Tree<T>*> const& subtrees() const {
        return children;
    }

    unsigned depth() const {
        unsigned maxDepth = 0;
        for (Tree<T>* subtree : subtrees()) {
            maxDepth = std::max(maxDepth, subtree->depth());
        }
        return 1 + maxDepth;
    }

    unsigned breadth() const {
        unsigned maxBreadth = 0;
        unsigned nChildren = subtrees().size();
        for (Tree<T>* subtree : subtrees()) {
            maxBreadth = std::max(maxBreadth, subtree->breadth());
        }
        return std::max(nChildren, maxBreadth);
    }
};