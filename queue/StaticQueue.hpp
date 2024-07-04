const int MAX_SIZE = 1024;

template <typename T>
class StaticQueue {
private:
	T data[MAX_SIZE];
	unsigned head, tail, size;  // Индекси и текущ брой на елементите

public:
	StaticQueue();              // Създаване на празна опашка

	bool full() const;
	bool empty() const;         // Проверка дали опашка е празна
	void push(const T& elem);   // Включване на елемент
	void pop();                 // Изключване на елемент
	T head() const;             // Достъп до първия елемент в опашка
};

// Задава индексите на първата празна позиция
template <typename T>
StaticQueue<T>::StaticQueue() : head(0), tail(0), size(0)
{}

template <typename T>
bool StaticQueue<T>::full() const {
	return size == MAX_SIZE;
}

template <typename T>
bool StaticQueue<T>::empty() const {
	return size == 0;
}

template <typename T>
T StaticQueue<T>::head() const {
	if (empty()) {
		throw std::runtime_error("Can not get elem from an empty queue");
	}
	return data[head];
}

template <typename T>
void StaticQueue<T>::push(const T& elem) {
	if (full()) {
		throw std::runtime_error("The queue is full!");
	}

	data[tail] = elem;
	size++;
	tail++;
	tail = tail % MAX_SIZE;
}

template <typename T>
void StaticQueue<T>::pop() {
	if (empty()) {
		throw std::runtime_error("Can not delete element from an empty queue");
	}
	size--;
	head++;
	head = head % MAX_SIZE;
}