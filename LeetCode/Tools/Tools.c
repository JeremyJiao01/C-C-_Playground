//
// Test Sorting Algorithms performance
//

#include "Func.h"

int characterReplacement(char * s, int k){
    int window[256] = {0};
    int right = 0;
    int left = 0;
    int A = 'A';
    int sLen = strlen(s);
    int maxLen = 1;
    window[s[0] - A]++;
    while(right < sLen){
        if(window[s[right] - A] == 0){
            k--;
            while(k < 0){
                window[s[left] - A]--;
                if(window[s[left] - A] == 0){
                    k++;
                }
                left++;
            }
        }
        if(k >= 0){
            maxLen = maxLen > (right - left + 1) ? maxLen : (right - left + 1);
        }
        right++;
    }
    return maxLen;
}

int main(){
//    srand(time(NULL));
//
//    int* randomArr = generateRandomArray(genNum);
//    Display(randomArr, genNum);
//    testSortTime(randomArr, genNum, quickSortArr);
    char record[] = "AABACBBA";
    int nums = characterReplacement(record, 2);
//    int tmp[5][5] = {0};
//    for(int i = 0; i < 5; i++){
//        printf("%d ", tmp[i][i]);
//    }
    printf("%d", nums);

    return 0;
}