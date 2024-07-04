template <typename T>
class List
{
private:
	struct Node
	{
		T data;
		Node* next;

        Node(const T& data, Node* next = nullptr)
			: data(data), next(next) {}
	};

	Node* head;
	Node* tail;

public:
	List();
	List(const List<T>& other);
	List<T>& operator=(const List<T>& other);
	~List();

private:
	void copy(const List<T>& other);
	void free();

public:
	void push_front(const T& elem);	// O(1)
	void push_back(const T& elem);	// O(1)
	void pop_front();				// O(1)
	bool empty() const;				// O(1)
};

template <typename T>
List<T>::List() : head(nullptr), tail(nullptr) {}

template <typename T>
List<T>::List(const List<T>& other)
{
	copy(other);
}

template <typename T>
List<T>& List<T>::operator=(const List<T>& other)
{
	if (this != &other)
	{
		free();
		copy(other);
	}
	return *this;
}

template <typename T>
List<T>::~List()
{
	free();
}

template <typename T>
void List<T>::push_front(const T& elem)
{
    head = new Node(elem, head);
    if (!tail)
    {
        tail = head;
    }
}

template <typename T>
bool List<T>::empty() const
{
	return head == nullptr;
}

template <typename T>
void List<T>::push_back(const T& elem)
{
	Node* newNode = new Node(elem);

	if (!tail)
	{
		head = tail = newNode;
		return;
	}

	tail->next = newNode;
	tail = newNode;
}

template <typename T>
void List<T>::pop_front()
{
	if (!head)
		throw length_error("Empty list!");

	Node* toDelete = head;
	head = head->next;
	delete toDelete;

	if (head == nullptr)
	{
		tail = nullptr;
	}
}

template <typename T>
void List<T>::copy(const List<T>& other)
{
	Node* iter = other.head;

	while (iter)
	{
		push_back(iter->data);
		iter = iter->next;
	}
}

template <typename T>
void List<T>::free()
{
	while (!empty())
	{
		pop_front();
	}
}