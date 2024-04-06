//
// Test Sorting Algorithms performance
//

#include "Func.h"
// # 239 滑动窗口最大值
// 使用双端队列，实现单调队列
int* maxSlidingWindow(int* nums, int numsSize, int k) {
    int q[numsSize];
    int left = 0, right = 0;
    for (int i = 0; i < k; ++i) {
        // 找到窗口初始位置的最大值
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
    }
    int returnSize = 0;
    int* ans = malloc(sizeof(int) * (numsSize - k + 1));
    ans[(returnSize)++] = nums[q[left]];
    for (int i = k; i < numsSize; ++i) {
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            // 只需找到最大值即可，是否超出滑动窗口由下一个循环来判断
            right--;
        }
        q[right++] = i;
        while (q[left] <= i - k) {
            // 这里为什么是 (i - k) ，因为滑动窗口的原因
            // i - k，指向的是当前 i 所在窗口的第一个元素
            // 若q[left]（元素下标） 小于等于 窗口的第一个元素下标
            // 代表着当前q[left]（最大值），已经不在窗口内了，需要找到下一个最大值
            left++;
        }
        ans[(returnSize)++] = nums[q[left]];
    }
    return ans;
}


int main(){
    srand(time(NULL));

//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
    int record[] = {1,3,-1,-3,5,3,6,7};
    int* returnNums = 0;
    int* nums = maxSlidingWindow(record, 8, 3);
//    int tmp[5][5] = {0};
    for(int i = 0; i < 8; i++){
        printf("%d ", nums[i]);
    }
//    printf("%d", nums);

    return 0;
}