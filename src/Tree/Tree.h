#pragma once

namespace Hazel
{
	enum Mode { // Ҫ�����Mode��������һ��namespace���ģ�������һ������С�
		LEVELORDER = 0, PREORDER = 1, INORDER = 2, POSTORDER = 3
	};
}

namespace Hazel
{
	template <typename ElemType, typename NNode>
	class Tree
	{
	public:
		Tree() : root(nullptr) {}
		Tree(const ElemType& value) : root(new NNode(value)) {}
		Tree(const Tree& rhs) = default;
		Tree& operator=(const Tree& rhs) = default;
		Tree(Tree&& rhs) noexcept = default;
		Tree& operator=(Tree&& rhs) noexcept = default;
		virtual ~Tree() { delete root; }

		// !��������
		virtual bool insert(const ElemType& value) = 0;
		virtual bool find(const ElemType& value) const = 0;
		virtual NNode* contains(const ElemType& value) const = 0;
		virtual bool empty() const = 0;
		virtual void clear() = 0;
		virtual const int size() const = 0;
		virtual const int leaves_size() const = 0;
		virtual const int height() const = 0;

	protected:
		NNode* root; // ���ڵ�ָ�룬����ΪNNode������N����
	};
}
