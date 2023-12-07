#pragma once

#include "Tree.h"
#include "TreeNode2.h"
#include "BinaryTreeAlgorithms.h"

namespace Hazel
{
	template <typename ElemType>
	class BinaryTree : public Tree<ElemType, TreeNode2<ElemType>>
	{
	public:
		using Tree<ElemType, TreeNode2<ElemType>>::root;

	public:
		BinaryTree();
		BinaryTree(const ElemType& val);
		BinaryTree(const BinaryTree& rhs);
		BinaryTree& operator=(const BinaryTree& rhs);
		BinaryTree(BinaryTree&& rhs) noexcept;
		BinaryTree& operator=(BinaryTree&& rhs) noexcept;
		~BinaryTree();

		TreeNode2<ElemType>* Root() const;
		bool find(const ElemType& value) const override;
		TreeNode2<ElemType>* contains(const ElemType& value) const override;
		bool empty() const override;
		void clear() override;
		const int size() const override;
		const int leaves_size() const override;
		const int height() const override;
		void print(std::ostream& os) const;
		template <typename Func> void traverse(Mode mode, Func f) const;

		bool insert(const ElemType& value) override;

	protected:
		void insert_helper(TreeNode2<ElemType>* node, const ElemType& value);
		TreeNode2<ElemType>* copy_helper(TreeNode2<ElemType>* node);
		TreeNode2<ElemType>* contains_helper(TreeNode2<ElemType>* node, const ElemType& value) const;
		void clear_helper(TreeNode2<ElemType>* node);
		int size_helper(TreeNode2<ElemType>* node) const;
		int leaves_size_helper(TreeNode2<ElemType>* node) const;
		int height_helper(TreeNode2<ElemType>* node) const;
		void print_helper(TreeNode2<ElemType>* node, std::ostream& os, int level) const;
		template <typename Func> void traverse_helper(TreeNode2<ElemType>* node, Mode mode, Func f) const;
	};
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::BinaryTree()
	: Tree<ElemType, TreeNode2<ElemType>>()
{
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::BinaryTree(const ElemType& val)
	: Tree<ElemType, TreeNode2<ElemType>>(val)
{
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::BinaryTree(const BinaryTree& rhs)
{
	if (rhs.empty())
		return;
	root = copy_helper(rhs.root);
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>& Hazel::BinaryTree<ElemType>::operator=(const BinaryTree& rhs)
{
	if (this != &rhs)
	{
		clear(); // 先清空目标树
		BinaryTree tmp(rhs); // 再调用拷贝构造函数来复制源树
		std::swap(root, tmp.root); // 再交换目标树和临时树的根节点
	}
	return *this;
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::BinaryTree(BinaryTree&& rhs) noexcept
{
	std::swap(root, rhs.root); // 直接交换目标树和源树的根节点
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>& Hazel::BinaryTree<ElemType>::operator=(BinaryTree&& rhs) noexcept
{
	if (this != &rhs)
	{
		clear(); // 先清空目标树
		std::swap(root, rhs.root); // 再交换目标树和源树的根节点
	}
	return *this;
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::~BinaryTree()
{
	clear();
}

template<typename ElemType>
inline TreeNode2<ElemType>* Hazel::BinaryTree<ElemType>::Root() const
{
	return root;
}

template<typename ElemType>
inline bool Hazel::BinaryTree<ElemType>::find(const ElemType& value) const
{
	return contains(value);
}

template<typename ElemType>
inline TreeNode2<ElemType>* Hazel::BinaryTree<ElemType>::contains(const ElemType& value) const
{
	return contains_helper(root, value);
}

template<typename ElemType>
inline bool Hazel::BinaryTree<ElemType>::empty() const
{
	return root == nullptr;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::clear()
{
	if (empty())
		return;
	clear_helper(root);
	root = nullptr;
}

template<typename ElemType>
inline const int Hazel::BinaryTree<ElemType>::size() const
{
	return size_helper(root);
}

template<typename ElemType>
inline const int Hazel::BinaryTree<ElemType>::leaves_size() const
{
	return leaves_size_helper(root);
}

template<typename ElemType>
inline const int Hazel::BinaryTree<ElemType>::height() const
{
	return height_helper(root);
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::print(std::ostream& os) const
{
	print_helper(root, os, 0);
}

template<typename ElemType>
inline bool Hazel::BinaryTree<ElemType>::insert(const ElemType& value)
{
	// 如果树为空，直接将根节点指向一个新节点
	if (empty()) {
		root = new TreeNode2<ElemType>(value);
		return true;
	}
	// 否则，调用辅助函数，从根节点开始插入
	insert_helper(root, value);
	return true;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::insert_helper(TreeNode2<ElemType>* node, const ElemType& value)
{
	// 如果节点的左子树为空，直接将左子节点指向一个新节点
	if (node->left == nullptr) {
		node->left = new TreeNode2<ElemType>(value, nullptr, nullptr, node);
		return;
	}
	// 如果节点的右子树为空，直接将右子节点指向一个新节点
	if (node->right == nullptr) {
		node->right = new TreeNode2<ElemType>(value, nullptr, nullptr, node);
		return;
	}
	// 否则，随机选择左子树或者右子树来插入
	int choice = rand() % 2;
	if (choice == 0) {
		insert_helper(node->left, value);
	}
	else {
		insert_helper(node->right, value);
	}
}

template<typename ElemType>
inline TreeNode2<ElemType>* Hazel::BinaryTree<ElemType>::copy_helper(TreeNode2<ElemType>* node)
{
	if (node == nullptr) {
		return nullptr;
	}
	// 创建一个新节点，复制当前节点的值
	TreeNode2<ElemType>* new_node = new TreeNode2<ElemType>(node->value);
	// 递归地复制左右子树，并连接到新节点
	new_node->left = copy_helper(node->left);
	new_node->right = copy_helper(node->right);
	// 返回新节点
	return new_node;
}

template<typename ElemType>
inline TreeNode2<ElemType>* Hazel::BinaryTree<ElemType>::contains_helper(TreeNode2<ElemType>* node, const ElemType& value) const
{
	if (node == nullptr) {
		return nullptr;
	}
	if (node->value == value) {
		return node;
	}
	TreeNode2<ElemType>* left_contains = contains_helper(node->left, value);
	if (left_contains != nullptr) {
		return left_contains;
	}
	TreeNode2<ElemType>* right_contains = contains_helper(node->right, value);
	return right_contains;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::clear_helper(TreeNode2<ElemType>* node)
{
	if (node == nullptr) // 如果节点为空，直接返回
		return;
	// 否则，先递归地删除左右子树
	clear_helper(node->left);
	clear_helper(node->right);
	// 再删除当前节点，并释放内存
	delete node;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::size_helper(TreeNode2<ElemType>* node) const
{
	// 如果节点为空，返回0
	if (node == nullptr) {
		return 0;
	}
	// 否则，递归地计算左右子树的节点个数，并返回总和加1
	int left_size = size_helper(node->left);
	int right_size = size_helper(node->right);
	return left_size + right_size + 1;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::leaves_size_helper(TreeNode2<ElemType>* node) const
{
	// 如果节点为空，返回0
	if (node == nullptr) {
		return 0;
	}
	// 如果节点是叶子节点，返回1
	if (node->left == nullptr && node->right == nullptr) {
		return 1;
	}
	// 否则，递归地计算左右子树的叶子节点个数，并返回总和
	int left_leaves = leaves_size_helper(node->left);
	int right_leaves = leaves_size_helper(node->right);
	return left_leaves + right_leaves;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::height_helper(TreeNode2<ElemType>* node) const
{
	if (node == nullptr)
		return 0;
	// 否则，返回节点的左右子树中较大的那个高度加一
	return std::max(height_helper(node->left), height_helper(node->right)) + 1;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::print_helper(TreeNode2<ElemType>* node, std::ostream& os, int level) const
{
	// !方案一
	// 如果节点为空，直接返回
	if (node == nullptr) {
		return;
	}
	// 否则，先递归地打印右子树
	print_helper(node->right, os, level + 1);
	// 再打印当前节点的值和位置，使用空格来表示缩进，使用/和\来表示连接和方向
	for (int i = 0; i < level; i++) {
		os << "    ";
	}
	os << node->value;
	if (node->left != nullptr && node->right != nullptr) {
		os << "<";
	}
	else if (node->right != nullptr) {
		os << "/";
	}
	else if (node->left != nullptr) {
		os << "\\";
	}
	os << std::endl;
	// 最后递归地打印左子树
	print_helper(node->left, os, level + 1);

	// !方案二
	//if (node == nullptr)
	//	return;
	//Queue<TreeNode2<ElemType>*> que;
	//que.push(node);
	//int cur_level = 1; // 记录当前层的节点数，初始为1
	//int next_level = 0; // 记录下一层的节点数，初始为0
	//int spaces = height() - 1; // 记录当前层的空格数，初始为树的高度减一
	//while (!que.empty())
	//{
	//	TreeNode2<ElemType>* cur = que.front();
	//	que.pop();
	//	// 打印当前层的空格
	//	for (int i = 0; i < spaces; ++i)
	//	{
	//		os << "   ";
	//	}
	//	// 打印节点值
	//	os << cur->value;
	//	// 如果该节点有左子节点，将它加入队尾，并将下一层的节点数加一 
	//	if (cur->left != nullptr) {
	//		que.push(cur->left);
	//		++next_level;
	//	}
	//	// 如果该节点有右子节点，也做同样的操作
	//	if (cur->right != nullptr) {
	//		que.push(cur->right);
	//		++next_level;
	//	}
	//	// 当当前层的节点数为0时，说明该层已经打印完毕，换行并更新当前层的节点数和空格数
	//	if (--cur_level == 0) { // 当前层的节点数减一
	//		// 打印换行符
	//		os << std::endl;
	//		// 重置当前层的节点数
	//		cur_level = next_level;
	//		// 重置下一层的节点数
	//		next_level = 0;
	//		// 重置空格数
	//		spaces--;
	//	}
	//}

	// !方案三
	//if (node == nullptr)
	//	return;
	//// 创建一个结构体来存储每个节点的父节点和位置信息
	//struct NodeInfo {
	//	TreeNode2<ElemType>* node; // 节点指针
	//	TreeNode2<ElemType>* parent; // 父节点指针
	//	bool is_left; // 是否是左子节点
	//	NodeInfo() = default;
	//	NodeInfo(TreeNode2<ElemType>* n, TreeNode2<ElemType>* p, bool l)
	//		: node(n), parent(p), is_left(l) {}
	//};
	//// 创建一个队列来存储每一层的节点信息
	//Queue<NodeInfo> q;
	//// 将根节点加入队列，父节点和位置信息为空
	//q.push(NodeInfo(node, nullptr, false));
	//// 记录当前层的节点数，初始为1
	//int curr_level = 1;
	//// 记录下一层的节点数，初始为0
	//int next_level = 0;
	//// 记录当前层的空格数，初始为树的高度减一
	//int spaces = height() - 1;
	//// 使用一个循环来遍历队列
	//while (!q.empty())
	//{
	//	// 取出队首的节点信息，并打印它的值和空格
	//	NodeInfo front = q.front();
	//	q.pop();
	//	// 打印当前层的空格数个空格
	//	for (int i = 0; i < spaces; i++)
	//	{
	//		os << "  ";
	//	}
	//	// 判断该节点是左子节点还是右子节点，然后打印相应的符号
	//	if (front.parent != nullptr)
	//	{
	//		if (front.is_left)
	//			os << "/";
	//		else
	//			os << "\\";
	//		os << " ";
	//	}
	//	os << front.node->value;
	//	// 如果该节点有左子节点，将它加入队尾，并将下一层的节点数加一
	//	if (front.node->left != nullptr)
	//	{
	//		q.push(NodeInfo(front.node->left, front.node, true));
	//		next_level++;
	//	}
	//	// 如果该节点有右子节点，也做同样的操作
	//	if (front.node->right != nullptr)
	//	{
	//		q.push(NodeInfo(front.node->right, front.node, false));
	//		next_level++;
	//	}
	//	// 当前层的节点数减一
	//	curr_level--;
	//	// 当当前层的节点数为0时，说明该层已经打印完毕，换行并更新当前层的节点数和空格数
	//	if (curr_level == 0)
	//	{
	//		os << std::endl;
	//		curr_level = next_level;
	//		next_level = 0;
	//		spaces--;
	//	}
	//}
}

template<typename ElemType>
template<typename Func>
inline void Hazel::BinaryTree<ElemType>::traverse(Mode mode, Func f) const
{
	traverse_helper(root, mode, f);
}

template<typename ElemType>
template<typename Func>
inline void Hazel::BinaryTree<ElemType>::traverse_helper(TreeNode2<ElemType>* node, Mode mode, Func f) const
{
	if (node == nullptr)
		return;
	if (mode == Mode::LEVELORDER) {
		Queue<TreeNode2<ElemType>*> que;
		que.push(root);
		while (!que.empty())
		{
			int size_ = que.size();
			for (int i = 0; i < size_; ++i)
			{
				TreeNode2<ElemType>* cur = que.front();
				que.pop();
				f(cur->value);
				if (cur->left)
					que.push(cur->left);
				if (cur->right)
					que.push(cur->right);
			}
		}
	}
	else if (mode == Mode::PREORDER) {
		f(node->value);
		traverse_helper(node->left, mode, f);
		traverse_helper(node->right, mode, f);
	}
	else if (mode == Mode::INORDER) {
		traverse_helper(node->left, mode, f);
		f(node->value);
		traverse_helper(node->right, mode, f);
	}
	else if (mode == Mode::POSTORDER) {
		traverse_helper(node->left, mode, f);
		traverse_helper(node->right, mode, f);
		f(node->value);
	}
	else {
		return;
	}
}
