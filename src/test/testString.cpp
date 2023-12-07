#include <iostream>
#include "../String/String.h"
#include "../Vector/Vector.h"

void testString()
{
	////!构造函数 和 print() 和 operator<<
	//Hazel::String s("ABCD");
	//s.print();
	//std::cout << s << std::endl;
	//std::cout << "==========================\n";

	//// !size() 和 capacity()
	//std::cout << "s.size() = " << s.size() << std::endl;
	//std::cout << "s.capacity() = " << s.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !operator[] 和 at()
	//s[0] = '1';
	//s.at(2) = '2';
	//std::cout << s << std::endl;
	//std::cout << "==========================\n";

	//// !iterator
	//for (auto& v : s) v = '6';
	//std::cout << s << std::endl;
	//std::cout << "==========================\n";

	//// !push_back() 和 append()
	//s.push_back('7');
	//s.append('1');
	//std::cout << s << std::endl;
	//std::cout << "s.size() = " << s.size() << std::endl;
	//std::cout << "s.capacity() = " << s.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !assign()
	//s.assign("12345");
	//std::cout << s << std::endl;
	//std::cout << "s.size() = " << s.size() << std::endl;
	//std::cout << "s.capacity() = " << s.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !append()
	//s.append("678910");
	//std::cout << s << std::endl;
	//std::cout << "s.size() = " << s.size() << std::endl;
	//std::cout << "s.capacity() = " << s.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !erase()
	//s.erase(0, 3);
	//std::cout << s << std::endl;
	//std::cout << "s.size() = " << s.size() << std::endl;
	//std::cout << "s.capacity() = " << s.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !compare() 和 运算符重载: < > <= >= == !=
	//Hazel::String s1("abcd");
	//Hazel::String s2("abcde");
	//if (s1.compare(s2) == 0)
	//	std::cout << "s1 == s2" << std::endl;
	//else
	//	std::cout << "s1 != s2" << std::endl;
	//if (s1 < s2)
	//	std::cout << "Yes" << std::endl;
	//else
	//	std::cout << "No" << std::endl;
	//std::cout << "==========================\n";

	//// !find() 和 rfind()
	//Hazel::String s3 = "cda";
	//if (s2.find(s3) != -1)
	//	std::cout << "Found it! With index: " << s2.find(s3) << std::endl;
	//else
	//	std::cout << "Didn't find it!" << std::endl;
	//std::cout << "==========================\n";

	//// !replace()
	//s1.replace("bcd", "bbb"); // abbb
	//std::cout << s1 << std::endl;
	//std::cout << "s1.size() = " << s1.size() << std::endl;
	//std::cout << "s1.capacity() = " << s1.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !c_str()
	//const char* str = s1.c_str();
	//std::cout << "(const char*): str = " << str << std::endl;
	//std::cout << "==========================\n";

	//// !find_first_of() 和 find_last_of()
	//char c1 = 'b';
	//if (s1.find_first_of(c1) != -1)
	//	std::cout << "Found first of \'" << c1 << "\' at " << s1.find_first_of('b') << std::endl;
	//if (s1.find_last_of(c1) != -1)
	//	std::cout << "Found last of \'" << c1 << "\' at " << s1.find_last_of('b') << std::endl;
	//std::cout << "==========================\n";

	//// !substr()
	//Hazel::String sub = s1.substr(1, 3); // [1,3)
	//std::cout << "sub = " << sub << std::endl;
	//std::cout << "sub.size() = " << sub.size() << std::endl;
	//std::cout << "sub.capacity() = " << sub.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !clear()
	//sub.clear();
	//if (sub.empty())
	//	std::cout << "sub is empty!" << std::endl;
	//std::cout << "sub.size() = " << sub.size() << std::endl;
	//std::cout << "sub.capacity() = " << sub.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !resize()
	//Hazel::String s4("abc");
	//std::cout << "before: s4 = " << s4 << std::endl;
	//s4.resize(10, 'D');
	//std::cout << "after: s4 = " << s4 << std::endl;
	//std::cout << "s4.size() = " << s4.size() << std::endl;
	//std::cout << "s4.capacity() = " << s4.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !find_first_of() 和 find_last_of()
	//Hazel::String s5("12abcdabcd");
	//std::cout << s5.find_first_of("abcd") << std::endl;
	//std::cout << s5.find_last_of("abcd") << std::endl; // ?有问题（返回的还是从前往后寻找的结果）
	//std::cout << "==========================\n";

	//// !insert
	//s5.insert(0, "000");
	//std::cout << s5 << std::endl;
	//std::cout << s5.length() << std::endl;
	//std::cout << "==========================\n";

	//// !reserve()
	//s5.reserve(100);
	//std::cout << s5.size() << std::endl;
	//std::cout << s5.capacity() << std::endl;
	//std::cout << "==========================\n";

	//// !iterator and const_iterator
	//for (Hazel::String::const_iterator it = s5.cbegin(); it != s5.cend(); ++it)
	//{
	//	std::cout << *it << std::endl;
	//}
	//std::cout << "==========================\n";

	//// !operator>> and operator<<
	//Hazel::String s6;
	//std::cin >> s6;
	//std::cout << s6 << std::endl;
	//std::cout << "==========================\n";

	//// !to_string()
	//Hazel::String s7 = Hazel::to_string(123);
	//std::cout << s7 << std::endl;
	//std::cout << "==========================\n";

	//// !getline()
	//Hazel::String s8;
	//getline(std::cin, s8, '5');
	//std::cout << s8 << std::endl;
	//std::cout << "==========================\n";

	std::cout << "Test over!" << std::endl;
}

int mainString()
{
	// test: const char* + String
	/*Hazel::String s9("456");
	s9 = "123" + s9;
	std::cout << s9 << "\n";*/

	// bug1:
	// test: Vector<String> vec(_size, "***");
	/*Hazel::Vector<Hazel::String> vec(10, "abc");
	for (const auto& v : vec)
		std::cout << v << "\n";*/

	// bug2:
	// test: 拷贝构造
	Hazel::String s10 = "123";
	std::cout << s10 << "\n";

	return 0;
}
