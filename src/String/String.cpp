#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

using Hazel::String;
using Hazel::StringIterator;
using Hazel::ConstStringIterator;

// 带默认参数的构造
String::String(const char* str)
	: _size(strlen(str)), _capacity(strlen(str) + 1)
{
	data = new char[_capacity];
	std::strcpy(data, str);
}

String::String(const char ch)
	: data(new char[2]), _size(1), _capacity(2)
{
	data[0] = ch;
	data[1] = '\0';
}

String::String(int len)
	: data(new char[len + 1]), _size(len), _capacity(len + 1)
{
	data[_size] = '\0';
}

// 析构
String::~String()
{
	//std::cout << "~String() called." << std::endl;
	delete[] data;
}

// 拷贝构造
String::String(const String& rhs)
{
	//delete[] data;
	_size = rhs._size;
	_capacity = rhs._capacity;
	data = new char[_capacity];
	std::strcpy(data, rhs.data);
}

// 拷贝赋值
String& String::operator=(const String& rhs)
{
	if (this != &rhs)
	{
		delete[] data;
		_size = rhs._size;
		_capacity = rhs._capacity;
		data = new char[_capacity];
		std::strcpy(data, rhs.data);
	}
	return *this;
}

// 移动构造
String::String(String&& rhs) noexcept
{
	data = rhs.data;
	rhs.data = nullptr;
	std::swap(_size, rhs._size);
	std::swap(_capacity, rhs._capacity);
}

// 移动赋值
String& String::operator=(String&& rhs) noexcept
{
	if (this != &rhs)
	{
		delete[] data;
		data = rhs.data;
		rhs.data = nullptr;
		std::swap(_size, rhs._size);
		std::swap(_capacity, rhs._capacity);
	}
	return *this;
}

// 下标运算符，返回引用
char& String::operator[](int index)
{
	return data[index];
}

// 下标运算符，返回const引用
inline const char& String::operator[](int index) const
{
	return data[index];
}

// 返回const引用
char& String::at(int index)
{
	return data[index];
}

// 返回const引用
const char& String::at(int index) const
{
	return data[index];
}

String String::operator+(const String& str)
{
	String result = *this;
	result += str;
	return result;
}

String& String::operator+=(const String& str)
{
	if (_size + str._size >= _capacity)
	{
		if (str._size >= _size)
			addCapacity(str._size + _size + 1);
		else
			addCapacity();
	}
	int beginIndex = _size;
	int endIndex = _size + str._size;
	for (int i = beginIndex; i < endIndex; ++i)
	{
		data[i] = str.data[i - beginIndex];
	}
	data[endIndex] = '\0';
	_size += str._size;
	return *this;
}

bool String::operator<(const String& compared)
{
	return !(*this > compared) && !(*this == compared);
}

bool String::operator<(const String& compared) const
{
	return !(*this > compared) && !(*this == compared);
}

bool String::operator>(const String& compared)
{
	return compare(compared) > 0;
}

bool String::operator>(const String& compared) const
{
	return compare(compared) > 0;
}

bool String::operator>=(const String& compared)
{
	return !(*this < compared);
}

bool String::operator>=(const String& compared) const
{
	return !(*this < compared);
}

bool String::operator<=(const String& compared)
{
	return !(*this > compared);
}

bool String::operator<=(const String& compared) const
{
	return !(*this > compared);
}

bool String::operator==(const String& other)
{
	return compare(other) == 0;
}

bool String::operator==(const String& other) const
{
	return compare(other) == 0;
}

bool String::operator!=(const String& other)
{
	return !(*this == other);
}

bool String::operator!=(const String& other) const
{
	return !(*this == other);
}

// 赋值，把str的内容完整的copy到this上
void String::assign(const char* str)
{
	delete[] data;
	_size = strlen(str);
	_capacity = _size + 1;
	data = new char[_capacity];
	std::strcpy(data, str);
}

// 赋值
void String::assign(const String& str)
{
	delete[] data;
	_size = str._size;
	_capacity = _size + 1;
	data = new char[_capacity];
	// #StrCpy
	StrCpy(str);
}

void String::append(const char ch)
{
	if (_size + 1 >= _capacity)
		addCapacity();
	data[_size] = ch;
	data[_size + 1] = '\0';
	_size++;
}

