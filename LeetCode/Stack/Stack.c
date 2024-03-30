// # 71 简化路径
// 去掉'/'
char** split(char* s, char delim, int* returnSize){
    int n = strlen(s);
    char** ans = (char**)malloc(sizeof(char*) * n);
    // 因为可能出现 .. 这种两个字符的情况，因此需要二维数组
    int pos = 0;
    int cur = 0;
    int len = 0;

    while(pos < n){
        while(pos < n && s[pos] == delim){
            ++pos;
            // 找到不是'/'的位置
        }
        cur = pos;
        while(pos < n && s[pos] != delim){
            ++pos;
            // 找到是'/'的位置
        }
        if(cur < n){
            ans[len] = (char*)malloc(sizeof(char) * (pos - cur + 1));
            // 每行存读到的一种元素
            strncpy(ans[len], s + cur, pos - cur);
            // 存入元素，从 s+cur开始，一共传输pos-cur个元素
            ans[len][pos - cur] = '\0';
            ++len;
        }
    }
    *returnSize = len;
    return ans;
}

char* simplifyPath(char* path) {
    int namesSize = 0;
    int n = strlen(path);
    char** names = split(path, '/', &namesSize);
    char** stack = (char**)malloc(sizeof(char*) * namesSize);
    int stackSize = 0;
    for(int i = 0; i < namesSize; ++i){
        if(!strcmp(names[i], "..")){
            if(stackSize > 0){
                --stackSize;
            }
        }else if(strcmp(names[i], ".")){
            stack[stackSize] = names[i];
            ++stackSize;
        }
    }
    char* ans = (char*)malloc(sizeof(char) * (n+1));
    int cur = 0;
    if(stackSize == 0){
        ans[cur] = '/';
        ++cur;
    }else{
        for(int i = 0; i < stackSize; i++){
            ans[cur] = '/'; // 出栈
            ++cur;
            strcpy(ans + cur, stack[i]);
            cur += strlen(stack[i]);
        }
    }
    ans[cur] = '\0';
    for(int i = 0; i < namesSize; i++){
        free(names[i]);
    }
    free(names);
    free(stack);
    return ans;
}

// # 20 有效的括号
char convert(char a){
    if (a == '}') return '{';
    if (a == ']') return '[';
    if (a == ')') return '(';
    return 0;
}

bool isValid(char* s) {
    int n = strlen(s);
    if(n % 2 == 1){
        return false;
    }
    int stack[n + 1];
    int node = 0;
    for(int i = 0; i < n; i++){
        char ch = convert(s[i]);
        if(ch){
            if(node == 0 || stack[node - 1] != ch){
                return false;
            }
            node--;
        }else{
            stack[node] = s[i];
            node++;
        }
    }
    return node == 0;
}

// # 150 逆波兰表达式求值(后缀表达式)

bool isNumber(char* token){
    return strlen(token) > 1 || ('0' <= token[0] && token[0] <= '9');
}

int evalRPN(char** tokens, int tokensSize) {
    int* stack = (int*)malloc(sizeof(int) * tokensSize);
    int node = 0;
    for(int i = 0; i < tokensSize; i++){
        char* token = tokens[i];
        if(isNumber(token)){
            stack[node++] = atoi(token); // 将字符串里的所有数字提取
        }else{
            int num2 = stack[--node];
            int num1 = stack[--node];
            switch(token[0]){
                case'+':
                    stack[node++] = num1 + num2;
                    break;
                case'-':
                    stack[node++] = num1 - num2;
                    break; 
                case'*':
                    stack[node++] = num1 * num2;
                    break;  
                case'/':
                    stack[node++] = num1 / num2;
                    break;                                                     
            }
        }
    }
    return stack[node - 1];
}

