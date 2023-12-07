#pragma warning(disable:4996)
#define _CRT_SECURE_NO_WARNINGS
#pragma once

#include <iostream>
#include "../Vector/Vector.h"

namespace Hazel
{
	class StringIterator;
	class ConstStringIterator;

	class String
	{
		friend class StringIterator;
		friend class ConstStringIterator;

		friend std::ostream& operator<<(std::ostream& os, const String& str);
		friend std::istream& operator>>(std::istream& is, String& str);
		friend String operator+(const char* l, const String& r);

	public:
		String(const char* str = "");
		String(const char ch);
		String(int len);
		~String();
		String(const String& rhs);
		String& operator=(const String& rhs);
		String(String&& rhs) noexcept;
		String& operator=(String&& rhs) noexcept;

		char& operator[](int index);
		const char& operator[](int index) const;
		char& at(int index);
		const char& at(int index) const;

		String operator+(const String& str);
		String& operator+=(const String& str);

		// 提供运算符重载（新增const版本）
		bool operator>(const String& compared);
		bool operator>(const String& compared) const;

		bool operator<(const String& compared);
		bool operator<(const String& compared) const;

		bool operator>=(const String& compared);
		bool operator>=(const String& compared) const;

		bool operator<=(const String& compared);
		bool operator<=(const String& compared) const;

		bool operator==(const String& other);
		bool operator==(const String& other) const;

		bool operator!=(const String& other);
		bool operator!=(const String& other) const;

		int size() const;
		int length() const;

		void assign(const char* str);
		void assign(const String& str);

		void append(const char ch);
		void append(const char* str);
		void append(const String& str);

		void insert(int pos, const char ch);
		void insert(int pos, const char* str);
		void insert(int pos, const String& str);

		void push_back(const char ch);

		void erase(int beginIndex, int endIndex); // 左闭右开

		using iterator = StringIterator;
		using const_iterator = ConstStringIterator;

		iterator contains(const char& ch);
		iterator contains(const char* str);
		iterator contains(const String& str);

		int find(const char& ch) const;
		int find(const char* str) const;
		int find(const String& str) const;
		int rfind(const char& ch) const;
		int rfind(const char* str) const;
		int rfind(const String& str) const;

		int find_first_of(const char* str) const;
		int find_first_of(const String& str) const;
		int find_last_of(const char* str) const;
		int find_last_of(const String& str) const;


		void replace(const char& ch, const char replaced);
		void replace(const char& ch, const char* replaced);
		void replace(const char& ch, const String& replaced);
		void replace(const char* str, const char* replaced);
		void replace(const String& str, const char* replaced);
		void replace(const char* str, const String& replaced);
		void replace(const String& str, const String& replaced);

		String substr(int beginIndex, int endIndex) const; // 左闭右开
		iterator begin();
		iterator end();
		const_iterator cbegin() const;
		const_iterator cend() const;
		const char* c_str() const;
		void resize(int newSize, const char ch = '\0');
		void reserve(int newCapacity);
		int capacity();
		void clear();
		bool empty() const;
		void reverse();
		int compare(const String& target);
		int compare(const String& target) const;

		void print() const;

	private:
		void addCapacity(int newCapacity = 0);
		void reduceCapacity(int newCapacity);
		void StrCpy(const String& str);
		static void getNext(Vector<int>& next, const String& needle);

	private:
		char* data;
		int _size;
		int _capacity;
	};

	// 迭代器
	class StringIterator
	{
	public:
		StringIterator(String* str, int index)
			: _str(str), _index(index) {}

		char& operator*() {
			return (*_str)[_index];
		}

		StringIterator& operator++() {
			_index++;
			return *this;
		}

		StringIterator operator++(int) {
			StringIterator temp(*this);
			_index++;
			return temp;
		}

		StringIterator& operator--() {
			_index--;
			return *this;
		}

		StringIterator operator--(int) {
			StringIterator temp(*this);
			_index--;
			return temp;
		}

		StringIterator operator+(int n) const {
			return StringIterator(_str, _index + n);
		}

		StringIterator operator-(int n) const {
			return StringIterator(_str, _index - n);
		}

		StringIterator& operator+=(int n) {
			_index += n;
			return *this;
		}

		StringIterator& operator-=(int n) {
			_index -= n;
			return *this;
		}

		char& operator[](int n) {
			return (*_str)[_index + n];
		}

		bool operator==(const StringIterator& rhs) const {
			return _index == rhs._index;
		}

		bool operator!=(const StringIterator& rhs) const {
			return _index != rhs._index;
		}

	private:
		String* _str;
		int _index;
	};

	// 常量迭代器
	class ConstStringIterator {
	public:
		ConstStringIterator(const String* str, int index)
			: _str(str), _index(index) {}

		const char& operator*() const {
			return (*_str)[_index];
		}

		ConstStringIterator& operator++() {
			_index++;
			return *this;
		}

		ConstStringIterator operator++(int) {
			ConstStringIterator temp(*this);
			_index++;
			return temp;
		}

		ConstStringIterator& operator--() {
			_index--;
			return *this;
		}

		ConstStringIterator operator--(int) {
			ConstStringIterator temp(*this);
			_index--;
			return temp;
		}

		ConstStringIterator operator+(int n) const {
			return ConstStringIterator(_str, _index + n);
		}

		ConstStringIterator operator-(int n) const {
			return ConstStringIterator(_str, _index - n);
		}

		ConstStringIterator& operator+=(int n) {
			_index += n;
			return *this;
		}

		ConstStringIterator& operator-=(int n) {
			_index -= n;
			return *this;
		}

		const char& operator[](int n) const {
			return (*_str)[_index + n];
		}

		bool operator==(const ConstStringIterator& rhs) const {
			return _index == rhs._index;
		}

		bool operator!=(const ConstStringIterator& rhs) const {
			return _index != rhs._index;
		}

	private:
		const String* _str;
		int _index;
	};


	String to_string(int val);
	String to_string(long val);
	String to_string(long long val);
	String to_string(unsigned val);
	String to_string(unsigned long val);
	String to_string(unsigned long long val);
	String to_string(float val);
	String to_string(double val);
	String to_string(long double val);

	std::istream& getline(std::istream& is, String& str); // 碰到'\n' 停止读取
	std::istream& getline(std::istream& is, String& str, char delim); // 碰到delim停止读取
}