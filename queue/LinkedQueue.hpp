#include <stdexcept>
#include <cassert>

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

    LinkedQueue(const LinkedQueue<T>& other) : head(nullptr), tail(nullptr) {
        try {
            copy(other);
        }
        catch (std::bad_alloc&) {
            free();
            throw;
        }
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
        Node* n = new Node(elem);
        if (empty()) {
            head = n;
        }
        else {
            tail->next = n;
        }
        tail = n;
    }

    T dequeue() {
        T res = first();
        Node* keep = head;
        head = head->next;
        if (head == nullptr) {
            tail = nullptr;
        }
        delete keep;
        return res;
    }

    const T& first() const {
        if (!empty())
            return head->data;
        throw std::underflow_error("Empty queue");
    }

    bool empty() const {
        return head == nullptr;
    }

    bool full() const { return false; }

private:
    void copy(const LinkedQueue<T>& other) {
        assert(empty());

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
