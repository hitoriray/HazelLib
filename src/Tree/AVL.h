#pragma once

#include "BST.h"

namespace Hazel
{

	// 重构：用K值来排序，V用来存放数据，Comparator为比较器，默认升序
	template <typename K, /* typename V, */ typename Comparator = std::less<K>>
	class AVL : public BST<K>
	{
	protected:
		using BST<K>::root;

	public:
		AVL();
		~AVL();

		bool insert(const K& key);
		bool remove(const K& key);

		TreeNode2<K>* predecessor(TreeNode2<K>*);
		TreeNode2<K>* successor(TreeNode2<K>*);

		using BST<K>::find;
		using BST<K>::contains;
		using BST<K>::clear;
		using BST<K>::empty;
		using BST<K>::size;
		using BST<K>::leaves_size;
		using BST<K>::height;
		using BST<K>::print;
		using BST<K>::traverse;

	protected:
		using BST<K>::insert_helper;
		using BST<K>::copy_helper;
		using BST<K>::clear_helper;
		using BST<K>::size_helper;
		using BST<K>::leaves_size_helper;
		using BST<K>::height_helper;
		using BST<K>::print_helper;
		using BST<K>::traverse_helper;

	private:
		void check_balance(TreeNode2<K>*);
		void left_rotate(TreeNode2<K>*);
		void right_rotate(TreeNode2<K>*);
		// 检查node是否为空指针
		void check_nullptr(TreeNode2<K>* node)
		{
			if (node == nullptr) {
				throw std::invalid_argument("node cannot be null");
			}
		}
		TreeNode2<K>* parent_of(TreeNode2<K>* node) { check_nullptr(node); return node->parent; }
		TreeNode2<K>* left_of(TreeNode2<K>* node) { check_nullptr(node);  return node->left; }
		TreeNode2<K>* right_of(TreeNode2<K>* node) { check_nullptr(node); return node->right; }
		// 修复AVL的平衡性
		void fix(TreeNode2<K>*);

	private:

	};

	template<typename K, typename Comparator>
	inline AVL<K, Comparator>::AVL()
		: BST<K>()
	{
	}

	template<typename K, typename Comparator>
	inline AVL<K, Comparator>::~AVL()
	{
		clear();
	}

	template<typename K, typename Comparator>
	inline bool AVL<K, Comparator>::insert(const K& key)
	{
		if (empty()) {
			root = new TreeNode2<K>(key);
			return true;
		}
		TreeNode2<K>* cur = root; // 使用一个指针来记录当前遍历的节点，初始为根节点
		TreeNode2<K>* parent = nullptr; // 使用一个指针来记录当前遍历的节点的父节点，初始为nullptr
		Comparator comp;
		while (cur) {
			parent = cur;
			if (comp(key, cur->value)) cur = cur->left;
			else if (comp(cur->value, key)) cur = cur->right;
			else return false; // ?找到相同的节点，返回false
		}
		TreeNode2<K>* p = new TreeNode2<K>(key);
		if (comp(key, parent->value))
			parent->left = p;
		else
			parent->right = p;
		p->parent = parent; // 将p的父节点设为parent

		//从插入的新节点开始，向上遍历到根节点，检查是否都平衡
		fix(p);

		return true;
	}

	template<typename K, typename Comparator>
	inline bool AVL<K, Comparator>::remove(const K& key)
	{
		if (empty()) return false;

		TreeNode2<K>* node = contains(key);
		if (node == nullptr) return false;

		// node 有两个子节点
		if (node->left && node->right)
		{
			// 用前驱节点替代：
			//TreeNode2<K>* rep = predecessor(node);
			// 用后继节点替代：（JDK中TreeMap的做法）
			TreeNode2<K>* rep = successor(node);
			// 将rep中的元素复制给node
			node->value = rep->value;
			// 此时要删除的节点变成了rep
			node = rep;
		}
		// 此时判断被删除的节点有且仅有的一个孩子(也就是替代节点)是它的左孩子还是右孩子。亦或是：被删除的节点是叶子节点
		TreeNode2<K>* replaced = node->left != nullptr ? node->left : node->right;
		// 1. 替代节点不为空（即要么是node的左孩子要么是node的右孩子）
		if (replaced != nullptr)
		{
			// 将replaced的父节点更新为node的父节点
			replaced->parent = parent_of(node);
			// 如果node无父节点，代表要删除的节点是根节点
			if (parent_of(node) == nullptr) {
				root = replaced;
			}
			// 并且根据node是它父亲的左孩子还是右孩子，用replaced替换掉node
			else if (node == left_of(parent_of(node))) {
				node->parent->left = replaced;
			}
			else {
				node->parent->right = replaced;
			}
		}
		// 2. 此时replaced为空，且node无父节点，说明node就是根节点，且整棵树有且只有根节点
		else if (parent_of(node) == nullptr)
		{
			delete node; // 删除node（即root）
			root = nullptr; // 将root置空
			return true; // 并返回
		}
		// 3. 替代节点为空（即node为叶子节点）———— 直接删除

		// 4. 删除节点node
		// 1）先调整平衡
		fix(parent_of(node));
		// 2）再删除
		delete node;

		return true;
	}

