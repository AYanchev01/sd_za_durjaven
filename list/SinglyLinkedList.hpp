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
	List() : head(nullptr), tail(nullptr) {}

	List(const List<T>& other) {
		copy(other);
	}

	List<T>& operator=(const List<T>& other) {
		if (this != &other) {
			free();
			copy(other);
		}
		return *this;
	}

	~List() {
		free();
	}

public:
	void push_front(const T& elem) { // O(1)
		head = new Node(elem, head);
		if (!tail) {
			tail = head;
		}
	}

	void push_back(const T& elem) { // O(1)
		Node* newNode = new Node(elem);

		if (!tail) {
			head = tail = newNode;
			return;
		}

		tail->next = newNode;
		tail = newNode;
	}

	void pop_front() { // O(1)
		if (!head)
			throw std::length_error("Empty list!");

		Node* toDelete = head;
		head = head->next;
		delete toDelete;

		if (head == nullptr) {
			tail = nullptr;
		}
	}

	bool empty() const { // O(1)
		return head == nullptr;
	}

private:
	void copy(const List<T>& other) {
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
