
// 快速排序1：
// 将pivote放在数组左侧
// 使用循环不变量divideLine以达到切分数组的效果

void swap(int* nums, int i, int j){
	int tmp = nums[i];
	nums[i] = nums[j];
	nums[j] = tmp;
}

int partition(int* nums, int left, int right){
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

void quickSort(int* nums, int left, int right){
	if(left >= right){
		return;
	}
	int p = partition(nums, left, right);
	quickSort(nums, left, p - 1);
	quickSort(nums, p + 1, right);
}

int* sortArr(int* nums, int numsSize){
	if(numsSize < 2){
		return nums; 
	}
	quickSort(nums, 0, numsSize - 1);
	return nums;
}

// 快速排序2
// 三分法
// 在快排的过程中，每一次我们要取一个元素作为枢纽值，
// 以这个数字来将序列划分为两部分。
// 在此我们采用三数取中法，也就是取左端、中间、右端三个数，
// 然后进行排序，将中间数作为枢纽值。

int partition(int* nums, int left, int right){
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
	int j = right - 1;
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

//-------------------------题目----------------------
// # 215 求数组中第k大的数
// 使用快速排序的思想
// 只要某次划分的 qqq 为倒数第 kkk 个下标的时候，我们就已经找到了答案
int quickselect(int *nums, int l, int r, int k) {
    if (l == r)
        return nums[k];
    int partition = nums[l], i = l - 1, j = r + 1;
    while (i < j) {
        do i++; while (nums[i] < partition);
        do j--; while (nums[j] > partition);
        if (i < j) {
            int tmp = nums[i];
            nums[i] = nums[j];
            nums[j] = tmp;
        }
    }
    if (k <= j)return quickselect(nums, l, j, k);
    else return quickselect(nums, j + 1, r, k);
}

int findKthLargest(int *nums, int numsSize, int k) {
    return quickselect(nums, 0, numsSize - 1, numsSize - k);
}

// 循环不变量练习
// # 26 删除有序数组中的重复项
// 思路：
// 使用双指针
// 相当于把不重复的元素移动到左边
// 若后一个 j 与前一个 i 值相等，则 j++
// 若不相等，则 i++; swap(nums, i, j); j++;
// 优化：当数组中没有重复元素，函数仍会原地复制一遍，
// 因此我们可以添加一个小判断，当 q - p > 1 时，才进行复制
int removeDuplicates(int* nums, int numsSize) {
    int i = 0;
    int j = 1;
    while(j <= numsSize - 1){
        if(nums[i] != nums[j]){
            if(j - i > 1){
                nums[i + 1] = nums[j];
            }
            i++;
        }
        j++;
    }
    return i + 1;
}

// # 80 删除有序数组中多余两个的重复项
int removeDuplicates(int* nums, int numsSize) {
    if (numsSize <= 2) {
        return numsSize;
    }
    int slow = 2, fast = 2;
    while (fast < numsSize) {
        if (nums[slow - 2] != nums[fast]) {
            nums[slow] = nums[fast];
            ++slow;
        }
        ++fast;
    }
    return slow;
}

