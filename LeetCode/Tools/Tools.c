//
// Test Sorting Algorithms performance
//

#include "Func.h"

int lengthOfLongestSubstring(char* s){
    int len = strlen(s);
    if(len < 2){
        return len;
    }
    int Hash[128] = {-1};
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

int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
//    int record[] = {1, 1, 1};
//    int nums = removeDuplicates(&record, 3);
//    int tmp[5][5] = {0};
//    for(int i = 0; i < 5; i++){
//        printf("%d ", tmp[i][i]);
//    }
//    printf("%d", nums);
    char s[] = "ABCDE";
    int returnSize = 5;
    char* returnCharArr = (char*)malloc(sizeof(char) * returnSize);
    for(int i = 0; i < returnSize; i++){
        if(i == returnSize){
            returnCharArr[i] = '\0';
        }else{
            returnCharArr[i] = s[i];
        }
    }
    int n = strlen(returnCharArr);
    printf("%d", n);
    for(int i = 0; i < returnSize; i++){
        printf("%s", returnCharArr[i]);
    }
    return 0;
}