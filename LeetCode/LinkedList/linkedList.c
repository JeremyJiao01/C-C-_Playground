/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

// # 206 反转单链表
// 使用非递归方法
struct ListNode* reverseList(struct ListNode* head) {
	if(head == NULL || head->next == NULL){
		return head;
	}
    struct ListNode* preNode = NULL;
    struct ListNode* curNode = head;
    while(curNode != NULL){
    	struct ListNode* nextNode = curNode->next;
    	curNode->next = preNode;
    	preNode = curNode;
    	curNode = nextNode;
    }
    return preNode;
}

// 使用递归的方法
struct ListNode* reverseList(struct ListNode* head) {
	if(head == NULL || head->next == NULL){
		return head;
	}
    struct ListNode* nextNode = head->next;
    struct ListNode* newNode = reverseList(nextNode);
    nextNode->next = head;
    head->next = NULL;
    return newNode;
}




