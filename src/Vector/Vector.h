#pragma once

#include <iostream>
#include <memory>
#include <initializer_list>
#include <algorithm>

namespace Hazel
{
	template <typename T>
	class Vector
	{
		template <typename T>
		friend std::istream& operator>>(std::istream& is, Vector<T>& vec);
		template <typename T>
		friend std::ostream& operator<<(std::ostream& os, const Vector<T>& vec);

		template <typename T>
		friend bool operator==(const Vector<T>& lhs, const Vector<T>& rhs);
		template <typename T>
		friend bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs);

	public:
		Vector() : elements(nullptr), first_free(nullptr), cap(nullptr) {}
		Vector(int size_, const T& val = T());
		Vector(std::initializer_list<T>);
		Vector(const Vector&);
		Vector& operator=(const Vector&);
		Vector(Vector&&) noexcept;
		Vector& operator=(Vector&&) noexcept;
		Vector& operator=(std::initializer_list<T>);
		~Vector();

		// members
		void push_back(const T&);
		void push_back(T&&);
		void pop_back(const T&);

		T front() { return elements[0]; }
		const T front() const { return elements[0]; }
		T back() { return elements[size() - 1]; }
		const T back() const { return elements[size() - 1]; }

		int size() const { return first_free - elements; }
		int capacity() const { return cap - elements; }

		T* begin() { return elements; }
		T* end() { return first_free; }
		const T* cbegin() const { return elements; }
		const T* cend()   const { return first_free; }
		T& at(int pos) { return *(elements + pos); }
		T& operator[](int n) { return elements[n]; }
		const T& at(int pos)	   const { return *(elements + pos); }
		const T& operator[](int n) const { return elements[n]; }

		void reserve(int new_cap);
		void resize(int count);
		void resize(int count, const T&);
		bool empty() const;
		void clear();
		void erase(T* pos);
		void swap(Vector<T>& other);

		void print() const;

	private:
		void chk_n_alloc() { if (size() == capacity()) reallocate(); }
		std::pair<T*, T*> alloc_n_copy(const T*, const T*);
		void free();				// 销毁元素并释放内存
		void reallocate();			// 获得更多内存并拷贝已有元素
		void alloc_n_move(std::size_t new_cap);
		void range_initialize(const T*, const T*);

	private:
		std::allocator<T> alloc; // 分配元素
		T* elements;	// 指向数组首元素的指针
		T* first_free;	// 指向数组第一个空闲元素的指针
		T* cap;			// 指向数组尾后位置的指针
	};

	// !重载函数
	template<typename T>
	inline std::istream& operator>>(std::istream& is, Vector<T>& vec)
	{
		int size_;
		is >> size_; // 输入Vector的大小
		vec.resize(size_); // 调整Vector的大小
		for (int i = 0; i < size_; ++i) {
			is >> vec[i];
		}
		return is;
	}

	template<typename T>
	inline std::ostream& operator<<(std::ostream& os, const Vector<T>& vec)
	{
		os << "[";
		for (int i = 0; i < vec.size(); ++i)
		{
			os << vec[i];
			if (i != vec.size() - 1)
				os << ", ";
		}
		os << "]";
		return os;
	}

	template<typename T>
	inline bool operator==(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;
		for (int i = 0; i < lhs.size(); i++)
			if (lhs[i] != rhs[i])
				return false;
		return true;
	}

	template<typename T>
	inline bool operator!=(const Vector<T>& lhs, const Vector<T>& rhs)
	{
		return !(lhs == rhs);
	}
}

template <typename T>
void Hazel::Vector<T>::push_back(const T& t)
{
	chk_n_alloc(); // 确保有空间容纳新元素
	alloc.construct(first_free++, t);
}

template <typename T>
void Hazel::Vector<T>::push_back(T&& t)
{
	chk_n_alloc();
	alloc.construct(first_free++, std::move(t));
}

template<typename T>
inline void Hazel::Vector<T>::pop_back(const T&)
{
	if (size() > 0) {
		alloc.destroy(--first_free); // 销毁最后一个元素
	}
}

template <typename T>
std::pair<T*, T*> Hazel::Vector<T>::alloc_n_copy(const T* b, const T* e)
{
	// 分配空间保存给定范围中的元素
	auto data = alloc.allocate(e - b);
	return { data, std::uninitialized_copy(b, e, data) };
	//             ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
	// which copies the range[first, last) to the space to which
	// the starting address data is pointing.
	// This function returns a pointer to one past the last element
}

template <typename T>
void Hazel::Vector<T>::free()
{
	// 不能传递给deallocate一个空指针，如果elements为0，该函数什么也不做
	if (elements) {
		std::for_each(elements, first_free, [this](T& rhs) { alloc.destroy(&rhs); });
		alloc.deallocate(elements, capacity());
	}
}


