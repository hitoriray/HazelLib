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
		Node* head; // ����һ���ڱ������Ϊͷ���
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
	Node* cur = head; // �ӵ�һ����Ч��㿪ʼ����
	while (cur->next)
	{
		std::cout << cur->next->data << " "; // ��ӡ��������
		cur = cur->next; // ָ����һ�����
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
	while (head->next) { // ��ͷ��βɾ�����н��
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
	return tail->data; // ����β��������
}

template <typename ElemType>
void Hazel::Queue<ElemType>::pop_front()
{
	if (empty())
		return;
	Node* temp = head->next; // ��һ����ʱָ��ָ���һ����Ч���
	head->next = temp->next; // ��ͷ���ĺ�̸���Ϊ�ڶ�����Ч���
	if (temp->next == nullptr) { // ���ֻ��һ���ڵ㣬��ôֻ��Ҫ��tailָ��head����
		tail = head;
	}
	else {
		temp->next->prev = head; // ���ڶ�����Ч����ǰ������Ϊͷ���
	}
	delete temp; // ɾ����һ����Ч���
	count--; // ����Ԫ�ظ�����һ
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
	Hazel::swap(*this, other); // ֱ�ӵ���Hazel�����swap
}

template <typename ElemType>
void Hazel::Queue<ElemType>::pop_back()
{
	if (empty())
		return;
	Node* temp = tail; // ��һ����ʱָ��ָ��ǰ��β���
	tail = tail->prev; // ��β������Ϊ��ǰ��
	tail->next = nullptr; // ���µ�β���ĺ���ÿ�
	delete temp; // ɾ��ԭ����β��� 
	count--;
}

template <typename ElemType>
void Hazel::Queue<ElemType>::push_front(ElemType value)
{
	Node* newNode = new Node(value, head, head->next); // ����һ���½�㣬��ǰ��Ϊͷ��㣬���Ϊͷ���ĺ��
	head->next->prev = newNode; // ��ͷ���ĺ�̵�ǰ��ָ���½��
	head->next = newNode; // ��ͷ���ĺ��ָ���½��
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

// �ڶ���β������һ��Ԫ��
template <typename ElemType>
void Hazel::Queue<ElemType>::push_back(ElemType value)
{
	Node* newNode = new Node(value, tail, nullptr); // ����һ���½�㣬��ǰ��Ϊ��ǰ��β��㣬���Ϊ��
	tail->next = newNode; // ����ǰ��β���ĺ��ָ���½��
	tail = newNode; // ��β������Ϊ�½��
	count++;
}

// Ĭ�Ϲ���
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

// ����
template<typename ElemType>
inline Hazel::Queue<ElemType>::~Queue()
{
	clear();
	delete head;
	head = nullptr;
}

// ��������
template<typename ElemType>
inline Hazel::Queue<ElemType>::Queue(const Queue& rhs)
{
	init();
	Node* cur = rhs.head->next; // ��rhs�ĵ�һ����Ч��㿪ʼ����
	while (cur) {
		push_back(cur->data); // ��p�����ݲ��뵽��ǰ���е�β��
		cur = cur->next;
	}
}

// ������ֵ
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
	head = rhs.head; // ֱ�ӽ���ǰ���е�ͷ���ָ��rhs��ͷ���
	tail = rhs.tail; // ֱ�ӽ���ǰ���е�β���ָ��rhs��β���
	count = rhs.count;
	rhs.head = nullptr; // ��rhs��ͷ����ÿ�
	rhs.tail = nullptr; // ��rhs��β����ÿ�
	rhs.count = 0; // ��rhs��Ԫ�ظ�����Ϊ0
}

template <typename ElemType>
Hazel::Queue<ElemType>& Hazel::Queue<ElemType>::operator=(const Queue& rhs)
{
	if (this != &rhs) // �����Ը�ֵ
	{
		this->~Queue();
		head = rhs.head;
		tail = rhs.tail;
		count = rhs.count;
		rhs.head = nullptr;
		rhs.tail = nullptr;
		rhs.count = 0;
	}
	return *this; // ���ص�ǰ���������
}

