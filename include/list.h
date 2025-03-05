#ifndef __List_H__
#define __List_H__

#include <iostream>

using namespace std;

template <class T>
class List {

	struct Node {
		T data;
		Node* next;

		Node() {
			data = T();
			next = nullptr;
		}

		Node(T value, Node* next) {
			data = value;
			this->next = next;
		}
	};

	Node* first = nullptr;

public:

	class iterator {
	protected:

		Node* current;

	public:

		explicit iterator(Node* Node) : current(Node) {}

		iterator& operator++() {
			current = current->next;
			return *this;
		}

		Node* getNode() const {
			return current;
		}

		iterator operator++(int) {
			iterator copy = *this;
			current = current->next;
			return copy;
		}

		T& operator*() {
			return current->data;
		}

		T* operator->() {
			return &(current->data);
		}	

		friend bool operator!=(const iterator& it1, const iterator& it2) {
			return it1.current != it2.current;
		}

		friend bool operator==(const iterator& it1, const iterator& it2) {
			return it1.current == it2.current;
		}
	};

	List();
	List(int n, T deflt = T());
	List(const List& other);
	~List();
	List& operator=(const List& other);
	void print();
	T& operator[](int index);
	size_t size();
	void shift(int k);
	//void shift_single();

	Node* insert(T value, Node* prev) {
		Node* temp = new Node;
		temp->next = prev->next;
		temp->data = value;
		prev->next = temp;
		return temp;
	}

	iterator insert(T value, iterator pos) {
		// If pos is at the beginning, handle separately (e.g., update first pointer)
		// Otherwise, extract the underlying Node* from pos:
		Node* prev = pos.getNode();
		Node* temp = new Node;
		temp->data = value;
		temp->next = prev->next;
		prev->next = temp;
		return iterator(temp);
	}

	Node* insert_front(T value) {
		Node* temp = new Node;
		temp->next = first;
		first = temp;
		temp->data = value;
		return first;
	}

	Node* erase(Node* prev) {
		Node* tmp = prev->next;
		if (!prev->next || !prev) {
			throw 1;
		}
		prev->next = tmp->next;
		delete tmp;
		return prev->next;
	}

	Node* erase_front() {
		if (!first) {
			throw "cant erase element that doesnt exist";
		}
		Node* tmp = first;
		first = tmp->next;
		delete tmp;
		return first;
	}

	Node* find(T value) {
		Node* current = first;
		while (current) {
			if (current->data == value) {
				return current;
			}
			current = current->next;
		}
		return nullptr;
	}
	
	Node* get_first() {
		return first;
	}

	iterator begin() {
		return iterator(first);
	}

	iterator end() {
		return iterator(nullptr);
	}
};

template <class T>
inline List<T>::List() {
	first = nullptr;
}

template <class T>
inline List<T>::List(int n, T deflt = T()) {
	if (n < 0) {
		throw "List size cant be negative";
	}
	if (n == 0) {
		first = nullptr;
		return;
	}

	first = new Node(deflt, nullptr);
	Node* current = first;

	for (int i = 1; i < n; ++i) {
		Node* tmp = new Node(deflt, nullptr);
		current->next = tmp;
		current = current->next;
	}
}

template <class T>
inline List<T>::List(const List& other) {
	if (!other.first) {
		first = nullptr;
		return;
	}

	first = new Node(other.first->data, nullptr);
	Node* current = first;
	Node* ocurrent = other.first;
	while (ocurrent->next) {
		current->next = new Node(ocurrent->next->data, nullptr);
		current = current->next;
		ocurrent = ocurrent->next;
	}
}

template <class T>
inline List<T>::~List() {
	while (first != nullptr) {
		Node* second = first->next;
		delete first;
		first = second;
	}
}

template <class T>
inline List<T>& List<T>::operator=(const List<T>& other) {
	if (this == &other) {
		return *this;
	}

	while (first) {
		Node* second = first->next;
		delete first;
		first = second;
	}

	if (!other.first) {
		first = nullptr;
		return *this;
	}

	first = new Node(other.first->data, nullptr);
	Node* current = first;
	Node* ocurrent = other.first->next;

	while (ocurrent) {
		current->next = new Node(ocurrent->data, nullptr);
		current = current->next;
		ocurrent = ocurrent->next;
	}
	return *this;
}

template <class T>
inline void List<T>::print() {
	Node* current = first;
	while (current) {
		cout << current->data << " ";
		current = current->next;
	}
}

template <class T>
inline T& List<T>::operator[](int index) {
	if (index < 0) {
		throw "index cant be negative";
	}

	Node* current = first;
	for (int i = 0; current != nullptr; i++) {
		if (i == index) {
			return current->data;
		}
		current = current->next;
	}

	throw "no element found";
}

template <class T>
size_t List<T>::size() {
	Node* current = first;
	int size = 0;
	while (current) {
		size += 1;
		current = current->next;
	}
	return size;
}
//-------------------------------------------------------------------------------|
//TASK 6																		 |
//Perform a cyclic shift of a list by k elements to the right in a single pass.	 |
//-------------------------------------------------------------------------------|

template <class T>
void List<T>::shift(int k) {
	if ((first == nullptr) || (k == 0)) {
		return;
	}

	if (k < 0) {
		throw "k cant be negative";
	}

	Node* fast = first;
	Node* slow = first;
	for (int i = 0; (i < k) && (fast != nullptr); i++) {
		fast = fast->next;
	}

	if (fast == nullptr) {
		throw "k cant be greater than the length of a list";
	}

	while (fast->next != nullptr) {
		slow = slow->next;
		fast = fast->next;
	}

	fast->next = first;
	first = slow->next;
	slow->next = nullptr;
} 

//i know thats not necessary i just did it for myself
//template <class T>
//void List<T>::shift_single() {
//	Node* current = first;
//	while (current) {
//		Node* cnext = current->next;
//		if (cnext->next == nullptr) {
//			current->next = nullptr;
//			cnext->next = first;
//			first = cnext;
//		}
//		current = current->next;
//	}
//}

#endif