//
// Test Sorting Algorithms performance
//

#include "Func.h"





int main(){
    srand(time(NULL));

    int* randomArr = generateRandomArray(genNum);
    Display(randomArr, genNum);
    testSortTime(randomArr, genNum, mergeSortArr);

    return 0;
}