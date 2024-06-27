#include <stdexcept>
#include <cassert>

template <typename T>
class LinkedStack
{
public:
    LinkedStack();
    LinkedStack(const LinkedStack<T>& stack);
    ~LinkedStack();
    LinkedStack<T>& operator=(const LinkedStack<T>& rhs);

    void push(const T& elem);
    T pop();
    const T& top() const;
    bool isEmpty() const;

private:
    struct Node
    {
        T data;
        Node* next;

        Node(const T& d, Node* n = nullptr)
            : data(d)
            , next(n)
        {}
    } *tos;

    void clear();
    void copy(const Node* top);
};

template <typename T>
LinkedStack<T>::LinkedStack()
    : tos(nullptr)
{}

template <typename T>
LinkedStack<T>::LinkedStack(const LinkedStack<T>& stack)
    : tos(nullptr)
{
    try {
        copy(stack.tos);
    }
    catch (std::bad_alloc&) {
        clear();
        throw;
    }
}

template <typename T>
LinkedStack<T>::~LinkedStack()
{
    clear();
}

template <typename T>
LinkedStack<T>& LinkedStack<T>::operator=(const LinkedStack<T>& rhs)
{
    if (this != &rhs) {
        clear();
        copy(rhs.tos);
    }
    return *this;
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
    if (!isEmpty())
        return tos->data;
    throw std::underflow_error("Empty stack");
}

template <typename T>
bool LinkedStack<T>::isEmpty() const
{
    return tos == nullptr;
}

template <typename T>
void LinkedStack<T>::clear()
{
    while (!isEmpty())
        pop();
}

template <typename T>
void LinkedStack<T>::copy(const Node* top)
{
    assert(tos == nullptr);
    if (top) {
        tos = new Node(top->data);
        top = top->next;

        Node* prev = tos;
        while (top) {
            prev->next = new Node(top->data);
            prev = prev->next;
            top = top->next;
        }
    }
}
