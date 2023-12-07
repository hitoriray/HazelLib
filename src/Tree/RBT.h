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
		// 提前声明有RBNode这个模板类存在
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
		// 寻找node的前驱和后继节点
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
		// 围绕p进行左旋
		void left_rotate(RBNode<K, V>* p);
		// 围绕p进行右旋
		void right_rotate(RBNode<K, V>* p);

		// 检查node是否为空指针
		inline void check_nullptr(RBNode<K, V>* node)
		{
			if (node == nullptr) {
				throw std::invalid_argument("node cannot be null");
			}
		}

		RBNode<K, V>* parent_of(RBNode<K, V>* node) { check_nullptr(node); return node->parent; }
		RBNode<K, V>* left_of(RBNode<K, V>* node) { check_nullptr(node);  return node->left; }
		RBNode<K, V>* right_of(RBNode<K, V>* node) { check_nullptr(node); return node->right; }
		// 如果node为空，则返回黑色【因为叶子（nil）节点都是黑色的】
		bool color_of(RBNode<K, V>* node) { return node == nullptr ? BLACK : node->color; }
		void set_color(RBNode<K, V>* node, bool color) { if (node) node->color = color; }

		// 每添加一个节点node到红黑树时就进行调整
		void fix_after_insert(RBNode<K, V>* node);

		// 获取key对应的节点node
		RBNode<K, V>* get_node(const K& key);
		// 删除node
		void delete_node(RBNode<K, V>* node);
		// 每删除一个节点node到红黑树时就进行调整
		void fix_after_remove(RBNode<K, V>* node);

		// 用于辅助打印红黑树print()函数
		int get_depth(RBNode<K, V>* node) const
		{
			return node == nullptr ? 0 : (1 + std::max(get_depth(node->left), get_depth(node->right)));
		}

		static void writeArray(RBNode<K, V>* cur_node, int row, int col, Vector<Vector<String>>& res, int depth)
		{
			// 保证输入的树不为空
			if (cur_node == nullptr)
				return;
			// 0、默认无色
			//res[row][col] = String(cur_node.getValue());
			// 1、颜色表示
			if (cur_node->color == BLACK) {
				res[row][col] = String("\033[30;3m" + cur_node->getValue()) + "\033[0m";
			}
			else {
				res[row][col] = String("\033[31;3m" + cur_node->getValue()) + "\033[0m";
			}
			//2、R,B 表示
			//res[row][col] = String(cur_node.getValue() + "-" + (cur_node->getColor() == BLACK ? "B" : "R") + "");
			// 计算当前位于树的第几层
			int cur_level = (row + 1) / 2;
			// 若到了最后一层，则返回
			if (cur_level == depth) return;
			// 计算当前行到下一行，每个元素之间的间隔（下一行的列索引与当前元素的列索引之间的间隔）
			int gap = depth - cur_level - 1;

			// 对左儿子进行判断，若有左儿子，则记录相应的"/"与左儿子的值
			if (cur_node->left != nullptr) {
				res[row + 1][col - gap] = "/";
				writeArray(cur_node->left, row + 2, col - gap * 2, res, depth);
			}
			// 对右儿子进行判断，若有右儿子，则记录相应的"\"与右儿子的值
			if (cur_node->right != nullptr) {
				res[row + 1][col + gap] = "\\";
				writeArray(cur_node->right, row + 2, col + gap * 2, res, depth);
			}
		}


	private:
		// 内部类RBNode
		template <typename K, typename V>
		class RBNode
		{
			friend class RBT; // 允许RBT访问RBNode的私有成员

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
			bool color; // true代表红色 false代表黑色

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
	// 第一种情况：如果是根节点，那么改为黑色
	if (empty()) {
		root = new RBNode<K, V>(key, value, BLACK);
		return true;
	}
	RBNode<K, V>* cur = root;
	RBNode<K, V>* parent = nullptr;
	Comparator comp;
	// 沿着根节点寻找插入位置：
	// 第二种情况：新增的节点与2节点合并，直接合并（上黑下红）
	// 第三种情况：新增的节点与3节点合并，直接合并（上1黑，下2红）
	// 第四种情况：新增的节点与3节点合并，此时需要分裂
	do
	{
		parent = cur;
		if (comp(key, parent->key)) { // 表示 key < parent->key 成立
			cur = cur->left; // 此时沿着左子树继续寻找
		}
		else if (comp(parent->key, key)) { // 表示 key > parent->key 成立
			cur = cur->right; // 此时沿着右子树继续寻找
		}
		else { // 说明 key == parent->key，此时用新的value替换掉原来的value
			cur->value = value;
			return true;
		}
	} while (cur);

	RBNode<K, V>* e = new RBNode<K, V>(key, value, RED, parent);
	// 判断e是parent的左孩子还是右孩子
	if (comp(key, parent->key)) // key < parent->key
		parent->left = e;
	else
		parent->right = e;
	// 调整
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
	// 每次删除都会转换成删除最后2层中的其中一个节点
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
	// 否则，先递归地打印右子树
	print_helper(node->right, os, level + 1);
	// 再打印当前节点的值和位置，使用空格来表示缩进，使用/和\来表示连接和方向
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
	// 最后递归地打印左子树
	print_helper(node->left, os, level + 1);
}

