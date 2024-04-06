

// # 622 设计循环队列
typedef struct {
    int* queue;
    int capacity;
    int front;
    int tail;
} MyCircularQueue;


MyCircularQueue* myCircularQueueCreate(int k) {
    MyCircularQueue* cirQueue = (MyCircularQueue*)malloc(sizeof(MyCircularQueue));
    cirQueue->queue = (int*)malloc(sizeof(int) * (k + 1));
    cirQueue->capacity = k + 1;
    cirQueue->front = 0;
    cirQueue->tail = 0;
    return cirQueue;
}

bool myCircularQueueEnQueue(MyCircularQueue* obj, int value) {
    if((obj->tail + 1) % obj->capacity == obj->front){
        return false;
    }else{
        obj->queue[obj->tail] = value;
        obj->tail = (obj->tail + 1) % obj->capacity;
    }
    return true;
}

bool myCircularQueueDeQueue(MyCircularQueue* obj) {
    if(obj->front == obj->tail){
        return false;
    }
    obj->front = (obj->front + 1) % obj->capacity;
    return true;
}

int myCircularQueueFront(MyCircularQueue* obj) {
    if(obj->tail == obj->front){
        return -1;
    }
    return obj->queue[obj->front];
}

int myCircularQueueRear(MyCircularQueue* obj) {
    if(obj->tail == obj->front){
        return -1;
    }
    return obj->queue[(obj->tail - 1 + obj->capacity) % obj->capacity];
    // When tail = 0, tail - 1 = -1 will cause heap over-flow
}

bool myCircularQueueIsEmpty(MyCircularQueue* obj) {
    return obj->front == obj->tail;
}

bool myCircularQueueIsFull(MyCircularQueue* obj) {
    return (obj->tail + 1) % obj->capacity == obj->front;
}

void myCircularQueueFree(MyCircularQueue* obj) {
    free(obj->queue);
    obj->queue = NULL;
    free(obj);
    obj = NULL;
}

// # 239 滑动窗口最大值
// 使用双端队列，实现单调队列
int* maxSlidingWindow(int* nums, int numsSize, int k) {
    int q[numsSize];
    int left = 0, right = 0;
    for (int i = 0; i < k; ++i) {
        // 找到窗口初始位置的最大值
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            right--;
        }
        q[right++] = i;
    }
    int returnSize = 0;
    int* ans = malloc(sizeof(int) * (numsSize - k + 1));
    ans[(returnSize)++] = nums[q[left]];
    for (int i = k; i < numsSize; ++i) {
        while (left < right && nums[i] >= nums[q[right - 1]]) {
            // 只需找到最大值即可，是否超出滑动窗口由下一个循环来判断
            right--;
        }
        q[right++] = i;
        while (q[left] <= i - k) {
            // 这里为什么是 (i - k) ，因为滑动窗口的原因
            // i - k，指向的是当前 i 所在窗口的第一个元素
            // 若q[left]（元素下标） 小于等于 窗口的第一个元素下标
            // 代表着当前q[left]（最大值），已经不在窗口内了，需要找到下一个最大值
            left++;
        }
        ans[(returnSize)++] = nums[q[left]];
    }
    return ans;
}


