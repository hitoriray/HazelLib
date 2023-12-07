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
		int _capacity; // 栈的容量
		int _top; // 栈顶的位置索引，-1表示栈为空
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
		//std::memcpy(data, rhs.data, capacity * sizeof(ElemType)); // std::memcpy只能用于平凡类型，不能用于自定义类型
		std::copy(rhs.data, rhs.data + _top + 1, data); // 使用std::copy来拷贝数组内容，调用元素的拷贝构造函数
	}
}

template<typename ElemType>
inline Hazel::Stack<ElemType>& Hazel::Stack<ElemType>::operator=(const Stack& rhs)
{
	if (this != &rhs)
	{
		std::cout << "operator=(const Stack&) called." << std::endl;
		if (!empty()) // 如果当前栈不为空，则清空栈
		{
			clear();
			delete[] data;
		}
		_capacity = rhs._capacity;
		_top = rhs._top;
		if (rhs.empty()) // 如果rhs栈容量为0，则将数组指针置为nullptr
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
	rhs.data = nullptr; // 将另一个栈对象的数组指针置为nullptr，避免析构时释放内存空间
	std::swap(_capacity, rhs._capacity);
	std::swap(_top, rhs._top);
}

template<typename ElemType>
inline Hazel::Stack<ElemType>& Hazel::Stack<ElemType>::operator=(Stack&& rhs) noexcept
{
	if (this != &rhs)
	{

		std::cout << "operator=(Stack&&) called." << std::endl;
		if (!empty()) // 如果当前栈不为空，则清空栈
		{
			clear(); // #清空栈，防止delete没成功清除掉内存而导致内存泄漏
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
	if (full()) // 栈满
	{
		addCapacity();
	}
	data[++_top] = value; // 栈顶位置加一，相当于压入了一个元素
}

template<typename ElemType>
inline void Hazel::Stack<ElemType>::push(ElemType&& value)
{
	if (full())
	{
		addCapacity();
	}
	data[++_top] = std::move(value); // 使用std::move将右值引用转换为左值引用，避免不必要的拷贝或者析构
}

template<typename ElemType>
template<typename... Args>
inline void Hazel::Stack<ElemType>::emplace(Args&& ... args)
{
	if (full())
		addCapacity(); // 同push函数中的处理逻辑

	// 这里使用了定位new（placement new），它的作用是在指定的内存位置上直接构造一个对象，而不需要分配新的内存空间。
	// 我们指定的内存位置是data + ++_top，也就是栈顶位置加一，相当于压入了一个元素。
	new (data + ++_top)
		ElemType(std::forward<Args>(args)...); // 在栈顶位置直接构造一个元素，使用std::forward来完美转发参数 
	// 这里使用了std::forward来完美转发参数，它的作用是保持参数的值类别（value category）不变，从而避免不必要的拷贝或者移动。
	// 我们使用了...来展开可变参数列表，相当于传入了所有的参数。我们使用了ElemType()来调用元素类型的构造函数，相当于构造了一个元素对象。
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
	_top--; // 栈顶位置减一，相当于弹出了栈顶元素
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
	for (int i = 0; i <= _top; i++) // 遍历栈中的元素
	{
		data[i].~ElemType(); // 手动调用元素的析构函数，释放资源
	}
	_top = -1; // 栈顶位置置为-1，相当于清空了栈
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
		_capacity = 10; // 如果栈容量为0，则默认将栈容量置为10
	}
	else {
		_capacity *= 2; // 否则，栈容量翻倍
	}
	ElemType* newData = nullptr;
	try {
		newData = new ElemType[_capacity]; // 尝试分配新的数组空间
	}
	catch (std::bad_alloc& e) { // 捕获内存分配失败的异常
		throw std::runtime_error("Stack is full!");
	}
	std::move(data, data + _top + 1, newData); // 使用std::move将原数组data中的内容移动到newData中，避免不必要的拷贝或者析构
	if (!empty()) // 如果原来的数组存在，即栈不空，则释放原来的数组空间
	{
		clear();
		delete[] data;
	}
	data = newData; // 更新数组指针
}
