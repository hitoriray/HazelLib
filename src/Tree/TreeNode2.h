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
	// �����ǰ�ڵ��������Ϊ�գ�ֱ�ӽ����ӽڵ�ָ��һ���½ڵ�
	if (left == nullptr) {
		left = new TreeNode2<ElemType>(val, nullptr, nullptr, this);
		return;
	}
	// ���򣬵ݹ�ز��뵽��������
	left->Left(val);
}

template<typename ElemType>
inline void TreeNode2<ElemType>::Right(const ElemType& val)
{
	// �����ǰ�ڵ��������Ϊ�գ�ֱ�ӽ����ӽڵ�ָ��һ���½ڵ�
	if (right == nullptr) {
		right = new TreeNode2<ElemType>(val, nullptr, nullptr, this);
		return;
	}
	// ���򣬵ݹ�ز��뵽��������
	right->Right(val);
}
