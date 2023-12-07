#pragma once

#include "BST.h"

#include "../Log/Log.h"
#include "../Vector/Vector.h"
#include "../String/String.h"


using Hazel::Vector;
using Hazel::String;

namespace Hazel
{
	template <typename K, typename V, typename Comparator = std::less<K>>
	class RBT : public BST<K>
	{
		// ��ǰ������RBNode���ģ�������
		template <typename K, typename V> class RBNode;

	public:
		RBT();
		~RBT();
		/* ... */

		bool insert(const K& key, const V& value = V());
		V remove(const K& key);
		int depth() const;
		void print(std::ostream& os) const;
		bool empty() const;
		void clear();
		// Ѱ��node��ǰ���ͺ�̽ڵ�
		RBNode<K, V>* predecessor(RBNode<K, V>* node);
		RBNode<K, V>* successor(RBNode<K, V>* node);

		/*using BinaryTree<ElemType>::clear;
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
		using BinaryTree<ElemType>::traverse_helper;*/

	protected:
		void clear_helper(RBNode<K, V>* node);
		void print_helper(RBNode<K, V>* node, std::ostream& os, int level) const;

	private:
		// Χ��p��������
		void left_rotate(RBNode<K, V>* p);
		// Χ��p��������
		void right_rotate(RBNode<K, V>* p);

		// ���node�Ƿ�Ϊ��ָ��
		inline void check_nullptr(RBNode<K, V>* node)
		{
			if (node == nullptr) {
				throw std::invalid_argument("node cannot be null");
			}
		}

		RBNode<K, V>* parent_of(RBNode<K, V>* node) { check_nullptr(node); return node->parent; }
		RBNode<K, V>* left_of(RBNode<K, V>* node) { check_nullptr(node);  return node->left; }
		RBNode<K, V>* right_of(RBNode<K, V>* node) { check_nullptr(node); return node->right; }
		// ���nodeΪ�գ��򷵻غ�ɫ����ΪҶ�ӣ�nil���ڵ㶼�Ǻ�ɫ�ġ�
		bool color_of(RBNode<K, V>* node) { return node == nullptr ? BLACK : node->color; }
		void set_color(RBNode<K, V>* node, bool color) { if (node) node->color = color; }

		// ÿ���һ���ڵ�node�������ʱ�ͽ��е���
		void fix_after_insert(RBNode<K, V>* node);

		// ��ȡkey��Ӧ�Ľڵ�node
		RBNode<K, V>* get_node(const K& key);
		// ɾ��node
		void delete_node(RBNode<K, V>* node);
		// ÿɾ��һ���ڵ�node�������ʱ�ͽ��е���
		void fix_after_remove(RBNode<K, V>* node);

		// ���ڸ�����ӡ�����print()����
		int get_depth(RBNode<K, V>* node) const
		{
			return node == nullptr ? 0 : (1 + std::max(get_depth(node->left), get_depth(node->right)));
		}

		static void writeArray(RBNode<K, V>* cur_node, int row, int col, Vector<Vector<String>>& res, int depth)
		{
			// ��֤���������Ϊ��
			if (cur_node == nullptr)
				return;
			// 0��Ĭ����ɫ
			//res[row][col] = String(cur_node.getValue());
			// 1����ɫ��ʾ
			if (cur_node->color == BLACK) {
				res[row][col] = String("\033[30;3m" + cur_node->getValue()) + "\033[0m";
			}
			else {
				res[row][col] = String("\033[31;3m" + cur_node->getValue()) + "\033[0m";
			}
			//2��R,B ��ʾ
			//res[row][col] = String(cur_node.getValue() + "-" + (cur_node->getColor() == BLACK ? "B" : "R") + "");
			// ���㵱ǰλ�����ĵڼ���
			int cur_level = (row + 1) / 2;
			// ���������һ�㣬�򷵻�
			if (cur_level == depth) return;
			// ���㵱ǰ�е���һ�У�ÿ��Ԫ��֮��ļ������һ�е��������뵱ǰԪ�ص�������֮��ļ����
			int gap = depth - cur_level - 1;

			// ������ӽ����жϣ���������ӣ����¼��Ӧ��"/"������ӵ�ֵ
			if (cur_node->left != nullptr) {
				res[row + 1][col - gap] = "/";
				writeArray(cur_node->left, row + 2, col - gap * 2, res, depth);
			}
			// ���Ҷ��ӽ����жϣ������Ҷ��ӣ����¼��Ӧ��"\"���Ҷ��ӵ�ֵ
			if (cur_node->right != nullptr) {
				res[row + 1][col + gap] = "\\";
				writeArray(cur_node->right, row + 2, col + gap * 2, res, depth);
			}
		}


