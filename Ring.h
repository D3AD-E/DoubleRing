#pragma once
#include <stdexcept>
template<class Key, class Info>
class Ring
{
private:
	struct Node
	{
		Key key;
		Info info;
		Node* next;
		Node* prev;
	};

public:

	class Iterator
	{
		friend class Ring;
	public:


		Iterator& operator=(Node* Node)
		{
			this->CurrentNode = Node;
			return *this;
		}

		Iterator& operator++()
		{
			CurrentNode = CurrentNode->next;
			return *this;
		}

		Iterator operator++(int)
		{
			Iterator iterator = *this;
			++* this;
			return iterator;
		}

		Iterator operator+(int count)
		{
			Iterator temp(CurrentNode);
			for (; count > 0; count--)
				temp++;
			return temp;
		}

		Iterator& operator--()
		{
			CurrentNode = CurrentNode->prev;
			return *this;
		}

		Iterator operator--(int)
		{
			Iterator iterator = *this;
			--* this;
			return iterator;
		}

		Iterator operator-(int count)
		{
			Iterator temp(CurrentNode);
			for (; count > 0; count--)
				temp--;
			return temp;
		}

		bool operator!=(const Iterator& iterator)
		{
			return CurrentNode != iterator.CurrentNode;
		}

		bool operator==(const Iterator& iterator)
		{
			return CurrentNode == iterator.CurrentNode;
		}

		Key& key()
		{
			return CurrentNode->key;
		}

		Info& info()
		{
			return CurrentNode->info;
		}
	private:
		Node* CurrentNode;

		Iterator(Node* Node) noexcept :
			CurrentNode(Node) { }
		Node* node()
		{
			return CurrentNode;
		}
	};

	class Const_Iterator
	{
		friend class Ring;
	public:


		Const_Iterator& operator=(const Node* Node)
		{
			this->CurrentNode = Node;
			return *this;
		}

		Const_Iterator& operator++()
		{
			CurrentNode = CurrentNode->next;
			return *this;
		}

		Const_Iterator operator++(int)
		{
			Const_Iterator Const_Iterator = *this;
			++* this;
			return Const_Iterator;
		}

		Const_Iterator operator+(int count)
		{
			Const_Iterator temp(CurrentNode);
			for (; count > 0; count--)
				temp++;
			return temp;
		}

		Const_Iterator& operator--()
		{
			CurrentNode = CurrentNode->prev;
			return *this;
		}

		Const_Iterator operator--(int)
		{
			Const_Iterator Const_Iterator = *this;
			--* this;
			return Const_Iterator;
		}

		Const_Iterator operator-(int count)
		{
			Const_Iterator temp(CurrentNode);
			for (; count > 0; count--)
				temp--;
			return temp;
		}

		bool operator!=(const Const_Iterator& Const_Iterator)
		{
			return CurrentNode != Const_Iterator.CurrentNode;
		}

		bool operator==(const Const_Iterator& Const_Iterator)
		{
			return CurrentNode == Const_Iterator.CurrentNode;
		}

		const Key& key()
		{
			return CurrentNode->key;
		}

		const Info& info()
		{
			return CurrentNode->info;
		}
	private:
		const Node* CurrentNode;

		Const_Iterator(const Node* Node) noexcept :
			CurrentNode(Node) { }
	};

public:
	Ring()
	{
		head = nullptr;
	}
	Ring(const Ring& other)
	{
		this->head = nullptr;
		if (other.empty())
		{
			return;
		}
		Node* thisnode = this->head;
		Node* othernode = other.head;
		do
		{
			Node* node = new Node;
			node->key = othernode->key;
			node->info = othernode->info;
			node->prev = nullptr;
			node->next = nullptr;
			if (empty())
			{
				head = node;
				head->next = head;
				head->prev = head;
				thisnode = head;
			}
			else
			{
				node->prev = thisnode;
				thisnode->next = node;
				thisnode = node;
			}
			othernode = othernode->next;
		} while (othernode != other.head);
		thisnode->next = head;
		head->prev = thisnode;
	}
	Ring(Iterator first, Iterator last)
	{
		head = nullptr;
		if (!isIteratorInElement(first, last))
			throw std::logic_error("Wrong position of iterators");
		else
		{
			*this = copy(first, last);
		}
	}
	Ring(Const_Iterator first, Const_Iterator last)
	{
		head = nullptr;
		if (!isIteratorInElement(first, last))
			throw std::logic_error("Wrong position of iterators");
		else
		{
			*this = copy(first, last);
		}
	}
	~Ring()
	{
		clear();
	}

