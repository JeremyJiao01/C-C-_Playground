//
// Test Sorting Algorithms performance
//

#include "Func.h"
int removeDuplicates(int* nums, int numsSize) {
    int i = 0;
    int j = 1;
    int tmp = 1;
    while(j <= numsSize - 1){
        if(nums[i] != nums[j]){
            tmp = 1;
            if(j - i > 1){
                nums[i + 1] = nums[j];
                j++;
            }else{
                j++;
            }
            i++;
        }else{
            tmp++;
            if(tmp <= 2){
                if(j - i > 1) {
                    nums[i + 1] = nums[j];
                }
                i++;
                j++;
            }
            if(tmp > 2){
                while(j <= numsSize - 1 && nums[i] == nums[j]){
                    j++;
                }
                if(j <= numsSize - 1){
                    i++;
                    nums[i] = nums[j];
                    j++;
                    tmp = 1;
                }
            }
        }
    }
    return i + 1;
}

int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
    int record[] = {1, 1, 1};
    int nums = removeDuplicates(&record, 3);
    for(int i = 0; i < nums; i++){
        printf("%d ", record[i]);
    }
    printf("%d", nums);
    return 0;
}