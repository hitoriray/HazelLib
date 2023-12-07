#pragma once

#include "LinkedList.h"

namespace Hazel
{
	// ��ת����
	template<typename T>
	ListNode<T>* reverseList(ListNode<T>* head)
	{
		// ��Ե�����ж�
		if (head == nullptr) return nullptr;
		if (head->next == nullptr) return head;
		// �ݹ���ã���ת�ڶ����ڵ㿪ʼ���������
		ListNode* last = reverseList(head->next);
		// ��תͷ�ڵ���ڶ����ڵ��ָ��
		head->next->next = head;
		// ��ʱ�� head �ڵ�Ϊβ�ڵ㣬next ��Ҫָ�� NULL
		head->next = nullptr;
		return last;
	}

	// ��������II
	template<typename T>
	ListNode<T>* detectCycle(ListNode<T>* head)
	{
		ListNode* fast = head, * slow = head;
		while (fast && fast->next) {
			slow = slow->next;
			fast = fast->next->next;
			// ����ָ����������ʱ��head �� �����㣬ͬʱ����ֱ������
			if (fast == slow) {
				ListNode* index1 = fast;
				ListNode* index2 = head;
				while (index1 != index2) {
					index1 = index1->next;
					index2 = index2->next;
				}
				return index1; // ���ػ������
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