#include <iostream>

const unsigned INITIAL_CAPACITY = 16;

template <typename T>
class DynamicStack {
private:
    T* data;
    int topIndex;                               // Индекс на последния елемент в стека
    int capacity;                               // Капацитет на стека

    bool full() const;                          // Проверка дали стек е пълен
    void resize();                              // Разширяване на стек
    void copy(const DynamicStack<T>& other);    // Копиране на стек
    void free();                                // Изтриване на паметта

public:
    DynamicStack();
    DynamicStack(const DynamicStack<T>& other);
    DynamicStack& operator=(const DynamicStack<T>& other);
    ~DynamicStack();

    bool empty() const;
    void push(const T& elem);
    void pop();
    T top() const;
};

// Голяма четворка
template <typename T>
DynamicStack<T>::DynamicStack() : topIndex(-1), capacity(INITIAL_CAPACITY) {
    data = new T[capacity];
}

template <typename T>
DynamicStack<T>::DynamicStack(const DynamicStack<T>& other) {
    copy(other);
}

template <typename T>
DynamicStack<T>& DynamicStack<T>::operator=(const DynamicStack<T>& other) {
    if (this != &other) {
        free();
        copy(other);
    }
    return *this;
}

template <typename T>
DynamicStack<T>::~DynamicStack() {
    free();
}

// Проверка дали стекът е празен - O(1)
template <typename T>
bool DynamicStack<T>::empty() const {
	return topIndex == -1;
}

// Изтриване на елемента на върха на стека - O(1)
template <typename T>
void DynamicStack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("You can not delete the top element of an empty stack!");
    }

    topIndex--;
}

// Извличане на върха на стека - O(1)
template <typename T>
T DynamicStack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return data[topIndex];
}

// Добавяне на елемент на върха на стека
// O(1) или O(n)
template <typename T>
void DynamicStack<T>::push(const T& elem) {
    if (full()) {
        resize();
    }
    data[++topIndex] = elem;
}

// Помощни методи
// Проверка дали стекът е пълен - O(1)
template <typename T>
bool DynamicStack<T>::full() const {
    return topIndex == capacity - 1;
}

// Чисто копиране на стек - O(n)
template <typename T>
void DynamicStack<T>::copy(const DynamicStack<T>& other) {
    topIndex = other.topIndex;
    capacity = other.capacity;

    data = new T[capacity];
    for (unsigned i = 0; i < capacity; i++) {
        data[i] = stackElements[i];
    }
}

// Преоразмеряване - O(n)
template <typename T>
void DynamicStack<T>::resize() {
    T* oldStackPtr = data;
    data = new T[2 * capacity];
    for (unsigned i = 0; i < capacity; i++) {
        data[i] = oldStackPtr[i];
    }
    capacity *= 2;        // Удвояване на капацитета
    delete[] oldStackPtr; // Изтриване на старата памет
}

// Изтриване на динамично заделената памет за елементите на стека - O(1)
template <typename T>
void DynamicStack<T>::free() {
    delete[] data;
}