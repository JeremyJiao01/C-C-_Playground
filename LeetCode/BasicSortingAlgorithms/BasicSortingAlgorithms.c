// 选择排序

void swap(int* nums, int minval, int i){
    int tmp = nums[minval];
    nums[minval] = nums[i];
    nums[i] = tmp;
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    for(int i = 0; i < numsSize - 1; i++){
        int minval = i;
        for(int j = i + 1; j < numsSize; j++){
            if(nums[j] < nums[minval]){
                minval = j;
            }
        }
        swap(nums, minval, i);
    }
    return nums;
}

// 插入排序

// 插入排序方法一
// 不断调换位置以达到有序
int* insertSorted1(int* nums, int numsSize){
    for(int i = 0; i < numsSize; i++){
        for(int j = i; j > 0; j--){
            if(nums[j] < nums[j-1]){
                swap(nums, j-1, j);
            }else{
                break;
            }
        }
    }
    return nums;
}

// 插入排序方法二
// 先将有序数组对调出一个空位，再将值插入
int* insertSorted2(int* nums, int numsSize){
    for(int i = 1; i < numsSize; i++){
        int temp = nums[i];
        int j = i;
        while(j > 0 && nums[j - 1] > temp){
            nums[j] = nums[j - 1];
            j--;
        }
        nums[j] = temp;
    }
    return  nums;
}
