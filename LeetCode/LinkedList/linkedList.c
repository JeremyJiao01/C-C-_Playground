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

// # 92 翻转指定区间内的元素
struct ListNode *reverseBetween(struct ListNode *head, int left, int right) {
    // 因为头节点有可能发生变化，使用虚拟头节点可以避免复杂的分类讨论
    struct ListNode *dummyNode = malloc(sizeof(struct ListNode));
    dummyNode->val = -1;
    dummyNode->next = head;

    struct ListNode *pre = dummyNode;
    // 第 1 步：从虚拟头节点走 left - 1 步，来到 left 节点的前一个节点
    for (int i = 0; i < left - 1; i++) {
        pre = pre->next;
    }

    // 第 2 步：从 pre 再走 right - left + 1 步，来到 right 节点
    struct ListNode *rightNode = pre;
    for (int i = 0; i < right - left + 1; i++) {
        rightNode = rightNode->next;
    }

    // 第 3 步：切断出一个子链表（截取链表）
    struct ListNode *leftNode = pre->next;
    struct ListNode *curr = rightNode->next;

    // 注意：切断链接
    pre->next = NULL;
    rightNode->next = NULL;

    // 第 4 步：同第 206 题，反转链表的子区间
    reverseLinkedList(leftNode);

    // 第 5 步：接回到原来的链表中
    pre->next = rightNode;
    leftNode->next = curr;
    return dummyNode->next;
}

// # 203 移除链表元素
struct ListNode* removeElements(struct ListNode* head, int val) {
    struct ListNode* dummyNode = malloc(sizeof(struct ListNode));
    dummyNode->next = head;
    struct ListNode* preNode = dummyNode;
    while(preNode->next != NULL){
        if(preNode->next->val == val){
            preNode->next = preNode->next->next;
        }else{
            preNode = preNode->next;
        }
    }
    return dummyNode->next;
}

// # 24 两两交换链表中的节点
struct ListNode* swapPairs(struct ListNode* head) {
    struct ListNode dummyHead;
    dummyHead.next = head;
    struct ListNode* temp = &dummyHead;
    while (temp->next != NULL && temp->next->next != NULL) {
        struct ListNode* node1 = temp->next;
        struct ListNode* node2 = temp->next->next;
        temp->next = node2;
        node1->next = node2->next;
        node2->next = node1;
        temp = node1;
    }
    return dummyHead.next;
}

// # 25 K个一组翻转链表
struct ListNode** Reverse(struct ListNode* head, struct ListNode* tail){
    struct ListNode* pre = tail->next;
    struct ListNode* p = head;
    while(pre != tail){
        struct ListNode* next = p->next;
        p->next = pre;
        pre = p;
        p = next;
    }
    struct ListNode** returnArr = (struct ListNode**)malloc(sizeof(struct ListNode*) * 2);
    returnArr[0] = head;
    returnArr[1] = tail;
    return returnArr;
}

struct ListNode* reverseKGroup(struct ListNode* head, int k) {
    struct ListNode* dummyNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyNode->next = head;
    struct ListNode* cureNode = dummyNode;

    while(cureNode != NULL){
        struct ListNode* tail = cureNode;
        // 查看剩余部分是否大于k  
        for(int i = 0; i < k; i++){      
            tail = tail->next;
            if(tail == NULL){
                return dummyNode->next;
            }
        }

        struct ListNode* next = tail->next;
        struct ListNode** reverse = Reverse(head, tail);
        head = reverse[1];
        tail = reverse[0];

        cureNode->next = head;
        tail->next = next;
        cureNode = tail;
        head = tail->next;
    }
    return dummyNode->next;
}
