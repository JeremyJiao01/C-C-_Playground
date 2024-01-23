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
