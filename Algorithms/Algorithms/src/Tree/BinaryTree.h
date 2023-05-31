#pragma once

#include <string>

#include "Tree.h"

template <typename T>
class TreeNode2
{
public:
	T value;
	TreeNode2* left, right;
	TreeNode2(T value_) : value(value_), left(nullptr), right(nullptr) {}
};

template <typename T>
class BinaryTree : public Tree<T, TreeNode2<T>>
{
protected:
	using Tree<T, TreeNode2<T>>::root;
public:
	BinaryTree() : Tree<T, TreeNode2<T>>() {}
	BinaryTree(const BinaryTree& rhs) = default;
	BinaryTree& operator=(const BinaryTree& rhs) = default;
	BinaryTree(BinaryTree&& rhs) noexcept = default;
	BinaryTree& operator=(BinaryTree&& rhs) noexcept = default;
	~BinaryTree() override { delete root; }

	void CreateTree() override;
	int GetDepth() override;
	
	// !基础操作
	void insert() override;
	void remove() override;
	void modify() override;
	void find() override;
	bool empty() override;
	void clear() override;
	void destroy() override;
	int GetNodes() override;
	int GetLeaves() override;

	// !算法
	std::vector<T> preorderTraverse() override;
	std::vector<T> morrisPre();
	std::vector<T> inorderTraverse() override;
	std::vector<T> morrisIn();
	std::vector<T> postorderTraverse() override;
	std::vector<T> morrisPost();
	std::vector<std::vector<T>> levelOrder() override;
	std::vector<std::vector<T>> levelOrderBottom() override;
	std::vector<double> averageOfLevels();
	std::vector<int> largestLevelValues();
	int maxDepth();
	int minDepth();
	BinaryTree* invertTree();
	bool isSymmetric();
	bool isSameTree(BinaryTree* other);
	bool isSubTree(BinaryTree* subTree);
	bool isBalanced();
	std::vector<std::string> binaryTreePaths();

private:
	void Init() override;
	void preorder_traversal();
	void inorder_traversal();
	void postorder_traversal();
	void level_order_traversal();
	// 以下两个函数均用于 morris后序遍历
	void dealEdge(std::vector<int>& result);
	BinaryTree* reverseEdge();
};
