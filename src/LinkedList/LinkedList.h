#pragma once

#include <iostream>

namespace Hazel
{
	template <typename ElemType>
	struct ListNode
	{
		ElemType data;
		ListNode<ElemType>* next;
		ListNode() : data(0), next(nullptr) {}
		ListNode(const ElemType& _data) : data(_data), next(nullptr) {}
		ListNode(const ElemType& _data, ListNode* _next) : data(_data), next(_next) {}
	};

	template<typename ElemType> class Iterator;
	template<typename ElemType> class ConstIterator;

	template <typename ElemType>
	class LinkedList
	{
	public:
		LinkedList();
		LinkedList(int n, const ElemType& v = ElemType());
		LinkedList(const LinkedList& rhs);
		LinkedList& operator=(const LinkedList& rhs);
		LinkedList(LinkedList&& rhs) noexcept;
		LinkedList& operator=(LinkedList&& rhs) noexcept;
		~LinkedList();

		void push_back(const ElemType& v);
		void push_front(const ElemType& v);
		void pop_back();
		void pop_front();
		void insert(const ElemType& v, int index);
		void remove(int index);
		void modify(int index, const ElemType& new_value);
		bool find(const ElemType& v) const;
		bool empty() const;
		void reverse();
		void clear();

		int size() { return _size; }
		constexpr int size() const { return _size; }

		ElemType& operator[](int index);
		const ElemType& operator[](int index) const;
		ElemType& at(int index);
		const ElemType& at(int index) const;

		ElemType front() const;
		ElemType back() const;

		template<typename Func> void traverse(Func f) const;
		void print(std::ostream& os) const;

		// !define a type alias for Iterator
		using iterator = Iterator<ElemType>;
		using const_iterator = ConstIterator<ElemType>;

		iterator begin() { return iterator(_dummyHead->next); }
		iterator end() { return iterator(nullptr); }
		const_iterator cbegin() const { return const_iterator(_dummyHead->next); }
		const_iterator cend() const { return const_iterator(nullptr); }
		const_iterator contains(const ElemType& v) const;
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		iterator insert(iterator pos, const ElemType& v);

	private:
		ListNode<ElemType>* _dummyHead;
		int _size;
	};


	// define an Iterator class
	template <typename ElemType>
	class Iterator
	{
		// declare LinkedList as friend
		friend class LinkedList<ElemType>;

	public:
		// constructor with a node pointer parameter
		Iterator(ListNode<ElemType>* p) : current(p) {}

		// dereference operator to return the data of the current node
		ElemType& operator*() const { return current->data; }

		// arrow operator to return the pointer to the data of the current node
		ElemType* operator->() const { return &(current->data); }

		// pre-increment operator to move the iterator to the next node
		Iterator& operator++()
		{
			current = current->next;
			return *this;
		}

		// post-increment operator to move the iterator to the next node
		Iterator operator++(int)
		{
			Iterator temp = *this;
			++(*this);
			return temp;
		}

		Iterator operator+(int n) const
		{
			Iterator temp = *this;
			while (n-- > 0) // while n is positive
			{
				temp++; // increment the copy by one step
			}
			return temp; // return the copy
		}

		Iterator& operator+=(int n)
		{
			while (n-- > 0) // while n is positive
			{
				(*this)++; // increment the current iterator by one step
			}
			return *this; // return the current iterator
		}

		// rhs must be forward to this
		int operator-(const Iterator& rhs) const
		{
			int dist = 0; // a variable to store the distance
			Iterator temp = *this; // make a copy of the current iterator
			while (rhs != temp) // while the copy is not equal to the right-hand side iterator
			{
				rhs++; // increment rhs by one step
				dist++; // increment the distance by one
			}
			return dist; // return the distance
		}

		// equality operator to compare two iterators
		bool operator==(const Iterator& rhs) const { return current == rhs.current; }

		// inequality operator to compare two iterators
		bool operator!=(const Iterator& rhs) const { return current != rhs.current; }

		ListNode<ElemType>* get() const { return current; }

	private:
		ListNode<ElemType>* current; // a pointer to the current node
	};

	// define a Const Iterator class
	template <typename ElemType>
	class ConstIterator
	{
		// declare LinkedList as friend
		friend class LinkedList<ElemType>;

