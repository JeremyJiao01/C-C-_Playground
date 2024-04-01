

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


