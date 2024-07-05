#include <iostream>
// This constant can be injected in the template as well (template <typename T, unsigned MAX_SIZE = 1024>)
const unsigned MAX_SIZE = 1024;

template <typename T>
class Stack {
private:
    T data[MAX_SIZE]; // Internal representation
    int topIndex;     // Index of the top of the stack

public:
    Stack() : topIndex(-1) {} // Create an empty stack

    bool full() const { // Helper function to check if stack is full
        return topIndex == MAX_SIZE - 1;
    }

    bool empty() const { // Check if stack is empty
        return topIndex == -1;
    }

    void push(const T& elem) { // Push an element onto the stack
        if (full()) {
            throw std::runtime_error("Stack is full!");
        }
        data[++topIndex] = elem;
    }

    void pop() { // Pop an element off the stack
        if (empty()) {
            throw std::runtime_error("You can not delete the top element of an empty stack!");
        }
        topIndex--;
    }

    const T& top() const { // Access the top element of the stack
        if (empty()) {
            throw std::runtime_error("You can not get the top element of an empty stack!");
        }
        return data[topIndex];
    }
};