	template<typename K, typename Comparator>
	inline TreeNode2<K>* AVL<K, Comparator>::predecessor(TreeNode2<K>* node)
	{
		if (node == nullptr)
			return nullptr;
		// 找到左子树的最右侧节点
		if (node->left != nullptr)
		{
			TreeNode2<K>* p = node->left;
			while (p->right)
				p = p->right;
			return p;
		}
		// 左子树不存在，在上边节点中寻找前驱节点（找到第一个向左拐弯点）
		TreeNode2<K>* p = node->parent;
		TreeNode2<K>* cur = node;
		while (p && cur == p->left) {
			cur = p;
			p = p->parent;
		}
		return p;
	}

	template<typename K, typename Comparator>
	inline TreeNode2<K>* AVL<K, Comparator>::successor(TreeNode2<K>* node)
	{
		if (node == nullptr)
			return nullptr;
		// 找到右子树的最左侧节点
		if (node->right != nullptr)
		{
			TreeNode2<K>* p = node->right;
			while (p->left)
				p = p->left;
			return p;
		}
		// 右子树不存在，在上边节点中寻找后继节点（找到第一个向右拐弯点）
		TreeNode2<K>* p = node->parent;
		TreeNode2<K>* cur = node;
		while (p && cur == p->right) {
			cur = p;
			p = p->parent;
		}
		return p;
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::check_balance(TreeNode2<K>* p)
	{
		if (p == nullptr)
			return;
		// 节点的左右子树的高度差
		int balance = height_helper(p->left) - height_helper(p->right);
		// 如果高度差大于1，说明左子树过高，需要进行右旋操作
		if (balance > 1)
		{
			// 如果左子树的右子树高于左子树的左子树，说明需要进行双旋操作，先对左子树进行左旋，再对节点p进行右旋
			if (height_helper(p->left->right) > height_helper(p->left->left))
			{
				left_rotate(p->left);
			}
			// 否则，只需要对节点p进行右旋
			right_rotate(p);
		}
		// 如果高度差小于-1，说明右子树过高，需要进行左旋操作
		else if (balance < -1)
		{
			// 如果右子树的左子树高于右子树的右子树，说明需要进行双旋操作，先对右子树进行右旋，再对节点p进行左旋
			if (height_helper(p->right->left) > height_helper(p->right->right))
			{
				right_rotate(p->right);
			}
			// 否则，只需要对节点p进行左旋
			left_rotate(p);
		}
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::left_rotate(TreeNode2<K>* p)
	{
		if (p == nullptr || p->right == nullptr)
			return;
		// 左旋操作（以p为中心节点进行旋转）
		// 记录旋转点节点的右子节点（r）和右子节点的左子节点（rl）
		TreeNode2<K>* r = p->right;
		TreeNode2<K>* rl = r->left;
		// 将r作为新的根节点，并将p作为它的左子节点
		r->left = p;
		// 将原来右子节点的左子节点（rl）作为原来根节点（p）的右子节点
		p->right = rl;
		// 如果rl不为空，则更新rl的父节点为p
		if (rl != nullptr) {
			rl->parent = p;
		}
		// 更新r的父节点为pf
		r->parent = p->parent;
		// 如果p本身就是root节点，那么现在root变成r了
		if (p->parent == nullptr)
			root = r;
		// 如果p是pf的左孩子，则将r变为pf的左孩子
		else if (p->parent->left == p)
			p->parent->left = r;
		// 如果p是pf的右孩子，则将r变为pf的右孩子
		else
			p->parent->right = r;
		// 最后将r更新为p的父节点
		p->parent = r;
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::right_rotate(TreeNode2<K>* p)
	{
		if (p == nullptr || p->right == nullptr)
			return;
		// 右旋操作（以p为中心节点进行旋转）
		TreeNode2<K>* l = p->left;
		TreeNode2<K>* lr = l->right;
		// 将l作为新的根节点，并将p作为它的右子节点
		l->right = p;
		// 将lr作为p的左子节点
		p->left = lr;
		// 如果lr不为空，则更新lr的父节点为p
		if (lr != nullptr) {
			lr->parent = p;
		}
		// 更新r的父节点为p的父节点
		l->parent = p->parent;
		// 如果p本身就是root节点，那么现在root变成l了
		if (p->parent == nullptr)
			root = l;
		// 如果p是pf的左孩子，则将l变为pf的左孩子
		else if (p->parent->left == p)
			p->parent->left = l;
		// 如果p是pf的右孩子，则将l变为pf的右孩子
		else
			p->parent->right = l;
		// 最后将l更新为p的父节点
		p->parent = l;
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::fix(TreeNode2<K>* p)
	{
		do check_balance(p); while (p = p->parent); // 递归处理父节点
	}

}