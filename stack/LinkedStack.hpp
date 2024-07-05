#include <stdexcept>

template <typename T>
class LinkedStack {
private:
    struct Node {
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr)
            : data(data)
            , next(next)
        {}
    } *tos;

public:
    LinkedStack() : tos(nullptr) {}

    LinkedStack(const LinkedStack<T>& other) {
        copy(other);
    }

    LinkedStack<T>& operator=(const LinkedStack<T>& other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    ~LinkedStack() {
        free();
    }

    void push(const T& elem) {
        tos = new Node(elem, tos);
    }

    void pop() {
        Node* toDel = tos;
        tos = tos->next;
        delete toDel;
    }

    const T& top() const {
        if (empty()) {
            throw std::underflow_error("Empty stack");
        }
        return tos->data;
    }

    bool empty() const {
        return tos == nullptr;
    }

private:
    void copy(const LinkedStack<T>& other) {
        if (other.empty()) {
            return;
        }
        tos = new Node(other.tos->data);
        Node* currentOther = other.tos->next;
        Node* currentThis = tos;

        while (currentOther) {
            currentThis->next = new Node(currentOther->data);
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }
    }

    void free() {
        while (!empty()) {
            pop();
        }
    }
};
