#include <stdio.h>

// # 704

// 给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
// 如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

int searchInsert(int* nums, int numsSize, int target) {
    if(nums == NULL){
        return 0;
    }
    int left = 0;
    int right = numsSize;
    while(left < right){
        int mid = (right + left) >> 1;
        if(nums[mid] < target){
            left = mid + 1;
        }
        else{
            right = mid;
        }
    }
    return left;
}

// # 153 查找数组出现相同数字的第一个和最后一个位置

// 给你一个按照非递减顺序排列的整数数组nums 和一个目标值target。
// 请你找出给定目标值在数组中的开始位置和结束位置。
// 如果数组中不存在目标值target,返回[-1, -1]。

// 在这种情况下，需要确认两个位置，则一个使用向下取整，一个使用向上取整即可

int SearchFirstPos(int* nums, int numsSize, int target, int* arr){
	int left = 0;
	int right = numsSize - 1;
	while(left < right){
		int mid = left + (right - left)/2;
		if(nums[mid] >= target){
			if(nums[mid] == target){
				arr[0] = mid;		
			}
			right = mid;
		}
		else{
			left = mid + 1;
		}
	}
	return arr[0];
}

void SearchLastPos(int* nums, int numsSize, int target, int*arr){
	int left =  0;
	int right = numsSize - 1;
	while(left < right){
		int mid = left + (right - left + 1)/2;
		if(nums[mid] <= target){
			if(nums[mid] == target){
				arr[1] = mid;
			}
			left = mid;
		}
		else{
			right = mid - 1;
		}
	}
}

int* searchRange(int* nums, int numsSize, int target, int* returnSize) {
	int* arr = (int*)malloc(2*sizeof(int));
	arr[0] = -1;
	arr[1] = -1;
	if(nums == NULL){
		return arr;
	}
	int firstpos = SearchFirstPos(nums, numsSize, target, arr);
	if(firstpos != -1){
		SearchLastPos(nums, numsSize, target, arr);
	}
	return arr;
}

// # 154 寻找旋转排序数组中的最小值

// 已知一个长度为 n 的数组，预先按照升序排列，
// 经由 1 到 n 次旋转后，得到输入数组。

// 例：数组 [a[0], a[1], a[2], ..., a[n-1]] 旋转一次的结果
// 为数组 [a[n-1], a[0], a[1], a[2], ..., a[n-2]]

// 给你一个元素值 [互不相同] 的数组 nums ，
// 它原来是一个升序排列的数组，并按上述情形进行了多次旋转。
// 请你找出并返回数组中的 [最小元素] 。

/*
 * 在旋转后有两种情况
 *
 * 值
 * ^
 * |             最小值
 * |             O |
 * |          O    | 
 * |       O       |
 * |----O---------------------O-----------
 * |               |            
 * |               |       O
 * |               |   O
 * |               O
 * |__________________________________> 索引
 */

//  设数组最后一个元素为x
//  在最小值右侧的值都严格 < x
//  在最小值左侧的值都严格 > x
//  1. 同样设 left 和 right , 当nums[mid] < nums[right]时
//     即 nums[mid] 为最小值右侧的元素，则忽略右半部分
//  2. 当 nums[mid] > nums[right] 时
//     nums[mid] 为最小值左侧的元素，因此可以忽略左半部分

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    while(left < right){
        int mid = (left + right) >> 1;
        if(nums[mid] < nums[right]){
            right = mid;
        }else{
            left = mid + 1;
        }
    }   
    return nums[left];
}

// # 34 寻找旋转排序数组中的最小值 II
// 与 I 不同点在于，数组中存在重复数字

int findMin(int* nums, int numsSize) {
    int left = 0;
    int right = numsSize - 1;
    while(left < right){
        int mid = (left + right) >> 1;
        if(nums[mid] < nums[right]){
            right = mid;
        }else if(nums[mid] > nums[right]){
            left = mid + 1;
        }else{
	    // 当mid指向的元素值与右指针相等时
	    // mid所指元素不为最小值，因此只需将搜索范围减少
	    // 即right--
            right -= 1;
        }
    }   
    return nums[left];
}

// # 33 搜索旋转数组
// 寻找旋转数组中的元素
// 由于数组旋转后，必会有两部分，这两部分局部有序
// 因此只需找到target在的区域

