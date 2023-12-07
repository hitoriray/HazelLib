#pragma once

#include "CompleteBinaryTree.h"
#include <cmath>

namespace Hazel
{
	template <typename ElemType>
	class PerfectBinaryTree : public CompleteBinaryTree<ElemType>
	{
	protected:
		using CompleteBinaryTree<ElemType>::root;

	public:
		PerfectBinaryTree();
		PerfectBinaryTree(std::initializer_list<ElemType> il);
		~PerfectBinaryTree();

		bool modify(const ElemType& old_value, const ElemType& new_value);
		bool find(const ElemType& value) const;
		TreeNode2<ElemType>* contains(const ElemType& value) const;

		using CompleteBinaryTree<ElemType>::clear;
		using CompleteBinaryTree<ElemType>::empty;
		using CompleteBinaryTree<ElemType>::size;
		using CompleteBinaryTree<ElemType>::leaves_size;
		using CompleteBinaryTree<ElemType>::height;
		using CompleteBinaryTree<ElemType>::print;
		using CompleteBinaryTree<ElemType>::traverse;

	protected:
		using CompleteBinaryTree<ElemType>::insert_helper;
		using CompleteBinaryTree<ElemType>::copy_helper;
		using CompleteBinaryTree<ElemType>::contains_helper;
		using CompleteBinaryTree<ElemType>::clear_helper;
		using CompleteBinaryTree<ElemType>::size_helper;
		using CompleteBinaryTree<ElemType>::leaves_size_helper;
		using CompleteBinaryTree<ElemType>::height_helper;
		using CompleteBinaryTree<ElemType>::print_helper;
		using CompleteBinaryTree<ElemType>::traverse_helper;
	};
}

template <typename ElemType>
inline Hazel::PerfectBinaryTree<ElemType>::PerfectBinaryTree()
	: CompleteBinaryTree<ElemType>()
{
}

template<typename ElemType>
inline Hazel::PerfectBinaryTree<ElemType>::PerfectBinaryTree(std::initializer_list<ElemType> il)
	: CompleteBinaryTree<ElemType>()
{
	int n = il.size();
	bool isPowerOfTwo = (n & (n + 1)) == 0; // 检查是否是2的幂
	double logValue = log2(n + 1); // 计算log2(n + 1)是否为整数
	if (!isPowerOfTwo || logValue != floor(logValue)) {
		throw std::runtime_error("Data error, unable to construct perfect binary tree!");
	}

	root = new TreeNode2<ElemType>(il[0]);
	Queue<TreeNode2<ElemType>*> que;
	int index = 1;
	while (index < n)
	{
		int k = que.size();
		for (int i = 0; i < k; i++)
		{
			TreeNode2<ElemType>* cur = que.front();
			que.pop();
			cur->left = new TreeNode2<ElemType>(il[index++]);
			cur->right = new TreeNode2<ElemType>(il[index++]);
			que.push(cur->left);
			que.push(cur->right);
		}
	}
}

template<typename ElemType>
inline Hazel::PerfectBinaryTree<ElemType>::~PerfectBinaryTree()
{
	~CompleteBinaryTree<ElemType>();
}