	Ring& operator=(const Ring& other)
	{
		if (this == &other)
			return *this;
		clear();
		Node* thisnode = head;
		Node* othernode = other.head;

		do
		{
			Node* node = new Node;
			node->key = othernode->key;
			node->info = othernode->info;
			node->prev = nullptr;
			node->next = nullptr;
			if (empty())
			{
				head = node;
				head->next = head;
				head->prev = head;
				thisnode = head;
			}
			else
			{
				node->prev = thisnode;
				thisnode->next = node;
				thisnode = node;
			}
			othernode = othernode->next;
		} while (othernode != other.head);
		thisnode->next = head;
		head->prev = thisnode;

		return *this;
	}
	Ring& operator+=(const Ring& other)
	{
		if (other.empty())
		{
			return *this;
		}
		else if (this->empty())
		{
			*this = other;
			return *this;
		}
		else
		{
			Node* thisnode = this->head->prev;
			Node* othernode = other.head;

			do
			{
				Node* node = new Node;
				node->key = othernode->key;
				node->info = othernode->info;

				node->prev = thisnode;
				thisnode->next = node;
				thisnode = node;

				othernode = othernode->next;
			} while (othernode != other.head);


			thisnode->next = head;
			head->prev = thisnode;
			return *this;
		}
	}
	Ring operator+(const Ring& other)
	{
		if (other.empty())
		{
			Ring result(*this);
			return result;
		}
		else if (this->empty())
		{
			Ring result(other);
			return result;
		}
		else
		{
			Ring ThisRing(*this);
			Node* thisnode = ThisRing.head->prev;
			Node* othernode = other.head;

			do
			{
				Node* node = new Node;
				node->key = othernode->key;
				node->info = othernode->info;

				node->prev = thisnode;
				thisnode->next = node;
				thisnode = node;

				othernode = othernode->next;
			} while (othernode != other.head);


			thisnode->next = ThisRing.head;
			ThisRing.head->prev = thisnode;
			
			return ThisRing;
		}
	}

	Const_Iterator begin() const
	{
		return Const_Iterator(head);
	}
	Const_Iterator end() const
	{
		return Const_Iterator(head->prev);
	}

	Iterator begin()
	{
		return Iterator(head);
	}
	Iterator end()
	{
		return Iterator(head->prev);
	}

	Iterator find(const Key& key, bool& found)
	{
		Iterator it(head);
		if (!contains(key))
		{
			found = false;
			return it(nullptr);
		}
		while (it.key() != key)
		{
			it++;
		}
		return it;
	}

	Iterator erase(Iterator pos)
	{
		if(!isIteratorInElement(pos))
			throw std::logic_error("Iterator is in the different ring");
		if (size()==1)
		{
			clear();
			return Iterator(nullptr);
		}
		else if (pos == begin())
		{
			Node* temp = head->next;
			head->next->prev = head->prev;
			head->prev->next = head->next;
			delete head;
			head = temp;
			return Iterator(temp);
		}
		else
		{
			Node* curr = pos.node();
			Node* next = curr->next;
			curr->next->prev = curr->prev;
			curr->prev->next = curr->next;
			delete curr;
			return Iterator(next);
		}
	}
	Iterator erase(Iterator first, Iterator last)
	{
		if (!isIteratorInElement(first, last))
			throw std::logic_error("Wrong position of iterators");
		if (first == begin() && last == end())
		{
			clear();
			return Iterator(nullptr);
		}
		while (first != last)
		{
			Iterator(temp) = first;
			first++;
			erase(temp);
		}
		last++;
		Iterator(temp) = first;
		erase(temp);
		return last;
	}
	Iterator insert(Iterator pos, const Key& key, const Info& info)
	{
		if (pos == begin())
		{
			push(key, info);
			return begin();
		}
		else
		{
			Node* curr = pos.node();
			Node* new_node = new Node;
			new_node->key = key;
			new_node->info = info;
			new_node->next = curr;
			new_node->prev = curr->prev;
			curr->prev->next = new_node;
			curr->prev = new_node;
			Iterator it(new_node);
			return it;
		}
	}
	Iterator insert(Iterator pos, size_t count, const Key& key, const Info& info)
	{
		if (pos == begin())
		{
			for (; count > 0; count--)
				push(key, info);
			return begin();
		}
		else
		{
			Node* curr = pos.node();
			Iterator it(curr);
			it--;
			for (; count > 0; count--)
			{
				Node* new_node = new Node;
				new_node->key = key;
				new_node->info = info;
				new_node->next = curr;
				new_node->prev = curr->prev;
				curr->prev->next = new_node;
				curr->prev = new_node;
			}
			it++;
			return it;
		}
	}