	public:
		// constructor with a node pointer parameter
		ConstIterator(ListNode<ElemType>* p) : current(p) {}

		// constructor with an iterator parameter
		ConstIterator(const Iterator<ElemType>& it) : current(it.get()) {}

		// assignment operator with an iterator parameter
		ConstIterator& operator=(const Iterator<ElemType>& it)
		{
			current = it.get();
			return *this;
		}

		// dereference operator to return the data of the current node as a constant reference
		const ElemType& operator*() const { return current->data; }

		// arrow operator to return the pointer to the data of the current node as a constant pointer
		const ElemType* operator->() const { return &(current->data); }

		// pre-increment operator to move the iterator to the next node
		ConstIterator& operator++()
		{
			current = current->next;
			return *this;
		}

		// post-increment operator to move the iterator to the next node
		ConstIterator operator++(int)
		{
			ConstIterator temp = *this;
			++(*this);
			return temp;
		}

		bool operator==(const ConstIterator& rhs) const { return current == rhs.current; }
		bool operator!=(const ConstIterator& rhs) const { return current != rhs.current; }

		ListNode<ElemType>* get() const { return current; }

	private:
		ListNode<ElemType>* current; // a pointer to the current node
	};

	
	template<typename ElemType>
	template<typename Func>
	inline void LinkedList<ElemType>::traverse(Func f) const
	{
		ListNode<ElemType>* cur = _dummyHead->next;
		while (cur)
		{
			f(cur->data);
			cur = cur->next;
		}
	}

}

template <typename ElemType>
inline Hazel::LinkedList<ElemType>::LinkedList()
	: _dummyHead(new ListNode<ElemType>(ElemType())), _size(0)
{
	std::cout << "LinkedList() called." << std::endl;
}

template<typename ElemType>
inline Hazel::LinkedList<ElemType>::LinkedList(int n, const ElemType& v)
	:_dummyHead(new ListNode<ElemType>(ElemType())), _size(n)
{
	std::cout << "LinkedList(int, const ElemType&) called." << std::endl;
	for (int i = 0; i < n; i++)
		push_back(v);
}

template<typename ElemType>
inline Hazel::LinkedList<ElemType>::LinkedList(const LinkedList& rhs)
	: _dummyHead(new ListNode<ElemType>(rhs._dummyHead->data)), _size(rhs._size)
{
	std::cout << "LinkedList copy constructor called." << std::endl;
	ListNode<ElemType>* cur = rhs._dummyHead->next;
	while (cur)
	{
		push_back(cur->data);
		cur = cur->next;
	}
}

template<typename ElemType>
inline Hazel::LinkedList<ElemType>& Hazel::LinkedList<ElemType>::operator=(const LinkedList& rhs)
{
	if (this != &rhs)
	{
		std::cout << "LinkedList copy assignment called." << std::endl;
		if (_dummyHead == nullptr)
			throw std::runtime_error("dummy head is NULL!");
		clear(); // clear the current list
		ListNode<ElemType>* cur = rhs._dummyHead->next;
		while (cur) // copy the data from the right-hand side list
		{
			push_back(cur->data);
			cur = cur->next;
		}
	}
	return *this;
}

template<typename ElemType>
inline Hazel::LinkedList<ElemType>::LinkedList(LinkedList&& rhs) noexcept
{
	std::cout << "LinkedList move constructor called." << std::endl;
	_dummyHead = rhs._dummyHead;
	_size = rhs._size;
	rhs._dummyHead = nullptr;
	rhs._size = 0;
}

template<typename ElemType>
inline Hazel::LinkedList<ElemType>& Hazel::LinkedList<ElemType>::operator=(LinkedList&& rhs) noexcept
{
	if (this != &rhs)
	{
		std::cout << "LinkedList move assignment called." << std::endl;
		clear();
		delete _dummyHead;
		_dummyHead = rhs._dummyHead;
		_size = rhs._size;
		rhs._dummyHead = nullptr;
		rhs._size = 0;
	}
	return *this;
}

