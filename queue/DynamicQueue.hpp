#include <stdexcept>

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
class DynamicQueue {
private:
    T* data;
    int headIndex;
    int tailIndex;
    int capacity;
    int currSize;

public:
    DynamicQueue() : headIndex(0), tailIndex(0), capacity(INITIAL_CAPACITY), currSize(0) {
        data = new T[capacity];
    }

    DynamicQueue(const DynamicQueue<T>& other) {
        copy(other);
    }

    DynamicQueue& operator=(const DynamicQueue<T>& other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    ~DynamicQueue() {
        free();
    }

    bool empty() const {
        return currSize == 0;
    }

    void enqueue(const T& elem) {
        if (currSize == capacity) {
            resize();
        }
        data[tailIndex] = elem;
        tailIndex = (tailIndex + 1) % capacity;
        ++currSize;
    }

    T dequeue() {
        if (empty()) {
            throw std::runtime_error("You cannot dequeue from an empty queue!");
        }
        T value = data[headIndex];
        headIndex = (headIndex + 1) % capacity;
        --currSize;
        return value;
    }

    T front() const {
        if (empty()) {
            throw std::runtime_error("You cannot get the front element of an empty queue!");
        }
        return data[headIndex];
    }

private:
    void resize() {
        T* oldElements = data;
        data = new T[2 * capacity];
        for (unsigned i = 0; i < currSize; i++) {
            data[i] = oldElements[(headIndex + i) % capacity];
        }
        capacity *= 2;
        delete[] oldElements;
        headIndex = 0;
        tailIndex = currSize;
    }

    void copy(const DynamicQueue<T>& other) {
        headIndex = other.headIndex;
        tailIndex = other.tailIndex;
        capacity = other.capacity;
        currSize = other.currSize;

        data = new T[capacity];
        for (unsigned i = 0; i < capacity; i++) {
            data[i] = other.data[i];
        }
    }

    void free() {
        delete[] data;
    }
};
