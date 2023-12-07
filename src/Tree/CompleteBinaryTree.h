#pragma once

#include "BinaryTree.h"

#define VERIFY_EMPTY if(empty()) {\
	throw std::runtime_error("Tree is empty!");\
	return false;\
}\

namespace Hazel
{
	template <typename ElemType>
	class CompleteBinaryTree : public BinaryTree<ElemType>
	{
	protected:
		using BinaryTree<ElemType>::root;

	public:
		CompleteBinaryTree();
		CompleteBinaryTree(std::initializer_list<ElemType> il);
		~CompleteBinaryTree();

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

template <typename ElemType>
Hazel::CompleteBinaryTree<ElemType>::CompleteBinaryTree()
	: BinaryTree<ElemType>()
{
}

template <typename ElemType>
Hazel::CompleteBinaryTree<ElemType>::CompleteBinaryTree(std::initializer_list<ElemType> il)
	: BinaryTree<ElemType>()
{
	for (const ElemType& elem : il)
		insert(elem);
}

template <typename ElemType>
Hazel::CompleteBinaryTree<ElemType>::~CompleteBinaryTree()
{
	~BinaryTree<ElemType>(); // 直接调用父类的析构
}

template <typename ElemType>
bool Hazel::CompleteBinaryTree<ElemType>::insert(const ElemType& new_value)
{
	if (empty()) {
		root = new TreeNode2<ElemType>(new_value);
		return true;
	}
	// 层序遍历，找到第一个子节点不满的节点
	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	TreeNode2<ElemType>* new_node = new TreeNode2<ElemType>(new_value);
	while (!que.empty())
	{
		int _size = que.size();
		for (int i = 0; i < _size; i++)
		{
			auto cur = que.front();
			que.pop();
			// 找到第一个子节点不满的节点：
			// 如果该节点左子节点不存在，则将其添加到该节点的左子节点
			if (!cur->left) {
				cur->left = new_node;
				return true;
			}
			// 同理，如果该节点右子节点不存在，则将其添加到该节点的右子节点
			if (!cur->right) {
				cur->right = new_node;
				return true;
			}
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
	}
	return false;
}

template<typename ElemType>
inline bool Hazel::CompleteBinaryTree<ElemType>::remove(const ElemType& removed_value)
{
	VERIFY_EMPTY

	// 获取最后一个叶子节点
	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	TreeNode2<ElemType>* cur = root; // 记录要删除的节点
	while (!que.empty())
	{
		int n = que.size();
		for (int i = 0; i < n; i++)
		{
			cur = que.front();
			que.pop();
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
	}
	delete cur; // 删除节点
	return true;
}

template<typename ElemType>
inline bool Hazel::CompleteBinaryTree<ElemType>::modify(const ElemType& old_value, const ElemType& new_value)
{
	VERIFY_EMPTY

	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	while (!que.empty())
	{
		int n = que.size();
		for (int i = 0; i < n; i++)
		{
			TreeNode2<ElemType>* cur = que.front();
			if (cur->value == old_value) {
				cur->value = new_value;
				return true;
			}
			que.pop();
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
	}
	return false;
}

template<typename ElemType>
inline bool Hazel::CompleteBinaryTree<ElemType>::find(const ElemType& value) const
{
	VERIFY_EMPTY

	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	while (!que.empty())
	{
		int n = que.size();
		for (int i = 0; i < n; i++)
		{
			TreeNode2<ElemType>* cur = que.front();
			if (cur->value == value) {
				return true;
			}
			que.pop();
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
	}
	return false;
}

template<typename ElemType>
inline TreeNode2<ElemType>* Hazel::CompleteBinaryTree<ElemType>::contains(const ElemType& value) const
{
	if (empty()) {
		throw std::runtime_error("Tree is empty!");
		return nullptr;
	}

	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	while (!que.empty())
	{
		int n = que.size();
		for (int i = 0; i < n; i++)
		{
			TreeNode2<ElemType>* cur = que.front();
			if (cur->value == value) {
				return cur;
			}
			que.pop();
			if (cur->left)
				que.push(cur->left);
			if (cur->right)
				que.push(cur->right);
		}
	}
	return nullptr;
}
