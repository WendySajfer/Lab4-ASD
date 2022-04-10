#ifndef _LIST_H_
#define _LIST_H_

class List {
private:
	class Node {
	public:
		Node* pNext;
		int p;
		Node(int p, Node* pNext = nullptr) {
			this->p = p;
			this->pNext = pNext;
		}
		void set_p(int _p) { this->p = _p; }
	};
	int Size;
	Node* head;
	Node* tail;
public:
	List(int);
	~List();
	int GetSize() { return Size; }
	void set_p(int p, const int index) {
		int counter = 0;
		Node* current = this->head;
		while (current != nullptr) {
			if (counter == index) {
				current->set_p(p);
				return;
			}
			current = current->pNext;
			counter++;
		}
	}
	void push_back(int p);
	void add_begin(int p) {
		Node* _head = new Node(p);
		_head->pNext = this->head;
		this->head = _head;
		this->Size++;
	}
	class Iterator {
	public:
		Iterator(Node* node = nullptr) : it_node(node) { }
		bool operator==(const Iterator& other) const {
			if (this == &other) {
				return true;
			}
			return it_node == other.it_node;
		}
		void set_p(int p) {
			it_node->set_p(p);
		}

		bool operator!=(const Iterator& other) const {
			return !operator==(other);
		}

		int operator*() const {
			if (it_node) {
				return it_node->p;
			}
			return int();
		}

		void operator++() {
			if (it_node) {
				it_node = it_node->pNext;
			}
		}
		void operator++(int) {
			if (it_node) {
				it_node = it_node->pNext;
			}
		}
		Node* get_pNext() {
			Node* Next = (*this).it_node;
			Next = Next->pNext;
			return Next;
		}
		void set_pNext(Node* Next) {
			((*this).it_node)->pNext = Next;
		}

		Iterator operator+(int n) {
			Iterator it_n_node = *this;
			Node* n_node = it_n_node.it_node;
			for (int i = 0; i < n; i++) {
				n_node = n_node->pNext;
			}
			Iterator it_n_node_1 = n_node;
			return it_n_node_1;
		}

		void operator+=(int n) {
			for (int i = 0; i < n; i++) {
				if (it_node) {
					it_node = it_node->pNext;
				}
			}
		}
	private:
		Node* it_node;
	};
	Iterator begin() const;
	Iterator get_tail() const;
	Iterator end() const;
	void insert(Iterator it, int p) {
		Node* ins_node = new Node(p);
		ins_node->pNext = it.get_pNext();
		it.set_pNext(ins_node);
		if (it == this->tail) tail = ins_node;
		this->Size++;
	}
	int& operator[](const int index);
};
List::List(int size_of_Array) {
	this->Size = 1;
	this->head = new Node(size_of_Array);
	tail = head;
}
List::~List() {
}
inline void List::push_back(int p)
{
	Node* node = new Node(p);
	tail->pNext = node;
	tail = node;
	Size++;
}
int& List::operator[](const int index)
{
	int counter = 0;
	Node* current = this->head;
	while (current != nullptr) {
		if (counter == index) {
			return current->p;
		}
		current = current->pNext;
		counter++;
	}
}

inline List::Iterator List::begin() const {
	return Iterator(head);
}
inline List::Iterator List::get_tail() const
{
	return Iterator(tail);
}
inline List::Iterator List::end() const {
	return Iterator(NULL);
}
#endif _LIST_H_