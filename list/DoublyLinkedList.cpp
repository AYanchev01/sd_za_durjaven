using namespace std;

template <typename T>
class DLList
{
private:
    struct Node
    {
        T data;
        Node* next;
        Node* prev;

        Node(const T& data, Node* next = nullptr, Node* prev = nullptr)
            : data(data), next(next), prev(prev) {}
    };

    Node* head;
    Node* tail;

public:
    DLList() : head(nullptr), tail(nullptr) {}

    DLList(const DLList<T>& other) {
        copy(other);
    }

    DLList<T>& operator=(const DLList<T>& other) {
        if (this != &other) {
            free();
            copy(other);
        }
        return *this;
    }

    ~DLList() {
        free();
    }

    void push_front(const T& elem) {
        Node* newNode = new Node(elem, head, nullptr);
        if (!head) {
            head = tail = newNode;
            return;
        }
        head->prev = newNode;
        head = newNode;
    }

    void push_back(const T& elem) {
        Node* newNode = new Node(elem, nullptr, tail);
        if (!tail) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        tail = newNode;
    }

    void pop_front() {
        if (!head)
            throw std::length_error("Empty list!");

        Node* toDelete = head;
        head = head->next;
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete toDelete;
    }

    void pop_back() {
        if (!tail)
            throw std::length_error("Empty list!");

        Node* toDelete = tail;
        tail = tail->prev;
        if (tail) {
            tail->next = nullptr;
        } else {
            head = nullptr;
        }
        delete toDelete;
    }

    bool empty() const {
        return head == nullptr;
    }

private:
    void copy(const DLList<T>& other) {
        Node* iter = other.head;
        while (iter) {
            push_back(iter->data);
            iter = iter->next;
        }
    }

    void free() {
        while (!empty()) {
            pop_front();
        }
    }
};