	private:
		// �ڲ���RBNode
		template <typename K, typename V>
		class RBNode
		{
			friend class RBT; // ����RBT����RBNode��˽�г�Ա

		public:
			RBNode()
				:key(K()), value(V()), color(RED), parent(nullptr), left(nullptr), right(nullptr)
			{
			}

			RBNode(const K& k, const V& v = k, bool c = RED, RBNode* p = nullptr, RBNode* l = nullptr, RBNode* r = nullptr)
				: key(k), value(v), color(c), parent(p), left(l), right(r)
			{
			}

			void setColor(bool _color) { color = _color; }
			bool getColor() { return color; }
			void setValue(V _value) { value = _value; }
			V getValue() { return value; }

		private:
			K key;
			V value;
			bool color; // true�����ɫ false�����ɫ

			RBNode<K, V>* parent;
			RBNode<K, V>* left;
			RBNode<K, V>* right;
		};

		RBNode<K, V>* root;
		static const bool RED = true;
		static const bool BLACK = false;
	};
}

template<typename K, typename V, typename Comparator>
inline Hazel::RBT<K, V, Comparator>::RBT()
	: root(nullptr)
{
}

template<typename K, typename V, typename Comparator>
inline Hazel::RBT<K, V, Comparator>::~RBT()
{
	clear();
}

template<typename K, typename V, typename Comparator>
inline bool Hazel::RBT<K, V, Comparator>::insert(const K& key, const V& value)
{
	// ��һ�����������Ǹ��ڵ㣬��ô��Ϊ��ɫ
	if (empty()) {
		root = new RBNode<K, V>(key, value, BLACK);
		return true;
	}
	RBNode<K, V>* cur = root;
	RBNode<K, V>* parent = nullptr;
	Comparator comp;
	// ���Ÿ��ڵ�Ѱ�Ҳ���λ�ã�
	// �ڶ�������������Ľڵ���2�ڵ�ϲ���ֱ�Ӻϲ����Ϻ��º죩
	// ����������������Ľڵ���3�ڵ�ϲ���ֱ�Ӻϲ�����1�ڣ���2�죩
	// ����������������Ľڵ���3�ڵ�ϲ�����ʱ��Ҫ����
	do
	{
		parent = cur;
		if (comp(key, parent->key)) { // ��ʾ key < parent->key ����
			cur = cur->left; // ��ʱ��������������Ѱ��
		}
		else if (comp(parent->key, key)) { // ��ʾ key > parent->key ����
			cur = cur->right; // ��ʱ��������������Ѱ��
		}
		else { // ˵�� key == parent->key����ʱ���µ�value�滻��ԭ����value
			cur->value = value;
			return true;
		}
	} while (cur);

	RBNode<K, V>* e = new RBNode<K, V>(key, value, RED, parent);
	// �ж�e��parent�����ӻ����Һ���
	if (comp(key, parent->key)) // key < parent->key
		parent->left = e;
	else
		parent->right = e;
	// ����
	fix_after_insert(e);

	return true;
}

template<typename K, typename V, typename Comparator>
inline V Hazel::RBT<K, V, Comparator>::remove(const K& key)
{
	RBNode<K, V>* node = get_node(key);
	if (node == nullptr)
		return V();
	V result = node->value;
	// ÿ��ɾ������ת����ɾ�����2���е�����һ���ڵ�
	delete_node(node);
	return result;
}