template <typename T>
void Hazel::Vector<T>::range_initialize(const T* first, const T* last)
{
	auto newdata = alloc_n_copy(first, last);
	elements = newdata.first;
	first_free = cap = newdata.second;
}

template<typename T>
inline Hazel::Vector<T>::Vector(int size_, const T& val)
	: elements(nullptr), first_free(nullptr), cap(nullptr)
{
	if (size_ > 0)
	{
		elements = alloc.allocate(size_); // 为size_个元素分配内存
		first_free = cap = elements + size_; // 将first_free和cap指针设置为数组的末尾
		std::uninitialized_fill(elements, first_free, val); // 用给定的类型T的值填充数组
	}
}

template <typename T>
Hazel::Vector<T>::Vector(std::initializer_list<T> il)
{
	range_initialize(il.begin(), il.end());
}

template <typename T>
Hazel::Vector<T>::Vector(const Vector& rhs)
{
	range_initialize(rhs.cbegin(), rhs.cend());
}

template <typename T>
Hazel::Vector<T>::~Vector()
{
	free();
}

template <typename T>
Hazel::Vector<T>& Hazel::Vector<T>::operator=(const Vector& rhs)
{
	// 调用alloc_n_copy分配内存，大小与rhs中元素占用空间一样多
	auto data = alloc_n_copy(rhs.begin(), rhs.end());
	free();
	elements = data.first;
	first_free = cap = data.second;
	return *this;
}

template <typename T>
void Hazel::Vector<T>::alloc_n_move(std::size_t new_cap)
{
	auto first = alloc.allocate(new_cap);
	// 移动元素：
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
		std::make_move_iterator(end()), first);
	free(); // 释放旧空间
	elements = first; // 更新指针
	first_free = last;
	cap = elements + new_cap;
}

template <typename T>
void Hazel::Vector<T>::reallocate()
{
	// 我们将分配当前大小（如果有的话）的两倍的内存空间
	std::size_t newCapacity = size() ? 2 * size() : 1;
	alloc_n_move(newCapacity);
}

template <typename T>
void Hazel::Vector<T>::reserve(int new_cap)
{
	if (new_cap <= capacity())
		return;
	alloc_n_move(new_cap);
}

template <typename T>
void Hazel::Vector<T>::resize(int count)
{
	resize(count, T());
}

template <typename T>
void Hazel::Vector<T>::resize(int count, const T& t)
{
	if (count > size()) {
		if (count > capacity())
			reserve(count * 2);
		for (auto i = size(); i != count; ++i)
			alloc.construct(first_free++, t);
	}
	else if (count < size()) {
		while (first_free != elements + count)
			alloc.destroy(--first_free);
	}
}

template<typename T>
inline bool Hazel::Vector<T>::empty() const
{
	return elements == nullptr;
}

template<typename T>
inline void Hazel::Vector<T>::clear()
{
	free();
}

template<typename T>
inline void Hazel::Vector<T>::erase(T* pos)
{
	if (pos && pos < first_free) // check if pos is valid and within range
	{
		alloc.destroy(pos); // destroy the element at pos
		if (pos != first_free - 1) // if pos is not the last element
		{
			// move the elements after pos one position forward
			std::uninitialized_copy(pos + 1, first_free, pos);
		}
		--first_free; // decrement first_free pointer
	}
}

template<typename T>
inline void Hazel::Vector<T>::swap(Vector<T>& other)
{
	using std::swap; // enable ADL
	swap(elements, other.elements); // swap the elements pointers
	swap(first_free, other.first_free); // swap the first_free pointers
	swap(cap, other.cap); // swap the cap pointers
}

template<typename T>
inline void Hazel::Vector<T>::print() const
{
	std::cout << "[";
	int i = 0;
	for (; i < size() - 1; i++)
	{
		std::cout << elements[i] << ", ";
	}
	std::cout << elements[i];
	std::cout << "]";
}

template <typename T>
Hazel::Vector<T>::Vector(Vector&& v) noexcept
	: elements(v.elements), first_free(v.first_free), cap(v.cap)
{
	v.elements = v.first_free = v.cap = nullptr;
}

template <typename T>
Hazel::Vector<T>& Hazel::Vector<T>::operator=(Vector&& rhs) noexcept
{
	if (this != &rhs) {
		free(); // 释放已有元素
		elements = rhs.elements; // 从rhs接管资源
		first_free = rhs.first_free;
		cap = rhs.cap;
		// 将rhs置于可析构状态
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

// members

template <typename T>
Hazel::Vector<T>& Hazel::Vector<T>::operator=(std::initializer_list<T> il)
{
	// alloc_n_copy分配内存空间并从给定范围内拷贝元素
	auto data = alloc_n_copy(il.begin(), il.end());
	free();					// 销毁对象中的元素并释放内存空间
	elements = data.first;	// 更新数据成员使其指向新空间
	first_free = cap = data.second;
	return *this;
}

