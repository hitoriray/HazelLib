#pragma once

#include <iostream>
#include <exception>

namespace Hazel
{
	template <typename ElemType>
	class Stack
	{
		template<typename ElemType>
		friend std::istream& operator>>(std::istream& is, Stack<ElemType>& st);
		template<typename ElemType>
		friend std::ostream& operator<<(std::ostream& os, const Stack<ElemType>& st);

		template<typename ElemType>
		friend bool operator==(const Stack<ElemType>& lhs, const Stack<ElemType>& rhs);
		template<typename ElemType>
		friend bool operator!=(const Stack<ElemType>& lhs, const Stack<ElemType>& rhs);

		template<typename ElemType>
		friend void swap(Stack<ElemType>& lhs, Stack<ElemType>& rhs);

	public:
		Stack();
		Stack(int cap, const ElemType& value = ElemType());
		Stack(std::initializer_list<ElemType> _data);
		Stack& operator=(std::initializer_list<ElemType> _data);
		~Stack();
		Stack(const Stack& rhs);
		Stack& operator=(const Stack& rhs);
		Stack(Stack&& rhs) noexcept;
		Stack& operator=(Stack&& rhs) noexcept;

		void push(const ElemType& value);
		void push(ElemType&& value);
		template<typename... Args> void emplace(Args&& ... args);
		ElemType get();
		ElemType top() const;
		void pop();
		int size() const;
		int capacity() const;
		bool empty() const;
		bool full() const;
		void clear();
		void swap(Stack<ElemType>& other);

		void print() const;

	private:
		void addCapacity();

	private:
		ElemType* data;
		int _capacity; // ջ������
		int _top; // ջ����λ��������-1��ʾջΪ��
	};


	template<typename ElemType>
	inline std::istream& operator>>(std::istream& is, Stack<ElemType>& st)
	{
		ElemType value;
		while (is >> value) {
			st.push(value);
		}
		return is;
	}

	template<typename ElemType>
	inline std::ostream& operator<<(std::ostream& os, const Stack<ElemType>& st)
	{
		for (int i = 0; i < st.size(); ++i)
			os << st.data[i] << " ";
		return os;
	}

	template<typename ElemType>
	inline bool operator==(const Stack<ElemType>& lhs, const Stack<ElemType>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (int i = 0; i < lhs.size(); ++i) {
			if (lhs.data[i] != rhs.data[i])
				return false;
		}
		return true;
	}

	template<typename ElemType>
	inline bool operator!=(const Stack<ElemType>& lhs, const Stack<ElemType>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename ElemType>
	inline void swap(Stack<ElemType>& lhs, Stack<ElemType>& rhs)
	{
		if (&lhs != &rhs)
		{
			std::swap(lhs.data, rhs.data);
			std::swap(lhs._capacity, rhs._capacity);
			std::swap(lhs._top, rhs._top);
		}
	}

}

template<typename ElemType>
inline Hazel::Stack<ElemType>::Stack()
	: data(nullptr), _capacity(0), _top(-1)
{
	std::cout << "Stack() called." << std::endl;
}

template<typename ElemType>
inline Hazel::Stack<ElemType>::Stack(std::initializer_list<ElemType> _data)
	: data(nullptr), _capacity(0), _top(-1)
{
	std::cout << "Stack(std::initializer_list<T>) called." << std::endl;
	if (_data.empty())
		return *this;
	for (const auto& value : _data)
		push(value);
}

template<typename ElemType>
inline Hazel::Stack<ElemType>& Hazel::Stack<ElemType>::operator=(std::initializer_list<ElemType> _data)
{
	std::cout << "operator=(std::initializer_list<T>) called." << std::endl;
	if (data != nullptr) {
		clear();
		delete[] data;
	}
	if (_data.empty())
		return *this;
	for (const auto& value : _data)
		push(value);
	return *this;
}

template<typename ElemType>
inline Hazel::Stack<ElemType>::Stack(int cap, const ElemType& value)
	: data(nullptr), _capacity(cap), _top(-1)
{
	std::cout << "Stack(int, const ElemType&) called." << std::endl;
	for (int i = 0; i < cap; ++i)
		push(value);
}

template<typename ElemType>
inline Hazel::Stack<ElemType>::~Stack()
{
	std::cout << "~Stack() called." << std::endl;
	if (!empty())
	{
		clear();
		delete[] data;
	}
}

template<typename ElemType>
inline Hazel::Stack<ElemType>::Stack(const Stack& rhs)
{
	std::cout << "Stack(const Stack&) called." << std::endl;
	_capacity = rhs._capacity;
	_top = rhs._top;
	if (rhs.empty())
	{
		data = nullptr;
	}
	else
	{
		data = new ElemType[rhs._capacity];
		//std::memcpy(data, rhs.data, capacity * sizeof(ElemType)); // std::memcpyֻ������ƽ�����ͣ����������Զ�������
		std::copy(rhs.data, rhs.data + _top + 1, data); // ʹ��std::copy�������������ݣ�����Ԫ�صĿ������캯��
	}
}

template<typename ElemType>
inline Hazel::Stack<ElemType>& Hazel::Stack<ElemType>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		std::cout << "operator=(const Stack&) called." << std::endl;
		if (!empty()) // �����ǰջ��Ϊ�գ������ջ
		{
			clear();
			delete[] data;
		}
		_capacity = rhs._capacity;
		_top = rhs._top;
		if (rhs.empty()) // ���rhsջ����Ϊ0��������ָ����Ϊnullptr
		{
			data = nullptr;
		}
		else
		{
			data = new ElemType[_capacity];
			std::copy(rhs.data, rhs.data + _top + 1, data);
		}
	}
	return *this;
}

