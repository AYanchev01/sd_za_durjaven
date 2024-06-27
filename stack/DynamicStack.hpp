#include <stdexcept>
#include <algorithm>

template <typename T>
class DynamicStack
{
public:
    DynamicStack(size_t size = 16)
        : data(new T[size])
        , tos(0)
        , capacity(size)
    {}
    DynamicStack(const DynamicStack<T>& rhs);

    DynamicStack<T>& operator=(const DynamicStack<T>& rhs);
    ~DynamicStack() { delete[] data; }

    void push(const T& elem);
    T pop();
    const T& top() const;
    bool isEmpty() const;

private:
    T* data;
    size_t tos;
    size_t capacity;

    void resize(size_t newCapacity);
};

template <typename T>
DynamicStack<T>::DynamicStack(const DynamicStack<T>& rhs)
    : data(new T[rhs.capacity])
    , tos(rhs.tos)
    , capacity(rhs.capacity)
{
    std::copy(rhs.data, rhs.data + rhs.tos, data);
}

template <typename T>
DynamicStack<T>& DynamicStack<T>::operator=(const DynamicStack<T>& rhs)
{
    if (this != &rhs) {
        T* newData = new T[rhs.capacity];
        std::copy(rhs.data, rhs.data + rhs.tos, newData);
        delete[] data;
        data = newData;
        tos = rhs.tos;
        capacity = rhs.capacity;
    }
    return *this;
}

template <typename T>
void DynamicStack<T>::push(const T& elem)
{
    if (tos == capacity) {
        resize(2 * capacity);
    }
    data[tos++] = elem;
}

template <typename T>
T DynamicStack<T>::pop()
{
    if (!isEmpty()) {
        return data[--tos];
    }
    throw std::underflow_error("Empty stack");
}

template <typename T>
const T& DynamicStack<T>::top() const
{
    if (!isEmpty()) {
        return data[tos - 1];
    }
    throw std::underflow_error("Empty stack");
}

template <typename T>
bool DynamicStack<T>::isEmpty() const
{
    return tos == 0;
}

template <typename T>
void DynamicStack<T>::resize(size_t newCapacity)
{
    T* newData = new T[newCapacity];
    std::copy(data, data + tos, newData);
    delete[] data;
    data = newData;
    capacity = newCapacity;
}
