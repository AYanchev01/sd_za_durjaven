#include <iostream>

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
class DynamicStack {
private:
    T* data;
    int topIndex; // Index of the last element in the stack
    int capacity; // Stack capacity

public:
    DynamicStack() : topIndex(-1), capacity(INITIAL_CAPACITY) {
        data = new T[capacity];
    }

    DynamicStack(const DynamicStack<T>& other) {
        copy(other);
    }

    DynamicStack<T>& operator=(const DynamicStack<T>& other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    ~DynamicStack() {
        free();
    }

    bool empty() const { // Check if stack is empty
        return topIndex == -1;
    }

    void push(const T& elem) { // Push an element onto the stack
        if (full()) {
            resize();
        }
        data[++topIndex] = elem;
    }

    void pop() { // Pop an element off the stack
        if (empty()) {
            throw std::runtime_error("You cannot delete the top element of an empty stack!");
        }
        topIndex--;
    }

    const T& top() const { // Access the top element of the stack
        if (empty()) {
            throw std::runtime_error("You cannot get the top element of an empty stack!");
        }
        return data[topIndex];
    }

private:
    bool full() const { // Check if stack is full
        return topIndex == capacity - 1;
    }

    void resize() { // Resize the stack
        T* oldStackPtr = data;
        data = new T[2 * capacity];
        for (unsigned i = 0; i < capacity; i++) {
            data[i] = oldStackPtr[i];
        }
        capacity *= 2; // Double the capacity
        delete[] oldStackPtr; // Delete the old memory
    }

    void copy(const DynamicStack<T>& other) { // Copy the stack
        topIndex = other.topIndex;
        capacity = other.capacity;

        data = new T[capacity];
        for (unsigned i = 0; i < capacity; i++) {
            data[i] = other.data[i];
        }
    }

    void free() { // Delete the memory
        delete[] data;
    }
};
