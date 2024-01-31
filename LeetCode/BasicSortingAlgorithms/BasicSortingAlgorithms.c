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
