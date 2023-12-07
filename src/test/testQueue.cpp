#include <iostream>

#include "../Queue/Queue.h"

int main04()
{
	Hazel::Queue<int> que;

	que.push_back(1);
	que.push_back(2);
	que.push_back(3);
	que.push_back(4);
	que.push_back(5);
	que.push_front(100);
	que.push_front(200);
	que.push_front(300);

	std::cout << "#que: ";
	que.print();
	std::cout << std::endl;
	std::cout << "que.size() = " << que.size() << std::endl;
	std::cout << "que.front() = " << que.front() << std::endl;
	std::cout << "que.back() = " << que.back() << std::endl;
	que.pop_front();
	que.pop_back();
	std::cout << "#que: " << que << std::endl;
	std::cout << "que.size() = " << que.size() << std::endl;
	std::cout << "que.front() = " << que.front() << std::endl;
	std::cout << "que.back() = " << que.back() << std::endl;
	std::cout << "==========================\n";

	auto front_val = que.get_front();
	auto back_val = que.get_back();
	std::cout << front_val << ", " << back_val << std::endl;
	std::cout << "que.size() = " << que.size() << std::endl;
	std::cout << que << std::endl;
	std::cout << "==========================\n";

	Hazel::Queue<int> que2 {42, 43, 44, 45, 46};
	std::cout << "before swap:\n#que2: " << que2 << std::endl;
	Hazel::swap(que, que2);
	std::cout << "after swap:\n#que: " << que << "\n#que2: " << que2 << std::endl;
	std::cout << "==========================\n";

	que2.clear();
	std::cout << "#que2: " << que2 << std::endl;
	std::cout << "que2.size() = " << que2.size() << std::endl;
	std::cout << "==========================\n";

	return 0;
}