// 附加str到this上
void String::append(const char* str)
{
	int len = strlen(str);
	if (_size + len >= _capacity)
	{
		addCapacity();
	}
	int beginIndex = _size;
	int endIndex = _size + len;
	for (int i = beginIndex; i < endIndex; ++i)
	{
		data[i] = str[i - beginIndex];
	}
	data[endIndex] = '\0';
	_size += len;
}

// 附加
inline void String::append(const String& str)
{
	*this += str;
}

int String::size() const
{
	return _size;
}

int String::length() const
{
	return size();
}

// 插入单个字符
void String::insert(int pos, const char ch)
{
	if (pos > _size) {
		throw std::out_of_range("String::insert() parameter out of range.");
		return;
	}
	if (_size + 1 >= _capacity)
		addCapacity();
	for (int i = _size; i > pos; --i)
	{
		data[i] = data[i - 1];
	}
	data[pos] = ch;
	data[++_size] = '\0';
}

// 插入字符串
void String::insert(int pos, const char* str)
{
	insert(pos, String(str));
}

void String::insert(int pos, const String& str)
{
	if (_size + str.size() >= _capacity)
		addCapacity();
	if (pos >= _size) {
		this->append(str);
		return;
	}
	int len = str.size();
	for (int i = _size + len - 1; i > pos + len - 1; --i)
	{
		data[i] = data[i - len];
	}
	for (int i = pos; i < pos + len; ++i)
	{
		data[i] = str[i - pos];
	}
	_size += len;
	data[_size] = '\0';
}

void Hazel::String::push_back(const char ch)
{
	append(ch);
}

void String::erase(int beginIndex, int endIndex)
{
	if (beginIndex < 0 || endIndex > _size) // 如果不合法，则直接return
		return;
	int erasedLen = endIndex - beginIndex;
	int finalLen = _size - erasedLen;
	while (finalLen--) // 从beginIndex开始，把后面的字符往前移动erasedLen个位置
	{
		data[beginIndex] = data[endIndex];
		++beginIndex;
		++endIndex;
	}
	_size -= erasedLen;
	data[_size] = '\0';
}

// 是否包含字符ch
StringIterator String::contains(const char& ch)
{
	for (int i = 0; i < _size; ++i)
		if (data[i] == ch)
			return StringIterator(this, i);
	return end();
}

// 是否包含字符串str
StringIterator String::contains(const char* needle)
{
	return contains(String(needle));
}

inline StringIterator String::contains(const String& needle)
{
	int pos = find(needle);
	if (pos == -1)
		return end();
	return begin() + pos;
}

int String::find(const char& ch) const
{
	for (int i = 0; i < _size; ++i)
		if (data[i] == ch)
			return i;
	return -1;
}

int String::find(const char* needle) const
{
	return find(String(needle));
}

// 从前往后寻找匹配字符串
int String::find(const String& needle) const
{
	if (needle.empty() || needle.size() > _size)
	{
		return -1;
	}
	Vector<int> next(needle.size());
	getNext(next, needle);
	int j = 0; // 因为next数组里记录的起始位置为0
	for (int i = 0; i < _size; i++) // 注意i就从0开始
	{
		while (j > 0 && data[i] != needle[j]) // 不匹配
		{
			j = next[j - 1]; // j 寻找之前匹配的位置
		}
		if (data[i] == needle[j]) // 匹配，j和i同时向后移动
		{
			j++; // i 的增加在for循环里
		}
		if (j == needle.size()) // 文本串s里出现了模式串needle
		{
			return (i - needle.size() + 1);
		}
	}
	return -1;
}

int String::rfind(const char& ch) const
{
	return rfind(String(ch));
}

int String::rfind(const char* str) const
{
	return rfind(String(str));
}

// 从后往前寻找匹配字符串
int String::rfind(const String& str) const
{
	if (str.empty() || str._size > _size)
		return -1;
	for (int i = _size - str._size; i >= 0; i--) // 从字符串的末尾开始向前遍历，每次调用contains方法查找子串
		if (find(str) == i)
			return i;
	return -1;
}

int String::find_first_of(const char* str) const
{
	return find_first_of(String(str));
}

int String::find_first_of(const String& str) const
{
	if (str.empty()) // 如果子串为空，返回-1
		return -1;
	return find(str);
}

int String::find_last_of(const char* str) const
{
	return find_last_of(String(str));
}

int String::find_last_of(const String& str) const
{
	if (str.empty())
		return -1;
	return rfind(str);
}

// 替换单个字符
void String::replace(const char& ch, const char replaced)
{
	if (find(ch) == -1) return;
	int index = find(ch);
	data[index] = replaced;
}