// # 316 去除重复字幕
char* removeDuplicateLetters(char* s) {
    int hash[26], visit[26];
    memset(hash, 0, sizeof(hash));
    memset(visit, 0, sizeof(visit));

    int n = strlen(s);
    for(int i = 0; i < n; i++){
    	hash[s[i] - 'a']++;
    }
    char* returnChar = (char*)malloc(sizeof(char)*27);
    int stackTop = 0;
    for(int i = 0; i < n; i++){
    	if(!visit[s[i] - 'a']){ // 如果没有访问过这个元素
    		while(stackTop > 0 && returnChar[stackTop - 1] > s[i]){
    		// 若前一个元素字典序大于当前
    			if(hash[returnChar[stackTop - 1] - 'a'] > 0){
    			// 若该元素在后面还会出现
    				visit[returnChar[--stackTop] - 'a'] = 0;
    				// 在栈中删去该元素	
    			} else {
    				// 如果后续没出现，则保留该元素
    				break;
    			}
    		}
    		visit[s[i] - 'a'] = 1;
    		returnChar[stackTop++] = s[i];
    		// 在栈中加入该元素
    	}
    	hash[s[i] - 'a'] -= 1;
    	// 元素在后续数量减一
    }
    returnChar[stackTop] = '\0';
    return returnChar;    
}

char* removeDuplicateLetters(char* s) {
    int hash[26], visit[26];
    memset(hash, 0, sizeof(hash));
    memset(visit, 0, sizeof(visit));

    int n = strlen(s);
    for(int i = 0; i < n; i++){
    	hash[s[i] - 'a']++;
    }
    char* returnChar = (char*)malloc(sizeof(char)*27);
    int stackTop = 0;
    for(int i = 0; i < n; i++){
    	if(!visit[s[i] - 'a']){ // 如果没有访问过这个元素
    		while(stackTop > 0 && returnChar[stackTop - 1] > s[i]){
    		// 若前一个元素字典序大于当前
    			if(hash[returnChar[stackTop - 1] - 'a'] > 0){
    			// 若该元素在后面还会出现
    				visit[returnChar[--stackTop] - 'a'] = 0;
    				// 在访问列表中删去该元素	
    			} else {
    				// 如果访问过该元素则直接跳过
    				break;
    			}
    		}
    		visit[s[i] - 'a'] = 1;
    		returnChar[stackTop++] = s[i];
    		// 在栈中加入该元素
    	}
    	hash[s[i] - 'a'] -= 1;
    	// 元素在后续数量减一
    }
    returnChar[stackTop] = '\0';
    return returnChar;    
}

// # 739 每日温度
int* dailyTemperatures(int* temperatures, int temperaturesSize, int* returnSize) {
    *returnSize = temperaturesSize;
    int* ans = (int*)malloc(sizeof(int) * temperaturesSize);

    for (int i = 0; i < temperaturesSize; ++i) {
        ans[i] = 0; // Initialize the answer array with 0
    }
    // We will use a dynamically-allocated array to simulate a stack.
    // stack is used to storage the subscript of temperatiures element
    int* stack = (int*)malloc(sizeof(int) * temperaturesSize);
    int stackTop = 0;

    for (int i = 0; i < temperaturesSize; ++i) {
        while (stackTop > 0 && temperatures[i] > temperatures[stack[stackTop - 1]]) {
            int prevIndex = stack[--stackTop]; // Simulating pop operation
            ans[prevIndex] = i - prevIndex;
        }
        // when temperatures element's value less than the previous elements' value 
        stack[stackTop++] = i; // Simulating push operation
    }
    return ans;
}

// # 496 下一个更大的元素
// 倒序遍历 nums2，并用单调栈中维护当前位置右边的更大的元素列表，
// 从栈底到栈顶的元素是单调递减的，得到每个元素右边的第一个更大元素值
// 使用哈希表存储以上得到的结果
int* nextGreaterElement(int* nums1, int nums1Size, int* nums2, int nums2Size, int* returnSize) {
    *returnSize = nums1Size;
    int* res = (int*)malloc(sizeof(int) * nums1Size);
    
    // Simulate the stack with a dynamic array
    int* stack = (int*)malloc(sizeof(int) * nums2Size);
    int stackSize = 0;
    
    // The "map" will be a 2D array with the first column being the number from nums2
    // and the second column being the next greater element for that number
    int** map = (int**)malloc(sizeof(int*) * nums2Size);
    for (int i = 0; i < nums2Size; ++i) {
        map[i] = (int*)malloc(sizeof(int) * 2);
    }

    for (int i = nums2Size - 1; i >= 0; --i) {
        while (stackSize > 0 && nums2[i] >= stack[stackSize - 1]) {
            --stackSize; // Simulating pop operation
        }
        map[i][0] = nums2[i];
        map[i][1] = stackSize == 0 ? -1 : stack[stackSize - 1];
        stack[stackSize++] = nums2[i]; // Simulating push operation
    }
    
    // Simulate the get operation from the map
    for (int i = 0; i < nums1Size; ++i) {
        for (int j = 0; j < nums2Size; ++j) {
            if (map[j][0] == nums1[i]) {
                res[i] = map[j][1];
                break;
            }
        }
    }
    return res;
}

