typedef struct {
    int* data;
    int capacity; // 堆能储存的最大容量
    int size; // 真正储存的元素个数
} Heap;

int heapSize(Heap* heap){
    return heap.size;
}

bool isEmpty(Heap* heap){
    return heap.size == 0;
}

int peek(Heap* heap){
    if(isEmpty){
        return 0;
    }
    return heap.data[1];
}

Heap* maxHeap(int capacity){
    // 下标0不存元素，因此需要空间为capacity + 1
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap.data = (int*)malloc(sizeof(int) * (capacity + 1));
    heap.capacity = capacity;
    heap.size = 0;
    return heap;
}

void offer(Heap* heap, int item){
    if(heap.size + 1 > capacity){
        return;
    }
    heap.data[heap.size + 1] = item;
    heap.size++;
    siftUp(heap);
}

void swap(int* data, int a, int b){
    int tmp = data[a];
    data[a] = data[b];
    data[b] = tmp;
}

void siftUp(Heap* heap, int k){
    while(heap.size > 1 && heap.data[k / 2] < data[heap.size]){
        // data[k/2]是父节点
        swap(heap.data, heap.size/2, heap.size);
        heap.size /= 2;
    }
}

int poll(Heap* heap, int x){
    if(heap.size == 0){
        return 0;
    }
    int ret = heap.data[1];
    heap.data[1] = heap.data[heap.size];
    // 把最后一个元素的值赋值到堆的根节点
    heap.size--;
    siftDown(heap, 1);
    // 再将根节点向下移动
    return ret;
}

void siftDown(Heap* heap, int k){
    while(2 * k <= heap.size){
        int j = 2 * k;
        // j + 1 为 k 的右孩子，因为0位置不存元素
        if(j + 1 <= heap.size && heap.data[j + 1] > heap.data[j]){
            // 右孩子大于左孩子
            j++;
        }
        if(heap.data[k] >= heap.data[j]){
            break;
        }
        swap(heap.data, k, j);
        k = j;
    }
}

void replace(Heap* heap, int item){
    if(isEmpty()){
        return;
    }
    heap.data[1] = item;
    siftDown(Heap, 1);
}

// 将数组整理成堆
// 1. 自顶而下：从非根节点开始逐个向上移动 O(N log N)
// 2. 自底而上：从非叶节点开始逐个向下移动 O(N)
Heap* arr2maxHeap(int* arr, int arrSize){
    Heap* heap = (Heap*)malloc(sizeof(Heap));
    heap.capacity = arrSize + 1;
    heap.data = (int*)malloc(sizeof(int) * capacity);
    heap.size = arrSize;
    for(int i = 0; i > heap.size; i++){
        heap.data[i + 1] = arr[i];
    }
    for(int i = heap.size / 2; i >= 1; i-- ){
        // 从最后一个非叶子结点开始
        siftDown(i);
    }
    return heap;
}

// # 912 排序数组（堆排序）
void heapify(int* nums, int numsSize){
    for(int i = (numsSize - 1) / 2; i >= 0; i--){
        siftDown(nums, i, len - 1);
    }
}
void siftDown(int* nums, int k, int end){
    while(k * 2 + 1<= end){
        int j = k * 2 + 1;
        if(j + 1 <= end && nums[j + 1] > nums[j]){
            j++;
        }
        if(nums[j] > nums[k]){
            swap(nums, j, k);
        }else{
            break;
        }
        k = j;
    }      
}
int* sortArr(int* nums, int numsSize){
    heapify(nums, numsSize);
    for(int i = numsSize - 1; i >= 1;){
        swap(nums, 0, i);
        i--;
        siftDown(nums, 0, i);
    }
    return nums;
}