/**
 * 左旋
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
	// 左旋操作：
	// 记录旋转点节点的右子节点（r）和右子节点的左子节点（rl）
	RBNode<K, V>* r = p->right;
	RBNode<K, V>* rl = r->left;
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

/**
 * 右旋
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
	// 右旋操作：
	RBNode<K, V>* l = p->left;
	RBNode<K, V>* lr = l->right;
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


/**
 * 对e进行调整
 *
 * 1.	2-3-4树：	新增元素 + 2-节点 = 3-节点
 *		红黑树：		新增红色节点 + 黑色父节点 = 上黑下红【不需要调整】

 * 2.	2-3-4树：	新增元素 + 3-节点 = 4-节点
 *		红黑树【4种情况：左3个（需要调整），右3个（需要调整），还有2种情况是左中右各一个（不需要调整）】
 *					新增红色节点 + 上黑下红 = 排序后中间节点是黑色，下面2个节点是红色（3-节点）【即上面1个黑，下面2个红】
		【情况一】左3个：右旋1次 + 变色
		【情况二】右3个：左旋1次 + 变色
		【情况三/四】不需要调整

 * 3.	2-3-4树：新增元素 + 4-节点 = 原来的4-节点分裂，中间元素上溢为父节点，新增元素与剩下的其中一个元素合并
 *									 【即上1红节点（如果是根节点，则再次变成黑色）+ 下面1个红色节点 + 1个（红+黑）节点】
 *
 *		红黑树：新增红色节点 + 爷爷节点(黑)，父节点和叔叔节点(红) = 爷爷节点(红)，父节点和叔叔节点(黑)【如果爷爷节点是根节点，则再次变黑】
 *							^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^		^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
 *									上1黑下2红					 上1红(root:黑) + 中2黑 + 下1红
 *
 */
