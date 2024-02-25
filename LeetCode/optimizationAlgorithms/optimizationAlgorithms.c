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




