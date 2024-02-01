
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
    } else{
        printf("未排序\n");
        Display(nums, numsSize);
    }
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time Spent is %.6f second\n", time_spent);
}

// -----------------------Sorting Algorithms----------------------------

void randomizedQuicksort(int* nums, int left, int right){
    if(left < right){
        int pos = randomizedPartition(nums, left, right);
        randomizedQuicksort(nums, left, pos - 1);
        randomizedQuicksort(nums, pos + 1, right);
    }
}

int randomizedPartition(int* nums, int left, int right){
    int randomNum = rand() % genNum; // 使用随机数找到pivote
    swap(nums, right, randomNum); // 将pivote放在最右的位置
    return partition(nums, left, right);
}

int partition(int* nums, int left, int right){
    // 以pivote为标准，将数组分为两部分
    // 左边小于pivote，右边大于pivote
    int pivot = nums[right];
    int i = left - 1;
    for(int j = left; j <= right - 1; ++j){
        if(nums[j] <= pivot){
            i = i + 1;
            swap(nums, i, j);
        }
        swap(nums, i + 1, right);
        return i + 1;
    }
}

void sortArray(int* nums, int numsSize) {
    randomizedQuicksort(nums, 0, numsSize - 1);
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