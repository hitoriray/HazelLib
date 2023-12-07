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
	~BinaryTree<ElemType>(); // ֱ�ӵ��ø��������
}

template <typename ElemType>
bool Hazel::CompleteBinaryTree<ElemType>::insert(const ElemType& new_value)
{
	if (empty()) {
		root = new TreeNode2<ElemType>(new_value);
		return true;
	}
	// ����������ҵ���һ���ӽڵ㲻���Ľڵ�
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
			// �ҵ���һ���ӽڵ㲻���Ľڵ㣺
			// ����ýڵ����ӽڵ㲻���ڣ�������ӵ��ýڵ�����ӽڵ�
			if (!cur->left) {
				cur->left = new_node;
				return true;
			}
			// ͬ������ýڵ����ӽڵ㲻���ڣ�������ӵ��ýڵ�����ӽڵ�
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

	// ��ȡ���һ��Ҷ�ӽڵ�
	Queue<TreeNode2<ElemType>*> que;
	que.push(root);
	TreeNode2<ElemType>* cur = root; // ��¼Ҫɾ���Ľڵ�
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
	delete cur; // ɾ���ڵ�
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
