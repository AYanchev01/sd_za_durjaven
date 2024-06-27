#include <stdexcept>

template <typename T>
class StaticQueue
{
public:
    StaticQueue(size_t size = 16)
        : data(new T[size+1])
        , head(0)
        , tail(0)
        , size(size+1)
    {}
    StaticQueue(const StaticQueue<T>& rhs);

    StaticQueue<T>& operator=(const StaticQueue<T>& rhs);
    ~StaticQueue() { delete[] data; }

    void enqueue(const T& data);
    T dequeue();
    const T& first() const;
    bool isEmpty() const;
    bool isFull() const;

private:
    T* data;
    size_t head, tail;
    const size_t size;
};

template <typename T>
StaticQueue<T>::StaticQueue(const StaticQueue<T>& rhs)
    : data(new T[rhs.size])
    , head(0)
    , tail(0)
    , size(rhs.size)
{
    for (size_t pos = rhs.head; pos != rhs.tail; pos = (pos + 1) % size)
        enqueue(rhs.data[pos]);
}

template <typename T>
StaticQueue<T>& StaticQueue<T>::operator=(const StaticQueue<T>& rhs)
{
    if (this != &rhs) {
        delete[] data;
        data = new T[rhs.size];
        head = tail = 0;
        size = rhs.size;
        for (size_t pos = rhs.head; pos != rhs.tail; pos = (pos + 1) % size)
            enqueue(rhs.data[pos]);
    }
    return *this;
}

template <typename T>
void StaticQueue<T>::enqueue(const T& elem)
{
    if (!isFull()) {
        data[tail] = elem;
        tail = (tail + 1) % size;
    } else {
        throw std::overflow_error("Queue is full");
    }
}

template <typename T>
T StaticQueue<T>::dequeue()
{
    if (!isEmpty()) {
        const T& res = data[head];
        head = (head + 1) % size;
        return res;
    }
    throw std::underflow_error("Empty queue");
}

template <typename T>
const T& StaticQueue<T>::first() const
{
    if (!isEmpty())
        return data[head];
    throw std::underflow_error("Empty queue");
}

template <typename T>
bool StaticQueue<T>::isEmpty() const
{
    return head == tail;
}

template <typename T>
bool StaticQueue<T>::isFull() const
{
    return (tail + 1) % size == head;
}
