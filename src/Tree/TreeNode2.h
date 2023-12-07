#pragma once

template <typename ElemType>
struct TreeNode2
{
	ElemType value;
	TreeNode2<ElemType>* left;
	TreeNode2<ElemType>* right;
	TreeNode2<ElemType>* parent;

	TreeNode2()
		: value(ElemType()), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode2(const ElemType& value_)
		: value(value_), left(nullptr), right(nullptr), parent(nullptr) {}
	TreeNode2(const ElemType& value_, TreeNode2* left_, TreeNode2* right_, TreeNode2* parent_ = nullptr)
		: value(value_), left(left_), right(right_), parent(parent_) {}

	void Left(const ElemType& val);
	void Right(const ElemType& val);
};

template<typename ElemType>
inline void TreeNode2<ElemType>::Left(const ElemType& val)
{
	// 如果当前节点的左子树为空，直接将左子节点指向一个新节点
	if (left == nullptr) {
		left = new TreeNode2<ElemType>(val, nullptr, nullptr, this);
		return;
	}
	// 否则，递归地插入到左子树中
	left->Left(val);
}

template<typename ElemType>
inline void TreeNode2<ElemType>::Right(const ElemType& val)
{
	// 如果当前节点的右子树为空，直接将右子节点指向一个新节点
	if (right == nullptr) {
		right = new TreeNode2<ElemType>(val, nullptr, nullptr, this);
		return;
	}
	// 否则，递归地插入到右子树中
	right->Right(val);
}