template <typename ElemType>
inline Hazel::LinkedList<ElemType>::~LinkedList()
{
	//std::cout << "~LinkedList() called." << std::endl;
	clear();
	delete _dummyHead;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::push_back(const ElemType& v)
{
	ListNode<ElemType>* cur = _dummyHead;
	while (cur->next)
	{
		cur = cur->next;
	}
	cur->next = new ListNode<ElemType>(v);
	_size++;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::push_front(const ElemType& v)
{
	ListNode<ElemType>* p = new ListNode<ElemType>(v);
	p->next = _dummyHead->next;
	_dummyHead->next = p;
	_size++;
}

template<typename ElemType>
inline void Hazel::LinkedList<ElemType>::pop_back()
{
	if (empty())
		return;
	ListNode<ElemType>* pre = _dummyHead;
	ListNode<ElemType>* cur = _dummyHead->next;
	while (cur->next) {
		pre = cur;
		cur = cur->next;
	}
	pre->next = nullptr;
	delete cur;
	_size--;
}

template<typename ElemType>
inline void Hazel::LinkedList<ElemType>::pop_front()
{
	if (empty())
		return;
	ListNode<ElemType>* tmp = _dummyHead->next;
	_dummyHead->next = tmp->next;
	delete tmp;
	_size--;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::insert(const ElemType& v, int index)
{
	if (index < 0 || index > _size) return;
	if (index == _size) push_back(v);
	ListNode<ElemType>* p = new ListNode<ElemType>(v);
	ListNode<ElemType>* cur = _dummyHead;
	while (index--)
	{
		cur = cur->next;
	}
	p->next = cur->next;
	cur->next = p;
	_size++;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::remove(int index)
{
	if (index >= _size || index < 0) return;
	if (index == 0)
	{
		pop_front();
		return;
	}
	if (index == _size - 1)
	{
		pop_back();
		return;
	}
	ListNode<ElemType>* cur = _dummyHead;
	while (index--)
	{
		cur = cur->next;
	}
	ListNode<ElemType>* tmp = cur->next;
	cur->next = cur->next->next;
	delete tmp;
	_size--;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::modify(int index, const ElemType& new_value)
{
	if (index >= _size || index < 0) return;
	ListNode<ElemType>* cur = _dummyHead;
	while (index--)
	{
		cur = cur->next;
	}
	cur->next->data = new_value;
}

template <typename ElemType>
inline bool Hazel::LinkedList<ElemType>::find(const ElemType& v) const
{
	ListNode<ElemType>* cur = _dummyHead;
	while (cur->next)
	{
		if (cur->next->data == v)
			return true;
		cur = cur->next;
	}
	return false;
}

template<typename ElemType>
inline typename Hazel::LinkedList<ElemType>::const_iterator Hazel::LinkedList<ElemType>::contains(const ElemType& v) const
{
	ListNode<ElemType>* cur = _dummyHead->next; // a pointer to store the current node
	while (cur) // while the current node is not null
	{
		if (cur->data == v) // if the current node's data equals the given value
		{
			return iterator(cur); // return a const iterator pointing to the current node
		}
		cur = cur->next; // move cur to the next node
	}
	return cend(); // if no node contains the given value, return a const iterator pointing to one past the last node
}

template<typename ElemType>
inline typename Hazel::LinkedList<ElemType>::iterator Hazel::LinkedList<ElemType>::erase(iterator pos)
{
	if (empty()) // check if the list is empty
	{
		return end(); // if the list is empty, return an iterator pointing to one past the last node
	}
	ListNode<ElemType>* cur = pos.get(); // a pointer to store the node to be deleted
	ListNode<ElemType>* pre = _dummyHead; // a pointer to store the previous node of the node to be deleted
	while (pre->next != cur) { // find the previous node of the node to be deleted
		pre = pre->next;
	}
	pre->next = cur->next; // link the previous node and the next node
	delete cur; // delete the node
	_size--; // decrement the size of the list
	return iterator(pre->next); // return an iterator pointing to the next node
}

template<typename ElemType>
inline typename Hazel::LinkedList<ElemType>::iterator Hazel::LinkedList<ElemType>::erase(iterator first, iterator last)
{
	if (empty())
		return end();
	if (first == last)
		return last;
	ListNode<ElemType>* cur = first.get(); // a pointer to store the current node to be deleted
	ListNode<ElemType>* pre = _dummyHead; // a pointer to store the previous node of the current node to be deleted
	while (pre->next != cur) // while the current node is not equal to the last node
	{
		pre = pre->next;
	}
	ListNode<ElemType>* temp; // a temp pointer to store the next node of the current node to be deleted
	while (cur != last.get())
	{
		temp = cur->next; // store the next node of the current node to be deleted
		delete cur;
		_size--;
		cur = temp;
	}
	pre->next = cur; // link the previous node and the current node (which is equal to last)
	return iterator(cur); // return an iterator pointing to the current node (which is equal to last)
}

// insert函数，接受一个迭代器和一个值作为参数，并返回一个迭代器
template<typename ElemType>
inline typename Hazel::LinkedList<ElemType>::iterator Hazel::LinkedList<ElemType>::insert(iterator pos, const ElemType& v)
{
	ListNode<ElemType>* newNode = new ListNode<ElemType>(v);
	// 如果迭代器指向空节点，说明要在链表末尾插入
	if (pos == end())
	{
		// 如果链表为空，直接在头部插入
		if (empty())
		{
			_dummyHead->next = newNode;
		}
		else // 否则，在尾部插入
		{
			ListNode<ElemType>* cur = _dummyHead->next;
			while (cur->next) // 找到链表尾部的节点
			{
				cur = cur->next;
			}
			cur->next = newNode; // 新节点插入到链表尾部
		}
	}
	// 否则，在迭代器指向的位置之前插入
	else
	{
		ListNode<ElemType>* prevNode = _dummyHead; // 找到迭代器指向的位置的前一个节点
		while (prevNode->next != pos.get())
		{
			prevNode = prevNode->next;
		}
		newNode->next = pos.get(); // 将新节点的next指针指向迭代器指向的节点
		prevNode->next = newNode; // 将前一个节点的next指针指向新节点
	}
	_size++; // 链表长度加一
	return iterator(newNode); // 返回指向新插入的元素的迭代器
}

template<typename ElemType>
inline void Hazel::LinkedList<ElemType>::reverse()
{
	ListNode<ElemType>* cur = _dummyHead->next; // 让cur指向头结点，而不是虚头节点！
	ListNode<ElemType>* pre = nullptr;
	while (cur->next)
	{
		auto tmp = cur->next; // 保存一下cur的下一个节点，因为接下来要改变cur->next
		cur->next = pre; // 翻转操作
		// 更新pre和cur指针
		pre = cur;
		cur = tmp;
	}
	cur->next = pre;
	_dummyHead->next = cur;
}

template <typename ElemType>
inline bool Hazel::LinkedList<ElemType>::empty() const
{
	return _size == 0;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::clear()
{
	if (empty())
		return;
	ListNode<ElemType>* tmp = _dummyHead->next;
	while (tmp)
	{
		_dummyHead->next = tmp->next;
		delete tmp;
		tmp = _dummyHead->next;
	}
	_size = 0;
}

template<typename ElemType>
inline ElemType& Hazel::LinkedList<ElemType>::operator[](int index)
{
	return at(index);
}

template<typename ElemType>
inline const ElemType& Hazel::LinkedList<ElemType>::operator[](int index) const
{
	return at(index);
}

template <typename ElemType>
ElemType& Hazel::LinkedList<ElemType>::at(int index)
{
	if (index < 0 || index >= _size) {
		throw std::out_of_range("invalid value: index.");
	}
	ListNode<ElemType>* cur = _dummyHead->next;
	while (index--)
	{
		cur = cur->next;
	}
	return cur->data;
}

template<typename ElemType>
inline const ElemType& Hazel::LinkedList<ElemType>::at(int index) const
{
	return at(index);
}

template<typename ElemType>
inline ElemType Hazel::LinkedList<ElemType>::back() const
{
	if (empty())
		return ElemType();
	return at(size() - 1);
}

template<typename ElemType>
inline ElemType Hazel::LinkedList<ElemType>::front() const
{
	if (empty())
		return ElemType();
	return _dummyHead->next->data;
}

template <typename ElemType>
inline void Hazel::LinkedList<ElemType>::print(std::ostream& os) const
{
	ListNode<ElemType>* cur = _dummyHead->next;
	while (cur) {
		os << cur->data << " ";
		cur = cur->next;
	}
}
