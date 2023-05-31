#pragma once

#include <vector>

template <typename T, typename N>
class Tree
{
public:
	Tree() : root(nullptr) {}
	Tree(const Tree& rhs) = default;
	Tree& operator=(const Tree& rhs) = default;
	Tree(Tree&& rhs) noexcept = default;
	Tree& operator=(Tree&& rhs) noexcept = default;
	virtual ~Tree() { delete root; }

	virtual void CreateTree() = 0;
	virtual int GetDepth() = 0;
	
	// !基础操作
	virtual void insert() = 0;
	virtual void remove() = 0;
	virtual void modify() = 0;
	virtual void find() = 0;
	virtual bool empty() = 0;
	virtual void clear() = 0;
	virtual void destroy() = 0;
	virtual int GetNodes() = 0;
	virtual int GetLeaves() = 0;

	// !算法
	virtual std::vector<T> preorderTraverse() = 0;
	virtual std::vector<T> inorderTraverse() = 0;
	virtual std::vector<T> postorderTraverse() = 0;
	virtual std::vector<std::vector<T>> levelOrder() = 0;
	virtual std::vector<std::vector<T>> levelOrderBottom() = 0;

private:
	virtual void Init() = 0;

protected:
	N* root; // 根节点指针，类型为N
};
