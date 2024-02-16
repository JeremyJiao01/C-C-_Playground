
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