template<typename K, typename V, typename Comparator>
inline int Hazel::RBT<K, V, Comparator>::depth() const
{
	return get_depth(root);
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::clear_helper(RBNode<K, V>* node)
{
	if (node == nullptr)
		return;
	clear_helper(node->left);
	clear_helper(node->right);
	delete node;
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::print_helper(RBNode<K, V>* node, std::ostream& os, int level) const
{
	if (node == nullptr)
		return;
	// �����ȵݹ�ش�ӡ������
	print_helper(node->right, os, level + 1);
	// �ٴ�ӡ��ǰ�ڵ��ֵ��λ�ã�ʹ�ÿո�����ʾ������ʹ��/��\����ʾ���Ӻͷ���
	for (int i = 0; i < level; i++) {
		os << "    ";
	}
	if (node->color == RED)
		os << Hazel::RED << node->key << Hazel::RESET;
	else
		os << node->key;
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
}

/**
 * ����
 *
 *		pf  (pf)			pf	 (pf)
 *		  \ (/)				  \ (/)
 *		   p				   pr(r)
 *		  /  \		==>		  /  \
 *	    pl	 pr(r)			 p	  rr
 *			/  \			/ \
 *		   rl   rr		   pl  rl
 */
template <typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::left_rotate(RBNode<K, V>* p)
{
	if (p == nullptr || p->right == nullptr)
		return;
	// ����������
	// ��¼��ת��ڵ�����ӽڵ㣨r�������ӽڵ�����ӽڵ㣨rl��
	RBNode<K, V>* r = p->right;
	RBNode<K, V>* rl = r->left;
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

/**
 * ����
 *
 *		pf  (pf)			pf	 (pf)
 *		  \ (/)				  \ (/)
 *		   p				   pl(l)
 *		  /  \		==>		  /  \
 *	  (l)pl   pr			ll	  p
 *		/  \					 / \
 *	  ll    lr					lr  pr
 */
template <typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::right_rotate(RBNode<K, V>* p)
{
	if (p == nullptr || p->right == nullptr)
		return;
	// ����������
	RBNode<K, V>* l = p->left;
	RBNode<K, V>* lr = l->right;
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


/**
 * ��e���е���
 *
 * 1.	2-3-4����	����Ԫ�� + 2-�ڵ� = 3-�ڵ�
 *		�������		������ɫ�ڵ� + ��ɫ���ڵ� = �Ϻ��º졾����Ҫ������

 * 2.	2-3-4����	����Ԫ�� + 3-�ڵ� = 4-�ڵ�
 *		�������4���������3������Ҫ����������3������Ҫ������������2������������Ҹ�һ��������Ҫ��������
 *					������ɫ�ڵ� + �Ϻ��º� = ������м�ڵ��Ǻ�ɫ������2���ڵ��Ǻ�ɫ��3-�ڵ㣩��������1���ڣ�����2���졿
		�����һ����3��������1�� + ��ɫ
		�����������3��������1�� + ��ɫ
		�������/�ġ�����Ҫ����

 * 3.	2-3-4��������Ԫ�� + 4-�ڵ� = ԭ����4-�ڵ���ѣ��м�Ԫ������Ϊ���ڵ㣬����Ԫ����ʣ�µ�����һ��Ԫ�غϲ�
 *									 ������1��ڵ㣨����Ǹ��ڵ㣬���ٴα�ɺ�ɫ��+ ����1����ɫ�ڵ� + 1������+�ڣ��ڵ㡿
 *
 *		�������������ɫ�ڵ� + үү�ڵ�(��)�����ڵ������ڵ�(��) = үү�ڵ�(��)�����ڵ������ڵ�(��)�����үү�ڵ��Ǹ��ڵ㣬���ٴα�ڡ�
 *							^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *									��1����2��					 ��1��(root:��) + ��2�� + ��1��
 *
 */
template <typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::fix_after_insert(RBNode<K, V>* node)
{
	check_nullptr(node);

	// �����ڵ�Ĭ��Ϊ��ɫ
	node->color = RED;

	// �����Ͼ��Ǹ��ڵ���Ϊ��ɫ������Ҫ������
	// �������ж���Ҫ�����ļ��������
	while (node != nullptr && node != root && color_of(parent_of(node)) == RED)
	{
		// ���node�ĸ��ڵ���үү�ڵ������
		if (parent_of(node) == left_of(parent_of(parent_of(node)))) // ����дparent_of()�����ָ��
		{
			// ��ȡnode������ڵ�
			RBNode<K, V>* uncle = right_of(parent_of(parent_of(node)));
			// �������ڵ�Ϊ��ɫ
			if (color_of(uncle) == RED)
			{
				// ��ʱ��Ӧ3�е����
				// ��node�ĸ��׺�����ڵ�����Ϊ��ɫ
				set_color(parent_of(node), BLACK);
				set_color(uncle, BLACK);
				// ��үү�ڵ�����Ϊ��ɫ
				set_color(parent_of(parent_of(node)), RED);
				// ��nodeָ���үү�ڵ㣬�Ա��үү�ڵ����ѭ�����ݹ飩�ж�
				node = parent_of(parent_of(node));
			}
			// �������ڵ㲻���ڻ�Ϊ��ɫ
			else
			{
				// ��ʱ����һ�������������nodeΪ�����׽ڵ���Һ���
				if (node == right_of(parent_of(node)))
				{
					// ��ʱֻ��Ҫ�Ը��׽ڵ���Ϊ֧������1�ξͱ���ˡ����һ����3
					node = parent_of(node); // ��ѡ��Ҫ��ǰ��nodeָ���׽ڵ㣬�Ա��������������3���
					left_rotate(node); // ���Դ�Ϊ֧������1��
				}
				// ��ʱ��Ӧ2�еġ����һ����3����������ڵ㲻���ڻ�Ϊ��ɫ
				// ���׽ڵ���ɫ
				set_color(parent_of(node), BLACK);
				// үү�ڵ���ɫ
				set_color(parent_of(parent_of(node)), RED);
				// ������үү�ڵ���Ϊ֧������1��
				right_rotate(parent_of(parent_of(node)));
			}
		}
		// ���´������������ƣ�left��right��������
		// ���node�ĸ��ڵ���үү�ڵ���Һ���
		else
		{
			RBNode<K, V>* uncle = left_of(parent_of(parent_of(node)));
			if (color_of(uncle) == RED)
			{
				// ��ʱ��Ӧ3�е����
				// ��node�ĸ��׺�����ڵ�����Ϊ��ɫ����үү�ڵ�����Ϊ��ɫ
				set_color(parent_of(node), BLACK);
				set_color(uncle, BLACK);
				set_color(parent_of(parent_of(node)), RED);
				// ��nodeָ���үү�ڵ㣬�Ա��үү�ڵ����ѭ�����ݹ飩�ж�
				node = parent_of(parent_of(node));
			}
			else
			{
				// ��ʱ����һ�������������nodeΪ�����׽ڵ������
				if (node == left_of(parent_of(node)))
				{
					// ��ʱֻ��Ҫ�Ը��׽ڵ���Ϊ֧������1�ξͱ���ˡ����һ����3
					node = parent_of(node);
					right_rotate(node);
				}
				// ��ʱ��Ӧ2�еġ����һ����3����������ڵ㲻���ڻ�Ϊ��ɫ
				// ���׽ڵ���ɫ��үү�ڵ���ɫ��������үү�ڵ���Ϊ֧������1��
				set_color(parent_of(node), BLACK);
				set_color(parent_of(parent_of(node)), RED);
				left_rotate(parent_of(parent_of(node)));
			}
		}
	}
	// ���һ����rootȾ��
	root->color = BLACK;
}

template<typename K, typename V, typename Comparator>
inline Hazel::RBT<K, V, Comparator>::RBNode<K, V>* Hazel::RBT<K, V, Comparator>::get_node(const K& key)
{
	RBNode<K, V>* node = root;
	Comparator comp;
	while (node)
	{
		if (comp(key, node->key))
			node = node->left;
		else if (comp(node->key, key))
			node = node->right;
		else
			return node;
	}
	return nullptr;
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::delete_node(RBNode<K, V>* node)
{
	// node �������ӽڵ�
	if (left_of(node) != nullptr && right_of(node) != nullptr)
	{
		// ��ǰ���ڵ������
		//RBNode<K, V>* rep = predecessor(node);
		// �ú�̽ڵ��������JDK��TreeMap��������
		RBNode<K, V>* rep = successor(node);
		// ��rep�е�Ԫ�ظ��Ƹ�node
		node->key = rep->key;
		node->value = rep->value;
		// ��ʱҪɾ���Ľڵ�����rep
		node = rep;
	}
	// ��ʱ�жϱ�ɾ���Ľڵ����ҽ��е�һ������(Ҳ��������ڵ�)���������ӻ����Һ��ӡ�����ǣ���ɾ���Ľڵ���Ҷ�ӽڵ�
	RBNode<K, V>* replaced = node->left != nullptr ? node->left : node->right;
	// ����ڵ㲻Ϊ�գ���Ҫô��node������Ҫô��node���Һ��ӣ�
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
		// �滻��Ϻ���Ҫ����������ĺ�ɫƽ��
		// ֻ�е���ɾ���Ľڵ����ɫΪ��ɫ������Ҫ����
		if (color_of(node) == BLACK) {
			// ��replacedΪ���Ľ��е���
			fix_after_remove(replaced); // ���������replacedһ���Ǻ�ɫ����ʱֻ���ɫ����
		}
		// ���nodeɾ��
		delete node;
	}
	// ��ʱreplacedΪ�գ���node�޸��ڵ㣬˵��node���Ǹ��ڵ㣬������������ֻ�и��ڵ�
	else if (parent_of(node) == nullptr)
	{
		delete node;
		root = nullptr; // ֱ�ӽ�root�ÿ�
	}
	// ����ڵ�Ϊ�գ���nodeΪҶ�ӽڵ㣩
	else
	{
		// ֻ�е�node����ɫΪ��ɫʱ��node��ɾ���Ļ��Ż��ƻ��������ĺ�ɫƽ�⣬��ʱ����Ҫ����
		// ����Ҫ�ȵ���
		if (color_of(node) == BLACK) {
			// ��nodeΪ���Ľ��е���
			fix_after_remove(node);
		}
		// ��ɾ��
		delete node;
	}
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::fix_after_remove(RBNode<K, V>* node)
{
	if (node == nullptr) return;
	// ��node���Ǹ��ڵ���Ϊ��ɫʱ�Ž��е���
	while (node != root && color_of(node) == BLACK)
	{
		// ɾ���Ľڵ�node�Ǹ��׵�����
		if (node == left_of(parent_of(node))) {
			// �ҵ��ֵܽڵ�
			RBNode<K, V>* bro = right_of(parent_of(node));
			// �ж�bro�Ƿ����������ֵܽڵ�
			if (color_of(bro) == RED) { // ֻ�е�broΪ��ɫʱ�Ų����������ֵܽڵ�
				// ��broȾ��
				set_color(bro, BLACK);
				// ����node�ĸ��ڵ�(��bro�ĸ��ڵ�)Ⱦ��
				set_color(parent_of(node), RED);
				// Ȼ����node�ĸ��ڵ�Ϊ��������1��
				left_rotate(parent_of(node));
				// �����ҵ��������ֵܽڵ�bro��
				bro = right_of(parent_of(node));
			}
			// ��������Լ��㲻�����ֵ�Ҳ���裨�ֵ���ͬ���㣬ͬʱ����
			if (color_of(left_of(bro)) == BLACK && color_of(right_of(bro)) == BLACK) // �ֵ�û�ý�
			{
				// ���������
				// ���ֵܽڵ�Ⱦ�죨�൱�����һ����ɫ��
				set_color(bro, RED);
				node = parent_of(node);
			}
			// ��������Լ��㲻����Ҫ���ֵܽ裬�����ֵܲ��裬ֻ���Ҹ��׽裬����������Ȼ���ֵ���������һ��ȥ���游�׵���
			else // �ֵ��еý�
			{
				// ������С�����1���ֵܽڵ�Ϊ3-�ڵ㣻2���ֵܽڵ�Ϊ4-�ڵ�
				// ����ֵܽڵ���Һ���Ϊ��
				if (color_of(right_of(bro)) == BLACK) {
					// ���ֵܽڵ������Ⱦ��
					set_color(left_of(bro));
					// ���ֵܽڵ�Ⱦ��
					set_color(bro);
					// ��broΪ��������
					right_rotate(bro);
					// ����bro
					bro = right_of(parent_of(node));
				}
				// ����ֵܽڵ���3-�ڵ㣬��ʱnode�����ַ������ֵܽڵ��
				// ��һ�֣��ֵܽڵ�ֻ��1���ڵ��ȥ����ʱ��Ҫ1������+1������
				// �ڶ��֣��ֵܽڵ��2���ڵ��ȥ����ʱֻ��Ҫ1���������ɣ�������������պú��ֵܽڵ�û�����ӵ����������ͬ��
				// ����ѡ��ڶ��ַ�����JDK��TreeMapҲ����ô���ģ�
				// ��bro��ɫ����������׽ڵ�һ��
				set_color(bro, color_of(parent_of(bro)));
				// ��bro�ĸ��׽ڵ���
				set_color(parent_of(bro), BLACK);
				// ��bro���Һ���Ⱦ��
				set_color(right_of(bro), BLACK);
				// ��node�ĸ��ڵ�Ϊ��������1��
				left_rotate(parent_of(node));
				// ��nodeָ��root����ʾѭ������
				node = root;
			}
		}
		// ɾ���Ľڵ�node�Ǹ��׵��Һ���
		else
		{
			// �ҵ��ֵܽڵ�
			RBNode<K, V>* bro = left_of(parent_of(node));
			// �ж�bro�Ƿ����������ֵܽڵ�
			if (color_of(bro) == RED) { // ֻ�е�broΪ��ɫʱ�Ų����������ֵܽڵ�
				// ��broȾ��
				set_color(bro, BLACK);
				// ����node�ĸ��ڵ�(��bro�ĸ��ڵ�)Ⱦ��
				set_color(parent_of(node), RED);
				// Ȼ����node�ĸ��ڵ�Ϊ��������1��
				right_rotate(parent_of(node));
				// �����ҵ��������ֵܽڵ�bro��
				bro = left_of(parent_of(node));
			}
			// ��������Լ��㲻�����ֵ�Ҳ���裨�ֵ���ͬ���㣬ͬʱ����
			if (color_of(right_of(bro)) == BLACK && color_of(left_of(bro)) == BLACK) // �ֵ�û�ý�
			{
				// ���������
				// ���ֵܽڵ�Ⱦ�죨�൱�����һ����ɫ��
				set_color(bro, RED);
				node = parent_of(node);
			}
			// ��������Լ��㲻����Ҫ���ֵܽ裬�����ֵܲ��裬ֻ���Ҹ��׽裬����������Ȼ���ֵ���������һ��ȥ���游�׵���
			else // �ֵ��еý�
			{
				// ������С�����1���ֵܽڵ�Ϊ3-�ڵ㣻2���ֵܽڵ�Ϊ4-�ڵ�
				// ����ֵܽڵ������Ϊ��
				if (color_of(left_of(bro)) == BLACK) {
					// ���ֵܽڵ���Һ���Ⱦ��
					set_color(right_of(bro));
					// ���ֵܽڵ�Ⱦ��
					set_color(bro);
					// ��broΪ��������
					left_rotate(bro);
					// ����bro
					bro = left_of(parent_of(node));
				}
				// ����ֵܽڵ���3-�ڵ㣬��ʱnode�����ַ������ֵܽڵ��
				// ��һ�֣��ֵܽڵ�ֻ��1���ڵ��ȥ����ʱ��Ҫ1������+1������
				// �ڶ��֣��ֵܽڵ��2���ڵ��ȥ����ʱֻ��Ҫ1���������ɣ�������������պú��ֵܽڵ�û�����ӵ����������ͬ��
				// ����ѡ��ڶ��ַ�����JDK��TreeMapҲ����ô���ģ�
				// ��bro��ɫ����������׽ڵ�һ��
				set_color(bro, color_of(parent_of(bro)));
				// ��bro�ĸ��׽ڵ���
				set_color(parent_of(bro), BLACK);
				// ��bro������Ⱦ��
				set_color(left_of(bro), BLACK);
				// ��node�ĸ��ڵ�Ϊ��������1��
				right_rotate(parent_of(node));
				// ��nodeָ��root����ʾѭ������
				node = root;
			}
		}
	}
	// ���һ������ڵ��Ǻ�ɫ����ֱ��Ⱦ�ڣ�����ɾ���ĺ�ɫ�ڵ㣬ʹ�ú������Ȼ���֣���ɫ��ƽ��
	set_color(node, BLACK);
}

template <typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::print(std::ostream& os) const
{
	print_helper(root, os, 0);

	//if (empty())
	//{
	//	os << "Empty Tree!";
	//	return;
	//}
	//// �õ��������
	//int treeDepth = this->depth();
	//// ���һ�еĿ��Ϊ2�ģ�n - 1���η���3���ټ�1
	//// ��Ϊ������ά����Ŀ��
	//int arrayHeight = treeDepth * 2 - 1;
	//int arrayWidth = (2 << (treeDepth - 2)) * 3 + 1;

	//// ��һ���ַ����������洢ÿ��λ��Ӧ��ʾ��Ԫ�أ�����������г�ʼ����Ĭ��Ϊһ���ո�
	//Vector<Vector<String>> res(arrayHeight, Vector<String>(arrayWidth, " "));
	//// �Ӹ��ڵ㿪ʼ���ݹ鴦��������
	////res[0][(arrayWidth + 1)/ 2] = (char)(root->value + '0');
	//writeArray(root, 0, arrayWidth / 2, res, treeDepth);

	//// ��ʱ���Ѿ���������Ҫ��ʾ��Ԫ�ش��浽�˶�ά�����У�����ƴ�Ӳ���ӡ����
	//for (const Vector<String>& line : res) {
	//	String s;
	//	for (int i = 0; i < line.size(); i++) {
	//		s.append(line[i]);
	//		if (line[i].size() > 1 && i <= line.size() - 1) {
	//			i += line[i].size() > 4 ? 2 : line[i].size() - 1;
	//		}
	//	}
	//	os << s << "\n";
	//}
}

template<typename K, typename V, typename Comparator>
inline bool Hazel::RBT<K, V, Comparator>::empty() const
{
	return root == nullptr;
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::clear()
{
	if (empty())
		return;
	clear_helper(root);
	root = nullptr;
}

template<typename K, typename V, typename Comparator>
inline Hazel::RBT<K, V, Comparator>::RBNode<K, V>* Hazel::RBT<K, V, Comparator>::predecessor(RBNode<K, V>* node)
{
	if (node == nullptr)
		return nullptr;
	// �ҵ������������Ҳ�ڵ�
	if (node->left != nullptr)
	{
		RBNode<K, V>* p = node->left;
		while (p->right)
			p = p->right;
		return p;
	}
	// �����������ڣ����ϱ߽ڵ���Ѱ��ǰ���ڵ㣨�ҵ���һ���������㣩
	RBNode<K, V>* p = node->parent;
	RBNode<K, V>* cur = node;
	while (p && cur == p->left) {
		cur = p;
		p = p->parent;
	}
	return p;
}

template<typename K, typename V, typename Comparator>
inline Hazel::RBT<K, V, Comparator>::RBNode<K, V>* Hazel::RBT<K, V, Comparator>::successor(RBNode<K, V>* node)
{
	if (node == nullptr)
		return nullptr;
	// �ҵ��������������ڵ�
	if (node->right != nullptr)
	{
		RBNode<K, V>* p = node->right;
		while (p->left)
			p = p->left;
		return p;
	}
	// �����������ڣ����ϱ߽ڵ���Ѱ�Һ�̽ڵ㣨�ҵ���һ�����ҹ���㣩
	RBNode<K, V>* p = node->parent;
	RBNode<K, V>* cur = node;
	while (p && cur == p->right) {
		cur = p;
		p = p->parent;
	}
	return p;
}
