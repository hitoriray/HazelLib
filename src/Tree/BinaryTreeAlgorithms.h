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
	 * @brief ��ӡ������
	 * @param mode 0 ����1 ǰ��2 ����3 ����
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
			if (root == nullptr) // ����ڵ�Ϊ�գ���ӡnull
			{
				std::cout << "null ";
				return;
			}
			std::cout << root->value << " "; // ��ӡ�ڵ��ֵ
			printTree(root->left, mode); // �ݹ��ӡ������
			printTree(root->right, mode); // �ݹ��ӡ������
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

	// !����������ȱ����㷨 (DFS)��
	// ��������ǰ�����
	template<typename ElemType>
	Vector<ElemType> preorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		preorder_traversal(root, ans);
		return ans;
	}

	// ���������������
	template<typename ElemType>
	Vector<ElemType> inorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		inorder_traversal(root, ans);
		return ans;
	}

	// �������ĺ������
	template<typename ElemType>
	Vector<ElemType> postorderTraverse(TreeNode<ElemType>* root)
	{
		Vector<int> ans;
		postorder_traversal(root, ans);
		return ans;
	}

	// !�������Ĺ�ȱ����㷨 (BFS)��
	// �������Ĳ������
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
				TreeNode* cur = que.front(); // ���ȼ�¼Ҫ�����Ľ��
				que.pop();
				vec.push_back(cur->value); // �ռ���ǰ����
				if (cur->left)			 // ���Ҫ�����Ľ����� ��/�� �ӽڵ㣬�� push �� que ��
					que.push(cur->left);
				if (cur->right)
					que.push(cur->right);
			}
			ans.push_back(vec); // ����ǰ����ӵ� ans ��
		}
		return ans;
	}

	// �������Ĳ�α������� --> ����
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
		std::reverse(ans.begin(), ans.end()); // ��תVector
		return ans;
	}
	
	// �ж϶������Ƿ�����ȫ������
	template <typename ElemType>
	bool is_complete(TreeNode<ElemType>* root)
	{
		if (!root) return false;
		Queue<TreeNode<ElemType>*> que; // �������ÿ��ڵ�
		que.push(root);
		while (!que.empty())
		{
			TreeNode<ElemType>* cur = que.front();
			// �����ǰ�ڵ��������Ӷ��У���ֱ�ӵ��������Ұ��������Һ��Ӽ������
			if (cur->left && cur->right)
			{
				que.pop();
				que.push(cur->left);
				que.push(cur->right);
			}
			// �����ǰ�ڵ�����Ϊ�գ��Һ��Ӳ�Ϊ�գ���һ��������ȫ������
			if (!cur->left && cur->right) return false;
			// �����ǰ�ڵ����Ӳ�Ϊ�գ��Һ���Ϊ�ջ��߸ýڵ�ΪҶ�ӽڵ�
			if ((cur->left && !cur->right) || !cur->left && !cur->right)
			{
				if (cur->left && !cur->right) // ���Ӳ��գ��������
					que.push(cur->left);
				que.pop(); // ������ǰ�ڵ�
				
				// �ж϶����еĽڵ��Ƿ���Ҷ�ӽڵ㣬����Ϊ��ȫ����������֮������ȫ��������
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
		int k = 1; // ��¼ÿһ��Ľڵ����
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
			k *= 2; // ÿһ��k����
		}
	}

}