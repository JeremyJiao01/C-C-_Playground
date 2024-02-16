//
// Test Sorting Algorithms performance
//

#include "Func.h"


int main(){
    srand(time(NULL));

    int* randomArr = generateRandomArray(genNum);
    Display(randomArr, genNum);
    testSortTime(randomArr, genNum, quickSortArr);
//    int record[4] = {-1, -1};
//    int* nums = countSmaller(&randomArr, genNum);
//    for(int i = 0; i < genNum; i++){
//        printf("%d ", nums[i]);
//    }

    return 0;
}