// # 215 数组中第K个最大元素
typedef struct{
    int* data;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* InitPQ(int capacity){
    PriorityQueue* pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    pq->data = (int*)malloc((capacity+1)*sizeof(int));
    pq->size = 0;
    pq->capacity = capacity;
    return pq;
}

void freePq(PriorityQueue* pq){
    free(pq->data);
    free(pq);
}

void siftUp(PriorityQueue* pq, int k){
    int tmp = pq->data[k];
    while(k > 1 && pq->data[k / 2] > tmp){
        pq->data[k] = pq->data[k / 2];
        k /= 2;
    }
    pq->data[k] = tmp;
}

void siftDown(PriorityQueue* pq, int k){
    int tmp = pq->data[k];
    while(2 * k <= pq->size){
        int j = 2 * k;
        if(j < pq->size && pq->data[j] > pq->data[j + 1]){
            j++;
        }
        if(pq->data[j] >= tmp){
            break;
        }else{
            pq->data[k] = pq->data[j];
            k = j;
        }
    }
    pq->data[k] = tmp;
}

void offer(PriorityQueue* pq, int item){
    if(pq->size + 1 > pq->capacity){
        pq->capacity *= 2;
        pq->data = (int*)realloc(pq->data, (pq->capacity + 1) * sizeof(int));
    }
    pq->data[++pq->size] = item;
    siftUp(pq, pq->size);
}

int poll(PriorityQueue* pq){
    if(pq->size == 0){
        exit(EXIT_FAILURE);
    }
    int res = pq->data[1];
    pq->data[1] = pq->[pq->size--];
    siftDown(pq, 1);
    return res;
}

int peek(PriorityQueue* pq){
    if(pq->size == 0){
        return NULL;
    }
    return pq->data[1];
}

void replace(PriorityQueue* pq, int item){
    pq->data[1] = item;
    siftDown(pq, 1);
}

int findKthLargest(int* nums, int numsSize, int k){
    PriorityQueue* minHeap = InitPQ(k);
    for(int i = 0; i < k; i++){
        offer(minHeap, nums[i]);
    }
    for(int i = k; i < numsSize; i++){
        if(nums[i] > peek(minHeap)){
            replace(minHeap, nums[i]);
        }
    }
    int res = peek(minHeap);
    freePq(minHeap);
    return res;
}

// #295 数据流的中位数
typedef struct {
    int *data;
    int size;
    int capacity;
} MaxHeap;

typedef struct {
    int *data;
    int size;
    int capacity;
} MinHeap;

typedef struct {
    MaxHeap* maxHeap;
    MinHeap* minHeap;
} MedianFinder;

MaxHeap* createMaxHeap(int capacity) {
    MaxHeap* heap = (MaxHeap*)malloc(sizeof(MaxHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

MinHeap* createMinHeap(int capacity) {
    MinHeap* heap = (MinHeap*)malloc(sizeof(MinHeap));
    heap->data = (int*)malloc(capacity * sizeof(int));
    heap->size = 0;
    heap->capacity = capacity;
    return heap;
}

MedianFinder* medianFinderCreate() {
    MedianFinder* obj = (MedianFinder*)malloc(sizeof(MedianFinder));
    obj->maxHeap = createMaxHeap(100);
    obj->minHeap = createMinHeap(100);
    return obj;
}

void swap(int* a, int* b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void maxHeapifyUp(MaxHeap* heap, int index) {
    while (index > 0 && heap->data[index] > heap->data[(index - 1) / 2]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void minHeapifyUp(MinHeap* heap, int index) {
    while (index > 0 && heap->data[index] < heap->data[(index - 1) / 2]) {
        swap(&heap->data[index], &heap->data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void maxHeapifyDown(MaxHeap* heap, int index) {
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] > heap->data[largest])
        largest = left;
    if (right < heap->size && heap->data[right] > heap->data[largest])
        largest = right;
    if (largest != index) {
        swap(&heap->data[index], &heap->data[largest]);
        maxHeapifyDown(heap, largest);
    }
}

void minHeapifyDown(MinHeap* heap, int index) {
    int smallest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;

    if (left < heap->size && heap->data[left] < heap->data[smallest])
        smallest = left;
    if (right < heap->size && heap->data[right] < heap->data[smallest])
        smallest = right;
    if (smallest != index) {
        swap(&heap->data[index], &heap->data[smallest]);
        minHeapifyDown(heap, smallest);
    }
}

void maxHeapPush(MaxHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    maxHeapifyUp(heap, heap->size - 1);
}

int maxHeapPop(MaxHeap* heap) {
    int maxValue = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    maxHeapifyDown(heap, 0);
    return maxValue;
}

void minHeapPush(MinHeap* heap, int value) {
    if (heap->size == heap->capacity) {
        heap->capacity *= 2;
        heap->data = (int*)realloc(heap->data, heap->capacity * sizeof(int));
    }
    heap->data[heap->size++] = value;
    minHeapifyUp(heap, heap->size - 1);
}

int minHeapPop(MinHeap* heap) {
    int minValue = heap->data[0];
    heap->data[0] = heap->data[--heap->size];
    minHeapifyDown(heap, 0);
    return minValue;
}

void medianFinderAddNum(MedianFinder* obj, int num) {
    if (obj->maxHeap->size == 0 || num <= obj->maxHeap->data[0]) {
        maxHeapPush(obj->maxHeap, num);
        if (obj->maxHeap->size > obj->minHeap->size + 1) {
            minHeapPush(obj->minHeap, maxHeapPop(obj->maxHeap));
        }
    } else {
        minHeapPush(obj->minHeap, num);
        if (obj->minHeap->size > obj->maxHeap->size) {
            maxHeapPush(obj->maxHeap, minHeapPop(obj->minHeap));
        }
    }
}

// #451 根据字符出现频率排序
// 用于存储字符和其频率的结构体
typedef struct {
    char character;
    int frequency;
} CharFrequency;

// 用于最大堆的比较函数
int compare(const void* a, const void* b) {
    return ((CharFrequency*)b)->frequency - ((CharFrequency*)a)->frequency;
}

// 用于统计字符频率的函数
void countFrequencies(const char* s, CharFrequency* freqMap, int* uniqueCount) {
    int freq[256] = {0};
    int len = strlen(s);

    for (int i = 0; i < len; ++i) {
        freq[(unsigned char)s[i]]++;
    }

    *uniqueCount = 0;
    for (int i = 0; i < 256; ++i) {
        if (freq[i] > 0) {
            freqMap[*uniqueCount].character = (char)i;
            freqMap[*uniqueCount].frequency = freq[i];
            (*uniqueCount)++;
        }
    }
}

// 主函数，实现频率排序
char* frequencySort(const char* s) {
    int len = strlen(s);
    if (len == 0) {
        char* res = (char*)malloc(1);
        res[0] = '\0';
        return res;
    }

    CharFrequency freqMap[256];
    int uniqueCount;
    countFrequencies(s, freqMap, &uniqueCount);

    // 建立最大堆
    qsort(freqMap, uniqueCount, sizeof(CharFrequency), compare);

    // 构建结果字符串
    char* res = (char*)malloc(len + 1);
    int index = 0;
    for (int i = 0; i < uniqueCount; ++i) {
        for (int j = 0; j < freqMap[i].frequency; ++j) {
            res[index++] = freqMap[i].character;
        }
    }
    res[index] = '\0';
    return res;
}

double medianFinderFindMedian(MedianFinder* obj) {
    if (obj->maxHeap->size > obj->minHeap->size) {
        return obj->maxHeap->data[0];
    }
    return (obj->maxHeap->data[0] + obj->minHeap->data[0]) / 2.0;
}

void medianFinderFree(MedianFinder* obj) {
    free(obj->maxHeap->data);
    free(obj->maxHeap);
    free(obj->minHeap->data);
    free(obj->minHeap);
    free(obj);
}
