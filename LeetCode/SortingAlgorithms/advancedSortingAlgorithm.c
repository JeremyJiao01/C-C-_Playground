// mergeSort
// 使用递归的方法，不断将数组分为两个有序的部分
// 在对数组进行有序合并

void mergeSort(int* nums, int numsSize, int left, int right){
	if(left == right){
		return;
	}
	int mid = (left + right) / 2;
	mergeSort(nums, left, mid);
	mergeSort(nums, mid + 1, right);
	mergeTwoArr(nums, numsSize, left, mid, right);
}

void mergeTwoArr(int* nums, int numsSize, int left, int mid, int right){
	int len = right - left + 1;
	int* tempArr = (int*)malloc(len * sizeof(int));
	int i = left;
	int j = mid + 1;
	int k = 0;
	// 判断指针下标是否越界
	while(i <= mid && j <= right){
		if(nums[i] <= nums[j]){
			tempArr[k++] = nums[i++];
		}else{
			tempArr[k++] = nums[j++];
		}
	}
	// 剩下的直接将数组中的值复制进去
	while(i <= mid){
		tempArr[k++] = nums[i++];
	}
	while(j <= right){
		tempArr[k++] = nums[j++];
	}
	// 重新排列原数组
	int b = 0; 
	for(int a = left; a <= right; a++){
		nums[a] = temp[b++];
	}
}

int* sortArr(int* nums, int numsSize){
	mergeSort(nums, numsSize, 0, len - 1);
	return nums;
}
