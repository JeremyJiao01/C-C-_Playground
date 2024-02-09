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

// 希尔排序
// 按照间隔初始值为数组长度，依次减半的方式

void shellSortAlg(int* nums, int gap, int end){
	int tmp = nums[end];
	int j = end;
	while(j >= gap && nums[j - gap] > tmp){
		nums[j] = nums[j - gap];
		j -= gqap;
	}
	nums[j] = tmp;
} 


int* shellSort(int* nums, int numsSize){
	int gap = numsSize / 2;
	while(gap >= 1){
		for(int i = 1; i < numsSize; i++){
			shellSortAlg(nums, gap, i);
		}
		gap /= 2;
	}
	return nums;
} 


// # 283 移动0
// 将数组中的0移动到后面，其他顺序不变
void moveZeroes(int* nums, int numsSize) {
    int cur = 0;
    int after = 0;
    while(after < numsSize){
        if(nums[after] != 0){
            nums[cur++] = nums[after];
        }
        ++after;
    }
    for(int i = cur; i < numsSize; i++){
        nums[i] = 0;
    }
}
