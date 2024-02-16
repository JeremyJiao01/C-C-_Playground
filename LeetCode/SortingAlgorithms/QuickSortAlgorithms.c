
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
