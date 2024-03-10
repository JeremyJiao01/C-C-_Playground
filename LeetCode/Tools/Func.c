
#include "Func.h"

// ------------------------Test FUNC---------------------------
void swap(int* nums, int i, int j){
    int tmp = nums[i];
    nums[i] = nums[j];
    nums[j] = tmp;
}

void Display(int* nums, int numsSize){
    for(int i = 0; i < numsSize; i++){
        printf("%d ", nums[i]);
    }
    printf("\n");
}

int generateNums(int n){
    // 生成的数限制在n以内
    int num = rand() % n + 1;
    return num;
}

int* generateRandomArray(int n){
    // 建立一个长度为n的随机数组
    int* newArr = (int*)malloc(n * sizeof(int));
    for(int i = 0; i < n; i++){
        newArr[i] = generateNums(n);
    }
    return newArr;
}

int* generateOrderedArray(int n, int degree){
    int* newOrderedArr = (int*)malloc(n * sizeof(int));
    int randNum = rand() % n + 1;
    for(int i = 1; i < n + 1; i++){
        newOrderedArr[i - 1] = i * (randNum);
    }
    for(int j = 0; j < degree; j++){
        int randChange = rand() % n;
        swap(newOrderedArr, randChange, j);
    }
    return newOrderedArr;
}

int* generateReversedArray(int n, int degree){
    int* reverseArr = (int*)malloc(n * sizeof(int));
    int randNum = rand() % n + 1;
    int num = 1;
    for(int i = n - 1; i >= 0; i--){
        reverseArr[i] = randNum * num;
        num++;
    }
    for(int j = 0; j < degree; j++){
        int randChange = rand() % n;
        swap(reverseArr, randChange, j);
    }
    return reverseArr;
}

int isSorted(int* nums, int numsSize){
    for(int i = 0; i < numsSize - 1; i++){
        if(nums[i] > nums[i+1]){
            return 0;
        }
    }
    return  1;
}

int compare(const void *a, const void *b){
    // 用于比较两个整数的大小
    return *(int*)a - *(int*)b;
}

void testSortTime(int *nums, int numsSize, void(*sort_func)(int*, int)){
    clock_t start, end;
    double  time_spent;
    // 启动计时器
    start = clock();
    // 调用排序函数对数组进行排序
    sort_func(nums, numsSize);
    // 停止计时器
    end = clock();
    // 计算排序函数执行的时间
    int result = isSorted(nums, numsSize);
    if(result){
        printf("已排序\n");
        Display(nums, numsSize);
    } else{
        printf("未排序\n");
        Display(nums, numsSize);
    }
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time Spent is %.6f second\n", time_spent);
}

// -------------------Basic Sort---------------------------------------
void choseSortArray(int* nums, int numsSize) {
    for(int i = 0; i < numsSize - 1; i++){
        int minval = i;
        for(int j = i + 1; j < numsSize; j++){
            if(nums[j] < nums[minval]){
                minval = j;
            }
        }
        swap(nums, minval, i);
    }
}

// ---------------------merge sort-----------------------------------
void mergeTwoArr(int* nums, int numsSize, int left, int mid, int right){
    int len = right - left + 1;
    int* tempArr = (int*)malloc(len * sizeof(int));
    int i = left;
    int j = mid + 1;
    int k = 0;
    while(i <= mid && j <= right){
        if(nums[i] <= nums[j]){
            tempArr[k++] = nums[i++];
        }else{
            tempArr[k++] = nums[j++];
        }
    }
    while(i <= mid){
        tempArr[k++] = nums[i++];
    }
    while(j <= right){
        tempArr[k++] = nums[j++];
    }
    int b = 0;
    for(int a = left; a <= right; a++){
        nums[a] = tempArr[b++];
    }
}

void mergeSort(int* nums, int numsSize, int left, int right){
    if(left == right){
        return;
    }
    int mid = (left + right) / 2;
    mergeSort(nums, numsSize, left, mid);
    mergeSort(nums, numsSize, mid + 1, right);
    mergeTwoArr(nums, numsSize, left, mid, right);
}