void String::replace(const char& ch, const char* replaced)
{
	replace(ch, String(replaced));
}

// 将单个字符替换成一段字符串
void String::replace(const char& ch, const String& replaced)
{
	if (find(ch) == -1) return; // 如果字符串中不包含该字符，直接返回
	if (_size - 1 + replaced.size() >= _capacity) addCapacity();
	int index = find(ch); // 获取该字符在字符串中的位置
	erase(index, index + 1);
	insert(index, replaced);
}

void String::replace(const char* str, const char* replaced)
{
	replace(str, String(replaced));
}

void String::replace(const String& str, const char* replaced)
{
	replace(str, String(replaced));
}

inline void String::replace(const char* str, const String& replaced)
{
	replace(String(str), replaced);
}

// 替换一段字符串，该字符串的长度可以是任意的
void String::replace(const String& str, const String& replaced)
{
	if (find(str) == -1) return;
	if (_size - str.size() + replaced.size() >= _capacity) addCapacity();
	int index = find(str);
	erase(index, index + str.size());
	insert(index, replaced);
	_size = _size - str.size() + replaced.size();
}

// 截取子串
String String::substr(int beginIndex, int endIndex) const
{
	if (beginIndex < 0 || endIndex > _size)
		return {};
	int subSize = endIndex - beginIndex;
	String result(subSize);
	int index = 0;
	for (int i = beginIndex; i < endIndex; ++i)
	{
		result.data[index++] = data[i];
	}
	result.data[index] = '\0';
	return result;
}

// 返回首字符
StringIterator String::begin()
{
	return StringIterator(this, 0);
}

// 返回尾字符
StringIterator String::end()
{
	return StringIterator(this, _size);
}

ConstStringIterator String::cbegin() const
{
	return ConstStringIterator(this, 0);
}

ConstStringIterator String::cend() const
{
	return ConstStringIterator(this, _size);
}

const char* String::c_str() const
{
	if (data[_size] == '\0') // 如果data指针已经以'\0'结尾，直接返回（我的设计就是C风格字符串）
		return data;
	else
		throw std::runtime_error("call c_str() error...");
	//// 否则，动态分配一个新的字符数组，并将data指针指向的内容复制过去（以防万一）
	//char* tmp = new char[_size + 1];
	//for (int i = 0; i < _size; ++i)
	//	tmp[i] = data[i];
	//tmp[_size] = '\0';
	//delete[] data;
	//data = tmp;
	//return const_cast<const char*>(data); // 返回const类型的data指针
}

// 更改大小
void String::resize(int newSize, const char ch)
{
	if (newSize == _size)
	{
		return;
	}
	if (newSize > _size)
	{
		try {
			while (newSize >= _capacity) // 直到扩大容量到足够容纳newSize才退出循环
				addCapacity();
		}
		catch (std::bad_alloc& e) {
			std::cerr << e.what() << std::endl;
			exit(1);
		}

		if (ch == '\0') {
			for (int i = _size; i < newSize; ++i) // 默认用'\0'填充剩余空间
				data[i] = '\0';
		}
		else {
			for (int i = _size; i < newSize; ++i)
				data[i] = ch;
		}
	}
	_size = newSize; // 如果newSize小于_size，直接将_size更改为newSize
	data[_size] = '\0'; // 并直接以'\0'结尾
}

// 更改预留容量
void String::reserve(int newCapacity)
{
	if (newCapacity > _size)
		addCapacity(newCapacity);
	else
		reduceCapacity(newCapacity);
}

int String::capacity()
{
	return _capacity;
}

void String::clear()
{
	_size = 0;
	data[0] = '\0';
}

bool String::empty() const
{
	return _size == 0;
}

// 打印字符串
void String::print() const
{
	for (int i = 0; i < _size; ++i) std::cout << data[i];
}

// 字符串翻转
void String::reverse()
{
	for (int i = 0, j = size() - 1; i < size() / 2; i++, j--)
	{
		std::swap(data[i], data[j]);
	}
}

// 字符串比较（若*this > target，则返回值>0；若*this == target，则返回值=0；若*this < target，则返回值<0）
int String::compare(const String& target)
{
	// 调用const版本的compare函数
	return static_cast<const String*>(this)->compare(target);
}

int String::compare(const String& target) const
{
	for (int i = 0; i < _size && i < target._size; ++i)
		if (data[i] != target.data[i])
			return data[i] - target.data[i];
	return _size - target._size;
}

