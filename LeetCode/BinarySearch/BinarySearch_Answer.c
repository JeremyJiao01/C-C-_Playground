// # 69 x的平方根
// 使用二分搜索：舍弃的范围是一个数的平方大于目标的范围
// 由于只返回整数，因此只需要返回一个小于等于目标值的数即可

int mySqrt(int x) {
   if(x == 0){
	return 0;
   }
   int left = 1;
   int right = x / 2; // 右指针需尽可能缩小搜索范围
   while(left < right){
	int mid = (left + right + 1) >> 1;
	if(mid > x / mid){ // 防止溢出所以调整为除法
		right = mid - 1;
	}else{
		left = mid;
	}
   }
   return left;
}

// # 287 寻找重复数
// 思路：
// 对于一个无序且有重复数字的数组
// 要找到其重复数字，我们需要计算每个数字的cnt值
// cnt[i] = nums[1 : n] <= i 的个数
// 即：当i <= target时，nums[1 : target - 1] 里的每个cnt[i] <= i
//     因为每个在target之前没有数字重复
//     使用这种方法就不用考虑查询的数组是否有序
//     因为判别依据是使用数组下标而不是数组内元素
int findDuplicate(int* nums, int numsSize){
	int left = 1; // 起始下标不需要为0，因为是通过下标判断
	int right = numsSize - 1;
	int ans = -1;
	while(left < right){
		int mid = (left + right) >> 1;
		int cnt = 0;
		int i = 0;
		for(int i = 0; i < n; i++){
			if(nums[i] <= mid){
				cnt++;
				// 计算当前下标的cnt值
			}		
		}
		if(cnt <= mid){ // 处于target之前
			left = mid + 1;
		}else{
			right = mid - 1;
			ans = mid;
		}
	}
	return ans;
}


// # 1300 转变数组后最接近目标值的数组和
//
// 方法一：
// 二分枚举法
// 1. 将数组按增序排序
// 2. 创建一个新的数组，长度为原数组+1，新数组从new[1]开始
//    每个位置i为原数组i及其之前所有元素的和
// 3. 遍历从1到原数组中的最大值（i）
//      1. 使用二分查找找到原数组中最接近i的值
//      2. 将大于i的所有数替换成i
//      3. 将元素组前i个的和后n-i个i的和相加 并与当前target相减的绝对值
//      4. 与之前得到的绝对差值比较，若小于之前的值，则保存

// 快速排序
void quick_sort(int* A, int low, int high){
    if(low >= high)
        return;
    int i = low, j = high;
    int temp = A[i];
    while(i<j){
        while(i<j && A[j] >= temp){
            j--;
        }
        A[i]=A[j];
        while(i<j && A[i] <= temp){
            i++;
        }
        A[j]=A[i];
    }
    A[i] = temp;
    quick_sort(A, low, i-1);
    quick_sort(A, i+1, high);
}

// 二分查找值的位置，若数组中不存在，则返回接近的最大值下标
int findLastpoint(int* nums, int numsSize, int target){
    int left =  0;
    int right = numsSize - 1;
    while(left < right){
        int mid = left + (right - left + 1)/2;
        if(nums[mid] <= target){
            if(nums[mid] == target){
                return mid;
            }
            left = mid;
        }
        else{
            right = mid - 1;
        }
    }
    return left + 1;
}

int findBestValue(int* arr, int arrSize, int target) {
    quick_sort(arr, 0, arrSize - 1);
    int* addNums = (int*)malloc((arrSize + 1)*sizeof(int));
    int i = 1;
    for(i = 1; i <= arrSize; i++){
        addNums[i] = arr[i - 1] + addNums[i - 1];
    }
    int max = arr[arrSize - 1];
    int ans = 0;
    int diff = target;
    for(i = 1; i <= max; i++){
        int cur = 0;
        if(i < arr[0]){
            // 若当前索引的值小于数组第一个元素的值
            // 则后续为此值 * 数组大小
            cur = arrSize * i;
        }else{
            int index = findLastpoint(arr, arrSize, i);
            cur = addNums[index] + (arrSize - index) * i;
        }
        if(abs(cur - target) < diff){
            ans = i;
            diff = abs(cur - target);
        }
    }
    free(addNums);
    addNums = NULL;
    return ans;
}

// 方法二：
// 双重二分查找
// 由于随着方法一中的前n项和是严格递增的
// 不存在两个不同的n项和，因此一定存在一个值
// 使得数组的和最接近且不大于target
// 通过二分查找我们能找到【最接近且不大于】与【最接近且不小于】的值
// 但是因为严格递增，所以【最接近且不大于】+ 1 就为【最接近且不小于】

int check(const int* arr, int size, int x) {
    int ret = 0;
    for (int i = 0; i < size; ++i) {
        ret += (arr[i] >= x ? x : arr[i]);
    }
    return ret;
}

// 快速排序
void quick_sort(int* A, int low, int high){
    if(low >= high)
        return;
    int i = low, j = high;
    int temp = A[i];
    while(i<j){
        while(i<j && A[j] >= temp){
            j--;
        }
        A[i]=A[j];
        while(i<j && A[i] <= temp){
            i++;
        }
        A[j]=A[i];
    }
    A[i] = temp;
    quick_sort(A, low, i-1);
    quick_sort(A, i+1, high);
}

// 二分查找值的位置，若数组中不存在，则返回接近的最大值下标
int findLastpoint(int* nums, int numsSize, int target){
    int left =  0;
    int right = numsSize - 1;
    while(left < right){
        int mid = left + (right - left + 1)/2;
        if(nums[mid] <= target){
            if(nums[mid] == target){
                return mid;
            }
            left = mid;
        }
        else{
            right = mid - 1;
        }
    }
    return left + 1;
}

int findBestValue(int* arr, int arrSize, int target) {
    quick_sort(arr, 0, arrSize - 1);
    int* addNums = (int*)malloc((arrSize + 1)*sizeof(int));
    int i = 1;
    for(i = 1; i <= arrSize; i++){
        addNums[i] = arr[i - 1] + addNums[i - 1];
    }
    int left = 0;
    int right = arr[arrSize - 1];
    int cur = 0;
    int ans = -1;
    while(left <= right){
        int mid = (left + right) / 2;
        if(mid < arr[0]){
            cur = mid * arrSize;
        }else{
            int index = findLastpoint(arr, arrSize, mid);
            cur = addNums[index] + (arrSize - index) * mid;
        }if(cur <= target){
            ans = mid;
            left = mid + 1;
        }else{
            right = mid - 1;
        }
    }
    int small = check(arr, arrSize, ans);
    int big = check(arr, arrSize, ans + 1);
    free(addNums);
    addNums = NULL;
    return abs(small - target) <= abs(big - target) ? ans : ans + 1;
}
