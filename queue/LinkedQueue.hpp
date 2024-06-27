#include <stdexcept>
#include <cassert>

template <typename T>
class LinkedQueue
{
public:
    LinkedQueue()
        : head(nullptr)
        , tail(nullptr)
    {}
    LinkedQueue(const LinkedQueue<T>& rhs);

    LinkedQueue<T>& operator=(const LinkedQueue<T>& rhs);
    ~LinkedQueue();

    void enqueue(const T& data);
    T dequeue();
    const T& first() const;
    bool isEmpty() const;
    bool isFull() const { return false; }

private:
    struct node
    {
        T data;
        node* next;
        node(const T& data, node* n = nullptr)
            : data(data), next(n) {}
    } *head, *tail;

    void clear();
    void copy(const node* start);
};

template <typename T>
LinkedQueue<T>::LinkedQueue(const LinkedQueue& queue)
    : head(nullptr), tail(nullptr)
{
    try {
        copy(queue.head);
    }
    catch (...) {
        clear();
        throw;
    }
}

template <typename T>
LinkedQueue<T>::~LinkedQueue()
{
    clear();
}

template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator=(const LinkedQueue<T>& rhs)
{
    if (this != &rhs) {
        clear();
        copy(rhs.head);
    }
    return *this;
}

template <typename T>
void LinkedQueue<T>::enqueue(const T& elem)
{
    node* n = new node(elem);
    if (isEmpty()) {
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
    node* keep = head;
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
    if (!isEmpty())
        return head->data;
    throw std::underflow_error("Empty queue");
}

template <typename T>
bool LinkedQueue<T>::isEmpty() const
{
    return head == nullptr;
}

template <typename T>
void LinkedQueue<T>::clear()
{
    while (!isEmpty())
        dequeue();
}

template <typename T>
void LinkedQueue<T>::copy(const node* start)
{
    assert(head == nullptr && isEmpty());

    while (start) {
        enqueue(start->data);
        start = start->next;
    }
}
