//
// Test Sorting Algorithms performance
//

#include "Func.h"

int mergingTwoArr(int* record, int left, int mid, int right, int* tmp){
    int len = right - left + 1;
    int i = left;
    int j = mid + 1;
    int count = 0;
    int k = 0;
    while(i <= mid && j <= right){
        if(record[i] <= record[j]){
            tmp[k] = record[i];
            k += 1;
            i += 1;
        }else{
            tmp[k] = record[j];
            k += 1;
            j += 1;
            count += 1;
        }
    }
    while(i <= mid){
        tmp[k] = record[i];
        k += 1;
        i += 1;
    }
    while(j <= right){
        tmp[k] = record[j];
        k += 1;
        j += 1;
    }
    int b = 0;
    for(int i = left; i <= right; i++){
        record[i] = tmp[b];
        b += 1;
    }
    return count;
}

int dividePairs(int* record, int left, int right, int* tmp){
    if(left == right){
        return 0;
    }
    int mid = left + (right - left) / 2;
    int leftParis = dividePairs(record, left, mid, tmp);
    int rightParis = dividePairs(record, mid + 1, right, tmp);

    if(record[mid] <= record[mid + 1]){
        return leftParis + rightParis;
    }
    int acrossParis = mergingTwoArr(record, left, mid, right, tmp);
    return leftParis + rightParis + acrossParis;
}


int reversePairs(int* record, int recordSize) {
    if(recordSize < 2){
        return 0;
    }
    int* tmp = (int*)malloc(recordSize * sizeof(int));
    return dividePairs(record, 0, recordSize - 1, tmp);
}




int main(){
//    srand(time(NULL));

//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, mergeSortArr);
    int record[4] = {7, 5, 6, 4};
    int nums = reversePairs(&record, 4);
    printf("%d", nums);
    return 0;
}