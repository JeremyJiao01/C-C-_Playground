// # 3 无重复字符的最长子串
// 使用滑动窗口的方法
// 滑动窗口可以理解为对暴力解法的优化
// 「暴力解法」通常以「二重循环」、「三重循环」的形式出现 优化的思路有
//		1. 以空间换时间：在遍历的过程中，记录变量的值，
//		   以使得每一次不同规模的区间的相关信息的计算不必从头开始；
//		2. 利用题目给出的性质，在枚举的过程中，能够一下子排除很多不必要的方案。
//
// 滑动窗口的解法思路为：
//		1. 双指针[left, right)，滑动窗口长度 = right - left
//		2. right++ 到数组内有重复元素时停止
//		3. left++ 直到越过重复元素，再重复第2步
//
// 这种 right 主动向右移动，left 被动向右移动的方式就是滑动窗口的思想，
// 也叫「尺取法」或者「虫取法」。
int lengthOfLongestSubstring(char* s){
	int len = strlen(s);
	if(len < 2){
		return len;
	}
	int Hash[128] = {-1};
    for(int i = 0; i < 128; i++){
        Hash[i] = -1;
    }
	// 将字符转换为ASCII码存在哈希表中
	int resLen = 1;
	for(int left = 0, right = 0; right < len; right++){
		Hash[s[right]]++;
		if(Hash[s[right]] == 2){
			while(Hash[s[right]] == 2){
				Hash[s[left]]--;
				left++;
			}
		}
		res = res > (right - left + 1) ? res : (right - left + 1);
	} 
	return res;
}
// 优化版本
// 哈希数组用ASCII码下标保存字母上一次出现的位置
// 若该位置大于left的位置，则直接将left移动到当前位置+1
int lengthOfLongestSubstring(char* s){
	int len = strlen(s);
	if(len < 2){
		return len;
	}
	int Hash[128] = {-1};
    for(int i = 0; i < 128; i++){
        Hash[i] = -1;
    }
	int res = 1;
    int left = 0;
	for(int right = 0; right < len; right++){
		if(Hash[s[right]] != -1){
			left = left > (Hash[s[right]] + 1) ? left : (Hash[s[right]] + 1);
		}
		Hash[s[right]] = right;
		res = res > (right - left + 1) ? res : (right - left + 1); 
	}
	return res;	
}

// # 76 覆盖最小子串
// 以 输入: S = "ADOBECODEBANC", T = "ABC" 为例
// 同样是使用滑动窗口的办法
// 我们需要对T内的字母进行频数统计
// 设置一个变量 distance 表示 T 中一共有多少个不同的字母
char minWindows(char* s, char* t){
	int window[128] = {0};
	int pattern[128] = {0};
	int A = 'A';
	int len = strlen(t);
	for(int i = 0; i < len; i++){
		pattern[t[i] - A]++;
	}
	int distance = 0; 
	//  T 中存在的字符数
	for(int i = 0; i < 128; i++){
		if(pattern[i] > 0){
			// pattern[i] > 0 表示 T 中存在 i 代表的元素
			distance++;
		}
	}
	int slen = strlen(s);
	int start = 0;
	int left = 0;
	int right = 0;
	int match = 0; // 用于保存[left, right)中与T相同字符的数量
	int minLen = slen + 1;

	while(right < slen){
		rightChar = s[right];
		if(pattern[rightChar - A] > 0){
			window[rightChar - A]++;
			// 在滑动窗口中记录存在的元素
			if(window[rightChar - A] == pattern[rightChar - A]){
				match++;
				// 当前元素存在于 T 中
			}
		}
		right++;
		while(match == distance){
			// 当所需元素都在[left, right)中，则需要保存此时的长度
			if(right - left < minLen){
				start = left;
				minLen = right - left;
			}
			// 考虑左边界向右边走
			leftchar = s[left];
			if(pattern[leftchar - A] > 0){
				window[leftchar - A]--;
				// 因为此时left需要++，所以要在window中去除当前元素
				if(window[leftchar - A] < pattern[leftchar - A]){
					match--;
				}
			}
			left++;
		}
	}
    if(minLen == sLen + 1){
        return "";
    }else{
        int returnSize = minLen;
        char* returnCharArr = (char*)malloc(sizeof(char) * returnSize);
        *returnCharArr = '\0';
        strncat(returnCharArr, s + start, returnSize);
        return returnCharArr;
    }
}

// # 209 长度最小的子数组
// 找出给定数组中，其总和大于等于target的长度最小的连续子数组
int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0;
    int right = 0;
    int count = 0;
    int minLen = numsSize + 1;
    while(right < numsSize){
        count += nums[right];
        while(count >= target){
            count -= nums[left];
            minLen = minLen < (right - left + 1) ? minLen : (right - left + 1);
            left++;
        }
        right++;
    }
    return minLen == (numsSize + 1) ? 0 : minLen; 
}


