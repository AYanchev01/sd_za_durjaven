#include <stdexcept>

template <typename T>
class LinkedQueue
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node(const T& data, Node* next = nullptr)
            : data(data), next(next) {}
    } *head, *tail;

public:
    LinkedQueue() : head(nullptr), tail(nullptr) {}

    LinkedQueue(const LinkedQueue<T>& other){
        copy(other);
    }

    LinkedQueue<T>& operator=(const LinkedQueue<T>& other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    ~LinkedQueue() {
        free();
    }

    void enqueue(const T& elem) {
        Node* newNode = new Node(elem);
        if (empty()) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    void dequeue() {
		if (empty())
            throw std::underflow_error("Empty queue");

        Node* toDel = head;
        head = head->next;
        delete toDel;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    const T& first() const {
        if (empty())
            throw std::underflow_error("Empty queue");

        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    bool full() const { return false; }

private:
    void copy(const LinkedQueue<T>& other) {
        Node* current = other.head;
        while (current) {
            enqueue(current->data);
            current = current->next;
        }
    }

    void free() {
        while (!empty())
            dequeue();
    }
};