// 使用栈来保存元素下标
// 当新的元素入栈时，弹出所有值小于当前元素的下标
// 整个遍历大小为numsSize * 2 - 1，只需对其取模即可
int* nextGreaterElements(int* nums, int numsSize, int* returnSize) {
    *returnSize = numsSize;
    if(numsSize == 0){
        return NULL;
    }
    int* returnArr = (int*)malloc(sizeof(int) * numsSize);
    memset(returnArr, -1, sizeof(int) * numsSize);
    int stack[numsSize * 2 - 1], stackTop = 0;
    for(int i = 0; i < numsSize * 2 - 1; i++){
        while(stackTop > 0 && nums[stack[stackTop - 1]] < nums[i % numsSize]){
            returnArr[stack[stackTop - 1]] = nums[i % numsSize];
            stackTop--;
        }
        stack[stackTop++] = i % numsSize;
    }
    return returnArr;
}

// # 84 柱状图中最大的矩形
// https://leetcode.cn/problems/largest-rectangle-in-histogram/solutions/142012/bao-li-jie-fa-zhan-by-liweiwei1419
int largestRectangleArea(int* heights, int heightsSize) {
    if(heightsSize == 0){
        return 0;
    }
    if(heightsSize == 1){
        return heights[0];
    }
    int res = 0;
    int* stack =  (int*)malloc(sizeof(int) * heightsSize);
    // the stack is storage the subscript of the heights array
    int stackTop = 0;

    for(int i = 0; i < heightsSize; i++){
        // 第一次遍历能够确定部分柱状的面积
        // 即右边存在严格小于其的柱形
        while(stackTop > 0 && heights[i] < heights[stack[stackTop - 1]]){
            int curHeight = heights[stack[--stackTop]];
            while(stackTop > 0 && heights[stack[stackTop - 1]] == curHeight){
                stackTop--;
            }
            int curWidth = 0;
            if(!stackTop > 0){
                curWidth = i;
            }else{
                curWidth = i - stack[stackTop - 1] - 1;
            }
            res = res > curWidth * curHeight ? res : curWidth * curHeight;
        }
        stack[stackTop++] = i;
    }

    while(stackTop > 0){
        // 栈中剩下柱形
        int curHeight = heights[stack[--stackTop]];
        while(stackTop > 0 && heights[stack[stackTop - 1]] == curHeight){
            stackTop--;
        }
        int curWidth;
        if(!stackTop > 0){
            curWidth = heightsSize;
        }else{
            curWidth = heightsSize - stack[stackTop - 1] - 1;
            // 因为是从最后一个柱形往前计算，所以在最右边增加一个高度为0的柱形
            // 即 高度为0的柱形坐标为heightsSize
        }
        res = res > curWidth * curHeight ? res : curWidth * curHeight;
    }
    return res;
}

// # 1019 链表中的下一个更大节点
typedef struct Pair {
    // 将栈保存为两个元素，第一个保存值，第二个保存索引
    int first;
    int second;
} Pair;

int* nextLargerNodes(struct ListNode* head, int* returnSize) {
    int len = 0;
    struct ListNode* cur = head;
    while (cur) {
        // 计算链表长度
        cur = cur->next;
        len++;
    }
    int* ans = (int *)calloc(len, sizeof(int));
    Pair stack[len];
    int top = 0, pos = 0;

    cur = head;
    int idx = -1;
    while (cur) {
        ++idx;
        ans[pos++] = 0;
        while (top > 0 && stack[top - 1].first < cur->val) {
            ans[stack[top - 1].second] = cur->val;
            top--;
        }
        stack[top].first = cur->val;
        stack[top].second = idx;
        top++;
        cur = cur->next;
    }
    *returnSize = len;
    return ans;
}

// # 232 用栈实现队列
typedef struct{
    int* stk;
    int stackSize;
    int stackMemory;
} Stack;

Stack* createStack(int stkSize){
    Stack* ret = malloc(sizeof(Stack));
    ret->stk = malloc(sizeof(int) * stkSize);
    ret->stackSize = 0;
    ret->stackMemory = stkSize;
    return ret;
}

