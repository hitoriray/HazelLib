#include <iostream>

#include "../Stack/Stack.h"


int main02()
{
	Hazel::Stack<int> st;

	st.push(1);
	st.push(2);
	st.push(3);
	st.push(4);
	st.push(5);
	st.print();
	std::cout << "\n==========================\n";

	std::cout << "st.size() = " << st.size() << std::endl;
	std::cout << "st.capacity() = " << st.capacity() << std::endl;
	std::cout << "st.top() = " << st.top() << std::endl;
	st.pop();
	st.print();
	std::cout << std::endl;
	std::cout << "st.top() = " << st.top() << std::endl;
	auto val = st.get();
	std::cout << "st.get() = " << val << std::endl;
	st.print();
	std::cout << std::endl;
	if (st.full())
		std::cout << "st is full\n";
	else
		std::cout << "st is not full\n";
	std::cout << "==========================\n";

	Hazel::Stack<int> st2(st);
	st2.print();
	std::cout << "\n==========================\n";

	Hazel::Stack<int> st3;
	st3 = st2;
	st3.print();
	std::cout << "\n==========================\n";

	Hazel::Stack<int> st4(std::move(st3));
	st4.print();
	std::cout << "\n==========================\n";

	st4 = std::move(st2);
	st4.print();
	std::cout << "\n==========================\n";

	if (st == st4)
		std::cout << "st == st4\n";
	else
		std::cout << "st != st4\n";
	std::cout << "==========================\n";

	st4.push(100);
	st4.push(200);
	st4.push(300);
	std::cout << "st: " << st << std::endl;
	std::cout << "st4: " << st4 << std::endl;
	swap(st, st4);
	//st.swap(st4);
	std::cout << "After swap:\n";
	std::cout << "st: " << st << std::endl;
	std::cout << "st4: " << st4 << std::endl;
	std::cout << "==========================\n";

	st4.clear();
	if (st4.empty())
		std::cout << "st4 is empty\n";
	else
		std::cout << "st4 is not empty\n";
	st4.print();
	std::cout << "==========================\n";

	Hazel::Stack<int> st5;
	std::cin >> st5;
	std::cout << "st5: " << st5 << std::endl;


	std::cout << "Test over!" << std::endl;
	return 0;
}
