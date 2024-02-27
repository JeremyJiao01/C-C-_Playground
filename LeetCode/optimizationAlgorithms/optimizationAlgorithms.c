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

// # 438.找到字符串中所有字母异位词
// 异位词 指由相同字母重排列形成的字符串（包括相同的字符串）
int* findAnagrams(char * s, char * p, int* returnSize){
    int sLen = strlen(s);
    int pLen = strlen(p);
    int* res = (int*)malloc(sizeof(int) * sLen);
    int resAddPos = 0;
    *returnSize = 0;
    if(sLen < pLen){
        return res;
    }
    //表示字母出现次数差距
        //count[x] = 0  表示 s与p中字母x出现次数相同 都出现了n次(n>=0)
        //count[x] = n  表示 在s中字母x出现次数比p多 多出现了n次(n>0)
        //count[x] = -n 表示 在s中字母x出现次数比p少 少出现了n次(n>0)    
    int count[26] = {0};
    for(int i = 0; i < pLen; i++){
        ++count[s[i] - 'a'];
        --count[p[i] - 'a'];
    }
    // 表示字母差异个数
    int differ = 0;
    for(int j = 0; j < 26; j++){
        if(count[j] != 0){
            ++differ;
        }
    }
    if(differ == 0){
        res[resAddPos] = 0;
        resAddPos++;
    }
    //向右滑动
    for(int i = 0; i < sLen - pLen; i++){
        //缩减时只考虑count[x]==1与count[x]==0的情况
        //因为缩减时字母x减少，count[x]会减去1
        //(1)count[x]==1时(次数差距1次，不相同)  
        //count[x]==0 -> 次数相同 -> 不相同变相同，字母差异个数减少1 -> differ--

        //(2)count[x]==0时(次数相同)  
        //count[x]==-1 -> 次数差距变为1次->相同变不相同 ，字母差异个数增加1 -> differ++

        //(3)count[x]==-1时(次数不相同) -> count[x]==-2 次数还是不相同-> 字母差异数不变

        //(4)count[x]==2时(次数不相同)  -> count[x]==1 次数还是不相同-> 字母差异数不变
        if(count[s[i] - 'a'] == 1){
            //窗口中s子串左边减少一个s[i]的数量(把原来多出来的1个s[i]去掉，变得相同)
            //两个字符串字母差距缩小 
            --differ;           
        }else if(count[s[i] - 'a'] == 0){
            //窗口中s子串左边减少一个s[i]的数量(把原来相同数量的s[i]的减少了1个，数量变得不相同)
            //两个字符串字母差距增大      
            ++differ;      
        }
        //窗口中s子串左边减少一个字母s[i]
        --count[s[i] - 'a'];  

        //添加时只考虑count[x]==-1与count[x]==0的情况，原因分析与缩减时类似
        //右添加一位，i+pLen
        if (count[s[i + pLen] - 'a'] == -1) {  
            //窗口中s子串右边增加一个s[i+pLen]的数量(把原来缺少的1个s[i]加上，数量变得相同)
            //两个字符串字母差距缩小
            --differ;
        } else if (count[s[i + pLen] - 'a'] == 0) {  
            //窗口中s子串右边增加一个s[i+pLen]的数量(把原来相同数量的s[i]多加了1个，变得不相同)
            //两个字符串字母差距增大
            ++differ;
        }
        //窗口中s子串右边增加一个字母s[i+pLen]
        ++count[s[i + pLen] - 'a'];
        //两个字符串字母差距为0
        if (differ == 0) {
            res[resAddPos] = i + 1;
            resAddPos++;
        }
    }
    *returnSize = resAddPos;
    return res;                
}

// #567 字符串的排序
bool checkInclusion(char* s1, char* s2) {
    int s1Len = strlen(s1);
    int s2Len = strlen(s2);
    if(s1Len > s2Len){
        return false;
    }
    int cnt[26] = {0};
    memset(cnt, 0, sizeof(cnt));
    for(int i = 0; i < s1Len; i++){
        --cnt[s1[i] - 'a'];
        ++cnt[s2[i] - 'a'];
    }
    int diff = 0;
    for(int i = 0; i < 26; i++){
        if(cnt[i] != 0){
            diff++;
        }
    }
    if(diff == 0){
        return true;
    }
    for(int i = s1Len; i < s2Len; i++){
        int x = s2[i] - 'a', y = s2[i - s1Len] - 'a';
        if(x == y){
            continue;
        }
        if(cnt[x] == 0){
            ++diff;
        }else if(cnt[x] == -1){
            --diff;
        }
        ++cnt[x];

        if(cnt[y] == 0){
            ++diff;
        }else if(cnt[y] == 1){
            --diff;
        }
        --cnt[y];
        
        if(diff == 0){
            return true;
        }
    }
    return false;
}
