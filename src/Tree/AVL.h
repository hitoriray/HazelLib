#pragma once

#include "BST.h"

namespace Hazel
{

	// �ع�����Kֵ������V����������ݣ�ComparatorΪ�Ƚ�����Ĭ������
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
		// ���node�Ƿ�Ϊ��ָ��
		void check_nullptr(TreeNode2<K>* node)
		{
			if (node == nullptr) {
				throw std::invalid_argument("node cannot be null");
			}
		}
		TreeNode2<K>* parent_of(TreeNode2<K>* node) { check_nullptr(node); return node->parent; }
		TreeNode2<K>* left_of(TreeNode2<K>* node) { check_nullptr(node);  return node->left; }
		TreeNode2<K>* right_of(TreeNode2<K>* node) { check_nullptr(node); return node->right; }
		// �޸�AVL��ƽ����
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
		TreeNode2<K>* cur = root; // ʹ��һ��ָ������¼��ǰ�����Ľڵ㣬��ʼΪ���ڵ�
		TreeNode2<K>* parent = nullptr; // ʹ��һ��ָ������¼��ǰ�����Ľڵ�ĸ��ڵ㣬��ʼΪnullptr
		Comparator comp;
		while (cur) {
			parent = cur;
			if (comp(key, cur->value)) cur = cur->left;
			else if (comp(cur->value, key)) cur = cur->right;
			else return false; // ?�ҵ���ͬ�Ľڵ㣬����false
		}
		TreeNode2<K>* p = new TreeNode2<K>(key);
		if (comp(key, parent->value))
			parent->left = p;
		else
			parent->right = p;
		p->parent = parent; // ��p�ĸ��ڵ���Ϊparent

		//�Ӳ�����½ڵ㿪ʼ�����ϱ��������ڵ㣬����Ƿ�ƽ��
		fix(p);

