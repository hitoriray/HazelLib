#include <iostream>

#include "../Tree/RBT.h"

void testRBTree()
{
	Hazel::RBT<Hazel::String, int> rbt;
	Hazel::String key;
	while (std::cout << "��������Ҫ����Ľڵ㣺\n" && std::cin >> key)
	{
		if (key.size() == 1)
			key = "00" + key;
		else if (key.size() == 2)
			key = "0" + key;
		rbt.insert(key);
		rbt.print(std::cout);
	}
}

int mainRBT()
{
	testRBTree();

	return 0;
}