// 计数排序
void sort(int* nums, int numsSize){
	int max = nums[0];
	//找到数组中最大的元素
	for(int i = 1; i < numsSize; i++){
		if(nums[i] > max){
			max = nums[i];
		}
	}
	int countArr_length = max + 1;
	int* count = (int*)malloc(sizeof(int) * countArr_length);
	// 遍历数组，完成计数
	// 将数值作为数组下标记录
	for(int i = 0; i < numsSize; i++){
		count[nums[i]] += 1;
	}
	// 将count数组改造为前缀和数组
	// 前缀和即统计一个数，排在他前面数出现的次数之和
	for(int i = 1; i <= max; i++){
		count[i] += count[i - 1];
	}
	// 对原始数组做拷贝
	int* numsCopy = (int*)malloc(sizeof(int) * numsSize);
	for(int i = 0; i < numsSize; i++){
		numsCopy[i] = nums[i];
	}
	// 从后向前扫描，依次吧看到的数协会原始数组
	// 从后向前保证稳定性
	for(int i = numsSize - 1; i >= 0; i--){
		int position = count[numsCopy[i]] - 1;
		nums[position] = numsCopy[i];
		count[numsCopy[i]]--;
	}
}
