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

// 低位优先的基数排序
// 按照个、十、百的顺序对数值进行排序操作
// 低位优先的基数排序，越高位的排序是放在后面进行的，
// 在高位相同的情况下，需要比较次高位，而次高位在之前的排序中已经排好序。
// 每一趟基于关键字的排序 必须使用稳定排序

int getMaxLen(int num){
	int maxlen = 0;
	while(num > 0){
		num /= 10;
		maxlen++;
	}
	return maxlen;
}

void countingSort(int* nums, int* tmp, int divisor, int len, int* count){
	// 内层循环将数组从头遍历一遍
	for(int j = 0; j < len; j++){
		// 计算指定数位上的数是几
		int remainder = (nums[j] / divisor) % 10;
		count[remainder]++;
	}
	for(int j = 1; j< 10; j++){
		count[j] += count[j - 1];
	}
	for(int j = len - 1; j >= 0; j--){
		int remainder = (nums[j] / divisor) % 10;
		int index = count[remainder] - 1;
		tmp[index] = nums[j];
		count[remainder]--;
	}
	for(int j = 0; j < 10; j++){
		count[j] = 0;
	}
}

void radixSort(int* nums, int numsSize){
	int max = nums[0];
	for(int i = 0; i < len; i++){
		if(nums[i] > max){
			max = nums[i];
		}
	}
	// 计算出最大的数字有几位
	// 这个数值决定了我们要将整个数组看几遍
	int maxlen = getMaxLen(max);
	// 每一趟都适用计数排序
	int* count = (int*)malloc(sizeof(int) * 10);
	int* tmp = (int*)malloc(sizeof(int) * numsSize);
	int divisor = 1;
	for(int i = 0; i < maxlen; i++){
		// 每一步都使用计数排序
		countingSort(nums, tmp, divisor, len, count);
		int* numsCopy = (int*)malloc(sizeof(int) * numsSize);
		for(int i = 0; i < numsSize; i++){
				numsCopy[i] = nums[i];
		}
		divisor *= 10;
	}
} 