int search(int* nums, int numsSize, int target) {
    if (nums == NULL || numsSize <= 0) {
        return -1;
    }
    int left = 0;
    int right = numsSize - 1;

    // 循环条件修改
    while (left < right) {
        int mid = (left + right) / 2; // 防止溢出
        if (nums[mid] == target) {
            return mid;
        }

        // 针对旋转数组的判断逻辑修改
        if (nums[mid] >= nums[left]) {
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }

    // 考虑 target 等于 right 的情况
    return (nums[right] == target) ? right : -1;
}

// # 81 搜索旋转排序数组 II
// 排序数组中存在重复数字，若target存在返回true，否则返回false

bool search(int *nums, int numsSize, int target) {
    if (nums == NULL || numsSize <= 0) {
        return false;
    }
    int left = 0;
    int right = numsSize - 1;

    // 循环条件修改
    while (left < right) {
        int mid = (left + right) / 2; // 防止溢出
        if (nums[mid] == target) {
            return true;
        }
        if (nums[left] == nums[mid] && nums[mid] == nums[right]) {
            // 因为存在重复数字，当两端都是重复数字时，缩小查找范围
            ++left;
            --right;
        } else if (nums[mid] >= nums[left]) {
            if (target >= nums[left] && target < nums[mid]) {
                right = mid - 1;
            } else {
                left = mid + 1;
            }
        } else {
            if (target > nums[mid] && target <= nums[right]) {
                left = mid + 1;
            } else {
                right = mid - 1;
            }
        }
    }
    // 考虑 target 等于 right 的情况
    return (nums[right] == target) ? true : false;
}

// # 852 山脉数组的峰顶索引
// 山脉数组：arr.length >= 3, 存在
// arr[0] < arr[1] < ... < arr[i] > arr[i + 1] > ... > arr[arr.length - 1]
// 返回峰顶下标 i 

// 方法一：将大于前一个作为判断条件
int peakIndexInMountainArray(int* arr, int arrSize) {
    int left = 1;
    int right = arrSize - 2;
    int ans = 1;
    while(left < right){
        int mid = (left + right + 1) / 2;
        if (arr[mid] > arr[mid - 1]){
            left = mid;
            ans = mid;
        }else{
            right = mid - 1;
        }
    }
    return ans;

// 方法二：将大于后一个作为判断条件
int peakIndexInMountainArray(int* arr, int arrSize) {
    int n = arrSize;
    int left = 1, right = n - 2, ans = 0;
    while (left <= right) {
        int mid = (left + right) / 2;
        if (arr[mid] > arr[mid + 1]) {
            ans = mid;
            right = mid - 1;
        } else {
            left = mid + 1;
        }
    }
    return ans;
}


// # 1095 山脉数组中查找目标值
// 思路：1. 先找到峰值
// 	 2. 在左侧寻找target
// 	 3. 若左侧没有则寻找右侧

// 1. 使用二分法找到峰值
int findMax_Index(int* nums, int numsSize){
    int left = 1;
    int right = numsSize - 2;
    int ans = 0;
    while(left <= right){
        int mid = (left + right) / 2;
        if (nums[mid] > nums[mid + 1]){
            right = mid - 1;
            ans = mid;
        }else{
            left = mid + 1;
        }
    }
    return ans;
}

// 2. 普通二分查找
// 对于二分搜索，由于山峰右侧为单调递减
// 因此当利用同一个函数时，需要设置flag
// 使用负数实现单调递增再进行后续的判断

int binarySearch(int* nums, int target, int left, int right, bool flag){
    if (!flag){
        target *= -1;
    }
    while(left <= right){
        int mid = (right + left) / 2;
        int cur = nums[mid] * (flag ? 1 : -1);
        if (cur == target) {
            return mid;
        } else if (cur < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    return -1;
}

int findInint(int target, int* nums, int numsSize) {
    int peak = findMax_Index(nums, numsSize);
    int left = binarySearch(nums, target, 0, peak, true);
    if (left == -1){
        return binarySearch(nums, target, peak + 1, numsSize - 1, false);
    }
    return left;
}


// # 4 寻找两个正序数组的中位数
// 求中位数 = 求第 k 小的数
// 理想情况：两数组中无重复元素
// 则查找第 k 小的数即：
// 1. A数组中的k/2（向下取整）+ B数组中的k/2（向下取整）
//    若A[k/2] < B[k/2]则A[0]~A[k/2]都舍弃
// 2. 由于排除了k/2个，此时k = K - K/2，再重复第一步中的操作
// 3. 当一个数组中所有元素都被舍弃，则直接在另一数组中找值即可 

int min (int a, int b) {
    if (a>b)
        return b;
    else
        return a;
}

// 求第k个值
int getKnum(int* nums1, int start1, int end1, int* nums2, int start2, int end2, int k){
    int len1 = end1 - start1 + 1;
    int len2 = end2 - start2 + 1;
    if(len1 > len2) return getKnum(nums2, start2, end2, nums1, start1, end1, k); // 始终保证nums1的数组小于nums2的数组
    if(len1 == 0) return nums2[start2 + k - 1];
    if(k == 1) return min(nums1[start1], nums2[start2]);
    
    int i = start1 + min(len1, k/2) - 1;
    int j = start2 + min(len2, k/2) - 1;

    if(nums1[i] > nums2[j]){
	// 通过判断舍弃数组前k个元素
        return getKnum(nums1, start1, end1, nums2, j + 1, end2, k - (j-start2 + 1));
    }else{
        return getKnum(nums1, i + 1, end1, nums2, start2, end2, k - (i - start1 + 1));
    }
}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
    int n = nums1Size;
    int m = nums2Size;
    int left = (n + m + 1) / 2;
    int right = (n + m + 2) / 2;
    return (getKnum(nums1, 0, n - 1, nums2, 0, m - 1, left) + getKnum(nums1, 0, n - 1, nums2, 0, m - 1, right)) * 0.5; 
    // 取平均数，因为可能出现奇数和偶数
}
