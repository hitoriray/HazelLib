#define _CRT_SECURE_NO_WARNINGS

#include "String.h"

using Hazel::String;
using Hazel::StringIterator;
using Hazel::ConstStringIterator;

// ��Ĭ�ϲ����Ĺ���
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

// ����
String::~String()
{
	//std::cout << "~String() called." << std::endl;
	delete[] data;
}

// ��������
String::String(const String& rhs)
{
	//delete[] data;
	_size = rhs._size;
	_capacity = rhs._capacity;
	data = new char[_capacity];
	std::strcpy(data, rhs.data);
}

// ������ֵ
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

// �ƶ�����
String::String(String&& rhs) noexcept
{
	data = rhs.data;
	rhs.data = nullptr;
	std::swap(_size, rhs._size);
	std::swap(_capacity, rhs._capacity);
}

// �ƶ���ֵ
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

// �±����������������
char& String::operator[](int index)
{
	return data[index];
}

// �±������������const����
inline const char& String::operator[](int index) const
{
	return data[index];
}

// ����const����
char& String::at(int index)
{
	return data[index];
}

// ����const����
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

// ��ֵ����str������������copy��this��
void String::assign(const char* str)
{
	delete[] data;
	_size = strlen(str);
	_capacity = _size + 1;
	data = new char[_capacity];
	std::strcpy(data, str);
}

// ��ֵ
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

// ����str��this��
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

// ����
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

// ���뵥���ַ�
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

// �����ַ���
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
	if (beginIndex < 0 || endIndex > _size) // ������Ϸ�����ֱ��return
		return;
	int erasedLen = endIndex - beginIndex;
	int finalLen = _size - erasedLen;
	while (finalLen--) // ��beginIndex��ʼ���Ѻ�����ַ���ǰ�ƶ�erasedLen��λ��
	{
		data[beginIndex] = data[endIndex];
		++beginIndex;
		++endIndex;
	}
	_size -= erasedLen;
	data[_size] = '\0';
}

// �Ƿ�����ַ�ch
StringIterator String::contains(const char& ch)
{
	for (int i = 0; i < _size; ++i)
		if (data[i] == ch)
			return StringIterator(this, i);
	return end();
}

// �Ƿ�����ַ���str
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

