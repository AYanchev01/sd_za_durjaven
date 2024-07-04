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
    DLList();
    DLList(const DLList<T>& other);
    DLList<T>& operator=(const DLList<T>& other);
    ~DLList();

private:
    void copy(const DLList<T>& other);
    void free();

public:
    void push_front(const T& elem);
    void push_back(const T& elem);

    void pop_front();
    void pop_back();

    bool empty() const;
};

template <typename T>
DLList<T>::DLList() : head(nullptr), tail(nullptr) {}

template <typename T>
DLList<T>::DLList(const DLList<T>& other)
{
    copy(other);
}

template <typename T>
DLList<T>& DLList<T>::operator=(const DLList<T>& other)
{
    if (this != &other)
    {
        free();
        copy(other);
    }

    return *this;
}

template <typename T>
DLList<T>::~DLList()
{
    free();
}

template <typename T>
void DLList<T>::push_front(const T& elem)
{
    Node* newNode = new Node(elem, head, nullptr);
    if (!head)
    {
        head = tail = newNode;
        return;
    }
    head->prev = newNode;
    head = newNode;
}

template <typename T>
void DLList<T>::push_back(const T& elem)
{
    Node* newNode = new Node(elem, nullptr, tail);
    if (!tail)
    {
        head = tail = newNode;
        return;
    }
    tail->next = newNode;
    tail = newNode;
}

template <typename T>
void DLList<T>::pop_front()
{
    if (!head)
        throw std::length_error("Empty list!");

    Node* toDelete = head;
    head = head->next;
    if (head)
    {
        head->prev = nullptr;
    }
    else
    {
        tail = nullptr;
    }
    delete toDelete;
}

template <typename T>
void DLList<T>::pop_back()
{
    if (!tail)
        throw std::length_error("Empty list!");

    Node* toDelete = tail;
    tail = tail->prev;
    if (tail)
    {
        tail->next = nullptr;
    }
    else
    {
        head = nullptr;
    }
    delete toDelete;
}

template <typename T>
bool DLList<T>::empty() const
{
    return head == nullptr;
}

template <typename T>
void DLList<T>::copy(const DLList<T>& other)
{
    Node* iter = other.head;
    while (iter)
    {
        push_back(iter->data);
        iter = iter->next;
    }
}

template <typename T>
void DLList<T>::free()
{
    while (!empty())
    {
        pop_front();
    }
}