void mergeSortArr(int* nums, int numsSize){
    mergeSort(nums, numsSize, 0, numsSize - 1);
}

// ---------------------Quick Sort-----------------------------------
int quickSortPartition_randomPivot(int* nums, int left, int right){
    srand(time(NULL));
    int randomNum = left + (rand() % (right - left + 1));
    swap(nums, left, randomNum);

    int dividePos = left;
    int pivot = nums[left];
    // 这里的循环不变量是 dividePos，即
    // [left + 1, dividepos] < pivot
    // [dividepos + 1, right) >= pivot
    for(int i = left + 1; i <= right; i++){
        if(nums[i] < pivot){
            dividePos++;
            swap(nums, i, dividePos);
        }
    }
    swap(nums, left, dividePos);
    return dividePos;
}

int quickSortPartition_threePart(int* nums, int left, int right){
    int mid = (left + right) / 2;
    if (nums[left] > nums[mid]) {
        swap(nums, left, mid);
    }
    if (nums[left] > nums[right]) {
        swap(nums, left, right);
    }
    if (nums[right] < nums[mid]) {
        swap(nums, right, mid);
    }

    swap(nums, mid, right - 1);
    int tmp = nums[right - 1];
    int i = left + 1;
    int j = right - 2;
    while(i <= j){
        if(nums[i] > tmp){
            while(nums[j] > tmp){
                if(i == j){
                    swap(nums, i, right - 1);
                    return i;
                }
                j--;
            }
            swap(nums, i, j);
            i++;
        }else{
            i++;
        }
    }
    return i;
}

void quickSort(int* nums, int left, int right, int mode){
    if(left >= right){
        return;
    }
    int p = 0;
    switch(mode){
        case 1:
            p = quickSortPartition_randomPivot(nums, left, right);
            break;
        case 2:
            p = quickSortPartition_threePart(nums, left, right);
            break;
    }
    quickSort(nums, left, p - 1, mode);
    quickSort(nums, p + 1, right, mode);
}

void quickSortArr(int* nums, int numsSize){
    if(numsSize < 2){
        return;
    }
    printf("Please Choose Mode\n 1 : randomPivot\n 2 : threeDivided\n");
    int mode = 0;
    scanf("%d\n", &mode);
    quickSort(nums, 0, numsSize - 1, mode);
}

// --------------------LinkedList----------------------------------

// Function to create a new node
LinkedNode* createNode(char value) {
    LinkedNode* newNode = (LinkedNode*)malloc(sizeof(LinkedNode));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

// Function to add a node at the tail
void addAtTail(LinkedList* list, char value) {
    LinkedNode* newNode = createNode(value);
    if (list->count == 0) {
        list->head = newNode;
    } else {
        LinkedNode* cur = list->head;
        while (cur->next != NULL) {
            cur = cur->next;
        }
        cur->next = newNode;
    }
    list->count++;
}

// Function to add a node at the head
void addAtHead(LinkedList* list, char value) {
    LinkedNode* newNode = createNode(value);
    if (list->count == 0) {
        list->head = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
    list->count++;
}

// Function to get a node at a given index
LinkedNode* get(LinkedList* list, int index) {
    if (list->count == 0 || index < 0 || index >= list->count) {
        return NULL;
    }
    LinkedNode* current = list->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

// Function to add a node at a given index
void addAtIndex(LinkedList* list, char value, int index) {
    if (list->count == 0 || index >= list->count) {
        return;
    }
    if (index <= 0) {
        addAtHead(list, value);
        return;
    }
    LinkedNode* prev = get(list, index - 1);
    LinkedNode* next = prev->next;
    LinkedNode* newNode = createNode(value);
    prev->next = newNode;
    newNode->next = next;
    list->count++;
}

// Function to remove a node at a given index
void removeAtIndex(LinkedList* list, int index) {
    if (list->count == 0 || index < 0 || index >= list->count) {
        return;
    }
    if (index == 0) {
        LinkedNode* temp = list->head;
        list->head = list->head->next;
        free(temp);
    } else {
        LinkedNode* prev = get(list, index - 1);
        LinkedNode* temp = prev->next;
        prev->next = prev->next->next;
        free(temp);
    }
    list->count--;
}