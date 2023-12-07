#include <iostream>

#include "../Vector/Vector.h"
#include "../Tree/BinaryTree.h"
#include "../Tree/BST.h"
#include "../Tree/BinaryTreeAlgorithms.h"

int main123()
{
	Hazel::BinaryTree<int> bt(10);
	bt.Root()->Left(11);
	bt.Root()->Right(12);
	bt.Root()->left->Left(13);
	bt.Root()->left->Right(14);
	bt.Root()->right->Left(15);
	bt.Root()->right->Right(16);
	bt.traverse(Hazel::LEVELORDER, [](const auto& val) { std::cout << val << " "; });
	std::cout << "\n==========================\n";

	Hazel::BST<int> bst(10);
	bst.insert(5);
	bst.insert(15);
	bst.insert(3);
	bst.insert(7);
	bst.insert(13);
	bst.insert(17);
	bst.insert(16);
	bst.insert(20);
	bst.insert(18);
	bst.traverse(Hazel::LEVELORDER, [](const auto& val) { std::cout << val << " "; });
	std::cout << "\n\n";
	bst.print(std::cout);
	std::cout << "\n==========================\n";

	bst.remove(3);
	bst.remove(17);

	if (bst.contains(20) != nullptr) {
		std::cout << "bst contains 20. And now it was modified to 200." << std::endl;
		bst.modify(20, 200);
	}
	else {
		std::cout << "bst does not contain 20." << std::endl;
	}

	bst.traverse(Hazel::LEVELORDER, [](const auto& val) { std::cout << val << " "; });
	std::cout << "\n\n";
	bst.print(std::cout);
	std::cout << std::endl;

	std::cout << "total size: " << bst.size() << std::endl;
	std::cout << "leaves size: " << bst.leaves_size() << std::endl;
	std::cout << "root's heigth: " << bst.height() << std::endl;


	return 0;
}
