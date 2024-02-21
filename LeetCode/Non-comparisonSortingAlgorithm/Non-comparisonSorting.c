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

// 桶排序
// 桶：可以容纳一个范围内的数
// 1. 先将数组中的数归类在各自对应的桶中
// 2. 每个桶内部进行排序
// 3. 按顺序取出所有桶的数，即得到有序数组
// 以下是一些设定桶排序区间范围的注意事项：
// 		每个桶的区间范围应该尽可能均匀，以便每个桶中的元素数量大致相同。
// 		如果待排序数据的元素分布不均匀，可以采用哈希函数或自定义划分等方法来提高桶排序的效率。
// 		桶排序的时间复杂度与桶的数量成正比，因此桶的数量不宜过多。

void insertSort(int* nums, int numsSize){
	for(int i = 0; i <= numsSize; i++){
		int tmp = nums[i];
		int j = i;
		while(j > 0 && nums[j - 1] > tmp){
			nums[j] = nums[j - 1];
			j--;
		}
		nums[j] = tmp;
	}
}

void bucketSort(int* nums, int numsSize){
	int max = nums[0];
	// 找到数组中的最大值，以确定计数数组的长度
	for(int i = 0; i < numsSize; i++){
		if(nums[i] > max){
			max = nums[i];
		}
	}
	// 计算数组中最大的数的位数
	// 这个决定了需要几个桶
	int maxLen = getMaxLen(max);
	// 步长，步长决定了每个桶容纳数的范围区间
	int step = 1000;
	if(maxLen < 5){
		step = (int)pow(10, maxLen - 1);
	}

	int bucketLen = max / step + 1; // 确定桶的数量
	int tmp[bucketLen][numsSize] = {0}; 
	// 因为不确定每个桶内的元素数量，所以都设置为numsSize
	int next[bucketLen] = {0}; 

	// 分桶
	for(int i = 0; i < numsSize; i++){
		// 找到索引
		int bucketIndex = nums[i] / step;
		tmp[bucketIndex][next[bucketIndex]] = nums[i];
		// 找到第几个桶，然后这个将元素存在这个桶的位置
		next[bucketIndex]++;
		// 更新这个桶内元素的数量
	}

	// 对每个桶进行插入排序
	for(int i = 0; i < bucketLen; i++){
		insertSort(tmp[i], next[i] - 1);
	}

	// 将桶内元素依次取出
	int index = 0;
	for(int i = 0; i < bucketLen; i++){
		int curLen = next[i];
		for(int j = 0; j < curLen; j++){
			nums[index] = tmp[i][j];
			index++;
		}
	}
}

