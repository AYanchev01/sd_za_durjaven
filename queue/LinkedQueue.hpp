#include <stdexcept>
#include <cassert>

template <typename T>
class LinkedQueue
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr)
            : data(data), next(next) {}
    } *head, *tail;

    void copy(const LinkedQueue<T>& other);
    void free();

public:
    LinkedQueue();
    LinkedQueue(const LinkedQueue<T>& other);
    LinkedQueue<T>& operator=(const LinkedQueue<T>& other);
    ~LinkedQueue();

    void enqueue(const T& data);
    T dequeue();
    const T& first() const;
    bool empty() const;
    bool full() const { return false; }
};

template <typename T>
LinkedQueue<T>::LinkedQueue() : head(nullptr), tail(nullptr)
{}

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue<T>& other)
    : head(nullptr), tail(nullptr)
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
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& other)
{
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    free();
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem)
{
    Node* n = new Node(elem);
    if (empty()) {
        head = n;
    }
    else {
        tail->next = n;
    }
    tail = n;
}

template <typename T>
T LinkedQueue<T>::dequeue()
{
    T res = first();
    Node* keep = head;
    head = head->next;
    if (head == nullptr) {
        tail = nullptr;
    }
    delete keep;
    return res;
}

template <typename T>
const T& LinkedQueue<T>::first() const
{
    if (!empty())
        return head->data;
    throw std::underflow_error("Empty queue");
}

template <typename T>
bool LinkedQueue<T>::empty() const
{
    return head == nullptr;
}

template <typename T>
void LinkedQueue<T>::copy(const LinkedQueue<T>& other)
{
    assert(empty());

    Node* current = other.head;
    while (current) {
        enqueue(current->data);
        current = current->next;
    }
}

template <typename T>
void LinkedQueue<T>::free()
{
    while (!empty())
        dequeue();
}
