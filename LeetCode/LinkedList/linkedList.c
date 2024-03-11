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

// # 876 链表的中间节点
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

// # 143 重新排序链表
struct ListNode* middleNode(struct ListNode* head) {
    struct ListNode* slow = head;
    struct ListNode* fast = head;
    while (fast->next != NULL && fast->next->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }
    return slow;
}

struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    while (curr != NULL) {
        struct ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}

void mergeList(struct ListNode* l1, struct ListNode* l2) {
    struct ListNode* l1_tmp;
    struct ListNode* l2_tmp;
    while (l1 != NULL && l2 != NULL) {
        l1_tmp = l1->next;
        l2_tmp = l2->next;

        l1->next = l2;
        l1 = l1_tmp;

        l2->next = l1;
        l2 = l2_tmp;
    }
}

void reorderList(struct ListNode* head) {
    if (head == NULL) {
        return;
    }
    struct ListNode* mid = middleNode(head);
    struct ListNode* l1 = head;
    struct ListNode* l2 = mid->next;
    mid->next = NULL;
    l2 = reverseList(l2);
    mergeList(l1, l2);
}

// # 61 旋转链表
struct ListNode* rotateRight(struct ListNode* head, int k) {
    if(head == NULL || head->next == NULL || k ==0){
        return head;
    }

    // 计算链表长度
    struct ListNode* curNode = head;
    int count = 1;
    while(curNode != NULL && curNode->next != NULL){
        count += 1;
        curNode = curNode->next;
    }

    // 计算要从哪里开始旋转
    int rotateNum = count - (k % count);
    if(rotateNum == count){
        return head;
    }

    curNode->next = head; // 将链表变成环，之后再断开
    for(int i = 0; i < rotateNum; i++){
        curNode = curNode->next;
    }
    struct ListNode* nextNode = curNode->next;
    curNode->next = NULL;
    return nextNode;
}

// # 328 奇偶链表
// 第一个节点视为奇数，第二个节点视为偶数
// 将奇数节点放在左边，偶数节点放在右边
struct ListNode* oddEvenList(struct ListNode* head) {
    if (head == NULL) {
        return head;
    }
    struct ListNode* evenHead = head->next;
    struct ListNode* odd = head;
    struct ListNode* even = evenHead;
    while (even != NULL && even->next != NULL) {
        odd->next = even->next;
        odd = odd->next;
        even->next = odd->next;
        even = even->next;
    }
    odd->next = evenHead;
    return head;
}

// # 234 回文链表
// 算法的正确性在于递归处理节点的顺序是 [相反] 的
// 而我们在函数外又记录了一个变量，因此从本质上，我们同时在正向和逆向迭代匹配。
// 在堆栈中存放好了数据后就可以进入被调用的函数。
// 在完成被调用函数之后，他会弹出堆栈顶部元素，以恢复在进行函数调用之前所在的函数。
// 在进行回文检查之前，递归函数将在堆栈中创建 n 个堆栈帧，计算机会逐个弹出进行处理。
// 这种方法不仅使用了O(n)的空间
// 同时为每个节点创建堆栈帧极大的限制了算法能够处理的最大链表大小。

// 在并发环境下，
// 函数运行时需要锁定其他线程或进程对链表的访问，因为在函数执行过程中链表会被修改。

// 整个流程可以分为以下五个步骤：

//  1. 找到前半部分链表的尾节点。// 使用快慢指针在一次遍历中找到中间
//  2. 反转后半部分链表。
//  3. 判断是否回文。
//  4. 恢复链表。
//  5. 返回结果。
struct ListNode* reverseList(struct ListNode* head) {
    struct ListNode* prev = NULL;
    struct ListNode* curr = head;
    while (curr != NULL) {
        struct ListNode* nextTemp = curr->next;
        curr->next = prev;
        prev = curr;
        curr = nextTemp;
    }
    return prev;
}


bool isPalindrome(struct ListNode* head) {
    if(head == NULL){
        return true;
    }

    struct ListNode* fast = head;
    struct ListNode* slow = head;
    while(fast->next != NULL && fast->next->next != NULL){
        fast = fast->next->next;
        slow = slow->next;
    }
    // slow 为中间节点，同时也是前半部分的尾部节点
    // 反转后半部分
    struct ListNode* secondHalfStart = reverseList(slow->next);
    
    // 判断是否为回文
    struct ListNode* p1 = head;
    struct ListNode* p2 = secondHalfStart;
    bool result = true;
    while(result && p2 != NULL){
        if(p1->val != p2->val){
            result = false;
        }
        p1 = p1->next;
        p2 = p2->next;
    }
    slow->next = reverseList(secondHalfStart);
    return result;
}

