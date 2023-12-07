#pragma once

#include "BinaryTree.h"

#include "../Queue/Queue.h"

namespace Hazel
{
	template <typename ElemType, typename Comparator = std::less<ElemType>>
	class BST : public BinaryTree<ElemType>
	{
	protected:
		using BinaryTree<ElemType>::root;

	public:
		BST();
		BST(const ElemType& value);
		BST(const BST& rhs);
		BST& operator=(const BST& rhs);
		BST(BST&& rhs) noexcept;
		BST& operator=(BST&& rhs) noexcept;
		~BST() override;

		bool insert(const ElemType& new_value);
		bool remove(const ElemType& removed_value);
		bool modify(const ElemType& old_value, const ElemType& new_value);
		bool find(const ElemType& value) const;
		TreeNode2<ElemType>* contains(const ElemType& value) const;

		using BinaryTree<ElemType>::clear;
		using BinaryTree<ElemType>::empty;
		using BinaryTree<ElemType>::size;
		using BinaryTree<ElemType>::leaves_size;
		using BinaryTree<ElemType>::height;
		using BinaryTree<ElemType>::print;
		using BinaryTree<ElemType>::traverse;

	protected:
		using BinaryTree<ElemType>::insert_helper;
		using BinaryTree<ElemType>::copy_helper;
		using BinaryTree<ElemType>::contains_helper;
		using BinaryTree<ElemType>::clear_helper;
		using BinaryTree<ElemType>::size_helper;
		using BinaryTree<ElemType>::leaves_size_helper;
		using BinaryTree<ElemType>::height_helper;
		using BinaryTree<ElemType>::print_helper;
		using BinaryTree<ElemType>::traverse_helper;
	};
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>::BST()
	: BinaryTree<ElemType>()
{
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>::BST(const ElemType& value)
	: BinaryTree<ElemType>(value)
{
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>::BST(const BST& rhs)
{
	if (rhs.empty())
		return;
	root = copy_helper(rhs.root);
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>& Hazel::BST<ElemType, Comparator>::operator=(const BST& rhs)
{
	if (this != &rhs)
	{
		clear(); // 先清空目标树
		BinaryTree tmp(rhs); // 再调用拷贝构造函数来复制源树
		std::swap(root, tmp.root); // 再交换目标树和临时树的根节点
	}
	return *this;
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>::BST(BST&& rhs) noexcept
{
	std::swap(root, rhs.root); // 直接交换目标树和源树的根节点
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>& Hazel::BST<ElemType, Comparator>::operator=(BST&& rhs) noexcept
{
	if (this != &rhs)
	{
		clear();
		std::swap(root, rhs.root);
	}
	return *this;
}

template <typename ElemType, typename Comparator>
bool Hazel::BST<ElemType, Comparator>::find(const ElemType& value) const
{
	return contains(value);
}

template<typename ElemType, typename Comparator>
inline TreeNode2<ElemType>* Hazel::BST<ElemType, Comparator>::contains(const ElemType& value) const
{
	if (empty())
		return nullptr;
	Comparator comp; // 创建一个比较器对象
	TreeNode2<ElemType>* cur = root;
	while (cur) {
		if (comp(cur->value, value))
			cur = cur->right;
		else if(comp(value, cur->value))
			cur = cur->left;
		else
			return cur; // 找到了，返回该节点
	}
	return nullptr;
}

template <typename ElemType, typename Comparator>
bool Hazel::BST<ElemType, Comparator>::modify(const ElemType& old_value, const ElemType& new_value)
{
	if (old_value == new_value) {
		throw std::runtime_error("The new value is the same as the old value!");
		return false;
	}
	return remove(old_value) && insert(new_value);
}

template <typename ElemType, typename Comparator>
bool Hazel::BST<ElemType, Comparator>::remove(const ElemType& removed_value)
{
	if (empty())
		return false;

	TreeNode2<ElemType>* parent = nullptr; // 记录要删除节点的父节点
	TreeNode2<ElemType>* cur = root; // 记录当前遍历到的节点
	TreeNode2<ElemType>* target = cur; // 记录要删除的节点
	Comparator comp;
	// 寻找要删除的节点
	while (cur && cur->value != removed_value)
	{
		parent = cur;
		if (comp(removed_value, cur->value))
			cur = cur->left;
		else
			cur = cur->right;
	}
	// 如果cur为空，说明没有找到要删除的节点，直接return
	if (cur == nullptr)
	{
		return false;
	}
	// 否则，说明找到了要删除的节点，对它进行判断（三种情况）
	// 第一种情况：只有右孩子（左、右都不存在的情况和这种情况的解法一样）
	if (cur->left == nullptr)
	{
		if (cur == root) // 如果cur就是根节点的话，让根节点指向根的右子节点
		{
			root = cur->right;
		}
		else if (cur == parent->left) // 如果cur是父节点的左孩子，让父节点的左孩子指向cur的右孩子
		{
			parent->left = cur->right;
		}
		else // 如果cur是父节点的右孩子，让父节点的右孩子指向cur的右孩子
		{
			parent->right = cur->right;
		}
		target = cur; // 记录要删除的节点
	}
	// 第二种情况：只有左孩子
	else if (cur->right == nullptr)
	{
		if (cur == root) // 如果cur就是根节点的话，让根节点指向根的左子节点
		{
			root = cur->left;
		}
		else if (cur == parent->left) // 如果cur是父节点的左孩子，让父节点的左孩子指向cur的左孩子
		{
			parent->left = cur->left;
		}
		else // 如果cur是父节点的右孩子，让父节点的右孩子指向cur的左孩子
		{
			parent->right = cur->left;
		}
		target = cur; // 记录要删除的节点
	}
	else // 第三种情况：左、右孩子都存在
	{
		// 找到cur的右子树的最左节点
		TreeNode2<ElemType>* left_most = cur->right;
		parent = cur; // 记录left_most的父节点
		while (left_most->left)
		{
			parent = left_most;
			left_most = left_most->left;
		}
		target = left_most; // 记录要删除的节点
		cur->value = left_most->value; // 将left_most的值赋给cur
		// 无论left_most是否有右孩子，都可以用它的右孩子来替换它。因为它是最左节点，所以它的右孩子一定没有左孩子
		if (parent->left == left_most)
		{
			parent->left = left_most->right;
		}
		else
		{
			parent->right = left_most->right;
		}
	}
	delete target;
	return true;
}

template<typename ElemType, typename Comparator>
inline Hazel::BST<ElemType, Comparator>::~BST()
{
	clear();
}

template <typename ElemType, typename Comparator>
bool Hazel::BST<ElemType, Comparator>::insert(const ElemType& new_value)
{
	if (empty()) {
		root = new TreeNode2<ElemType>(new_value);
		return true;
	}
	TreeNode2<ElemType>* cur = root; // 使用一个指针来记录当前遍历的节点，初始为根节点
	TreeNode2<ElemType>* parent = nullptr; // 使用一个指针来记录当前遍历的节点的父节点，初始为nullptr
	Comparator comp; // 创建一个比较器对象
	while (cur) {
		parent = cur;
		if (comp(new_value, cur->value)) { // 如果新值小于当前节点的值，向左子树查找
			cur = cur->left;
		}
		else if (comp(cur->value, new_value)) { // 如果新值大于当前节点的值，向右子树查找
			cur = cur->right;
		}
		else { // 如果新值等于当前节点的值，说明已经存在该值，不需要插入，直接返回
			return false;
		}
	}
	TreeNode2<ElemType>* newNode = new TreeNode2<ElemType>(new_value);
	// 判断新节点应该插入到父节点的左边还是右边，并更新父节点的指针
	if (comp(new_value, parent->value))
		parent->left = newNode;
	else
		parent->right = newNode;

	return true;
}
