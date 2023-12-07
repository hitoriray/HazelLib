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
		void free();				// ����Ԫ�ز��ͷ��ڴ�
		void reallocate();			// ��ø����ڴ沢��������Ԫ��
		void alloc_n_move(std::size_t new_cap);
		void range_initialize(const T*, const T*);

	private:
		std::allocator<T> alloc; // ����Ԫ��
		T* elements;	// ָ��������Ԫ�ص�ָ��
		T* first_free;	// ָ�������һ������Ԫ�ص�ָ��
		T* cap;			// ָ������β��λ�õ�ָ��
	};

	// !���غ���
	template<typename T>
	inline std::istream& operator>>(std::istream& is, Vector<T>& vec)
	{
		int size_;
		is >> size_; // ����Vector�Ĵ�С
		vec.resize(size_); // ����Vector�Ĵ�С
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
	chk_n_alloc(); // ȷ���пռ�������Ԫ��
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
		alloc.destroy(--first_free); // �������һ��Ԫ��
	}
}

template <typename T>
std::pair<T*, T*> Hazel::Vector<T>::alloc_n_copy(const T* b, const T* e)
{
	// ����ռ䱣�������Χ�е�Ԫ��
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
	// ���ܴ��ݸ�deallocateһ����ָ�룬���elementsΪ0���ú���ʲôҲ����
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
		elements = alloc.allocate(size_); // Ϊsize_��Ԫ�ط����ڴ�
		first_free = cap = elements + size_; // ��first_free��capָ������Ϊ�����ĩβ
		std::uninitialized_fill(elements, first_free, val); // �ø���������T��ֵ�������
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
	// ����alloc_n_copy�����ڴ棬��С��rhs��Ԫ��ռ�ÿռ�һ����
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
	// �ƶ�Ԫ�أ�
	auto last = std::uninitialized_copy(std::make_move_iterator(begin()),
		std::make_move_iterator(end()), first);
	free(); // �ͷžɿռ�
	elements = first; // ����ָ��
	first_free = last;
	cap = elements + new_cap;
}

template <typename T>
void Hazel::Vector<T>::reallocate()
{
	// ���ǽ����䵱ǰ��С������еĻ������������ڴ�ռ�
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
		free(); // �ͷ�����Ԫ��
		elements = rhs.elements; // ��rhs�ӹ���Դ
		first_free = rhs.first_free;
		cap = rhs.cap;
		// ��rhs���ڿ�����״̬
		rhs.elements = rhs.first_free = rhs.cap = nullptr;
	}
	return *this;
}

// members

template <typename T>
Hazel::Vector<T>& Hazel::Vector<T>::operator=(std::initializer_list<T> il)
{
	// alloc_n_copy�����ڴ�ռ䲢�Ӹ�����Χ�ڿ���Ԫ��
	auto data = alloc_n_copy(il.begin(), il.end());
	free();					// ���ٶ����е�Ԫ�ز��ͷ��ڴ�ռ�
	elements = data.first;	// �������ݳ�Աʹ��ָ���¿ռ�
	first_free = cap = data.second;
	return *this;
}

