
// 第一种思路使用三个分支来分别判断mid下一次的位置
int Search(int nums[], int numsSize, int target){
	int left = 0;
	int right = numsSize - 1;
	while(left <= right){
	int mid = (left + right) >> 1; // 使用位运算能够减少运算时间
				       // 但有可能产生溢出
	// int mid = left + (right - 1)/2 这种方法能够避免内存溢出
	if(nums[mid] == target)
		return mid;
	else if(nums[mid] <= target)
		left = left + 1;
	else if(nums[mid] >= target)
		right = right - 1;
	}
	return -1;
}

// 第二种分支的思路是：
// 将需要搜索的数组分为两部分当目标不在一部分内，则直接转到第二个部分
// 即while的判断条件为(left < right)
int Search(int nums[], int numsSize, int target){
	int left = 0;
	int right = len - 1; // 这里因为是数组所以-1
	while(left < right){
		int mid = left + (right - left + 1)/2
			// 这里(right - left + 1)是实现向上取整
			// 因为在while的判断中，最后一次会存在两个元素
			// 若不使用向上取整，则会导致死循环
		if(nums[mid] > target){
			right = mid - 1;
		}
		else{
			left = mid;
		}
	}
	if(nums[left] == target){
		return left;
	}
	return -1;
}