// 扩展容量，默认扩展为其2倍
void String::addCapacity(int newCapacity)
{
	if (newCapacity < 0)
		throw std::invalid_argument("New capacity cannot be negative!");

	int newCap = newCapacity;
	if (newCapacity == 0) { // 如果传入的参数为0（即默认值），则扩展为原来的2倍
		newCap = _capacity * 2;
	}
	else if (newCapacity > _capacity) {
		newCap = newCapacity;
	}
	else {
		throw std::invalid_argument("New capacity cannot be less than current capacity!");
	}

	char* newData = nullptr;
	try {
		newData = new char[newCap];
	}
	catch (std::bad_alloc& e) {
		throw std::runtime_error("String is full!"); // 抛出异常
	}
	std::memcpy(newData, data, _size + 1); // 使用std::memcpy来复制数组内容，包括空字符
	std::swap(data, newData); // 使用std::swap来交换两个数组指针
	delete[] newData; // 释放原来的数组空间
	_capacity = newCap; // 更新容量
}

// 收缩容量
void String::reduceCapacity(int newCapacity)
{
	if (newCapacity > _size)
	{
		_capacity = newCapacity;
		return;
	}
	const char* tmp = data;
	delete[] data;
	data = new char[newCapacity];
	_capacity = newCapacity;
	_size = newCapacity - 1;
	std::strcpy(data, tmp);
}

// 把str复制给this
void String::StrCpy(const String& str)
{
	for (int i = 0; i < _size; ++i)
	{
		data[i] = str[i];
	}
	data[_size] = '\0';
}

// 获取next数组。用于KMP算法
void String::getNext(Vector<int>& next, const String& needle)
{
	int j = 0;
	next[0] = 0;
	for (int i = 1; i < needle.size(); i++) // 注意i从1开始
	{
		while (j > 0 && needle[i] != needle[j]) // j要保证大于0，因为下面有取j-1作为数组下标的操作
		{
			j = next[j - 1]; // 注意这里，是要找前一位的对应的回退位置了
		}
		if (needle[i] == needle[j]) // 找到相同的前后缀
		{
			j++;
		}
		next[i] = j; // 将j（前缀的长度）赋给next[i]
	}
}

std::ostream& Hazel::operator<<(std::ostream& os, const String& s)
{
	os << s.data; // 直接输出对象的数组内容，因为是C风格的字符串，所以不需要指定长度
	return os;
}

std::istream& Hazel::operator>>(std::istream& is, String& s)
{
	delete[] s.data;
	char tmp[256]; //定义一个临时的字符数组，用来存储输入的数据，可以根据需要调整大小
	is >> tmp;
	s._size = strlen(tmp);
	s.data = new char[s._size + 1];
	std::strcpy(s.data, tmp);
	return is;
}

String Hazel::operator+(const char* l, const String& r)
{
	String res = String(l) + r;
	return res;
}


namespace Hazel
{
	std::istream& getline(std::istream& is, String& str)
	{
		return is >> str;
	}

	std::istream& getline(std::istream& is, String& str, char delim)
	{
		str.clear();
		char ch;
		while (is.get(ch))
		{
			if (ch == delim || ch == EOF)
				break;
			str.append(ch);
		}
		return is;
	}

	String to_string(int val)
	{
		char buf[20];
		std::sprintf(buf, "%d", val);
		return String(buf);
	}

	String to_string(long val)
	{
		char buf[20];
		std::sprintf(buf, "%ld", val);
		return String(buf);
	}

	String to_string(long long val)
	{
		char buf[20];
		std::sprintf(buf, "%lld", val);
		return String(buf);
	}

	String to_string(unsigned val)
	{
		char buf[20];
		std::sprintf(buf, "%u", val);
		return String(buf);
	}

	String to_string(unsigned long val)
	{
		char buf[20];
		std::sprintf(buf, "%lu", val);
		return String(buf);
	}

	String to_string(unsigned long long val)
	{
		char buf[20];
		std::sprintf(buf, "%llu", val);
		return String(buf);
	}

	String to_string(float val)
	{
		char buf[20];
		std::sprintf(buf, "%f", val);
		return String(buf);
	}

	String to_string(double val)
	{
		char buf[20];
		std::sprintf(buf, "%f", val);
		return String(buf);
	}

	String to_string(long double val)
	{
		char buf[20];
		std::sprintf(buf, "%lf", val);
		return String(buf);
	}
}