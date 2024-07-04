#include <iostream>
// This constant can be injected in the template as well (template <typename T, unsigned MAX_SIZE = 1024>)
const unsigned MAX_SIZE = 1024;

template <typename T>
class Stack {
private:
    T data[MAX_SIZE];         // Вътрешно представяне
    int topIndex;             // Индекс на върха на стека

public:
    Stack();                  // Създаване на празен стек

    bool full() const;        // Помощна функция за запълненост
    bool empty() const;       // Проверка дали стек е празен
    void push(const T& elem); // Включване на елемент
    void pop();               // Изключване на елемент
    T top() const;            // Достъп до върха на стека
};

// Конструктор за създаване на празен стек
template <typename T>
Stack<T>::Stack() : topIndex(-1) {}

// Проверка дали стекът е празен - O(1)
template <typename T>
bool Stack<T>::empty() const {
	return topIndex == -1;
}

// Проверка дали стекът е пълен - O(1)
template <typename T>
bool Stack<T>::full() const {
	return topIndex == MAX_SIZE - 1;
}

// Извличане на върха на стека - O(1)
template <typename T>
T Stack<T>::top() const {
    if (empty()) {
        throw std::runtime_error("You can not get the top element of an empty stack!");
    }

    return data[topIndex];
}

// Добавяне на елемент на върха стека - O(1)
template <typename T>
void Stack<T>::push(const T& elem) {
    if (full()) {
        throw std::runtime_error("Stack is full!");
    }
    
    data[++topIndex] = elem;
}

// Изтриване на елемента на върха на стека - O(1)
template <typename T>
void Stack<T>::pop() {
    if (empty()) {
        throw std::runtime_error("You can not delete the top element of an empty stack!");
    }
    topIndex--;
}