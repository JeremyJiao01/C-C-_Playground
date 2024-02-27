//
// Test Sorting Algorithms performance
//

#include "Func.h"

int minSubArrayLen(int target, int* nums, int numsSize) {
    int left = 0;
    int right = 0;
    int count = 0;
    int start = 0;
    int minLen = 0;
    while(right < numsSize){
        count += nums[right];
        while(count > target){
            count -= nums[left];
            left++;
        }
        if(count == target){
            minLen = right - left + 1;
            // start = left;
        }
        right++;
    }
    return minLen;
}

int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
    int record[] = {1, 2, 3, 4, 5};
    int nums = minSubArrayLen(11, &record, 5);
//    int tmp[5][5] = {0};
//    for(int i = 0; i < 5; i++){
//        printf("%d ", tmp[i][i]);
//    }
    printf("%d", nums);

    return 0;
}