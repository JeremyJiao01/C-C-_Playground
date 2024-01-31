
// 快速排序1：
// 将pivote放在数组右侧
void randomizedQuicksort(int* nums, int left, int right){
    if(left < right){
        int pos = randomizedPartition(nums, left, right);
        randomizedQuicksort(nums, left, pos - 1);
        randomizedQuicksort(nums, pos + 1, right);
    }
}

int randomizedPartition(int* nums, int left, int right){
    srand(time(NULL));
    int randomNum = rand(); // 使用随机数找到pivote
    swap(nums, right, randomNum); // 将pivote放在最右的位置
    return partition(nums, left, right);
}

int partition(int* nums, int left, int right){
    // 以pivote为标准，将数组分为两部分
    // 左边小于pivote，右边大于pivote
    int pivot = nums[right];
    int i = left - 1;
    for(int j = left; j <= right - 1; j++){
        if(nums[j] <= pivot){
            i = i + 1;
            swap(nums, i, j);
        }
        swap(nums, i + 1, r);
        return i + 1;
    }
}

void swap(int* nums, int i, int j){
    int temp = nums[i];
    nums[i] = nums[j];
    nums[j] = temp;
}

int* sortArray(int* nums, int numsSize, int* returnSize) {
    randomizedQuicksort(nums, 0, numsSize - 1);
    return nums;
}
