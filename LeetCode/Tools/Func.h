
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>
#define genNum 10 // size of generated array
int generateNums(int n);

void Display(int* nums, int numsSize);

int* generateRandomArray(int n);

int* generateOrderedArray(int n, int degree);

int* generateReversedArray(int n, int degree);

void swap(int* nums, int i, int j);

int isSorted(int* nums, int numsSize);

int compare(const void *a, const void *b);

void testSortTime(int *nums, int numsSize, void(*sort_func)(int *, int));

//-----------------------------Choose Sort------------------------
void choseSortArray(int* nums, int numsSize);

//-----------------------------Merge Sort-------------------------
void mergeTwoArr(int* nums, int numsSize, int left, int mid, int right);
void mergeSort(int* nums, int numsSize, int left, int right);
void mergeSortArr(int* nums, int numsSize);

//-----------------------------Quick Sort-----------------------
int quickSortPartition_randomPivot(int* nums, int left, int right);
int quickSortPartition_threePart(int* nums, int left, int right);
void quickSort(int* nums, int left, int right, int mode);
void quickSortArr(int* nums, int numsSize);

//------------------------------CreatLinkedList----------------
// Node structure
typedef struct LinkedNode {
    char value;
    struct LinkedNode* next;
} LinkedNode;
// Linked List structure
typedef struct LinkedList {
    int count; // Length of the linked list
    LinkedNode* head;
} LinkedList;
LinkedNode* createNode(char value);
void addAtTail(LinkedList* list, char value);
void addAtHead(LinkedList* list, char value);
LinkedNode* get(LinkedList* list, int index);
void addAtIndex(LinkedList* list, char value, int index);
void removeAtIndex(LinkedList* list, int index);
