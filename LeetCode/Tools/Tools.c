//
// Test Sorting Algorithms performance
//

#include "Func.h"




int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
//    int record[] = {1,8,6,2,5,4,8,3,7};
//    int nums = maxArea(record, 9);
//    int tmp[5][5] = {0};
    for(int i = 0; i < 3; i++){
        printf("%d ", i);
    }
//    printf("%d", nums);
    NODE L;
    initnode(&L, 0);
    CreatList(L, 6);
    PrintList(L);
    return 0;
}