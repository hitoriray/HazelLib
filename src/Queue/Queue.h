#pragma once

#include <iostream>

namespace Hazel
{
	template <typename ElemType>
	class Queue
	{
	protected:
		struct Node
		{
			ElemType data;
			Node* prev;
			Node* next;

			Node(const ElemType& value, Node* p = nullptr, Node* n = nullptr)
				: data(value), prev(p), next(n) {}
		};

	private:
		template<typename ElemType>
		friend std::istream& operator>>(std::istream& is, Queue<ElemType>& que);
		template<typename ElemType>
		friend std::ostream& operator<<(std::ostream& os, const Queue<ElemType>& que);

		template<typename ElemType>
		friend bool operator==(const Queue<ElemType>& lhs, const Queue<ElemType>& rhs);
		template<typename ElemType>
		friend bool operator!=(const Queue<ElemType>& lhs, const Queue<ElemType>& rhs);

		template<typename ElemType>
		friend void swap(Queue<ElemType>& lhs, Queue<ElemType>& rhs);

	public:
		Queue();
		Queue(int cap, ElemType value = ElemType());
		Queue(std::initializer_list<ElemType> data);
		~Queue();
		Queue(const Queue& rhs);
		Queue& operator=(const Queue& rhs);
		Queue(Queue&& rhs) noexcept;
		Queue& operator=(Queue&& rhs) noexcept;

		void push(const ElemType& value);
		void pop();
		ElemType get();
		void push_back(ElemType value);
		void push_front(ElemType value);
		void pop_back();
		void pop_front();
		ElemType get_back();
		ElemType get_front();
		void swap(Queue& other);

		ElemType back();
		const ElemType back() const;
		ElemType front();
		const ElemType front() const;

		void clear();
		bool empty() const;
		int size();
		constexpr int size() const;

		void print() const;

	private:
		void init();

	private:
		Node* head; // 创建一个哨兵结点作为头结点
		Node* tail;
		int count;
	};


	template<typename ElemType>
	inline void swap(Queue<ElemType>& lhs, Queue<ElemType>& rhs)
	{
		if (&lhs != &rhs)
		{
			std::swap(lhs.head, rhs.head);
			std::swap(lhs.tail, rhs.tail);
			std::swap(lhs.count, rhs.count);
		}
	}

	template<typename ElemType>
	inline std::istream& operator>>(std::istream& is, Queue<ElemType>& que)
	{
		ElemType value;
		while (is >> value) {
			que.push_back(value);
		}
		return is;
	}

	template<typename ElemType>
	inline std::ostream& operator<<(std::ostream& os, const Queue<ElemType>& que)
	{
		auto cur = que.head->next;
		while (cur) {
			os << cur->data << " ";
			cur = cur->next;
		}
		return os;
	}

	template<typename ElemType>
	inline bool operator==(const Queue<ElemType>& lhs, const Queue<ElemType>& rhs)
	{
		if (&lhs == &rhs)
			return true;
		if (lhs.count != rhs.count)
			return false;
		auto p = lhs.head->next;
		auto q = rhs.head->next;
		while (p && q)
		{
			if (p->data != q->data)
				return false;
			p = p->next;
			q = q->next;
		}
		return true;
	}

	template<typename ElemType>
	inline bool operator!=(const Queue<ElemType>& lhs, const Queue<ElemType>& rhs)
	{
		return !(lhs == rhs);
	}

}

template <typename ElemType>
void Hazel::Queue<ElemType>::print() const
{
	Node* cur = head; // 从第一个有效结点开始遍历
	while (cur->next)
	{
		std::cout << cur->next->data << " "; // 打印结点的数据
		cur = cur->next; // 指向下一个结点
	}
}

template<typename ElemType>
inline void Hazel::Queue<ElemType>::init()
{
	head = new Node(0);
	tail = head;
	count = 0;
}

template <typename ElemType>
constexpr int Hazel::Queue<ElemType>::size() const
{
	return count;
}

template<typename ElemType>
inline void Hazel::Queue<ElemType>::clear()
{
	if (empty())
		return;
	while (head->next) { // 从头到尾删除所有结点
		Node* temp = head->next;
		head->next = temp->next;
		delete temp;
	}
	tail = head;
	count = 0;
}

template <typename ElemType>
bool Hazel::Queue<ElemType>::empty() const
{
	return count == 0;
}

template<typename ElemType>
inline int Hazel::Queue<ElemType>::size()
{
	return count;
}

template <typename ElemType>
const ElemType Hazel::Queue<ElemType>::front() const
{
	if (empty())
		return ElemType();
	return head->next->data;
}

template <typename ElemType>
ElemType Hazel::Queue<ElemType>::front()
{
	if (empty())
		return ElemType();
	return head->next->data;
}

template <typename ElemType>
const ElemType Hazel::Queue<ElemType>::back() const
{
	if (empty())
		return ElemType();
	return tail->data;
}

template <typename ElemType>
ElemType Hazel::Queue<ElemType>::back()
{
	if (empty())
		return ElemType();
	return tail->data; // 返回尾结点的数据
}