// # 147 对链表进行插入排序
struct ListNode* insertionSortList(struct ListNode* head) {
    if(head == NULL){
        return head;
    }
    struct ListNode* dummyHead = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyHead->next = head;
    struct ListNode* lastNode = head;
    struct ListNode* curNode = head->next;
    while(curNode != NULL){
        if(curNode->val >= lastNode->val){
            lastNode = lastNode->next;
        }else{
            struct ListNode* prevNode = dummyHead;
            // 这里需要找到插入点的前一个位置
            while(prevNode->next->val <= curNode->val){
                prevNode = prevNode->next;
            }
            lastNode->next = curNode->next;
            curNode->next = prevNode->next;
            prevNode->next = curNode;
        }
        curNode = lastNode->next;
    }
    return dummyHead->next;
}

// # 19 删除链表的倒数第N个结点
struct ListNode* removeNthFromEnd(struct ListNode* head, int n) {
    struct ListNode* dummyNode = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyNode->next = head;
    int count = 0;
    struct ListNode* curNode = dummyNode;
    while(curNode->next != NULL){
        curNode = curNode->next;
        count++;
    }
    int number = count - n;
    curNode = dummyNode;
    while(number--){
        curNode = curNode->next;
    }
    struct ListNode* deleteNode = curNode->next;
    curNode->next = deleteNode->next;
    deleteNode->next = NULL;
    return dummyNode->next;
}

// # 2 两数相加
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
    // 1. 两链表从头开始遍历
    //    若遍历到一个链表中有元素，另一无元素时自动为0
    // 2. 若两数之和 / 10 不为0，则Carry = 1
    //    当遍历到下一个元素时自动+1，同时Carry = 0
    //
    struct ListNode *head = NULL, *tail = NULL;
    int carry = 0;
    while (l1 || l2) {
	// 此处为判断链表是否遍历完
	// 若未遍历完，则取值为当前节点的值
	// 若遍历到空节点，则数值为0
        int n1 = l1 ? l1->val : 0; 
        int n2 = l2 ? l2->val : 0;
	// 当前总和需要加上进位的数
        int sum = n1 + n2 + carry;
        if (!head) {
            head = tail = malloc(sizeof(struct ListNode));
            tail->val = sum % 10;
            tail->next = NULL;
        } else {
            tail->next = malloc(sizeof(struct ListNode));
            tail->next->val = sum % 10;
            tail = tail->next;
            tail->next = NULL;
        }
	//判断是否有进位
        carry = sum / 10;
	// 防止继续遍历空节点导致报错
        if (l1) {
            l1 = l1->next;
        }
        if (l2) {
            l2 = l2->next;
        }
    }
    // 这里已经推出while循环了，则表示两个链表的姐都都已经遍历完
    // 若此时进位标识仍大于0，则需要再创建一个节点来进位
    if (carry > 0) {
        tail->next = malloc(sizeof(struct ListNode));
        tail->next->val = carry;
        tail->next->next = NULL;
    }
    return head;
}

// # 21 合并两个有序链表
struct ListNode* mergeTwoLists(struct ListNode* list1, struct ListNode* list2) {
    struct ListNode* dummyNode1 = (struct ListNode*)malloc(sizeof(struct ListNode));
    struct ListNode* dummyNode2 = (struct ListNode*)malloc(sizeof(struct ListNode));
    dummyNode1->next = list1;
    dummyNode2->next = list2;
    struct ListNode* curNode1 = dummyNode1;
    struct ListNode* curNode2 = dummyNode2;
    struct ListNode* head = NULL;
    struct ListNode* tail = NULL;
    int flag = 0;
    while(curNode1->next || curNode2->next){
        int n1 = curNode1->next ? curNode1->next->val : 200;
        int n2 = curNode2->next ? curNode2->next->val : 200;
        if(!head){
            head = tail = malloc(sizeof(struct ListNode));
            if(n1 > n2){
                tail->val = n2;
                flag = 2;
            } else {
                tail->val = n1;
                flag = 1;
            }            
            tail->next = NULL;
        }else{
            tail->next = malloc(sizeof(struct ListNode));
            if(n1 > n2){
                tail->next->val = n2;
                flag = 2;
            } else {
                tail->next->val = n1;
                flag = 1;
            }
            tail = tail->next;
            tail->next = NULL;
        }
        if(curNode1 && flag == 1){
            curNode1 = curNode1->next;
        }
        if(curNode2 && flag == 2){
            curNode2 = curNode2->next;
        }
    }
    return head;
}