template <typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::fix_after_insert(RBNode<K, V>* node)
{
	check_nullptr(node);

	// 新增节点默认为红色
	node->color = RED;

	// 本质上就是父节点若为黑色，则不需要调整。
	// 下面是判断需要调整的几种情况：
	while (node != nullptr && node != root && color_of(parent_of(node)) == RED)
	{
		// 如果node的父节点是爷爷节点的左孩子
		if (parent_of(node) == left_of(parent_of(parent_of(node)))) // 这样写parent_of()避免空指针
		{
			// 获取node的叔叔节点
			RBNode<K, V>* uncle = right_of(parent_of(parent_of(node)));
			// 如果叔叔节点为红色
			if (color_of(uncle) == RED)
			{
				// 此时对应3中的情况
				// 将node的父亲和叔叔节点设置为黑色
				set_color(parent_of(node), BLACK);
				set_color(uncle, BLACK);
				// 将爷爷节点设置为红色
				set_color(parent_of(parent_of(node)), RED);
				// 将node指向成爷爷节点，以便对爷爷节点进行循环（递归）判断
				node = parent_of(parent_of(node));
			}
			// 如果叔叔节点不存在或为黑色
			else
			{
				// 此时还有一种特殊情况：即node为它父亲节点的右孩子
				if (node == right_of(parent_of(node)))
				{
					// 此时只需要以父亲节点作为支点左旋1次就变成了【情况一】左3
					node = parent_of(node); // 首选需要提前将node指向父亲节点，以便适用于下面的左3情况
					left_rotate(node); // 再以此为支点左旋1次
				}
				// 此时对应2中的【情况一】左3个，即叔叔节点不存在或为黑色
				// 父亲节点变黑色
				set_color(parent_of(node), BLACK);
				// 爷爷节点变红色
				set_color(parent_of(parent_of(node)), RED);
				// 并且以爷爷节点作为支点右旋1次
				right_rotate(parent_of(parent_of(node)));
			}
		}
		// 以下代码与上面类似，left和right交换即可
		// 如果node的父节点是爷爷节点的右孩子
		else
		{
			RBNode<K, V>* uncle = left_of(parent_of(parent_of(node)));
			if (color_of(uncle) == RED)
			{
				// 此时对应3中的情况
				// 将node的父亲和叔叔节点设置为黑色并将爷爷节点设置为红色
				set_color(parent_of(node), BLACK);
				set_color(uncle, BLACK);
				set_color(parent_of(parent_of(node)), RED);
				// 将node指向成爷爷节点，以便对爷爷节点进行循环（递归）判断
				node = parent_of(parent_of(node));
			}
			else
			{
				// 此时还有一种特殊情况：即node为它父亲节点的左孩子
				if (node == left_of(parent_of(node)))
				{
					// 此时只需要以父亲节点作为支点右旋1次就变成了【情况一】左3
					node = parent_of(node);
					right_rotate(node);
				}
				// 此时对应2中的【情况一】左3个，即叔叔节点不存在或为黑色
				// 父亲节点变黑色，爷爷节点变红色，并且以爷爷节点作为支点右旋1次
				set_color(parent_of(node), BLACK);
				set_color(parent_of(parent_of(node)), RED);
				left_rotate(parent_of(parent_of(node)));
			}
		}
	}
	// 最后一步将root染黑
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
	// node 有两个子节点
	if (left_of(node) != nullptr && right_of(node) != nullptr)
	{
		// 用前驱节点替代：
		//RBNode<K, V>* rep = predecessor(node);
		// 用后继节点替代：（JDK中TreeMap的做法）
		RBNode<K, V>* rep = successor(node);
		// 将rep中的元素复制给node
		node->key = rep->key;
		node->value = rep->value;
		// 此时要删除的节点变成了rep
		node = rep;
	}
	// 此时判断被删除的节点有且仅有的一个孩子(也就是替代节点)是它的左孩子还是右孩子。亦或是：被删除的节点是叶子节点
	RBNode<K, V>* replaced = node->left != nullptr ? node->left : node->right;
	// 替代节点不为空（即要么是node的左孩子要么是node的右孩子）
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
		// 替换完毕后，需要调整红黑树的黑色平衡
		// 只有当被删除的节点的颜色为黑色，才需要调整
		if (color_of(node) == BLACK) {
			// 以replaced为中心进行调整
			fix_after_remove(replaced); // 这种情况，replaced一定是红色，此时只需变色即可
		}
		// 最后将node删除
		delete node;
	}
	// 此时replaced为空，且node无父节点，说明node就是根节点，且整棵树有且只有根节点
	else if (parent_of(node) == nullptr)
	{
		delete node;
		root = nullptr; // 直接将root置空
	}
	// 替代节点为空（即node为叶子节点）
	else
	{
		// 只有当node的颜色为黑色时，node被删除的话才会破坏整棵树的黑色平衡，此时才需要调整
		// 必须要先调整
		if (color_of(node) == BLACK) {
			// 以node为中心进行调整
			fix_after_remove(node);
		}
		// 再删除
		delete node;
	}
}

