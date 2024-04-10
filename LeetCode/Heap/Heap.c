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

void siftUp(Heap* heap){
    while(heap.size > 1 && heap.data[k / 2] < data[heap.size]){
        // data[k/2]是父节点
        swap(heap.data, heap.size/2, heap.size);
        heap.size /= 2;
    }
}

int poll(Heap* heap){
    if(size == 0){
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
    while(2 * k <= size){
        int j = 2 * k;
        // j + 1 为 k 的右孩子，因为0位置不存元素
        if(j + 1 <= size && heap.data[j + 1] > data[j]){
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




