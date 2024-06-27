#include <stdexcept>

template <typename T>
class DynamicQueue
{
public:
    DynamicQueue(size_t size = 16)
        : data(new T[size])
        , head(0)
        , tail(0)
        , capacity(size)
        , count(0)
    {}
    DynamicQueue(const DynamicQueue<T>& rhs);

    DynamicQueue<T>& operator=(const DynamicQueue<T>& rhs);
    ~DynamicQueue() { delete[] data; }

    void enqueue(const T& data);
    T dequeue();
    const T& first() const;
    bool isEmpty() const;
    bool isFull() const { return false; }

private:
    T* data;
    size_t head, tail;
    size_t capacity;
    size_t count;

    void resize(size_t newCapacity);
};

template <typename T>
DynamicQueue<T>::DynamicQueue(const DynamicQueue<T>& rhs)
    : data(new T[rhs.capacity])
    , head(rhs.head)
    , tail(rhs.tail)
    , capacity(rhs.capacity)
    , count(rhs.count)
{
    std::copy(rhs.data, rhs.data + rhs.capacity, data);
}

template <typename T>
DynamicQueue<T>& DynamicQueue<T>::operator=(const DynamicQueue<T>& rhs)
{
    if (this != &rhs) {
        delete[] data;
        data = new T[rhs.capacity];
        head = rhs.head;
        tail = rhs.tail;
        capacity = rhs.capacity;
        count = rhs.count;
        std::copy(rhs.data, rhs.data + rhs.capacity, data);
    }
    return *this;
}

template <typename T>
void DynamicQueue<T>::enqueue(const T& elem)
{
    if (count == capacity) {
        resize(2 * capacity);
    }
    data[tail] = elem;
    tail = (tail + 1) % capacity;
    ++count;
}

template <typename T>
T DynamicQueue<T>::dequeue()
{
    if (!isEmpty()) {
        const T& res = data[head];
        head = (head + 1) % capacity;
        --count;
        return res;
    }
    throw std::underflow_error("Empty queue");
}

template <typename T>
const T& DynamicQueue<T>::first() const
{
    if (!isEmpty())
        return data[head];
    throw std::underflow_error("Empty queue");
}

template <typename T>
bool DynamicQueue<T>::isEmpty() const
{
    return count == 0;
}

template <typename T>
void DynamicQueue<T>::resize(size_t newCapacity)
{
    T* newData = new T[newCapacity];
    for (size_t i = 0; i < count; ++i) {
        newData[i] = data[(head + i) % capacity];
    }
    delete[] data;
    data = newData;
    head = 0;
    tail = count;
    capacity = newCapacity;
}
