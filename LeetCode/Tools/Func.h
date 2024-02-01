
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#define genNum 20 // size of generated array
int generateNums(int n);

void Display(int* nums, int numsSize);

int* generateRandomArray(int n);

int* generateOrderedArray(int n, int degree);

int* generateReversedArray(int n, int degree);

void swap(int* nums, int i, int j);

int isSorted(int* nums, int numsSize);

int compare(const void *a, const void *b);

void testSortTime(int *nums, int numsSize, void(*sort_func)(int *, int));

//-----------------------------QUICK SORT-------------------------
void randomizedQuicksort(int* nums, int left, int right);
int randomizedPartition(int* nums, int left, int right);
int partition(int* nums, int left, int right);
void sortArray(int* nums, int numsSize);

//-----------------------------Chose Sort------------------------
void choseSortArray(int* nums, int numsSize);