#include <stdexcept>

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
class DynamicQueue {
private:
    T* data;
    int head;
    int tail;
    int capacity;
    int count;

    void resize();
    void copy(const DynamicQueue<T>& other);
    void free();

public:
    DynamicQueue();
    DynamicQueue(const DynamicQueue<T>& other);
    DynamicQueue& operator=(const DynamicQueue<T>& other);
    ~DynamicQueue();

    bool empty() const;
    void enqueue(const T& elem);
    T dequeue();
    T front() const;
};

template <typename T>
DynamicQueue<T>::DynamicQueue() : head(0), tail(0), capacity(INITIAL_CAPACITY), count(0) {
    data = new T[capacity];
}

template <typename T>
DynamicQueue<T>::DynamicQueue(const DynamicQueue<T>& other) {
    copy(other);
}

template <typename T>
DynamicQueue<T>& DynamicQueue<T>::operator=(const DynamicQueue<T>& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
DynamicQueue<T>::~DynamicQueue() {
    free();
}

template <typename T>
void DynamicQueue<T>::resize() {
    T* oldElements = data;
    data = new T[2 * capacity];
    for (unsigned i = 0; i < count; i++) {
        data[i] = oldElements[(head + i) % capacity];
    }
    capacity *= 2;
    delete[] oldElements;
    head = 0;
    tail = count;
}

template <typename T>
bool DynamicQueue<T>::empty() const {
    return count == 0;
}

template <typename T>
void DynamicQueue<T>::enqueue(const T& elem) {
    if (count == capacity) {
        resize();
    }
    data[tail] = elem;
    tail = (tail + 1) % capacity;
    ++count;
}

template <typename T>
T DynamicQueue<T>::dequeue() {
    if (empty()) {
        throw std::runtime_error("You cannot dequeue from an empty queue!");
    }
    T value = data[head];
    head = (head + 1) % capacity;
    --count;
    return value;
}

template <typename T>
T DynamicQueue<T>::front() const {
    if (empty()) {
        throw std::runtime_error("You cannot get the front element of an empty queue!");
    }
    return data[head];
}

template <typename T>
void DynamicQueue<T>::copy(const DynamicQueue<T>& other) {
    head = other.head;
    tail = other.tail;
    capacity = other.capacity;
    count = other.count;

    data = new T[capacity];
    for (unsigned i = 0; i < capacity; i++) {
        data[i] = other.data[i];
    }
}

template <typename T>
void DynamicQueue<T>::free() {
    delete[] data;
}