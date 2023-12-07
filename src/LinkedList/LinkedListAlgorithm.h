#pragma once

#include "LinkedList.h"

namespace Hazel
{
	// 反转链表
	template<typename T>
	ListNode<T>* reverseList(ListNode<T>* head)
	{
		// 边缘条件判断
		if (head == nullptr) return nullptr;
		if (head->next == nullptr) return head;
		// 递归调用，翻转第二个节点开始往后的链表
		ListNode* last = reverseList(head->next);
		// 翻转头节点与第二个节点的指向
		head->next->next = head;
		// 此时的 head 节点为尾节点，next 需要指向 NULL
		head->next = nullptr;
		return last;
	}

	// 环形链表II
	template<typename T>
	ListNode<T>* detectCycle(ListNode<T>* head)
	{
		ListNode* fast = head, * slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			// 快慢指针相遇，此时从head 和 相遇点，同时查找直至相遇
			if (fast == slow) {
				ListNode* index1 = fast;
				ListNode* index2 = head;
				while (index1 != index2) {
					index1 = index1->next;
					index2 = index2->next;
				}
				return index1; // 返回环的入口
			}
		}
		return nullptr;
	}

	template<typename T>
	LinkedList<T>* mergeList(LinkedList<T>* lst1, LinkedList<int>* lst2)
	{
		ListNode* lst1_end = lst1->end();
		lst1_end->next = lst2->begin();
		return lst1;
	}
}