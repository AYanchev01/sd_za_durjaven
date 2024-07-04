const int MAX_SIZE = 1024;

template <typename T>
class StaticQueue {
private:
    T data[MAX_SIZE];
    unsigned headIndex, tailIndex, currSize; // Indices and current number of elements

public:
    StaticQueue() : headIndex(0), tailIndex(0), currSize(0) {} // Create an empty queue

    bool full() const { // Check if queue is full
        return currSize == MAX_SIZE;
    }

    bool empty() const { // Check if queue is empty
        return currSize == 0;
    }

    void push(const T& elem) { // Enqueue an element
        if (full()) {
            throw std::runtime_error("The queue is full!");
        }
        data[tailIndex] = elem;
        currSize++;
        tailIndex++;
        tailIndex = tailIndex % MAX_SIZE;
    }

    void pop() { // Dequeue an element
        if (empty()) {
            throw std::runtime_error("Cannot delete element from an empty queue");
        }
        currSize--;
        headIndex++;
        headIndex = headIndex % MAX_SIZE;
    }

    T head() const { // Access the front element
        if (empty()) {
            throw std::runtime_error("Cannot get element from an empty queue");
        }
        return data[headIndex];
    }
};
