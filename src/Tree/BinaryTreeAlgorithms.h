#pragma once

#define TreeNode TreeNode2

#include "TreeNode2.h"
#include "../Queue/Queue.h"
#include "../Vector/Vector.h"
#include "../String/String.h"
#include <unordered_map>

using std::unordered_map;

namespace Hazel
{
	/**
	 * @brief 打印二叉树
	 * @param mode 0 层序；1 前序；2 中序；3 后序
	 */
	template <typename ElemType>
	void printTree(TreeNode<ElemType>* root, Mode mode)
	{
		if (root == nullptr) {
			std::cout << "null ";
			return;
		}
		if (mode == Mode::LEVELORDER)
		{
			Queue<TreeNode<ElemType>*> que;
			que.push(root);
			while (!que.empty())
			{
				int size = que.size();
				for (int i = 0; i < size; ++i)
				{
					TreeNode<ElemType>* node = que.front();
					que.pop();
					if (node == nullptr) {
						std::cout << "null ";
						continue;
					}
					std::cout << node->value << " ";
					if (node->left) {
						que.push(node->left);
						if (!node->right) que.push(nullptr);
					}
					if (node->right) {
						if (!node->left) que.push(nullptr);
						que.push(node->right);
					}
				}
			}
		}
		else if (mode == Mode::PREORDER)
		{
			if (root == nullptr) // 如果节点为空，打印null
			{
				std::cout << "null ";
				return;
			}
			std::cout << root->value << " "; // 打印节点的值
			printTree(root->left, mode); // 递归打印左子树
			printTree(root->right, mode); // 递归打印右子树
		}
		else if (mode == Mode::INORDER)
		{
			if (root == nullptr)
			{
				std::cout << "null ";
				return;
			}
			printTree(root->left, mode);
			std::cout << root->value << " ";
			printTree(root->right, mode);
		}
		else if (mode == Mode::POSTORDER)
		{
			if (root == nullptr)
			{
				std::cout << "null ";
				return;
			}
			printTree(root->left, mode);
			printTree(root->right, mode);
			std::cout << root->value << " ";
		}
		else
			return;
	}

	template <typename ElemType, typename Func>
	void traverse(TreeNode<ElemType>* root, Mode mode, Func f)
	{
		if (root == nullptr) {
			return;
		}
		if (mode == Mode::LEVELORDER)
		{
			Queue<TreeNode<ElemType>*> que;
			que.push(root);
			while (!que.empty())
			{
				int size = que.size();
				for (int i = 0; i < size; ++i)
				{
					TreeNode<ElemType>* node = que.front();
					que.pop();
					f(node->value);
					if (node->left)
						que.push(node->left);
					if (node->right)
						que.push(node->right);
				}
			}
		}
		else if (mode == Mode::PREORDER)
		{
			if (root == nullptr)
			{
				return;
			}
			f(root->value);
			printTree(root->left, mode);
			printTree(root->right, mode);
		}
		else if (mode == Mode::INORDER)
		{
			if (root == nullptr)
			{
				return;
			}
			printTree(root->left, mode);
			f(root->value);
			printTree(root->right, mode);
		}
		else if (mode == Mode::POSTORDER)
		{
			if (root == nullptr)
			{
				return;
			}
			printTree(root->left, mode);
			printTree(root->right, mode);
			f(root->value);
		}
		else {
			return;
		}
	}

	// !二叉树的深度遍历算法 (DFS)：
	// 二叉树的前序遍历
	template<typename ElemType>
	Vector<ElemType> preorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		preorder_traversal(root, ans);
		return ans;
	}

	// 二叉树的中序遍历
	template<typename ElemType>
	Vector<ElemType> inorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		inorder_traversal(root, ans);
		return ans;
	}

	// 二叉树的后序遍历
	template<typename ElemType>
	Vector<ElemType> postorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		postorder_traversal(root, ans);
		return ans;
	}

	// !二叉树的广度遍历算法 (BFS)：
	// 二叉树的层序遍历
	template<typename ElemType>
	Vector<Vector<ElemType>> levelOrder(TreeNode<ElemType>* root)
	{
		Queue<TreeNode*> que;
		if (root != nullptr)
			que.push(root);
		Vector<Vector<int>> ans;
		while (!que.empty())
		{
			int size = que.size();
			Vector<int> vec;
			for (int i = 0; i < size; ++i)
			{
				TreeNode* cur = que.front(); // 事先记录要弹出的结点
				que.pop();
				vec.push_back(cur->value); // 收集当前层结点
				if (cur->left)			 // 如果要弹出的结点存在 左/右 子节点，则 push 到 que 中
					que.push(cur->left);
				if (cur->right)
					que.push(cur->right);
			}
			ans.push_back(vec); // 将当前层添加到 ans 中
		}
		return ans;
	}

	// 二叉树的层次遍历（底 --> 顶）
	template<typename ElemType>
	Vector<Vector<int>> levelOrderBottom(TreeNode<ElemType>* root)
	{
		Queue<TreeNode*> que;
		Vector<Vector<int>> ans;
		if (root != nullptr)
			que.push(root);
		while (!que.empty())
		{
			int size = que.size();
			Vector<int> vec;
			for (int i = 0; i < size; ++i)
			{
				TreeNode* cur = que.front();
				que.pop();
				vec.push_back(cur->value);
				if (cur->left)
					que.push(cur->left);
				if (cur->right)
					que.push(cur->right);
			}
			ans.push_back(vec);
		}
		std::reverse(ans.begin(), ans.end()); // 反转Vector
		return ans;
	}
	
	// 判断二叉树是否是完全二叉树
	template <typename ElemType>
	bool is_complete(TreeNode<ElemType>* root)
	{
		if (!root) return false;
		Queue<TreeNode<ElemType>*> que; // 层序遍历每层节点
		que.push(root);
		while (!que.empty())
		{
			TreeNode<ElemType>* cur = que.front();
			// 如果当前节点两个孩子都有，则直接弹出，并且把他的左右孩子加入队列
			if (cur->left && cur->right)
			{
				que.pop();
				que.push(cur->left);
				que.push(cur->right);
			}
			// 如果当前节点左孩子为空，右孩子不为空，则一定不是完全二叉树
			if (!cur->left && cur->right) return false;
			// 如果当前节点左孩子不为空，右孩子为空或者该节点为叶子节点
			if ((cur->left && !cur->right) || !cur->left && !cur->right)
			{
				if (cur->left && !cur->right) // 左孩子不空，加入队列
					que.push(cur->left);
				que.pop(); // 弹出当前节点
				
				// 判断队列中的节点是否都是叶子节点，是则为完全二叉树，反之不是完全二叉树。
				while (!que.empty())
				{
					cur = que.front();
					if (!cur->left && !cur->right) que.pop();
					else return false;
				}
				return true;
			}
		}
		return true;
	}

	template <typename ElemType>
	bool is_perfect(TreeNode<ElemType>* root)
	{
		if (!root)
			return false;
		Queue<TreeNode<ElemType>*> que;
		que.push(root);
		int k = 1; // 记录每一层的节点个数
		while (!que.empty())
		{
			int n = que.size();
			if (n != k)
				return false;
			for (int i = 0; i < n; i++)
			{
				TreeNode<ElemType>* cur = que.front();
				que.pop();
				if (cur->left)
					que.push(cur->left);
				if(cur->right)
					que.push(cur->right);
			}
			k *= 2; // 每一层k翻倍
		}
	}

}