		return true;
	}

	template<typename K, typename Comparator>
	inline bool AVL<K, Comparator>::remove(const K& key)
	{
		if (empty()) return false;

		TreeNode2<K>* node = contains(key);
		if (node == nullptr) return false;

		// node �������ӽڵ�
		if (node->left && node->right)
		{
			// ��ǰ���ڵ������
			//TreeNode2<K>* rep = predecessor(node);
			// �ú�̽ڵ��������JDK��TreeMap��������
			TreeNode2<K>* rep = successor(node);
			// ��rep�е�Ԫ�ظ��Ƹ�node
			node->value = rep->value;
			// ��ʱҪɾ���Ľڵ�����rep
			node = rep;
		}
		// ��ʱ�жϱ�ɾ���Ľڵ����ҽ��е�һ������(Ҳ��������ڵ�)���������ӻ����Һ��ӡ�����ǣ���ɾ���Ľڵ���Ҷ�ӽڵ�
		TreeNode2<K>* replaced = node->left != nullptr ? node->left : node->right;
		// 1. ����ڵ㲻Ϊ�գ���Ҫô��node������Ҫô��node���Һ��ӣ�
		if (replaced != nullptr)
		{
			// ��replaced�ĸ��ڵ����Ϊnode�ĸ��ڵ�
			replaced->parent = parent_of(node);
			// ���node�޸��ڵ㣬����Ҫɾ���Ľڵ��Ǹ��ڵ�
			if (parent_of(node) == nullptr) {
				root = replaced;
			}
			// ���Ҹ���node�������׵����ӻ����Һ��ӣ���replaced�滻��node
			else if (node == left_of(parent_of(node))) {
				node->parent->left = replaced;
			}
			else {
				node->parent->right = replaced;
			}
		}
		// 2. ��ʱreplacedΪ�գ���node�޸��ڵ㣬˵��node���Ǹ��ڵ㣬������������ֻ�и��ڵ�
		else if (parent_of(node) == nullptr)
		{
			delete node; // ɾ��node����root��
			root = nullptr; // ��root�ÿ�
			return true; // ������
		}
		// 3. ����ڵ�Ϊ�գ���nodeΪҶ�ӽڵ㣩�������� ֱ��ɾ��

		// 4. ɾ���ڵ�node
		// 1���ȵ���ƽ��
		fix(parent_of(node));
		// 2����ɾ��
		delete node;

		return true;
	}

	template<typename K, typename Comparator>
	inline TreeNode2<K>* AVL<K, Comparator>::predecessor(TreeNode2<K>* node)
	{
		if (node == nullptr)
			return nullptr;
		// �ҵ������������Ҳ�ڵ�
		if (node->left != nullptr)
		{
			TreeNode2<K>* p = node->left;
			while (p->right)
				p = p->right;
			return p;
		}
		// �����������ڣ����ϱ߽ڵ���Ѱ��ǰ���ڵ㣨�ҵ���һ���������㣩
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
		// �ҵ��������������ڵ�
		if (node->right != nullptr)
		{
			TreeNode2<K>* p = node->right;
			while (p->left)
				p = p->left;
			return p;
		}
		// �����������ڣ����ϱ߽ڵ���Ѱ�Һ�̽ڵ㣨�ҵ���һ�����ҹ���㣩
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
		// �ڵ�����������ĸ߶Ȳ�
		int balance = height_helper(p->left) - height_helper(p->right);
		// ����߶Ȳ����1��˵�����������ߣ���Ҫ������������
		if (balance > 1)
		{
			// �������������������������������������˵����Ҫ����˫���������ȶ������������������ٶԽڵ�p��������
			if (height_helper(p->left->right) > height_helper(p->left->left))
			{
				left_rotate(p->left);
			}
			// ����ֻ��Ҫ�Խڵ�p��������
			right_rotate(p);
		}
		// ����߶Ȳ�С��-1��˵�����������ߣ���Ҫ������������
		else if (balance < -1)
		{
			// �������������������������������������˵����Ҫ����˫���������ȶ������������������ٶԽڵ�p��������
			if (height_helper(p->right->left) > height_helper(p->right->right))
			{
				right_rotate(p->right);
			}
			// ����ֻ��Ҫ�Խڵ�p��������
			left_rotate(p);
		}
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::left_rotate(TreeNode2<K>* p)
	{
		if (p == nullptr || p->right == nullptr)
			return;
		// ������������pΪ���Ľڵ������ת��
		// ��¼��ת��ڵ�����ӽڵ㣨r�������ӽڵ�����ӽڵ㣨rl��
		TreeNode2<K>* r = p->right;
		TreeNode2<K>* rl = r->left;
		// ��r��Ϊ�µĸ��ڵ㣬����p��Ϊ�������ӽڵ�
		r->left = p;
		// ��ԭ�����ӽڵ�����ӽڵ㣨rl����Ϊԭ�����ڵ㣨p�������ӽڵ�
		p->right = rl;
		// ���rl��Ϊ�գ������rl�ĸ��ڵ�Ϊp
		if (rl != nullptr) {
			rl->parent = p;
		}
		// ����r�ĸ��ڵ�Ϊpf
		r->parent = p->parent;
		// ���p�������root�ڵ㣬��ô����root���r��
		if (p->parent == nullptr)
			root = r;
		// ���p��pf�����ӣ���r��Ϊpf������
		else if (p->parent->left == p)
			p->parent->left = r;
		// ���p��pf���Һ��ӣ���r��Ϊpf���Һ���
		else
			p->parent->right = r;
		// ���r����Ϊp�ĸ��ڵ�
		p->parent = r;
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::right_rotate(TreeNode2<K>* p)
	{
		if (p == nullptr || p->right == nullptr)
			return;
		// ������������pΪ���Ľڵ������ת��
		TreeNode2<K>* l = p->left;
		TreeNode2<K>* lr = l->right;
		// ��l��Ϊ�µĸ��ڵ㣬����p��Ϊ�������ӽڵ�
		l->right = p;
		// ��lr��Ϊp�����ӽڵ�
		p->left = lr;
		// ���lr��Ϊ�գ������lr�ĸ��ڵ�Ϊp
		if (lr != nullptr) {
			lr->parent = p;
		}
		// ����r�ĸ��ڵ�Ϊp�ĸ��ڵ�
		l->parent = p->parent;
		// ���p�������root�ڵ㣬��ô����root���l��
		if (p->parent == nullptr)
			root = l;
		// ���p��pf�����ӣ���l��Ϊpf������
		else if (p->parent->left == p)
			p->parent->left = l;
		// ���p��pf���Һ��ӣ���l��Ϊpf���Һ���
		else
			p->parent->right = l;
		// ���l����Ϊp�ĸ��ڵ�
		p->parent = l;
	}

	template<typename K, typename Comparator>
	inline void AVL<K, Comparator>::fix(TreeNode2<K>* p)
	{
		do check_balance(p); while (p = p->parent); // �ݹ鴦���ڵ�
	}

}