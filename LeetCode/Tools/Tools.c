//
// Test Sorting Algorithms performance
//

#include "Func.h"

int maxArea(int* height, int heightSize) {
    if(heightSize < 3){
        return 0;
    }
    int leftMax = height[0];
    int rightMax = height[heightSize - 1];
    int S = 0;
    int ans = 0;
    int left = 0;
    int right = heightSize - 1;
    while(left <= right){
        int minVal = leftMax < rightMax ? leftMax : rightMax;
        if(minVal == leftMax){
            if(height[left] >= leftMax){
                S = (right - left) * leftMax;
                ans = S > ans ? S : ans;
            }
            left++;
            leftMax = height[left] > leftMax ? height[left] : leftMax;
        }else{
            if(height[right] >= rightMax){
                S = (right - left) * rightMax;
                ans = S > ans ? S : ans;
            }
            right--;
            rightMax = height[right] > rightMax ? height[right] : rightMax;
        }
    }
    return ans;
}

int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
    int record[] = {1,8,6,2,5,4,8,3,7};
    int nums = maxArea(record, 9);
//    int tmp[5][5] = {0};
//    for(int i = 0; i < 5; i++){
//        printf("%d ", tmp[i][i]);
//    }
    printf("%d", nums);

    return 0;
}