// ��ǰ����Ѱ��ƥ���ַ���
int String::find(const String& needle) const
{
	if (needle.empty() || needle.size() > _size)
	{
		return -1;
	}
	Vector<int> next(needle.size());
	getNext(next, needle);
	int j = 0; // ��Ϊnext�������¼����ʼλ��Ϊ0
	for (int i = 0; i < _size; i++) // ע��i�ʹ�0��ʼ
	{
		while (j > 0 && data[i] != needle[j]) // ��ƥ��
		{
			j = next[j - 1]; // j Ѱ��֮ǰƥ���λ��
		}
		if (data[i] == needle[j]) // ƥ�䣬j��iͬʱ����ƶ�
		{
			j++; // i ��������forѭ����
		}
		if (j == needle.size()) // �ı���s�������ģʽ��needle
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

// �Ӻ���ǰѰ��ƥ���ַ���
int String::rfind(const String& str) const
{
	if (str.empty() || str._size > _size)
		return -1;
	for (int i = _size - str._size; i >= 0; i--) // ���ַ�����ĩβ��ʼ��ǰ������ÿ�ε���contains���������Ӵ�
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
	if (str.empty()) // ����Ӵ�Ϊ�գ�����-1
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

// �滻�����ַ�
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

// �������ַ��滻��һ���ַ���
void String::replace(const char& ch, const String& replaced)
{
	if (find(ch) == -1) return; // ����ַ����в��������ַ���ֱ�ӷ���
	if (_size - 1 + replaced.size() >= _capacity) addCapacity();
	int index = find(ch); // ��ȡ���ַ����ַ����е�λ��
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

// �滻һ���ַ��������ַ����ĳ��ȿ����������
void String::replace(const String& str, const String& replaced)
{
	if (find(str) == -1) return;
	if (_size - str.size() + replaced.size() >= _capacity) addCapacity();
	int index = find(str);
	erase(index, index + str.size());
	insert(index, replaced);
	_size = _size - str.size() + replaced.size();
}

// ��ȡ�Ӵ�
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

// �������ַ�
StringIterator String::begin()
{
	return StringIterator(this, 0);
}

// ����β�ַ�
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
	if (data[_size] == '\0') // ���dataָ���Ѿ���'\0'��β��ֱ�ӷ��أ��ҵ���ƾ���C����ַ�����
		return data;
	else
		throw std::runtime_error("call c_str() error...");
	//// ���򣬶�̬����һ���µ��ַ����飬����dataָ��ָ������ݸ��ƹ�ȥ���Է���һ��
	//char* tmp = new char[_size + 1];
	//for (int i = 0; i < _size; ++i)
	//	tmp[i] = data[i];
	//tmp[_size] = '\0';
	//delete[] data;
	//data = tmp;
	//return const_cast<const char*>(data); // ����const���͵�dataָ��
}

// ���Ĵ�С
void String::resize(int newSize, const char ch)
{
	if (newSize == _size)
	{
		return;
	}
	if (newSize > _size)
	{
		try {
			while (newSize >= _capacity) // ֱ�������������㹻����newSize���˳�ѭ��
				addCapacity();
		}
		catch (std::bad_alloc& e) {
			std::cerr << e.what() << std::endl;
			exit(1);
		}

		if (ch == '\0') {
			for (int i = _size; i < newSize; ++i) // Ĭ����'\0'���ʣ��ռ�
				data[i] = '\0';
		}
		else {
			for (int i = _size; i < newSize; ++i)
				data[i] = ch;
		}
	}
	_size = newSize; // ���newSizeС��_size��ֱ�ӽ�_size����ΪnewSize
	data[_size] = '\0'; // ��ֱ����'\0'��β
}

// ����Ԥ������
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

// ��ӡ�ַ���
void String::print() const
{
	for (int i = 0; i < _size; ++i) std::cout << data[i];
}

// �ַ�����ת
void String::reverse()
{
	for (int i = 0, j = size() - 1; i < size() / 2; i++, j--)
	{
		std::swap(data[i], data[j]);
	}
}

// �ַ����Ƚϣ���*this > target���򷵻�ֵ>0����*this == target���򷵻�ֵ=0����*this < target���򷵻�ֵ<0��
int String::compare(const String& target)
{
	// ����const�汾��compare����
	return static_cast<const String*>(this)->compare(target);
}

int String::compare(const String& target) const
{
	for (int i = 0; i < _size && i < target._size; ++i)
		if (data[i] != target.data[i])
			return data[i] - target.data[i];
	return _size - target._size;
}

// ��չ������Ĭ����չΪ��2��
void String::addCapacity(int newCapacity)
{
	if (newCapacity < 0)
		throw std::invalid_argument("New capacity cannot be negative!");

	int newCap = newCapacity;
	if (newCapacity == 0) { // �������Ĳ���Ϊ0����Ĭ��ֵ��������չΪԭ����2��
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
		throw std::runtime_error("String is full!"); // �׳��쳣
	}
	std::memcpy(newData, data, _size + 1); // ʹ��std::memcpy�������������ݣ��������ַ�
	std::swap(data, newData); // ʹ��std::swap��������������ָ��
	delete[] newData; // �ͷ�ԭ��������ռ�
	_capacity = newCap; // ��������
}

// ��������
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

// ��str���Ƹ�this
void String::StrCpy(const String& str)
{
	for (int i = 0; i < _size; ++i)
	{
		data[i] = str[i];
	}
	data[_size] = '\0';
}

// ��ȡnext���顣����KMP�㷨
void String::getNext(Vector<int>& next, const String& needle)
{
	int j = 0;
	next[0] = 0;
	for (int i = 1; i < needle.size(); i++) // ע��i��1��ʼ
	{
		while (j > 0 && needle[i] != needle[j]) // jҪ��֤����0����Ϊ������ȡj-1��Ϊ�����±�Ĳ���
		{
			j = next[j - 1]; // ע�������Ҫ��ǰһλ�Ķ�Ӧ�Ļ���λ����
		}
		if (needle[i] == needle[j]) // �ҵ���ͬ��ǰ��׺
		{
			j++;
		}
		next[i] = j; // ��j��ǰ׺�ĳ��ȣ�����next[i]
	}
}

std::ostream& Hazel::operator<<(std::ostream& os, const String& s)
{
	os << s.data; // ֱ�����������������ݣ���Ϊ��C�����ַ��������Բ���Ҫָ������
	return os;
}

std::istream& Hazel::operator>>(std::istream& is, String& s)
{
	delete[] s.data;
	char tmp[256]; //����һ����ʱ���ַ����飬�����洢��������ݣ����Ը�����Ҫ������С
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