template<typename ElemType>
inline Hazel::Stack<ElemType>::Stack(Stack&& rhs) noexcept
{
	std::cout << "Stack(Stack&&) called." << std::endl;
	data = rhs.data;
	rhs.data = nullptr; // ����һ��ջ���������ָ����Ϊnullptr����������ʱ�ͷ��ڴ�ռ�
	std::swap(_capacity, rhs._capacity);
	std::swap(_top, rhs._top);
}

template<typename ElemType>
inline Hazel::Stack<ElemType>& Hazel::Stack<ElemType>::operator=(Stack&& rhs) noexcept
{
	if (this != &rhs)
	{

		std::cout << "operator=(Stack&&) called." << std::endl;
		if (!empty()) // �����ǰջ��Ϊ�գ������ջ
		{
			clear(); // #���ջ����ֹdeleteû�ɹ�������ڴ�������ڴ�й©
			delete[] data;
		}
		data = rhs.data;
		rhs.data = nullptr;
		std::swap(_capacity, rhs._capacity);
		std::swap(_top, rhs._top);
	}
	return *this;
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::push(const ElemType& value)
{
	if (full()) // ջ��
	{
		addCapacity();
	}
	data[++_top] = value; // ջ��λ�ü�һ���൱��ѹ����һ��Ԫ��
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::push(ElemType&& value)
{
	if (full())
	{
		addCapacity();
	}
	data[++_top] = std::move(value); // ʹ��std::move����ֵ����ת��Ϊ��ֵ���ã����ⲻ��Ҫ�Ŀ�����������
}

template<typename ElemType>
template<typename... Args>
inline void Hazel::Stack<ElemType>::emplace(Args&& ... args)
{
	if (full())
		addCapacity(); // ͬpush�����еĴ����߼�

	// ����ʹ���˶�λnew��placement new����������������ָ�����ڴ�λ����ֱ�ӹ���һ�����󣬶�����Ҫ�����µ��ڴ�ռ䡣
	// ����ָ�����ڴ�λ����data + ++_top��Ҳ����ջ��λ�ü�һ���൱��ѹ����һ��Ԫ�ء�
	new (data + ++_top)
		ElemType(std::forward<Args>(args)...); // ��ջ��λ��ֱ�ӹ���һ��Ԫ�أ�ʹ��std::forward������ת������ 
	// ����ʹ����std::forward������ת�����������������Ǳ��ֲ�����ֵ���value category�����䣬�Ӷ����ⲻ��Ҫ�Ŀ��������ƶ���
	// ����ʹ����...��չ���ɱ�����б��൱�ڴ��������еĲ���������ʹ����ElemType()������Ԫ�����͵Ĺ��캯�����൱�ڹ�����һ��Ԫ�ض���
}

template<typename ElemType>
inline ElemType Hazel::Stack<ElemType>::get()
{
	if (empty())
		return ElemType();
	ElemType elem = top();
	this->pop();
	return elem;
}

template<typename ElemType>
inline ElemType Hazel::Stack<ElemType>::top() const
{
	if (empty())
		return ElemType();
	return data[_top];
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::pop()
{
	if (empty())
		return;
	_top--; // ջ��λ�ü�һ���൱�ڵ�����ջ��Ԫ��
}

template<typename ElemType>
inline int Hazel::Stack<ElemType>::size() const
{
	return _top + 1;
}

template<typename ElemType>
inline int Hazel::Stack<ElemType>::capacity() const
{
	return _capacity;
}

template<typename ElemType>
inline bool Hazel::Stack<ElemType>::empty() const
{
	return _top == -1;
}

template<typename ElemType>
inline bool Hazel::Stack<ElemType>::full() const
{
	return _top == _capacity - 1;
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::clear()
{
	for (int i = 0; i <= _top; i++) // ����ջ�е�Ԫ��
	{
		data[i].~ElemType(); // �ֶ�����Ԫ�ص������������ͷ���Դ
	}
	_top = -1; // ջ��λ����Ϊ-1���൱�������ջ
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::swap(Stack<ElemType>& other)
{
	Hazel::swap(*this, other);
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::print() const
{
	if (empty()) return;
	for (int i = 0; i <= _top; ++i)
		std::cout << data[i] << " ";
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::addCapacity()
{
	if (empty()) {
		_capacity = 10; // ���ջ����Ϊ0����Ĭ�Ͻ�ջ������Ϊ10
	}
	else {
		_capacity *= 2; // ����ջ��������
	}
	ElemType* newData = nullptr;
	try {
		newData = new ElemType[_capacity]; // ���Է����µ�����ռ�
	}
	catch (std::bad_alloc& e) { // �����ڴ����ʧ�ܵ��쳣
		throw std::runtime_error("Stack is full!");
	}
	std::move(data, data + _top + 1, newData); // ʹ��std::move��ԭ����data�е������ƶ���newData�У����ⲻ��Ҫ�Ŀ�����������
	if (!empty()) // ���ԭ����������ڣ���ջ���գ����ͷ�ԭ��������ռ�
	{
		clear();
		delete[] data;
	}
	data = newData; // ��������ָ��
}