template <typename ElemType>
void Hazel::Queue<ElemType>::pop_front()
{
	if (empty())
		return;
	Node* temp = head->next; // 用一个临时指针指向第一个有效结点
	head->next = temp->next; // 将头结点的后继更新为第二个有效结点
	if (temp->next == nullptr) { // 如果只有一个节点，那么只需要将tail指向head即可
		tail = head;
	}
	else {
		temp->next->prev = head; // 将第二个有效结点的前驱更新为头结点
	}
	delete temp; // 删除第一个有效结点
	count--; // 队列元素个数减一
}

template<typename ElemType>
inline ElemType Hazel::Queue<ElemType>::get_back()
{
	if (empty())
		return ElemType();
	ElemType tmp = back();
	pop_back();
	return tmp;
}

template<typename ElemType>
inline ElemType Hazel::Queue<ElemType>::get_front()
{
	return get();
}

template<typename ElemType>
inline void Hazel::Queue<ElemType>::swap(Queue& other)
{
	Hazel::swap(*this, other); // 直接调用Hazel里面的swap
}

template <typename ElemType>
void Hazel::Queue<ElemType>::pop_back()
{
	if (empty())
		return;
	Node* temp = tail; // 用一个临时指针指向当前的尾结点
	tail = tail->prev; // 将尾结点更新为其前驱
	tail->next = nullptr; // 将新的尾结点的后继置空
	delete temp; // 删除原来的尾结点 
	count--;
}

template <typename ElemType>
void Hazel::Queue<ElemType>::push_front(ElemType value)
{
	Node* newNode = new Node(value, head, head->next); // 创建一个新结点，其前驱为头结点，后继为头结点的后继
	head->next->prev = newNode; // 将头结点的后继的前驱指向新结点
	head->next = newNode; // 将头结点的后继指向新结点
	count++;
}

template<typename ElemType>
inline void Hazel::Queue<ElemType>::push(const ElemType& value)
{
	push_back(value);
}

template<typename ElemType>
inline void Hazel::Queue<ElemType>::pop()
{
	pop_front();
}

template<typename ElemType>
inline ElemType Hazel::Queue<ElemType>::get()
{
	if (empty())
		return ElemType();
	ElemType tmp = front();
	pop_front();
	return tmp;
}

// 在队列尾部插入一个元素
template <typename ElemType>
void Hazel::Queue<ElemType>::push_back(ElemType value)
{
	Node* newNode = new Node(value, tail, nullptr); // 创建一个新结点，其前驱为当前的尾结点，后继为空
	tail->next = newNode; // 将当前的尾结点的后继指向新结点
	tail = newNode; // 将尾结点更新为新结点
	count++;
}

// 默认构造
template<typename ElemType>
inline Hazel::Queue<ElemType>::Queue()
	: head(new Node(ElemType())), tail(head), count(0)
{

}

template<typename ElemType>
inline Hazel::Queue<ElemType>::Queue(std::initializer_list<ElemType> data)
{
	init();
	for (const auto& value : data)
		push_back(value);
}

template<typename ElemType>
inline Hazel::Queue<ElemType>::Queue(int cap, ElemType value)
{
	init();
	for (int i = 0; i < cap; ++i)
		push_back(value);
}

// 析构
template<typename ElemType>
inline Hazel::Queue<ElemType>::~Queue()
{
	clear();
	delete head;
	head = nullptr;
}

// 拷贝构造
template<typename ElemType>
inline Hazel::Queue<ElemType>::Queue(const Queue& rhs)
{
	init();
	Node* cur = rhs.head->next; // 从rhs的第一个有效结点开始遍历
	while (cur) {
		push_back(cur->data); // 将p的数据插入到当前队列的尾部
		cur = cur->next;
	}
}

// 拷贝赋值
template <typename ElemType>
Hazel::Queue<ElemType>& Hazel::Queue<ElemType>::operator=(Queue&& rhs) noexcept
{
	if (this != &rhs)
	{
		this->~Queue();
		init();
		Node* cur = rhs.head;
		while (cur->next) {
			push_back(cur->next->data);
			cur = cur->next;
		}
	}
	return *this;
}

template <typename ElemType>
Hazel::Queue<ElemType>::Queue(Queue&& rhs) noexcept
{
	head = rhs.head; // 直接将当前队列的头结点指向rhs的头结点
	tail = rhs.tail; // 直接将当前队列的尾结点指向rhs的尾结点
	count = rhs.count;
	rhs.head = nullptr; // 将rhs的头结点置空
	rhs.tail = nullptr; // 将rhs的尾结点置空
	rhs.count = 0; // 将rhs的元素个数置为0
}

template <typename ElemType>
Hazel::Queue<ElemType>& Hazel::Queue<ElemType>::operator=(const Queue& rhs)
{
	if (this != &rhs) // 避免自赋值
	{
		this->~Queue();
		head = rhs.head;
		tail = rhs.tail;
		count = rhs.count;
		rhs.head = nullptr;
		rhs.tail = nullptr;
		rhs.count = 0;
	}
	return *this; // 返回当前对象的引用
}

