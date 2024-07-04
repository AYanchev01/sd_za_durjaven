#include <stdexcept>
#include <cassert>

template <typename T>
class LinkedStack
{
private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& data, Node* next = nullptr)
            : data(data)
            , next(next)
        {}
    } *tos;

    void copy(const LinkedStack<T>& other);
    void free();

public:
    LinkedStack();
    LinkedStack(const LinkedStack<T>& other);
    LinkedStack<T>& operator=(const LinkedStack<T>& other);
    ~LinkedStack();

    void push(const T& elem);
    T pop();
    const T& top() const;
    bool empty() const;
};

template <typename T>
LinkedStack<T>::LinkedStack() : tos(nullptr)
{}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& other)
    : tos(nullptr)
{
    try {
        copy(other);
    }
    catch (std::bad_alloc&) {
        free();
        throw;
    }
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& other)
{
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    free();
}

template <typename T>
void LinkedStack<T>::push(const T& elem)
{
    tos = new Node(elem, tos);
}

template <typename T>
T LinkedStack<T>::pop()
{
    T res = top();
    Node* keep = tos;
    tos = tos->next;
    delete keep;
    return res;
}

template <typename T>
const T& LinkedStack<T>::top() const
{
    if (empty()) {
        throw std::underflow_error("Empty stack");
    }

    return tos->data;
}

template <typename T>
bool LinkedStack<T>::empty() const
{
    return tos == nullptr;
}

template <typename T>
void LinkedStack<T>::copy(const LinkedStack<T>& other)
{
    assert(tos == nullptr);
    if (other.tos) {
        tos = new Node(other.tos->data);
        Node* currentOther = other.tos->next;
        Node* currentThis = tos;

        while (currentOther) {
            currentThis->next = new Node(currentOther->data);
            currentThis = currentThis->next;
            currentOther = currentOther->next;
        }
    }
}

template <typename T>
void LinkedStack<T>::free()
{
    while (!empty())
        pop();
}
