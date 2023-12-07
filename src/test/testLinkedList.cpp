#include <iostream>

#include "../LinkedList/LinkedList.h"

int main01()
{
	Hazel::LinkedList<int> lst;

	// Test push_back()
	lst.push_back(1);
	lst.push_back(2);
	lst.push_back(3);
	lst.push_back(4);
	lst.push_back(5);
	// Test push_front()
	lst.push_front(10);
	// Test size()
	std::cout << "lst's size: " << lst.size() << std::endl;
	// Test print()
	std::cout << "lst: \n";
	lst.print(std::cout);
	std::cout << std::endl;
	// Test empty()
	std::cout << ((lst.empty() == true) ? "true" : "false") << std::endl;
	// Test reverse()
	lst.reverse();
	std::cout << "After reverse: \n";
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test iterator
	std::cout << "iterator range: \n";
	for (auto v : lst) std::cout << v << " ";
	std::cout << std::endl;
	std::cout << "const_iterator range: \n";
	for (const auto& v : lst) std::cout << v << " ";
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test operator[] and at()
	std::cout << "lst[0] = " << lst[0] << std::endl;
	std::cout << "lst[1] = " << lst.at(1) << std::endl;
	std::cout << "=================================\n";

	// Test erase()
	std::cout << "erased single: \n";
	lst.erase(lst.begin() + 1);
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "erased range: \n";
	lst.erase(lst.begin() + 2, lst.end());
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test contains()
	if (lst.contains(3) != lst.end()) std::cout << "lst include \'3\'";
	else std::cout << "lst doesn't include \'3\'";
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test find()
	if (lst.find(5) != -1) std::cout << "lst include \'5\'";
	else std::cout << "lst doesn't include \'5\'";
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test insert()
	lst.insert(lst.begin(), 100);
	lst.insert(lst.end(), 200);
	lst.insert(300, 1); // 把300插入到lst[1]的位置
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test pop_back() and pop_front()
	lst.pop_back();
	lst.pop_front();
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test remove()
	lst.remove(0);
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test clear()
	lst.clear();
	lst.push_back(42);
	lst.print(std::cout);
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test copy constructor
	Hazel::LinkedList<int> lst2(lst);
	std::cout << "=================================\n";

	// Test move constructor
	Hazel::LinkedList<int> lst3(std::move(lst));
	std::cout << "=================================\n";

	// Test copy assignment
	lst2 = lst3;
	std::cout << "=================================\n";

	// Test move assignment
	lst2 = std::move(lst3);
	std::cout << "=================================\n";

	// Test traverse()
	lst2.push_back(1);
	lst2.push_back(2);
	lst2.push_back(3);
	lst2.push_back(4);
	lst2.push_back(5);
	lst2.traverse([](const auto& v) { std::cout << v << " "; });
	std::cout << std::endl;
	lst2.traverse([](int& v) { v *= 2; });
	lst2.traverse([](const auto& v) { std::cout << v << " "; });
	std::cout << std::endl;
	std::cout << "=================================\n";

	// Test modify()
	lst2.modify(0, 100);
	lst2.modify(1, 200);
	lst2.modify(2, 300);
	lst2.traverse([](const auto& v) { std::cout << v << " "; });


	std::cout << "Test over!" << std::endl;
	return 0;
}