void stackPush(Stack* obj, int x){
    obj->stk[obj->stackSize++] = x;
}

void stackPop(Stack* obj){
    obj->stackSize--;
}

int stackTop(Stack* obj){
    return obj->stk[obj->stackSize - 1];
}

bool stackEmpty(Stack* obj){
    return obj->stackSize == 0;
}

void stackFree(Stack* obj){
    free(obj->stk);
}

typedef struct {
    Stack* inStack;
    Stack* outStack;
} MyQueue;


MyQueue* myQueueCreate() {
    MyQueue* ret = malloc(sizeof(MyQueue));
    ret->inStack = createStack(100);
    ret->outStack = createStack(100);
    return ret;
}

void in2out(MyQueue* obj){
    while(!stackEmpty(obj->inStack)){
        stackPush(obj->outStack, stackTop(obj->inStack));
        stackPop(obj->inStack);
    }
}

void myQueuePush(MyQueue* obj, int x) {
    stackPush(obj->inStack, x);   
}

int myQueuePop(MyQueue* obj) {
    if(stackEmpty(obj->outStack)){
        in2out(obj);
    }
    int x = stackTop(obj->outStack);
    stackPop(obj->outStack);
    return x;
}

int myQueuePeek(MyQueue* obj) {
    if(stackEmpty(obj->outStack)){
        in2out(obj);
    }
    return stackTop(obj->outStack);
}

bool myQueueEmpty(MyQueue* obj) {
    return stackEmpty(obj->inStack) && stackEmpty(obj->outStack);
}

void myQueueFree(MyQueue* obj) {
    stackFree(obj->inStack);
    stackFree(obj->outStack);
}

// # 225 用队列实现栈
#define LEN 20
typedef struct queue {
    int *data;
    int head;
    int rear;
    int size;
} Queue;

typedef struct {
    Queue *queue1, *queue2;
} MyStack;

Queue *initQueue(int k) {
    Queue *obj = (Queue *)malloc(sizeof(Queue));
    obj->data = (int *)malloc(k * sizeof(int));
    obj->head = -1;
    obj->rear = -1;
    obj->size = k;
    return obj;
}

void enQueue(Queue *obj, int e) {
    if (obj->head == -1) {
        obj->head = 0;
    }
    obj->rear = (obj->rear + 1) % obj->size;
    obj->data[obj->rear] = e;
}

int deQueue(Queue *obj) {
    int a = obj->data[obj->head];
    if (obj->head == obj->rear) {
        obj->rear = -1;
        obj->head = -1;
        return a;
    }
    obj->head = (obj->head + 1) % obj->size;
    return a;
}

int isEmpty(Queue *obj) {
    return obj->head == -1;
}

MyStack *myStackCreate() {
    MyStack *obj = (MyStack *)malloc(sizeof(MyStack));
    obj->queue1 = initQueue(LEN); // used to storage stack nums
    obj->queue2 = initQueue(LEN); // uesd to push nums into stack
    return obj;
}

void myStackPush(MyStack *obj, int x) {
    if (isEmpty(obj->queue1)) {
        enQueue(obj->queue2, x);
    } else {
        enQueue(obj->queue1, x);
    }
}

int myStackPop(MyStack *obj) {
    if (isEmpty(obj->queue1)) {
        while (obj->queue2->head != obj->queue2->rear) {
            enQueue(obj->queue1, deQueue(obj->queue2));
        }
        return deQueue(obj->queue2);
    }
    while (obj->queue1->head != obj->queue1->rear) {
        enQueue(obj->queue2, deQueue(obj->queue1));
    }
    return deQueue(obj->queue1);
}

int myStackTop(MyStack *obj) {
    if (isEmpty(obj->queue1)) {
        return obj->queue2->data[obj->queue2->rear];
    }
    return obj->queue1->data[obj->queue1->rear];
}

bool myStackEmpty(MyStack *obj) {
    if (obj->queue1->head == -1 && obj->queue2->head == -1) {
        return true;
    }
    return false;
}

void myStackFree(MyStack *obj) {
    free(obj->queue1->data);
    obj->queue1->data = NULL;
    free(obj->queue1);
    obj->queue1 = NULL;
    free(obj->queue2->data);
    obj->queue2->data = NULL;
    free(obj->queue2);
    obj->queue2 = NULL;
    free(obj);
    obj = NULL;
}






























