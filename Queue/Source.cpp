#include <iostream>

using namespace std;


template <typename T>
class Queue {
	T* queue;
	int size;
	int lastElement;
public:
	Queue() {
		queue = nullptr;
		size = 0;
		lastElement = -1;
	}

	Queue(const Queue& q) {
		queue = new T[q.size];
		this->size = q.size;
		this->lastElement = q.lastElement;
		for (int i = 0; i < lastElement + 1; i++) {
			queue[i] = q.queue[i];
		}
	}

	bool isEmpty() {
		return lastElement == -1 ? true : false;
	}

	bool isFull() {
		return lastElement == size - 1 ? true : false;
	}

	void enqueue(T elem) {
		if (lastElement < size - 1) {
			queue[++lastElement] = elem;
		}
		else {
			T* newQueue = new T[size + 5];
			for (int i = 0; i < size; i++) {
				newQueue[i] = queue[i];
			}
			newQueue[++lastElement] = elem;
			if (queue != nullptr) {
				delete[] queue;
			}
			queue = newQueue;
			size += 5;
		}
	}

	void dequeue() {
		T* newQueue = new T[size];
		for (int i = 1; i < lastElement + 1; i++) {
			newQueue[i - 1] = queue[i];
		}
		delete[] queue;
		queue = newQueue;
		lastElement--;
	}

	void info()const {
		cout << "\n---------------------------------------------------------------------" << endl;
		cout << "Size : " << size << endl;
		cout << "Index of the last element : " << lastElement << endl;
		for (int i = 0; i < size; i++) {
			cout << i << ")\t" << queue[i] << endl;
		}
		cout << "---------------------------------------------------------------------" << endl << endl;
	}

	~Queue() {
		if (queue != nullptr) {
			delete[] queue;
		}
	}
};

template <typename T>
struct Element {
	T elem;
	short priority;

	Element() : elem(-9999), priority(9999) {};

	Element(const Element& e) {
		this->elem = e.elem;
		this->priority = e.priority;
	}

	void operator()(const Element& e) {
		this->elem = e.elem;
		this->priority = e.priority;
	}

	void operator()(T elem, short p) {
		this->elem = elem;
		this->priority = p;
	}
};

template<typename T>
void swap(Element<T>& e1, Element<T>& e2) {
	Element<T> e(e1);
	e1(e2);
	e2(e);
}

template <typename T>
class QueueWithPriority {
	Element<T>* queue;
	int size;
	int lastIndex;
public:
	QueueWithPriority() {
		queue = nullptr;
		size = 0;
		lastIndex = -1;
	}

	bool isEmpty()const {
		return lastIndex == -1 ? true : false;
	}

	bool isFull()const {
		return lastIndex == size - 1 ? true : false;
	}

	void insertWithPriority(T value, short priority) {
		if (!isFull()) {
			queue[++lastIndex](value, priority);
		}
		else {
			Element<T>* newQueue = new Element<T>[size + 5];
			for (int i = 0; i < size; i++) {
				newQueue[i] = queue[i];
			}
			newQueue[++lastIndex](value, priority);
			if (queue != nullptr) {
				delete[] queue;
			}
			queue = newQueue;
			size += 5;
		}
		for (int i = 0; i < lastIndex + 1; i++) {
			if (queue[i].priority > priority) {
				for (int j = i; j < lastIndex; j++) {
					swap(queue[j], queue[lastIndex]);
				}
				break;
			}
		}
	}

	T pullHighestPriorityElement() {
		T elem = queue[0].elem;
		Element<T>* newQueue = new Element<T>[size];
		for (int i = 1; i < lastIndex + 1; i++) {
			newQueue[i - 1] = queue[i];
		}
		if (queue != nullptr) {
			delete[] queue;
		}
		lastIndex--;
		queue = newQueue;
		return elem;
	}

	T peek()const {
		return queue[0].elem;
	}

	void info()const {
		cout << "\n---------------------------------------------------------------------" << endl << endl;
		cout << "Size : " << size << endl;
		cout << "Index of the last element : " << lastIndex << endl;
		for (int i = 0; i < size; i++) {
			cout << i << ")\t" << queue[i].elem << "\tpriority: " << queue[i].priority << endl;
		}
		cout << "\n---------------------------------------------------------------------" << endl << endl;
	}

	~QueueWithPriority() {
		if (queue != nullptr) {
			delete[] queue;
		}
	}
};

void main() {
	Queue<int> queue1;
	cout << "Is queue empty : " << boolalpha << queue1.isEmpty() << endl;
	queue1.enqueue(1);
	queue1.enqueue(2);
	queue1.enqueue(3);
	queue1.enqueue(4);
	queue1.enqueue(5);
	queue1.enqueue(6);
	queue1.enqueue(7);
	queue1.enqueue(8);
	queue1.enqueue(9);
	queue1.info();
	cout << "Is queue full : " << boolalpha << queue1.isFull() << endl;
	queue1.enqueue(10);
	queue1.info();
	cout << "Is queue full : " << boolalpha << queue1.isFull() << endl;
	queue1.dequeue();
	queue1.info();
	cout << "Is queue full : " << boolalpha << queue1.isFull() << endl;
	cout << "\n#######################################################################################" << endl << endl;
	QueueWithPriority<int> queue2;
	cout << "Is queue empty : " << boolalpha << queue2.isEmpty() << endl;
	queue2.insertWithPriority(1, 6);
	queue2.insertWithPriority(2, 2);
	queue2.insertWithPriority(3, 4);
	queue2.insertWithPriority(4, 1);
	queue2.insertWithPriority(5, 1);
	queue2.insertWithPriority(6, 7);
	queue2.insertWithPriority(7, 3);
	queue2.insertWithPriority(8, 2);
	queue2.insertWithPriority(9, 6);
	queue2.info();
	cout << "Is queue full : " << boolalpha << queue2.isFull() << endl;
	queue2.insertWithPriority(10, 2);
	queue2.info();
	cout << "Is queue full : " << boolalpha << queue2.isFull() << endl;
	cout << "Element with highest priority : " << queue2.pullHighestPriorityElement() << endl;				//повертає значення, не індекс
	queue2.info();
	cout << "Is queue full : " << boolalpha << queue2.isFull() << endl;
	cout << "Element with highest priority : " << queue2.peek() << endl;
}