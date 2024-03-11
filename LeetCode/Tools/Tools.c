//
// Test Sorting Algorithms performance
//

#include "Func.h"


LinkedNode* mergeTwoLists(LinkedNode* list1, LinkedNode* list2) {
    LinkedNode* dummyNode1 = (LinkedNode*)malloc(sizeof(LinkedNode));
    LinkedNode* dummyNode2 = (LinkedNode*)malloc(sizeof(LinkedNode));
    dummyNode1->next = list1;
    dummyNode2->next = list2;
    LinkedNode* curNode1 = dummyNode1;
    LinkedNode* curNode2 = dummyNode2;
    LinkedNode* head = NULL;
    LinkedNode* tail = NULL;
    int flag = 0;
    while(curNode1->next || curNode2->next){
        int n1 = curNode1->next ? curNode1->next->value : 200;
        int n2 = curNode2->next ? curNode2->next->value : 200;
        if(!head){
            head = tail = malloc(sizeof(LinkedNode));
            if(n1 > n2){
                tail->value = n2;
                flag = 2;
            } else {
                tail->value = n1;
                flag = 1;
            }
            tail->next = NULL;
        }else{
            tail->next = malloc(sizeof(LinkedNode));
            if(n1 > n2){
                tail->next->value = n2;
                flag = 2;
            } else {
                tail->next->value = n1;
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


int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
//    int record[] = {1,8,6,2,5,4,8,3,7};
//    int nums = maxArea(record, 9);
//    int tmp[5][5] = {0};
//    for(int i = 0; i < 3; i++){
//        printf("%d ", i);
//    }
//    printf("%d", nums);

    LinkedList* l1 = (LinkedList*)malloc(sizeof(LinkedList));
    l1->count = 0;
    l1->head = NULL;
    addAtTail(l1, 1);
    addAtTail(l1, 2);
    addAtTail(l1, 4);
    LinkedNode* current1 = l1->head;

    LinkedList* l2 = (LinkedList*)malloc(sizeof(LinkedList));
    l2->count = 0;
    l2->head = NULL;
    addAtTail(l2, 1);
    addAtTail(l2, 3);
    addAtTail(l2, 4);
    LinkedNode* current2 = l2->head;

    LinkedNode * returnList = mergeTwoLists(current1, current2);
    for(int i = 0; i < 6; i++){
        printf("%d\n", returnList->value);
        returnList = returnList->next;
    }
    
    return 0;
}