	Ring copy(Iterator position)
	{
		Ring ring;
		if(position != nullptr)
			ring.push(position);
		return ring;
	}
	Ring copy(Iterator first, Iterator last)
	{
		if (!isIteratorInElement(first, last))
			throw std::logic_error("Iterators belong to different rings");
		if (first == begin() && last == end())
		{
			Ring ring(*this);
			return ring;
		}
		Ring ring;
		for (; first != last; first++)
		{
			ring.push(first);
		}
		ring.push(first++);
		return ring;
	}

	Ring copy(Const_Iterator position) const
	{
		Ring ring;
		if (position != nullptr)
			ring.push(position);
		return ring;
	}
	Ring copy(Const_Iterator first, Const_Iterator last) const 
	{
		if (!isIteratorInElement(first, last))
			throw std::logic_error("Iterators belong to different rings");
		if (first == begin() && last == end())
		{
			Ring ring(*this);
			return ring;
		}
		Ring ring;
		for (; first != last; first++)
		{
			ring.push(first);
		}
		ring.push(first++);
		return ring;
	}

	bool empty() const
	{
		if (head == nullptr)
			return true;
		else
			return false;
	}
	bool contains(const Key& key)
	{
		Iterator it(head);
		do
		{
			if (it.key() == key)
				return true;
			it++;
		} while (it != head);
return false;
	}

	void push(const Key& key, const Info& info)
	{
		if (head == nullptr)
		{
			Node* node = new Node;
			node->key = key;
			node->info = info;
			node->next = node;
			node->prev = node;
			head = node;
			return;
		}

		Node* new_node = new Node;
		new_node->key = key;
		new_node->info = info;

		/* Find last node */
		Node* last = head->prev;

		// Start is going to be next of new_node 
		new_node->next = head;

		// Make new node previous of start 
		head->prev = new_node;

		// Make last preivous of new node 
		new_node->prev = last;

		// Make new node next of old last 
		last->next = new_node;
	}
	void clear()
	{
		if (!head)
			return;
		Node* node = head;
		Node* del_node;
		do
		{
			del_node = node;
			node = node->next;
			delete del_node;
		} while (node != head);

		head = nullptr;
	}

	int size()
	{
		Node* temp = head;
		int size = 0;
		if (!head)
			return size;
		do
		{
			size++;
			temp = temp->next;
		} while (temp != head);
		return size;
	}


	//to be removed
	void displayList()
	{
		Node* ptr = head;
		if (!head)
		{
			std::cout <<"Empty"<<std::endl;
			std::cout << std::endl;
			return;
		}
		do
		{
			std::cout << ptr->key << std::endl;
			ptr = ptr->next;
		} while (ptr != head);
		std::cout << std::endl;
	}
	void displayListRev()
	{
		Node* ptr = head;
		if (!head)
		{
			std::cout << "Empty" << std::endl;
			std::cout << std::endl;
			return;
		}
		do
		{
			ptr = ptr->prev;
			std::cout << ptr->key << std::endl;
		} while (ptr != head);
		std::cout << std::endl;
	}

private:
	Node* head;
	bool isIteratorInElement(Iterator first, Iterator last)
	{
		Iterator it(first);
		do
		{
			if (it == last)
				return true;
			it++;
		} while (it != first);
		return false;
	}
	bool isIteratorInElement(Iterator it)
	{
		Iterator iter = begin();
		do
		{
			if (iter == it)
				return true;
			iter++;
		} while (iter != begin());
		return false;
	}
	bool isIteratorInElement(Const_Iterator first, Const_Iterator last)
	{
		Iterator it(first);
		do
		{
			if (it == last)
				return true;
			it++;
		} while (it != first);
		return false;
	}
	bool isIteratorInElement(Const_Iterator it)
	{
		Iterator iter = begin();
		do
		{
			if (iter == it)
				return true;
			iter++;
		} while (iter != begin());
		return false;
	}
	void push(Iterator it)
	{
		push(it.key(), it.info());
	}
	void push(Const_Iterator it)
	{
		push(it.key(), it.info());
	}
};