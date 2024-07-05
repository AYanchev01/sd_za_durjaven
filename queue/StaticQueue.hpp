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

    void enqueue(const T& elem) { // Enqueue an element
        if (full()) {
            throw std::runtime_error("The queue is full!");
        }
        data[tailIndex] = elem;
        tailIndex = (tailIndex + 1) % MAX_SIZE;
        currSize++;
    }

    void dequeue() { // Dequeue an element
        if (empty()) {
            throw std::runtime_error("Cannot delete element from an empty queue");
        }
        currSize--;
        headIndex = (headIndex + 1) % MAX_SIZE;
    }

    const T& head() const { // Access the front element
        if (empty()) {
            throw std::runtime_error("Cannot get element from an empty queue");
        }
        return data[headIndex];
    }
};
