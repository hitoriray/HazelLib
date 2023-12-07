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
		clear(); // �����Ŀ����
		BinaryTree tmp(rhs); // �ٵ��ÿ������캯��������Դ��
		std::swap(root, tmp.root); // �ٽ���Ŀ��������ʱ���ĸ��ڵ�
	}
	return *this;
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>::BinaryTree(BinaryTree&& rhs) noexcept
{
	std::swap(root, rhs.root); // ֱ�ӽ���Ŀ������Դ���ĸ��ڵ�
}

template<typename ElemType>
inline Hazel::BinaryTree<ElemType>& Hazel::BinaryTree<ElemType>::operator=(BinaryTree&& rhs) noexcept
{
	if (this != &rhs)
	{
		clear(); // �����Ŀ����
		std::swap(root, rhs.root); // �ٽ���Ŀ������Դ���ĸ��ڵ�
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
	// �����Ϊ�գ�ֱ�ӽ����ڵ�ָ��һ���½ڵ�
	if (empty()) {
		root = new TreeNode2<ElemType>(value);
		return true;
	}
	// ���򣬵��ø����������Ӹ��ڵ㿪ʼ����
	insert_helper(root, value);
	return true;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::insert_helper(TreeNode2<ElemType>* node, const ElemType& value)
{
	// ����ڵ��������Ϊ�գ�ֱ�ӽ����ӽڵ�ָ��һ���½ڵ�
	if (node->left == nullptr) {
		node->left = new TreeNode2<ElemType>(value, nullptr, nullptr, node);
		return;
	}
	// ����ڵ��������Ϊ�գ�ֱ�ӽ����ӽڵ�ָ��һ���½ڵ�
	if (node->right == nullptr) {
		node->right = new TreeNode2<ElemType>(value, nullptr, nullptr, node);
		return;
	}
	// �������ѡ������������������������
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
	// ����һ���½ڵ㣬���Ƶ�ǰ�ڵ��ֵ
	TreeNode2<ElemType>* new_node = new TreeNode2<ElemType>(node->value);
	// �ݹ�ظ������������������ӵ��½ڵ�
	new_node->left = copy_helper(node->left);
	new_node->right = copy_helper(node->right);
	// �����½ڵ�
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
	if (node == nullptr) // ����ڵ�Ϊ�գ�ֱ�ӷ���
		return;
	// �����ȵݹ��ɾ����������
	clear_helper(node->left);
	clear_helper(node->right);
	// ��ɾ����ǰ�ڵ㣬���ͷ��ڴ�
	delete node;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::size_helper(TreeNode2<ElemType>* node) const
{
	// ����ڵ�Ϊ�գ�����0
	if (node == nullptr) {
		return 0;
	}
	// ���򣬵ݹ�ؼ������������Ľڵ�������������ܺͼ�1
	int left_size = size_helper(node->left);
	int right_size = size_helper(node->right);
	return left_size + right_size + 1;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::leaves_size_helper(TreeNode2<ElemType>* node) const
{
	// ����ڵ�Ϊ�գ�����0
	if (node == nullptr) {
		return 0;
	}
	// ����ڵ���Ҷ�ӽڵ㣬����1
	if (node->left == nullptr && node->right == nullptr) {
		return 1;
	}
	// ���򣬵ݹ�ؼ�������������Ҷ�ӽڵ�������������ܺ�
	int left_leaves = leaves_size_helper(node->left);
	int right_leaves = leaves_size_helper(node->right);
	return left_leaves + right_leaves;
}

template<typename ElemType>
inline int Hazel::BinaryTree<ElemType>::height_helper(TreeNode2<ElemType>* node) const
{
	if (node == nullptr)
		return 0;
	// ���򣬷��ؽڵ�����������нϴ���Ǹ��߶ȼ�һ
	return std::max(height_helper(node->left), height_helper(node->right)) + 1;
}

template<typename ElemType>
inline void Hazel::BinaryTree<ElemType>::print_helper(TreeNode2<ElemType>* node, std::ostream& os, int level) const
{
	// !����һ
	// ����ڵ�Ϊ�գ�ֱ�ӷ���
	if (node == nullptr) {
		return;
	}
	// �����ȵݹ�ش�ӡ������
	print_helper(node->right, os, level + 1);
	// �ٴ�ӡ��ǰ�ڵ��ֵ��λ�ã�ʹ�ÿո�����ʾ������ʹ��/��\����ʾ���Ӻͷ���
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
	// ���ݹ�ش�ӡ������
	print_helper(node->left, os, level + 1);

	// !������
	//if (node == nullptr)
	//	return;
	//Queue<TreeNode2<ElemType>*> que;
	//que.push(node);
	//int cur_level = 1; // ��¼��ǰ��Ľڵ�������ʼΪ1
	//int next_level = 0; // ��¼��һ��Ľڵ�������ʼΪ0
	//int spaces = height() - 1; // ��¼��ǰ��Ŀո�������ʼΪ���ĸ߶ȼ�һ
	//while (!que.empty())
	//{
	//	TreeNode2<ElemType>* cur = que.front();
	//	que.pop();
	//	// ��ӡ��ǰ��Ŀո�
	//	for (int i = 0; i < spaces; ++i)
	//	{
	//		os << "   ";
	//	}
	//	// ��ӡ�ڵ�ֵ
	//	os << cur->value;
	//	// ����ýڵ������ӽڵ㣬���������β��������һ��Ľڵ�����һ 
	//	if (cur->left != nullptr) {
	//		que.push(cur->left);
	//		++next_level;
	//	}
	//	// ����ýڵ������ӽڵ㣬Ҳ��ͬ���Ĳ���
	//	if (cur->right != nullptr) {
	//		que.push(cur->right);
	//		++next_level;
	//	}
	//	// ����ǰ��Ľڵ���Ϊ0ʱ��˵���ò��Ѿ���ӡ��ϣ����в����µ�ǰ��Ľڵ����Ϳո���
	//	if (--cur_level == 0) { // ��ǰ��Ľڵ�����һ
	//		// ��ӡ���з�
	//		os << std::endl;
	//		// ���õ�ǰ��Ľڵ���
	//		cur_level = next_level;
	//		// ������һ��Ľڵ���
	//		next_level = 0;
	//		// ���ÿո���
	//		spaces--;
	//	}
	//}

	// !������
	//if (node == nullptr)
	//	return;
	//// ����һ���ṹ�����洢ÿ���ڵ�ĸ��ڵ��λ����Ϣ
	//struct NodeInfo {
	//	TreeNode2<ElemType>* node; // �ڵ�ָ��
	//	TreeNode2<ElemType>* parent; // ���ڵ�ָ��
	//	bool is_left; // �Ƿ������ӽڵ�
	//	NodeInfo() = default;
	//	NodeInfo(TreeNode2<ElemType>* n, TreeNode2<ElemType>* p, bool l)
	//		: node(n), parent(p), is_left(l) {}
	//};
	//// ����һ���������洢ÿһ��Ľڵ���Ϣ
	//Queue<NodeInfo> q;
	//// �����ڵ������У����ڵ��λ����ϢΪ��
	//q.push(NodeInfo(node, nullptr, false));
	//// ��¼��ǰ��Ľڵ�������ʼΪ1
	//int curr_level = 1;
	//// ��¼��һ��Ľڵ�������ʼΪ0
	//int next_level = 0;
	//// ��¼��ǰ��Ŀո�������ʼΪ���ĸ߶ȼ�һ
	//int spaces = height() - 1;
	//// ʹ��һ��ѭ������������
	//while (!q.empty())
	//{
	//	// ȡ�����׵Ľڵ���Ϣ������ӡ����ֵ�Ϳո�
	//	NodeInfo front = q.front();
	//	q.pop();
	//	// ��ӡ��ǰ��Ŀո������ո�
	//	for (int i = 0; i < spaces; i++)
	//	{
	//		os << "  ";
	//	}
	//	// �жϸýڵ������ӽڵ㻹�����ӽڵ㣬Ȼ���ӡ��Ӧ�ķ���
	//	if (front.parent != nullptr)
	//	{
	//		if (front.is_left)
	//			os << "/";
	//		else
	//			os << "\\";
	//		os << " ";
	//	}
	//	os << front.node->value;
	//	// ����ýڵ������ӽڵ㣬���������β��������һ��Ľڵ�����һ
	//	if (front.node->left != nullptr)
	//	{
	//		q.push(NodeInfo(front.node->left, front.node, true));
	//		next_level++;
	//	}
	//	// ����ýڵ������ӽڵ㣬Ҳ��ͬ���Ĳ���
	//	if (front.node->right != nullptr)
	//	{
	//		q.push(NodeInfo(front.node->right, front.node, false));
	//		next_level++;
	//	}
	//	// ��ǰ��Ľڵ�����һ
	//	curr_level--;
	//	// ����ǰ��Ľڵ���Ϊ0ʱ��˵���ò��Ѿ���ӡ��ϣ����в����µ�ǰ��Ľڵ����Ϳո���
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
