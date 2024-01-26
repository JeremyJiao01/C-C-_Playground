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