template<typename K, typename V, typename Comparator>
inline void Hazel::RBT<K, V, Comparator>::fix_after_remove(RBNode<K, V>* node)
{
	if (node == nullptr) return;
	// 当node不是根节点且为黑色时才进行调整
	while (node != root && color_of(node) == BLACK)
	{
		// 删除的节点node是父亲的左孩子
		if (node == left_of(parent_of(node))) {
			// 找到兄弟节点
			RBNode<K, V>* bro = right_of(parent_of(node));
			// 判断bro是否是真正的兄弟节点
			if (color_of(bro) == RED) { // 只有当bro为红色时才不是真正的兄弟节点
				// 将bro染黑
				set_color(bro, BLACK);
				// 并把node的父节点(即bro的父节点)染红
				set_color(parent_of(node), RED);
				// 然后以node的父节点为中心左旋1次
				left_rotate(parent_of(node));
				// 最后就找到真正的兄弟节点bro了
				bro = right_of(parent_of(node));
			}
			// 情况三：自己搞不定，兄弟也不借（兄弟情同手足，同时自损）
			if (color_of(left_of(bro)) == BLACK && color_of(right_of(bro)) == BLACK) // 兄弟没得借
			{
				// 情况更复杂
				// 把兄弟节点染红（相当于损掉一个黑色）
				set_color(bro, RED);
				node = parent_of(node);
			}
			// 情况二：自己搞不定，要找兄弟借，但是兄弟不借，只能找父亲借，父亲下来，然后兄弟找最左侧的一个去代替父亲当家
			else // 兄弟有得借
			{
				// 分两种小情况：1）兄弟节点为3-节点；2）兄弟节点为4-节点
				// 如果兄弟节点的右孩子为空
				if (color_of(right_of(bro)) == BLACK) {
					// 把兄弟节点的左孩子染黑
					set_color(left_of(bro));
					// 把兄弟节点染红
					set_color(bro);
					// 以bro为中心右旋
					right_rotate(bro);
					// 更新bro
					bro = right_of(parent_of(node));
				}
				// 如果兄弟节点是3-节点，此时node有两种方案向兄弟节点借
				// 第一种：兄弟节点只借1个节点出去，此时需要1次右旋+1次左旋
				// 第二种：兄弟节点借2个节点出去，此时只需要1次左旋即可（而且这次左旋刚好和兄弟节点没有左孩子的情况代码相同）
				// 我们选择第二种方案（JDK中TreeMap也是这么做的）
				// 把bro颜色变成与它父亲节点一致
				set_color(bro, color_of(parent_of(bro)));
				// 把bro的父亲节点变黑
				set_color(parent_of(bro), BLACK);
				// 把bro的右孩子染黑
				set_color(right_of(bro), BLACK);
				// 以node的父节点为中心左旋1次
				left_rotate(parent_of(node));
				// 让node指向root，表示循环结束
				node = root;
			}
		}
		// 删除的节点node是父亲的右孩子
		else
		{
			// 找到兄弟节点
			RBNode<K, V>* bro = left_of(parent_of(node));
			// 判断bro是否是真正的兄弟节点
			if (color_of(bro) == RED) { // 只有当bro为红色时才不是真正的兄弟节点
				// 将bro染黑
				set_color(bro, BLACK);
				// 并把node的父节点(即bro的父节点)染红
				set_color(parent_of(node), RED);
				// 然后以node的父节点为中心右旋1次
				right_rotate(parent_of(node));
				// 最后就找到真正的兄弟节点bro了
				bro = left_of(parent_of(node));
			}
			// 情况三：自己搞不定，兄弟也不借（兄弟情同手足，同时自损）
			if (color_of(right_of(bro)) == BLACK && color_of(left_of(bro)) == BLACK) // 兄弟没得借
			{
				// 情况更复杂
				// 把兄弟节点染红（相当于损掉一个黑色）
				set_color(bro, RED);
				node = parent_of(node);
			}
			// 情况二：自己搞不定，要找兄弟借，但是兄弟不借，只能找父亲借，父亲下来，然后兄弟找最左侧的一个去代替父亲当家
			else // 兄弟有得借
			{
				// 分两种小情况：1）兄弟节点为3-节点；2）兄弟节点为4-节点
				// 如果兄弟节点的左孩子为空
				if (color_of(left_of(bro)) == BLACK) {
					// 把兄弟节点的右孩子染黑
					set_color(right_of(bro));
					// 把兄弟节点染红
					set_color(bro);
					// 以bro为中心左旋
					left_rotate(bro);
					// 更新bro
					bro = left_of(parent_of(node));
				}
				// 如果兄弟节点是3-节点，此时node有两种方案向兄弟节点借
				// 第一种：兄弟节点只借1个节点出去，此时需要1次右旋+1次左旋
				// 第二种：兄弟节点借2个节点出去，此时只需要1次左旋即可（而且这次左旋刚好和兄弟节点没有左孩子的情况代码相同）
				// 我们选择第二种方案（JDK中TreeMap也是这么做的）
				// 把bro颜色变成与它父亲节点一致
				set_color(bro, color_of(parent_of(bro)));
				// 把bro的父亲节点变黑
				set_color(parent_of(bro), BLACK);
				// 把bro的左孩子染黑
				set_color(left_of(bro), BLACK);
				// 以node的父节点为中心右旋1次
				right_rotate(parent_of(node));
				// 让node指向root，表示循环结束
				node = root;
			}
		}
	}
	// 情况一：替代节点是红色，则直接染黑，补偿删除的黑色节点，使得红黑树依然保持（黑色）平衡
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
	//// 得到树的深度
	//int treeDepth = this->depth();
	//// 最后一行的宽度为2的（n - 1）次方乘3，再加1
	//// 作为整个二维数组的宽度
	//int arrayHeight = treeDepth * 2 - 1;
	//int arrayWidth = (2 << (treeDepth - 2)) * 3 + 1;

	//// 用一个字符串数组来存储每个位置应显示的元素，并对数组进行初始化，默认为一个空格
	//Vector<Vector<String>> res(arrayHeight, Vector<String>(arrayWidth, " "));
	//// 从根节点开始，递归处理整个树
	////res[0][(arrayWidth + 1)/ 2] = (char)(root->value + '0');
	//writeArray(root, 0, arrayWidth / 2, res, treeDepth);

	//// 此时，已经将所有需要显示的元素储存到了二维数组中，将其拼接并打印即可
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
	// 找到左子树的最右侧节点
	if (node->left != nullptr)
	{
		RBNode<K, V>* p = node->left;
		while (p->right)
			p = p->right;
		return p;
	}
	// 左子树不存在，在上边节点中寻找前驱节点（找到第一个向左拐弯点）
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
	// 找到右子树的最左侧节点
	if (node->right != nullptr)
	{
		RBNode<K, V>* p = node->right;
		while (p->left)
			p = p->left;
		return p;
	}
	// 右子树不存在，在上边节点中寻找后继节点（找到第一个向右拐弯点）
	RBNode<K, V>* p = node->parent;
	RBNode<K, V>* cur = node;
	while (p && cur == p->right) {
		cur = p;
		p = p->parent;
	}
	return p;
}
