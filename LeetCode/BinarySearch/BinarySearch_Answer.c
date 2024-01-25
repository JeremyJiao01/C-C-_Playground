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

int findDuplicate(int* nums, int numsSize){
	int left = 0;
	int right = numsSize - 1;
	int ans = -1;
	while(left < right){
		int mid = (left + right + 1) >> 1;
		int cnt = 0;
		int i = 0;
		for(int i = 0; i < n; i++){
			if(nums[i] <= mid){
				cnt++;
			}		
		}
		if(cnt > mid){
			right = mid - 1;
			ans = mid;
		}else{
			left = mid;
		}
	}
	return ans;
}
